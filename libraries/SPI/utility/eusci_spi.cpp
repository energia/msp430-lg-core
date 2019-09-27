/**
 * File: eusci_spi.c - msp430 USCI SPI implementation
 *
 * EUSCI flavor implementation by Robert Wessels <robertinant@yahoo.com>
 * Copyright (c) 2012 by Rick Kimball <rick@kimballsoftware.com>
 * spi abstraction api for msp430
 *
 * Jan 2019 optimized code 
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
#endif    1
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
#define UCzSTATW     ( (spiModule < 10) ? (*((volatile uint16_t *) ((uint16_t)(OFS_UCBxSTATW  + SPI_baseAddress)))) : (*((volatile uint16_t *) ((uint16_t)(OFS_UCAxSTATW  + SPI_baseAddress)))) )
#define UCzTXBUF     (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxTXBUF  + SPI_baseAddress))))
#define UCzRXBUF     (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxRXBUF  + SPI_baseAddress))))
#define UCzIFG       ( (spiModule < 10) ? (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxIFG    + SPI_baseAddress)))) : (*((volatile uint8_t *) ((uint16_t)(OFS_UCAxIFG    + SPI_baseAddress)))) )
#define UCzIE        ( (spiModule < 10) ? (*((volatile uint8_t *) ((uint16_t)(OFS_UCBxIE     + SPI_baseAddress)))) : (*((volatile uint8_t *) ((uint16_t)(OFS_UCAxIE     + SPI_baseAddress)))) )


/**
 * USCI flags for various the SPI MODEs
 *
 * Note: The msp430 UCCKPL tracks the CPOL value. However,
 * the UCCKPH flag is inverted when compared to the CPHA
 * value described in Motorola documentation.
 */

#define SPI_MODE_0 (UCCKPH)        /* CPOL=0 CPHA=0 */
#define SPI_MODE_1 (0)            /* CPOL=0 CPHA=1 */
#define SPI_MODE_2 (UCCKPL | UCCKPH)    /* CPOL=1 CPHA=0 */
#define SPI_MODE_3 (UCCKPL)        /* CPOL=1 CPHA=1 */

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

/* Calculate divisor to keep SPI clock close to 4MHz but never over */
#ifndef SPI_CLOCK_SPEED
#define SPI_CLOCK_SPEED 4000000L
#endif

#if F_CPU < 4000000L
#define SPI_CLOCK_DIV 1
#else
#define SPI_CLOCK_DIV ((F_CPU / SPI_CLOCK_SPEED) + (F_CPU % SPI_CLOCK_SPEED == 0 ? 0:1))
#endif

#if defined(DEFAULT_SPI)
    uint8_t spiModule = DEFAULT_SPI;
#else
    uint8_t spiModule = 0;
#endif

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
    UCzBR0 = SPI_CLOCK_DIV & 0xFF;
    UCzBR1 = (SPI_CLOCK_DIV >> 8 ) & 0xFF;

    /* Release USCI for operation. */
    UCzCTLW0 &= ~UCSWRST;
}

/**
 * spi_disable() - put USCI into reset mode.
 */
void spi_disable(void)
{
    /* Wait for previous tx to complete. */
    while (UCzSTATW & UCBUSY);
    /* Put USCI in reset mode. */
    UCzCTLW0 |= UCSWRST;
}

/**
 * spi_send() - send a byte and recv response.
 */
uint8_t spi_send(const uint8_t data)
{
    /* Wait for previous tx to complete. */
    while (UCzSTATW & UCBUSY);
    /* Clear RX Flag */
    //UCzIFG &= ~UCRXIFG;
    UCzRXBUF; /* reading RXBUF to clear error bits and UCRXIFG */


    /* Send byte */
    UCzTXBUF = data;

    /* Wait for a rx character? */
    while (!(UCzIFG & UCRXIFG));

    /* Reading clears RXIFG flag. */
    return UCzRXBUF;
}

/**
 * spi_send() - send a word and recv response.
 */
