/**
 * File: eusci_spi.c - msp430 USCI SPI implementation
 *
 * EUSCI flavor implementation by Robert Wessels <robertinant@yahoo.com>
 * Copyright (c) 2012 by Rick Kimball <rick@kimballsoftware.com>
 * spi abstraction api for msp430
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 */

#include <msp430.h>
#include <stdint.h>
#include "spi_430.h"
#include <Energia.h>

#ifdef __MSP430_HAS_EUSCI_B0__


#if defined(__MSP430_HAS_EUSCI_B0__)
#define UCB0_BASE __MSP430_BASEADDRESS_EUSCI_B0__
#endif
#if defined(__MSP430_HAS_EUSCI_B1__)
#define UCB1_BASE __MSP430_BASEADDRESS_EUSCI_B1__
#endif
#if defined(__MSP430_HAS_EUSCI_B2__)
#define UCB2_BASE __MSP430_BASEADDRESS_EUSCI_B2__
#endif
#if defined(__MSP430_HAS_EUSCI_B3__)
#define UCB3_BASE __MSP430_BASEADDRESS_EUSCI_B3__
#endif


#if defined(DEFAULT_SPI) && (DEFAULT_SPI == 1)
uint16_t SPI_baseAddress = UCB1_BASE;
#else
uint16_t SPI_baseAddress = UCB0_BASE;
#endif

#define UCBzCTLW0     (*((volatile uint16_t *)((uint16_t)(OFS_UCBxCTLW0  + UCB0_BASE))))
#define UCBzCTL0      (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxCTL0   + UCB0_BASE))))
#define UCBzCTL1      (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxCTL1   + UCB0_BASE))))
#define UCBzBRW       (*((volatile uint16_t *)((uint16_t)(OFS_UCBxBRW    + UCB0_BASE))))
#define UCBzBR0       (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxBR0    + UCB0_BASE))))
#define UCBzBR1       (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxBR1    + UCB0_BASE))))
#define UCBzTXBUF     (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxTXBUF  + UCB0_BASE))))
#define UCBzRXBUF     (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxRXBUF  + UCB0_BASE))))
#define UCBzIFG       (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxIFG    + UCB0_BASE))))
#define UCBzIE        (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxIE     + UCB0_BASE))))


/**
 * USCI flags for various the SPI MODEs
 *
 * Note: The msp430 UCCKPL tracks the CPOL value. However,
 * the UCCKPH flag is inverted when compared to the CPHA
 * value described in Motorola documentation.
 */

#define SPI_MODE_0 (UCCKPH)		/* CPOL=0 CPHA=0 */
#define SPI_MODE_1 (0)			/* CPOL=0 CPHA=1 */
#define SPI_MODE_2 (UCCKPL | UCCKPH)	/* CPOL=1 CPHA=0 */
#define SPI_MODE_3 (UCCKPL)		/* CPOL=1 CPHA=1 */

#define SPI_MODE_MASK (UCCKPL | UCCKPH)

/**
 * spi_initialize() - Configure USCI UCBz for SPI mode
 *
 * P2.0 - CS (active low)
 * P1.5 - SCLK
 * P1.6 - MISO aka SOMI
 * P1.7 - MOSI aka SIMO
 *
 */
void spi_initialize(void)
{
	/* Put USCI in reset mode, source USCI clock from SMCLK. */
	UCBzCTLW0 = UCSWRST | UCSSEL_2;

	/* SPI in master MODE 0 - CPOL=0 SPHA=0. */
	UCBzCTLW0 |= SPI_MODE_0 | UCMSB | UCSYNC | UCMST;

	/* Set pins to SPI mode. */
#if defined(DEFAULT_SPI)
	if (SPI_baseAddress == UCB1_BASE) {
		pinMode_int(SCK1, SPISCK1_SET_MODE);
		pinMode_int(MOSI1, SPIMOSI1_SET_MODE);
		pinMode_int(MISO1, SPIMISO1_SET_MODE);
	}else{
		pinMode_int(SCK0, SPISCK0_SET_MODE);
		pinMode_int(MOSI0, SPIMOSI0_SET_MODE);
		pinMode_int(MISO0, SPIMISO0_SET_MODE);
	}
#else
	pinMode_int(SCK, SPISCK_SET_MODE);
	pinMode_int(MOSI, SPIMOSI_SET_MODE);
	pinMode_int(MISO, SPIMISO_SET_MODE);
#endif


	/* Set initial speed to 4MHz. */
	UCBzBR0 = SPI_CLOCK_DIV4 & 0xFF;
	UCBzBR1 = (SPI_CLOCK_DIV4 >> 8 ) & 0xFF;

	/* Release USCI for operation. */
	UCBzCTLW0 &= ~UCSWRST;
}

/**
 * spi_disable() - put USCI into reset mode.
 */
void spi_disable(void)
{
	/* Put USCI in reset mode. */
	UCBzCTLW0 |= UCSWRST;
}

