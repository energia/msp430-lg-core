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

#if defined(__MSP430_HAS_EUSCI_B0__) || defined(DEFAULT_SPI)


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

#if defined(__MSP430_HAS_EUSCI_A0__)
#define UCA0_BASE __MSP430_BASEADDRESS_EUSCI_A0__
#endif
#if defined(__MSP430_HAS_EUSCI_A1__)
#define UCA1_BASE __MSP430_BASEADDRESS_EUSCI_A1__
#endif
#if defined(__MSP430_HAS_EUSCI_A2__)
#define UCA2_BASE __MSP430_BASEADDRESS_EUSCI_A2__
#endif
#if defined(__MSP430_HAS_EUSCI_A3__)
#define UCA3_BASE __MSP430_BASEADDRESS_EUSCI_A3__
#endif


#if defined(DEFAULT_SPI)
#if (DEFAULT_SPI == 0)
uint16_t SPI_baseAddress = UCB0_BASE;
#endif	
#if (DEFAULT_SPI == 1)
uint16_t SPI_baseAddress = UCB1_BASE;
#endif	
#if (DEFAULT_SPI == 2)
uint16_t SPI_baseAddress = UCB2_BASE;
#endif	
#if (DEFAULT_SPI == 3)
uint16_t SPI_baseAddress = UCB3_BASE;
#endif	
#if (DEFAULT_SPI == 10)
uint16_t SPI_baseAddress = UCA0_BASE;
#endif	
#if (DEFAULT_SPI == 11)
uint16_t SPI_baseAddress = UCA1_BASE;
#endif	
#if (DEFAULT_SPI == 12)
uint16_t SPI_baseAddress = UCA2_BASE;
#endif	1
#if (DEFAULT_SPI == 13)
uint16_t SPI_baseAddress = UCA3_BASE;
#endif	
#else
uint16_t SPI_baseAddress = UCB0_BASE;
#endif


#define UCzCTLW0     (*((volatile uint16_t *)((uint16_t)(OFS_UCBxCTLW0  + SPI_baseAddress))))
#define UCzCTL0      (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxCTL0   + SPI_baseAddress))))
#define UCzCTL1      (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxCTL1   + SPI_baseAddress))))
#define UCzBRW       (*((volatile uint16_t *)((uint16_t)(OFS_UCBxBRW    + SPI_baseAddress))))
#define UCzBR0       (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxBR0    + SPI_baseAddress))))
#define UCzBR1       (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxBR1    + SPI_baseAddress))))
#define UCzTXBUF     (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxTXBUF  + SPI_baseAddress))))
#define UCzRXBUF     (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxRXBUF  + SPI_baseAddress))))
#if (DEFAULT_SPI < 10)
#define UCzIFG       (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxIFG    + SPI_baseAddress))))
#define UCzIE        (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxIE     + SPI_baseAddress))))
#else
#define UCzIFG       (*((volatile uint8_t *) ((uint16_t)(OFS_UCAxIFG    + SPI_baseAddress))))
#define UCzIE        (*((volatile uint8_t *) ((uint16_t)(OFS_UCAxIE     + SPI_baseAddress))))
#endif


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
 * spi_initialize() - Configure USCI UCz for SPI mode
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
	UCzCTLW0 = UCSWRST | UCSSEL_2;

	/* SPI in master MODE 0 - CPOL=0 SPHA=0. */
	UCzCTLW0 |= SPI_MODE_0 | UCMSB | UCSYNC | UCMST;

	/* Set pins to SPI mode. */
#if defined(DEFAULT_SPI)
#if defined(UCB0_BASE) && defined(SPISCK0_SET_MODE)
	if (SPI_baseAddress == UCB0_BASE) {
		pinMode_int(SCK0, SPISCK0_SET_MODE);
		pinMode_int(MOSI0, SPIMOSI0_SET_MODE);
		pinMode_int(MISO0, SPIMISO0_SET_MODE);
	}
