/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * 2012-04-29 rick@kimballsoftware.com - added msp430 support.
 *
 */

#include <Energia.h>

#include "SPI.h"

#if defined(DEFAULT_SPI)
    uint8_t spiModule = DEFAULT_SPI;
#else
    uint8_t spiModule = 0;
#endif

SPIClass::SPIClass(void) {
#if defined(DEFAULT_SPI)
   setModule(DEFAULT_SPI);
#else
   setModule(0);
#endif
}

void SPIClass::setModule(uint8_t module)
{
   spiModule = module;
#if defined(__MSP430_HAS_EUSCI_B0__)
   if (module == 0)
   {
      SPI_baseAddress = UCB0_BASE;
   }
#endif
#if defined(__MSP430_HAS_EUSCI_B1__)
   if (module == 1)
   {
      SPI_baseAddress = UCB1_BASE;
   }
#endif
#if defined(__MSP430_HAS_EUSCI_B2__)
   if (module == 2)
   {
      SPI_baseAddress = UCB2_BASE;
   }
#endif
#if defined(__MSP430_HAS_EUSCI_B3__)
   if (module == 3)
   {
      SPI_baseAddress = UCB3_BASE;
   }
#endif
#if defined(__MSP430_HAS_EUSCI_A0__)
   if (module == 10)
   {
      SPI_baseAddress = UCA0_BASE;
   }
#endif
#if defined(__MSP430_HAS_EUSCI_A1__)
   if (module == 11)
   {
      SPI_baseAddress = UCA1_BASE;
   }
#endif
#if defined(__MSP430_HAS_EUSCI_A2__)
   if (module == 12)
   {
      SPI_baseAddress = UCA2_BASE;
   }
#endif
#if defined(__MSP430_HAS_EUSCI_A3__)
   if (module == 13)
   {
      SPI_baseAddress = UCA3_BASE;
   }
#endif
}

/*
 * Pre-Initialize a SPI instances
 */
SPIClass SPI;