/**
 * spi_send() - send a byte and recv response.
 */
uint8_t spi_send(const uint8_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCBzIFG & UCTXIFG));

	/* Setting TXBUF clears the TXIFG flag. */
	UCBzTXBUF = data;

	/* Wait for a rx character? */
	while (!(UCBzIFG & UCRXIFG));

	/* Reading clears RXIFG flag. */
	return UCBzRXBUF;
}

uint16_t spi_send16(const uint16_t data)
{
	uint16_t datain;
	/* Wait for previous tx to complete. */
	while (!(UCBzIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCBzTXBUF = data | 0xFF;
	/* Wait for previous tx to complete. */
	while (!(UCBzIFG & UCTXIFG));

	datain = UCBzRXBUF << 8;
	/* Setting TXBUF clears the TXIFG flag. */
	UCBzTXBUF = data >> 8;

	/* Wait for a rx character? */
	while (!(UCBzIFG & UCRXIFG));

	/* Reading clears RXIFG flag. */
	return (datain | UCBzRXBUF);
}

void spi_send(void *buf, uint16_t count)
{
    uint8_t *ptx = (uint8_t *)buf;
    uint8_t *prx = (uint8_t *)buf;
	if (count == 0) return;
	/* Wait for previous tx to complete. */
	while (!(UCBzIFG & UCTXIFG));
	while(count){
		if (UCBzIFG & UCRXIFG){
			/* Reading RXBUF clears the RXIFG flag. */
			*prx++ = UCBzRXBUF;
		}
		if (UCBzIFG & UCTXIFG){
			/* Setting TXBUF clears the TXIFG flag. */
			UCBzTXBUF = *ptx++;
			count--;
		}
	}
	/* Wait for last rx character? */
	while (!(UCBzIFG & UCRXIFG));
	*prx++ = UCBzRXBUF;
}

/**
 * spi_transmit() - send a byte.
 */
void spi_transmit(const uint8_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCBzIFG & UCTXIFG));

	/* Setting TXBUF clears the TXIFG flag. */
	UCBzTXBUF = data;

	/* Wait for a rx character? */
	while (!(UCBzIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCBzIFG &= ~UCRXIFG;
}

void spi_transmit16(const uint16_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCBzIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCBzTXBUF = data | 0xFF;
	/* Wait for previous tx to complete. */
	while (!(UCBzIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCBzTXBUF = data >> 8;

	/* Wait for a rx character? */
	while (!(UCBzIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCBzIFG &= ~UCRXIFG;
}

void spi_transmit(void *buf, uint16_t count)
{
    uint8_t *ptx = (uint8_t *)buf;
	if (count == 0) return;
	while(count){
		if (UCBzIFG & UCTXIFG){
			/* Setting TXBUF clears the TXIFG flag. */
			UCBzTXBUF = *ptx++;
			count--;
		}
	}
	/* Wait for last rx character? */
	while (!(UCBzIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCBzIFG &= ~UCRXIFG;
}

/***SPI_MODE_0
 * spi_set_divisor() - set new clock divider for USCI.
 *
 * USCI speed is based on the SMCLK divided by BR0 and BR1.
 *
 */
void spi_set_divisor(const uint16_t clkdiv)
{
	/* Hold UCBz in reset. */
	UCBzCTLW0 |= UCSWRST;

	UCBzBR0 = clkdiv & 0xFF;
	UCBzBR1 = (clkdiv >> 8 ) & 0xFF;

	/* Release for operation. */
	UCBzCTLW0 &= ~UCSWRST;
}

/**
 * spi_set_bitorder(LSBFIRST=0 | MSBFIRST=1).
 */
void spi_set_bitorder(const uint8_t order)
{
	/* Hold UCBz in reset. */
	UCBzCTLW0 |= UCSWRST;

	UCBzCTLW0 = (UCBzCTLW0 & ~UCMSB) | ((order == 1 /*MSBFIRST*/) ? UCMSB : 0); /* MSBFIRST = 1 */

	/* Release for operation. */
	UCBzCTLW0 &= ~UCSWRST;
}

/**
 * spi_set_datamode() - mode 0 - 3.
 */
void spi_set_datamode(const uint8_t mode)
{
	/* Hold UCBz in reset. */
	UCBzCTL1 |= UCSWRST;
	switch(mode) {
	case 0: /* SPI_MODE0 */
		UCBzCTLW0 = (UCBzCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_0;
		break;
	case 1: /* SPI_MODE1 */
		UCBzCTLW0 = (UCBzCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_1;
		break;
	case 2: /* SPI_MODE2 */
		UCBzCTLW0 = (UCBzCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_2;
		break;
	case 4: /* SPI_MODE3 */
		UCBzCTLW0 = (UCBzCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_3;
		break;
	default:
		break;
	}

	/* Release for operation. */
	UCBzCTL1 &= ~UCSWRST;
}
#endif