#endif	
#if defined(UCB1_BASE) && defined(SPISCK1_SET_MODE)
	if (SPI_baseAddress == UCB1_BASE) {
		pinMode_int(SCK1, SPISCK1_SET_MODE);
		pinMode_int(MOSI1, SPIMOSI1_SET_MODE);
		pinMode_int(MISO1, SPIMISO1_SET_MODE);
	}
#endif	
#if defined(UCB2_BASE) && defined(SPISCK2_SET_MODE)
	if (SPI_baseAddress == UCB2_BASE) {
		pinMode_int(SCK2, SPISCK2_SET_MODE);
		pinMode_int(MOSI2, SPIMOSI2_SET_MODE);
		pinMode_int(MISO2, SPIMISO2_SET_MODE);
	}
#endif	
#if defined(UCB3_BASE) && defined(SPISCK3_SET_MODE)
	if (SPI_baseAddress == UCB3_BASE) {
		pinMode_int(SCK3, SPISCK3_SET_MODE);
		pinMode_int(MOSI3, SPIMOSI3_SET_MODE);
		pinMode_int(MISO3, SPIMISO3_SET_MODE);
	}
#endif	
#if defined(UCA0_BASE) && defined(SPISCK10_SET_MODE)
	if (SPI_baseAddress == UCA0_BASE) {
		pinMode_int(SCK10, SPISCK10_SET_MODE);
		pinMode_int(MOSI10, SPIMOSI10_SET_MODE);
		pinMode_int(MISO10, SPIMISO10_SET_MODE);
	}
#endif	
#if defined(UCA1_BASE) && defined(SPISCK11_SET_MODE)
	if (SPI_baseAddress == UCA1_BASE) {
		pinMode_int(SCK11, SPISCK11_SET_MODE);
		pinMode_int(MOSI11, SPIMOSI11_SET_MODE);
		pinMode_int(MISO11, SPIMISO11_SET_MODE);
	}
#endif	
#if defined(UCA2_BASE) && defined(SPISCK12_SET_MODE)
	if (SPI_baseAddress == UCA2_BASE) {
		pinMode_int(SCK12, SPISCK12_SET_MODE);
		pinMode_int(MOSI12, SPIMOSI12_SET_MODE);
		pinMode_int(MISO12, SPIMISO12_SET_MODE);
	}
#endif	
#if defined(UCA3_BASE) && defined(SPISCK13_SET_MODE)
	if (SPI_baseAddress == UCA3_BASE) {
		pinMode_int(SCK13, SPISCK13_SET_MODE);
		pinMode_int(MOSI13, SPIMOSI13_SET_MODE);
		pinMode_int(MISO13, SPIMISO13_SET_MODE);
	}
#endif	
#else
	pinMode_int(SCK, SPISCK_SET_MODE);
	pinMode_int(MOSI, SPIMOSI_SET_MODE);
	pinMode_int(MISO, SPIMISO_SET_MODE);
#endif


	/* Set initial speed to 4MHz. */
	UCzBR0 = SPI_CLOCK_DIV4 & 0xFF;
	UCzBR1 = (SPI_CLOCK_DIV4 >> 8 ) & 0xFF;

	/* Release USCI for operation. */
	UCzCTLW0 &= ~UCSWRST;
}

/**
 * spi_disable() - put USCI into reset mode.
 */
void spi_disable(void)
{
	/* Put USCI in reset mode. */
	UCzCTLW0 |= UCSWRST;
}

/**
 * spi_send() - send a byte and recv response.
 */
uint8_t spi_send(const uint8_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCzIFG & UCTXIFG));

	/* Setting TXBUF clears the TXIFG flag. */
	UCzTXBUF = data;

	/* Wait for a rx character? */
	while (!(UCzIFG & UCRXIFG));

	/* Reading clears RXIFG flag. */
	return UCzRXBUF;
}