uint16_t spi_send16(const uint16_t data)
{
    uint16_t datain;
    /* Wait for previous tx to complete. */
    while (UCzSTATW & UCBUSY);
    UCzRXBUF; /* reading RXBUF to clear error bits and UCRXIFG */

    if (UCzCTLW0 & UCMSB) // MSB first?
    {
        UCzTXBUF = data >> 8; // send MSB first
        while (!(UCzIFG & UCRXIFG)); /* Wait for a rx character */
        datain = UCzRXBUF; // receive MSB first

        UCzTXBUF = data & 0xFF; // send LSB
        while (!(UCzIFG & UCRXIFG)); /* Wait for a rx character */
        return ((datain << 8) | UCzRXBUF); // receive LSB
    }
    else
    {
        UCzTXBUF = data & 0xFF; // send LSB first
        /* Wait for a rx character */
        while (!(UCzIFG & UCRXIFG));
        datain = UCzRXBUF; // receive LSB first
        UCzTXBUF = data >> 8; // send MSB
        /* Wait for a rx character */
        while (!(UCzIFG & UCRXIFG));
        uint16_t tmp = UCzRXBUF;      // receive MSB
        return (datain | (tmp << 8)); //
    }
}

/**
 * spi_send() - send buffer of byte and recv response.
 */
void spi_send(void *buf, uint16_t count) 
{
    if (count == 0) return;
    
    uint8_t *ptx = (uint8_t *)buf;
    uint8_t *prx = (uint8_t *)buf;
    volatile uint8_t *pIFG = &UCzIFG;
    volatile uint16_t *pSTATW = &UCzSTATW;
    volatile uint8_t *pTX = &UCzTXBUF;
    volatile uint8_t *pRX = &UCzRXBUF;

    /* Wait for previous tx to complete. */
    while (*pSTATW & UCBUSY);
    //UCzRXBUF; /* reading RXBUF to clear error bits and UCRXIFG */
    *pRX; // should be faster since pRX contains calculated address
    while(count != 0){
        //while (!(*pIFG & UCTXIFG)); /* no needed as we check RXIFG */
        /* Setting TXBUF clears the TXIFG flag. */
        *pTX = *ptx++;
        count--;
        while (!(*pIFG & UCRXIFG));
        /* Reading RXBUF clears the RXIFG flag. */
        *prx++ = *pRX;
    }
}

/**
 * spi_transmit() - send a byte.
 */
void spi_transmit(const uint8_t data)
{
    /* Wait for previous tx to complete. */
    while (UCzSTATW & UCBUSY);
    UCzRXBUF; /* reading RXBUF to clear error bits and UCRXIFG */

    /* Setting TXBUF clears the TXIFG flag. */
    UCzTXBUF = data;

    /* Wait for previous tx to complete. */
    while (UCzSTATW & UCBUSY);
    UCzRXBUF; /* reading RXBUF to clear error bits and UCRXIFG */

}

void spi_transmit16(const uint16_t data)
{
    /* Wait for previous tx to complete. */
    while (UCzSTATW & UCBUSY);
    
    if (UCzCTLW0 & UCMSB) // MSB first?
    {
        UCzTXBUF = data >> 8; // send MSB first
        while (!(UCzIFG & UCTXIFG)); // waiting for TX buffer is ready
        UCzTXBUF = data & 0xFF; // send LSB
    }
    else
    {
        UCzTXBUF = data & 0xFF; // send LSB first
        while (!(UCzIFG & UCTXIFG)); // waiting for TX buffer is ready
        UCzTXBUF = data >> 8; // send MSB
    }

    while (UCzSTATW & UCBUSY);
    /* clear RXIFG flag. */
    UCzRXBUF; /* reading RXBUF to clear error bits and UCRXIFG */
}

void spi_transmit(void *buf, uint16_t count)
{
    if (count == 0) return;

    uint8_t *ptx = (uint8_t *)buf;
    volatile uint8_t *pIFG = &UCzIFG;
    volatile uint16_t *pSTATW = &UCzSTATW;
    volatile uint8_t *pTX = &UCzTXBUF;

    /* Wait for previous tx to complete. */
    while (*pSTATW & UCBUSY);
    while(count){
        if (*pIFG & UCTXIFG){
            /* Setting TXBUF clears the TXIFG flag. */
            *pTX = *ptx++;
            count--;
        }
    }
    /* Wait for previous tx to complete. */
    while (*pSTATW & UCBUSY);
    UCzRXBUF; /* reading RXBUF to clear error bits and UCRXIFG */

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
