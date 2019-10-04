/**
 * File: usi_spi.c - msp430 USI SPI implementation
 *
 * Copyright (c) 2012 by Rick Kimball <rick@kimballsoftware.com>
 * spi abstraction api for msp430
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * 07-14-2012 - rick@kimballsoftware.com 
 *    Fixed MODE2/MODE3 phase problems. Added logic to deal with USI5 errata.
 */

#include <msp430.h>
#include <stdint.h>
#include "spi_430.h"

#ifdef __MSP430_HAS_USI__
/**
 * USI flags for various the SPI MODEs
 *
 * Note: The msp430 USICKPL tracks the CPOL value. However,
 * the USICKPH flag is inverted when compared to the CPHA
 * value described in Motorola documentation.
 */
#define SPI_DIV_MASK    (USIDIV0 | USIDIV1 | USIDIV2)
#define SPI_SSEL_MASK    (USISSEL0 | USISSEL1 | USISSEL2)
#define SPI_LSBMSB_MASK (USILSB)

#if defined(DEFAULT_SPI)
    uint8_t spiModule = DEFAULT_SPI;
#else
    uint8_t spiModule = 0;
#endif


/* deal with USI5 errata see: document slaz061b */
void USI5_workaround()
{
    uint8_t savepins = P1OUT & (BIT5 | BIT6); // save pins 5, 6
    P1OUT = (P1OUT & ~(BIT5 | BIT6)) | (P1IN & (BIT5 | BIT6)); // output to pins 5, 6 their input values
                                                               // because USI outputs are turned off and
                                                               // we don't want any changes on SCLK, MOSI

    USICTL0  &= ~(USIPE5 | USIPE6 | USIOE); // turn off SCLK and MOSI for a while for USI5 workaround
    USICTL0  |= USIMST;                     // USI is SPI MASTER
    P1DIR |= BIT5 | BIT6;                   // configure P1.5, P1.6 as P1OUT

    USICNT = 1;                             // USI5 errata workaround
    while (!(USICTL1 & USIIFG));            // wait for transmit to complete
    USISRL;                                 // read incoming data and clear USIIFG

    USICTL0  |= USIPE5 | USIPE6 | USIPE7 | USIOE;    // turn on MISO, SCLK and MOSI
    P1OUT = (P1OUT & ~(BIT5 | BIT6)) | savepins;
}

/**
 * spi_initialize() - Configure USI for SPI mode
 *
 * P2.0 - CS (active low)
 * P1.5 - SCLK
 * P1.6 - MOSI aka SIMO
 * P1.7 - MISO aka SOMI
 */

void spi_initialize(void)
{
    USICTL0  |= USISWRST;                   // put USI in reset mode, source USI clock from SMCLK
    USICTL0  |= USIPE5 | USIPE6 | USIPE7 | USIMST | USIOE;
    USICKCTL = (USICKCTL & ~(SPI_SSEL_MASK | SPI_DIV_MASK)) | USIDIV_2 | USISSEL_2; // default speed 4MHz 16MHz/4
    USICTL1   = USICKPH;                    // SPI_MODE_0

    P1OUT |= BIT5 | BIT6;                   // SPI OUTPUT PINS HIGH -- why???
    P1DIR = (P1DIR & ~BIT7) | BIT5 | BIT6;  // configure P1.5, P1.6, P1.7 for USI

    USICTL0 &= ~USISWRST;                   // release USI for operation

    USI5_workaround();
}

void spi_disable(void) {
    USICTL0 |= USISWRST;        // put USI in reset mode
}

/**
 * spi_send() - send a byte and recv response
 */

uint8_t spi_send(const uint8_t _data)
{
    USISRL = _data;
    USICNT = 8;
    while (!(USICTL1 & USIIFG)) {
        ; // wait for an USICNT to decrement to 0
    }
    return USISRL; // reading clears RXIFG flag
}

uint16_t spi_send16(const uint16_t data)
{
 USISR = data;
 USICNT = 16 | USI16B;
 while (!(USICTL1 & USIIFG)) {
        ; // wait for an USICNT to decrement to 0
 }
 return USISR;
}

void spi_send(void *buf, uint16_t count)
{
    uint8_t *p = (uint8_t *)buf;
	if (count == 0) return;
	while(count){
		*p = spi_send(*p);
		*p++;
		count--;
	}
}

/**
 * spi_transmit() - send a byte
 */

void spi_transmit(const uint8_t _data)
{
    USISRL = _data;
    USICNT = 8;
    while (!(USICTL1 & USIIFG)) {
        ; // wait for an USICNT to decrement to 0
    }

    // clear USIIFG flag
    USISRL;
}

void spi_transmit16(const uint16_t data)
{
 USISR = data;
 USICNT = 16 | USI16B;
 while (!(USICTL1 & USIIFG)) {
        ; // wait for an USICNT to decrement to 0
 }
}

void spi_transmit(void *buf, uint16_t count)
{
    uint8_t *p = (uint8_t *)buf;
	if (count == 0) return;
	while(count){
		spi_transmit(*p++);
		count--;
	}
}


/**
 * spi_set_divisor() - set new clock divider for USI
 *
 * There are a fixed set of valid values for clock divisors
 * see the slau144 for details. DIV by 2/4/8 .. 128
 */

void spi_set_divisor(const uint16_t clkdiv)
{
    USICTL0 |= USISWRST;        // put USI in reset mode
    USICKCTL = (USICKCTL & ~SPI_DIV_MASK) | clkdiv;
    USICTL0 &= ~USISWRST;        // release for operation
}

/**
 * spi_set_bitorder (enum LSBFIRST=0|MSBFIRST=1)
 *
 * Note: this should use the LSBFIRST/MSBFIRST defines however
 * it doesn't to allow this code to compile without Energia.
 *
 */
void spi_set_bitorder(const uint8_t order)
{
    USICTL0 |= USISWRST;        // put USI in reset mode
    USICTL0 = (USICTL0 & ~SPI_LSBMSB_MASK) | ((order == 1 /*MSBFIRST*/) ? 0 : USILSB); /* MSBFIRST = 1 */
    USICTL0 &= ~USISWRST;       // release for operation
}

/**
 * spi_set_datamode() - Motorola SPI Mode 0 ... 3
 *
 * mode is really an enum SPI_MODE0 ... SPI_MODE3 as defined in
 * the Energia header file.
 */
void spi_set_datamode(const uint8_t mode)
{
    USICTL0 |= USISWRST;        // put USI in reset mode while we make changes
    switch(mode) {
    case 0:                   /* SPI_MODE0 */
        USICKCTL &= ~USICKPL; /* CPOL=0 */
        USICTL1  |= USICKPH;  /* CPHA=0 */
        break;

    case 1:                   /* SPI_MODE1 */
        USICKCTL &= ~USICKPL; /* CPOL=0 */
        USICTL1  &= ~USICKPH; /* CPHA=1 */
        break;

    case 2:                   /* SPI_MODE2 */
        USICKCTL |= USICKPL;  /* CPOL=1 */
        USICTL1  |= USICKPH;  /* CPHA=0 */
        break;

    case 4:                   /* SPI_MODE3 */
        USICKCTL |= USICKPL;  /* CPOL=1 */
        USICTL1  &= ~USICKPH; /* CPHA=1 */
        break;

    default:
        break;
    }
    USICTL0 &= ~USISWRST;       // release for operation

    if ( USICTL1 & USICKPH ) USI5_workaround();
}

#else
    //#warning "Error! This device doesn't have a USI peripheral"
#endif