uint16_t spi_send16(const uint16_t data)
{
	uint16_t datain;
	/* Wait for previous tx to complete. */
	while (!(UCzIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCzTXBUF = data | 0xFF;
	/* Wait for previous tx to complete. */
	while (!(UCzIFG & UCTXIFG));

	datain = UCzRXBUF << 8;
	/* Setting TXBUF clears the TXIFG flag. */
	UCzTXBUF = data >> 8;

	/* Wait for a rx character? */
	while (!(UCzIFG & UCRXIFG));

	/* Reading clears RXIFG flag. */
	return (datain | UCzRXBUF);
}

void spi_send(void *buf, uint16_t count)
{
    uint8_t *ptx = (uint8_t *)buf;
    uint8_t *prx = (uint8_t *)buf;
	if (count == 0) return;
	/* Wait for previous tx to complete. */
	while (!(UCzIFG & UCTXIFG));
	while(count){
		if (UCzIFG & UCRXIFG){
			/* Reading RXBUF clears the RXIFG flag. */
			*prx++ = UCzRXBUF;
		}
		if (UCzIFG & UCTXIFG){
			/* Setting TXBUF clears the TXIFG flag. */
			UCzTXBUF = *ptx++;
			count--;
		}
	}
	/* Wait for last rx character? */
	while (!(UCzIFG & UCRXIFG));
	*prx++ = UCzRXBUF;
}

/**
 * spi_transmit() - send a byte.
 */
void spi_transmit(const uint8_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCzIFG & UCTXIFG));

	/* Setting TXBUF clears the TXIFG flag. */
	UCzTXBUF = data;

	/* Wait for a rx character? */
	while (!(UCzIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCzIFG &= ~UCRXIFG;
}

void spi_transmit16(const uint16_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCzIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCzTXBUF = data | 0xFF;
	/* Wait for previous tx to complete. */
	while (!(UCzIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCzTXBUF = data >> 8;

	/* Wait for a rx character? */
	while (!(UCzIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCzIFG &= ~UCRXIFG;
}

void spi_transmit(void *buf, uint16_t count)
{
    uint8_t *ptx = (uint8_t *)buf;
	if (count == 0) return;
	while(count){
		if (UCzIFG & UCTXIFG){
			/* Setting TXBUF clears the TXIFG flag. */
			UCzTXBUF = *ptx++;
			count--;
		}
	}
	/* Wait for last rx character? */
	while (!(UCzIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCzIFG &= ~UCRXIFG;
}

/***SPI_MODE_0
 * spi_set_divisor() - set new clock divider for USCI.
 *
 * USCI speed is based on the SMCLK divided by BR0 and BR1.
 *
 */
void spi_set_divisor(const uint16_t clkdiv)
{
	/* Hold UCz in reset. */
	UCzCTLW0 |= UCSWRST;

	UCzBR0 = clkdiv & 0xFF;
	UCzBR1 = (clkdiv >> 8 ) & 0xFF;

	/* Release for operation. */
	UCzCTLW0 &= ~UCSWRST;
}

/**
 * spi_set_bitorder(LSBFIRST=0 | MSBFIRST=1).
 */
void spi_set_bitorder(const uint8_t order)
{
	/* Hold UCz in reset. */
	UCzCTLW0 |= UCSWRST;

	UCzCTLW0 = (UCzCTLW0 & ~UCMSB) | ((order == 1 /*MSBFIRST*/) ? UCMSB : 0); /* MSBFIRST = 1 */

	/* Release for operation. */
	UCzCTLW0 &= ~UCSWRST;
}

/**
 * spi_set_datamode() - mode 0 - 3.
 */
void spi_set_datamode(const uint8_t mode)
{
	/* Hold UCz in reset. */
	UCzCTL1 |= UCSWRST;
	switch(mode) {
	case 0: /* SPI_MODE0 */
		UCzCTLW0 = (UCzCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_0;
		break;
	case 1: /* SPI_MODE1 */
		UCzCTLW0 = (UCzCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_1;
		break;
	case 2: /* SPI_MODE2 */
		UCzCTLW0 = (UCzCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_2;
		break;
	case 4: /* SPI_MODE3 */
		UCzCTLW0 = (UCzCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_3;
		break;
	default:
		break;
	}

	/* Release for operation. */
	UCzCTL1 &= ~UCSWRST;
}
#endif
