/*
  ************************************************************************
  *   pins_energia.h
  *
  *   Pin definition functions for LaunchPad w/ msp430fr2476
  *      Copyright (c) 2015 Robert Wessels. All right reserved.
  *
  *     Contribution: Stefan Sch
  *
  ***********************************************************************
  Derived from:
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#ifndef Pins_Energia_h
#define Pins_Energia_h
#ifndef BV
#define BV(x) (1 << (x))
#endif

#include <msp430fr2xx_4xxgeneric.h>

// Attribute for placing R/W variables in FRAM
// Example
//      uint8_t DisplayBuffer[LCD_MAXIMUM_Y][LCD_MAXIMUM_X] PLACE_IN_FRAM;
#define PLACE_IN_FRAM __attribute__((section(".text#")))


#if defined(__MSP430_HAS_EUSCI_B0__)
static const uint8_t SS0       = 27;  /* P1.0 */
static const uint8_t SCK0      = 28;  /* P1.1 */
static const uint8_t MOSI0     = 10;  /* P1.2 aka SIMO */
static const uint8_t MISO0     = 9;   /* P1.3 aka SOMI */
static const uint8_t SS1       = 8;   /* P4.5 */
static const uint8_t SCK1      = 7;   /* P3.5 */
static const uint8_t MOSI1     = 15;  /* P3.2 aka SIMO */
static const uint8_t MISO1     = 14;  /* P3.6 aka SOMI */
static const uint8_t TWISDA0  = 10;  /* P1.2 UCB0 */
static const uint8_t TWISCL0  = 9;   /* P1.3 UCB0 */
static const uint8_t TWISDA1  = 15;  /* P3.2 UCB1 */
static const uint8_t TWISCL1  = 14;  /* P3.6 UCB1 */
#define TWISDA0_SET_MODE (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL0_SET_MODE (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISDA1_SET_MODE (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL1_SET_MODE (PORT_SELECTION0 | INPUT_PULLUP)

/* Define the default SPI settings */
#define DEFAULT_SPI 1
#define SS    SS1
#define SCK   SCK1
#define MOSI  MOSI1
#define MISO  MISO1
#define SPISCK_SET_MODE  SPISCK1_SET_MODE
#define SPIMOSI_SET_MODE SPIMOSI1_SET_MODE
#define SPIMISO_SET_MODE SPIMISO1_SET_MODE
#define SPISCK0_SET_MODE  (PORT_SELECTION0)
#define SPIMOSI0_SET_MODE (PORT_SELECTION0)
#define SPIMISO0_SET_MODE (PORT_SELECTION0)
#define SPISCK1_SET_MODE  (PORT_SELECTION0)
#define SPIMOSI1_SET_MODE (PORT_SELECTION0)
#define SPIMISO1_SET_MODE (PORT_SELECTION0)
/* Define the default I2C settings */
#define DEFAULT_I2C 0
#define TWISDA TWISDA0
#define TWISCL TWISCL0
#define TWISDA_SET_MODE  TWISDA0_SET_MODE
#define TWISCL_SET_MODE  TWISCL0_SET_MODE
#endif

#if defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
static const uint8_t DEBUG_UARTRXD = 42;  /* Receive  Data (RXD) at P1.5 */
static const uint8_t DEBUG_UARTTXD = 41;  /* Transmit Data (TXD) at P1.4 */
static const uint8_t AUX_UARTRXD = 3;     /* Receive  Data (RXD) at P2.5 */
static const uint8_t AUX_UARTTXD = 4;     /* Transmit Data (TXD) at P2.6 */
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define AUX_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define AUX_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define DEBUG_UART_MODULE_OFFSET 0x00
#define AUX_UART_MODULE_OFFSET 0x20
#define SERIAL1_AVAILABLE 1
#endif


/* Analog pins */

static const uint8_t A0  = 27;
static const uint8_t A1  = 28;
static const uint8_t A2  = 128 + 2; // Not available on BoosterPack header
static const uint8_t A3  = 128 + 3; // Not available on BoosterPack header
static const uint8_t A4  = 128 + 4; // Not available on BoosterPack header
static const uint8_t A5  = 128 + 5; // Not available on BoosterPack header
static const uint8_t A6  = 2;
static const uint8_t A7  = 23;
static const uint8_t A8  = 24;
static const uint8_t A9  = 25;
static const uint8_t A10 = 26;
static const uint8_t A11 = 6;
static const uint8_t A12 = 128 + 12; // Not available on BoosterPack header
static const uint8_t A13 = 128 + 13; // Not available on BoosterPack header
static const uint8_t A14 = 128 + 14; // Not available on BoosterPack header
static const uint8_t A15 = 128 + 15; // Not available on BoosterPack header

/* Enable P2.0/1 as XTAL pins = FR2433 */
#define INIT_LFXTAL_PINS    P2SEL0 = BIT0 | BIT1

/*
 FR2476 LaunchPad pin mapping - for all functions see docu

                               +--\/--+                                 +--\/--+
                          3.3v |1   21| 5.0v               (TB0.4) P5.2 |40  20| GND
                    (A6)  P1.6 |2   22| GND                (TB0.3) P5.1 |39  19| P4.6 (TA3.1)
     (UCA1RXD -> Serial1) P2.5 |3   23| P1.7 (A7)          (TB0.2) P5.0 |38  18| P2.1 (XIN)
     (UCA1TXD -> Serial1) P2.6 |4   24| P4.3 (A8)          (TB0.1) P4.7 |37  17| P2.0 (XOUT)
                          P2.2 |5   25| P4.4 (A9)          (TA2.2) P6.0 |36  16| RST
                    (A11) P5.4 |6   26| P5.3 (A10)         (TA2.1) P3.3 |35  15| P3.2 (UCB1SIMO) (UCB1SDA)
     (UCB1CLK)            P3.5 |7   27| P1.0 (A0)                  P6.1 |34  14| P3.6 (UCB1SOMI) (UCB1SCL)
                  (TB0.6) P4.5 |8   28| P1.1 (A1)                  P6.2 |33  13| P4.2
     (UCB0SCL)            P1.3 |9   29| P5.7 (TA2.1)               P4.1 |32  12| P2.7
     (UCB0SDA)            P1.2 |10  30| P3.7 (TA3.2)               P3.1 |31  11| P2.4
                               +------+                                 +------+

                                 ----+
                                   41| P1.4 (UCA0TXD -> ezFET -> Serial)
                                   42| P1.5 (UCA0RXD -> ezFET -> Serial)
                                   43| P4.0 (PUSH1)
                                   44| P2.3 (PUSH2)
                                 ----+
*/

/* Pin names based on the silkscreen */

/* PIN1 = 3.3v */
static const uint8_t P1_6 = 2;
static const uint8_t P2_5 = 3;
static const uint8_t P2_6 = 4;
static const uint8_t P2_2 = 5;
static const uint8_t P5_4 = 6;
static const uint8_t P3_5 = 7;
static const uint8_t P4_5 = 8;
static const uint8_t P1_3 = 9;
static const uint8_t P1_2 = 10;

static const uint8_t P2_4 = 11;
static const uint8_t P2_7 = 12;
static const uint8_t P4_2 = 13;
static const uint8_t P3_6 = 14;
static const uint8_t P3_2 = 15;
/* PIN16 is RST */
static const uint8_t P2_0 = 17;
static const uint8_t P2_1 = 18;
static const uint8_t P4_6 = 19;
/* PIN20 is GND */

/* PIN21 is 5.0v */
/* PIN22 is GND */
static const uint8_t P1_7 = 23;
static const uint8_t P4_3 = 24;
static const uint8_t P4_4 = 25;
static const uint8_t P5_3 = 26;
static const uint8_t P1_0 = 27;
static const uint8_t P1_1 = 28;
static const uint8_t P5_7 = 29;
static const uint8_t P3_7 = 30;

static const uint8_t P3_1 = 31;
static const uint8_t P4_1 = 32;
static const uint8_t P6_2 = 33;
static const uint8_t P6_1 = 34;
static const uint8_t P3_3 = 35;
static const uint8_t P6_0 = 36;
static const uint8_t P4_7 = 37;
static const uint8_t P5_0 = 38;
static const uint8_t P5_1 = 39;
static const uint8_t P5_2 = 40;

/* Extra pins not on the header + temp sensor */
static const uint8_t P1_4 = 41;    /* on Pin 8 of J101 (Header to Debugger) */
static const uint8_t P1_5 = 42;    /* on Pin 10 of J101 (Header to Debugger) */
static const uint8_t P4_0 = 43;
static const uint8_t P2_3 = 44;
static const uint8_t PUSH1 = 43;
static const uint8_t PUSH2 = 44;
static const uint8_t RED_LED = 39;
static const uint8_t GREEN_LED = 27;
static const uint8_t RED_LED2 = 39;
static const uint8_t GREEN_LED2 = 38;
static const uint8_t BLUE_LED2 = 37;


static const uint8_t TEMPSENSOR = 128 + 12;

#ifdef ARDUINO_MAIN
const uint16_t port_to_input[] = {
   NOT_A_PORT,
   (uint16_t) (P1_BASE+OFS_P1IN),
   (uint16_t) (P2_BASE+OFS_P2IN),
#ifdef __MSP430_HAS_PORT3_R__
   (uint16_t) (P3_BASE+OFS_P3IN),
#endif
#ifdef __MSP430_HAS_PORT4_R__
   (uint16_t) (P4_BASE+OFS_P4IN),
#endif
#ifdef __MSP430_HAS_PORT5_R__
   (uint16_t) (P5_BASE+OFS_P5IN),
#endif
#ifdef __MSP430_HAS_PORT6_R__
   (uint16_t) (P6_BASE+OFS_P6IN),
#endif
#ifdef __MSP430_HAS_PORT7_R__
   (uint16_t) (P7_BASE+OFS_P7IN),
#endif
#ifdef __MSP430_HAS_PORT8_R__
   (uint16_t) (P8_BASE+OFS_P8IN),
#endif
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) (P9_BASE+OFS_P9IN),
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) (P10_BASE+OFS_P10IN),
#endif
#ifdef __MSP430_HAS_PORTJ_R__
   (uint16_t) (PJ_BASE+OFS_PJIN),
#endif
};

const uint16_t port_to_output[] = {
   NOT_A_PORT,
   (uint16_t) (P1_BASE+OFS_P1OUT),
   (uint16_t) (P2_BASE+OFS_P2OUT),
#ifdef __MSP430_HAS_PORT3_R__
   (uint16_t) (P3_BASE+OFS_P3OUT),
#endif
#ifdef __MSP430_HAS_PORT4_R__
   (uint16_t) (P4_BASE+OFS_P4OUT),
#endif
#ifdef __MSP430_HAS_PORT5_R__
   (uint16_t) (P5_BASE+OFS_P5OUT),
#endif
#ifdef __MSP430_HAS_PORT6_R__
   (uint16_t) (P6_BASE+OFS_P6OUT),
#endif
#ifdef __MSP430_HAS_PORT7_R__
   (uint16_t) (P7_BASE+OFS_P7OUT),
#endif
#ifdef __MSP430_HAS_PORT8_R__
   (uint16_t) (P8_BASE+OFS_P8OUT),
#endif
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) (P9_BASE+OFS_P9OUT),
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) (P10_BASE+OFS_P10OUT),
#endif
#ifdef __MSP430_HAS_PORTJ_R__
   (uint16_t) (PJ_BASE+OFS_PJOUT),
#endif
};

const uint16_t port_to_dir[] = {
   NOT_A_PORT,
   (uint16_t) (P1_BASE+OFS_P1DIR),
   (uint16_t) (P2_BASE+OFS_P2DIR),
#ifdef __MSP430_HAS_PORT3_R__
   (uint16_t) (P3_BASE+OFS_P3DIR),
#endif
#ifdef __MSP430_HAS_PORT4_R__
   (uint16_t) (P4_BASE+OFS_P4DIR),
#endif
#ifdef __MSP430_HAS_PORT5_R__
   (uint16_t) (P5_BASE+OFS_P5DIR),
#endif
#ifdef __MSP430_HAS_PORT6_R__
   (uint16_t) (P6_BASE+OFS_P6DIR),
#endif
#ifdef __MSP430_HAS_PORT7_R__
   (uint16_t) (P7_BASE+OFS_P7DIR),
#endif
#ifdef __MSP430_HAS_PORT8_R__
   (uint16_t) (P8_BASE+OFS_P8DIR),
#endif
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) (P9_BASE+OFS_P9DIR),
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) (P10_BASE+OFS_P10DIR),
#endif
#ifdef __MSP430_HAS_PORTJ_R__
   (uint16_t) (PJ_BASE+OFS_PJDIR),
#endif
};

const uint16_t port_to_ren[] = {
      NOT_A_PORT,
      (uint16_t) (P1_BASE+OFS_P1REN),
      (uint16_t) (P2_BASE+OFS_P2REN),
   #ifdef __MSP430_HAS_PORT3_R__
      (uint16_t) (P3_BASE+OFS_P3REN),
   #endif
   #ifdef __MSP430_HAS_PORT4_R__
      (uint16_t) (P4_BASE+OFS_P4REN),
   #endif
   #ifdef __MSP430_HAS_PORT5_R__
      (uint16_t) (P5_BASE+OFS_P5REN),
   #endif
   #ifdef __MSP430_HAS_PORT6_R__
      (uint16_t) (P6_BASE+OFS_P6REN),
   #endif
   #ifdef __MSP430_HAS_PORT7_R__
      (uint16_t) (P7_BASE+OFS_P7REN),
   #endif
   #ifdef __MSP430_HAS_PORT8_R__
      (uint16_t) (P8_BASE+OFS_P8REN),
   #endif
   #ifdef __MSP430_HAS_PORT9_R__
      (uint16_t) (P9_BASE+OFS_P9REN),
   #endif
   #ifdef __MSP430_HAS_PORT10_R__
      (uint16_t) (P10_BASE+OFS_P10REN),
   #endif
   #ifdef __MSP430_HAS_PORTJ_R__
      (uint16_t) (PJ_BASE+OFS_PJREN),
   #endif
};

const uint16_t port_to_sel0[] = {  /* put this PxSEL register under the group of PxSEL0 */
      NOT_A_PORT,
      (uint16_t) (P1_BASE+OFS_P1SEL0),
      (uint16_t) (P2_BASE+OFS_P2SEL0),
   #ifdef __MSP430_HAS_PORT3_R__
      (uint16_t) (P3_BASE+OFS_P3SEL0),
   #endif
   #ifdef __MSP430_HAS_PORT4_R__
      (uint16_t) (P4_BASE+OFS_P4SEL0),
   #endif
   #ifdef __MSP430_HAS_PORT5_R__
      (uint16_t) (P5_BASE+OFS_P5SEL0),
   #endif
   #ifdef __MSP430_HAS_PORT6_R__
      (uint16_t) (P6_BASE+OFS_P6SEL0),
   #endif
   #ifdef __MSP430_HAS_PORT7_R__
      (uint16_t) (P7_BASE+OFS_P7SEL0),
   #endif
   #ifdef __MSP430_HAS_PORT8_R__
      (uint16_t) (P8_BASE+OFS_P8SEL0),
   #endif
   #ifdef __MSP430_HAS_PORT9_R__
      (uint16_t) (P9_BASE+OFS_P9SEL0),
   #endif
   #ifdef __MSP430_HAS_PORT10_R__
      (uint16_t) (P10_BASE+OFS_P10SEL0),
   #endif
   #ifdef __MSP430_HAS_PORTJ_R__
      (uint16_t) (PJ_BASE+OFS_PJSEL0),
   #endif
};

const uint16_t port_to_sel1[] = {
      NOT_A_PORT,
      (uint16_t) (P1_BASE+OFS_P1SEL1),
      (uint16_t) (P2_BASE+OFS_P2SEL1),
   #ifdef __MSP430_HAS_PORT3_R__
      (uint16_t) (P3_BASE+OFS_P3SEL1),
   #endif
   #ifdef __MSP430_HAS_PORT4_R__
      (uint16_t) (P4_BASE+OFS_P4SEL1),
   #endif
   #ifdef __MSP430_HAS_PORT5_R__
      (uint16_t) (P5_BASE+OFS_P5SEL1),
   #endif
   #ifdef __MSP430_HAS_PORT6_R__
      (uint16_t) (P6_BASE+OFS_P6SEL1),
   #endif
   #ifdef __MSP430_HAS_PORT7_R__
      (uint16_t) (P7_BASE+OFS_P7SEL1),
   #endif
   #ifdef __MSP430_HAS_PORT8_R__
      (uint16_t) (P8_BASE+OFS_P8SEL1),
   #endif
   #ifdef __MSP430_HAS_PORT9_R__
      (uint16_t) (P9_BASE+OFS_P9SEL1),
   #endif
   #ifdef __MSP430_HAS_PORT10_R__
      (uint16_t) (P10_BASE+OFS_P10SEL1),
   #endif
   #ifdef __MSP430_HAS_PORTJ_R__
      (uint16_t) (PJ_BASE+OFS_PJSEL1),
   #endif
};

const uint8_t digital_pin_to_timer[] = {
   NOT_ON_TIMER, /*  dummy */
   NOT_ON_TIMER, /*  1 - 3.3v */
   NOT_ON_TIMER, /*  2 - P1.6 */
   NOT_ON_TIMER, /*  3 - P2.5 */
   NOT_ON_TIMER, /*  4 - P2.6 */
   NOT_ON_TIMER, /*  5 - P2.2 */
   NOT_ON_TIMER, /*  6 - P5.4 */
   NOT_ON_TIMER, /*  7 - P3.5 */
   NOT_ON_TIMER, /*  8 - P4.5 */
   NOT_ON_TIMER, /*  9 - P1.3 */
   NOT_ON_TIMER, /* 10 - P1.2 */
   NOT_ON_TIMER, /* 11 - P2.4 */
   NOT_ON_TIMER, /* 12 - P2.7 */
   NOT_ON_TIMER, /* 13 - P4.2 */
   NOT_ON_TIMER, /* 14 - P3.6 */
   NOT_ON_TIMER, /* 15 - P3.2 */
   NOT_ON_TIMER, /* 16 - RST  */
   NOT_ON_TIMER, /* 17 - P2.0 */
   NOT_ON_TIMER, /* 18 - P2.1 */
   T3A1_SEL1,    /* 19 - P4.6 */
   NOT_ON_TIMER, /* 20 - GND  */
   NOT_ON_TIMER, /* 21 - 5.0v */
   NOT_ON_TIMER, /* 22 - GND  */
   NOT_ON_TIMER, /* 23 - P1.7 */
   T0B5_SEL1,    /* 24 - P4.3 */
   T0B6_SEL1,    /* 25 - P4.4 */
   NOT_ON_TIMER, /* 26 - P5.3 */
   NOT_ON_TIMER, /* 27 - P1.0 */
   T0A1_SEL1,    /* 28 - P1.1 */
   T2A1,         /* 29 - P5.7 */
   T2A2,         /* 30 - P3.7 */
   NOT_ON_TIMER, /* 31 - P3.1 */
   NOT_ON_TIMER, /* 32 - P4.1 */
   NOT_ON_TIMER, /* 33 - P6.2 */
   NOT_ON_TIMER, /* 34 - P6.1 */
   NOT_ON_TIMER, /* 35 - P3.3 */
   T2A2,         /* 36 - P6.0 */
   T0B1_SEL1,    /* 37 - P4.7 */
   T0B2_SEL1,    /* 38 - P5.0 */
   T0B3_SEL1,    /* 39 - P5.1 */
   T0B4_SEL1,    /* 40 - P5.2 */
   T1A2_SEL1,    /* 41 - P1.4 */
   T1A1_SEL1,    /* 42 - P1.5 */
   T3A1,         /* 43 - P4.0 */
   NOT_ON_TIMER, /* 44 - P2.3 */
};

const uint8_t digital_pin_to_port[] = {
   NOT_A_PIN, /*  dummy */
   NOT_A_PIN, /*  1 - 3.3v */
   P1,        /*  2 - P1.6 */
   P2,        /*  3 - P2.5 */
   P2,        /*  4 - P2.6 */
   P2,        /*  5 - P2.2 */
   P5,        /*  6 - P5.4 */
   P3,        /*  7 - P3.5 */
   P4,        /*  8 - P4.5 */
   P1,        /*  9 - P1.3 */
   P1,        /* 10 - P1.2 */
   P2,        /* 11 - P2.4 */
   P2,        /* 12 - P2.7 */
   P4,        /* 13 - P4.2 */
   P3,        /* 14 - P3.6 */
   P3,        /* 15 - P3.2 */
   NOT_A_PIN, /* 16 - RST  */
   P2,        /* 17 - P2.0 */
   P2,        /* 18 - P2.1 */
   P4,        /* 19 - P4.6 */
   NOT_A_PIN, /* 20 - GND  */
   NOT_A_PIN, /* 21 - 5.0v */
   NOT_A_PIN, /* 22 - GND  */
   P1,        /* 23 - P1.7 */
   P4,        /* 24 - P4.3 */
   P4,        /* 25 - P4.4 */
   P5,        /* 26 - P5.3 */
   P1,        /* 27 - P1.0 */
   P1,        /* 28 - P1.1 */
   P5,        /* 29 - P5.7 */
   P3,        /* 30 - P3.7 */
   P3,        /* 31 - P3.1 */
   P4,        /* 32 - P4.1 */
   P6,        /* 33 - P6.2 */
   P6,        /* 34 - P6.1 */
   P3,        /* 35 - P3.3 */
   P6,        /* 36 - P6.0 */
   P4,        /* 37 - P4.7 */
   P5,        /* 38 - P5.0 */
   P5,        /* 39 - P5.1 */
   P5,        /* 40 - P5.2 */
   P1,        /* 41 - P1.4 */
   P1,        /* 42 - P1.5 */
   P4,        /* 43 - P4.0 */
   P2,        /* 44 - P2.3 */
};

const uint8_t digital_pin_to_bit_mask[] = {
   NOT_A_PIN, /* 0,  pin count starts at 1 */
   NOT_A_PIN, /*  1 - 3.3v */
   BV(6),     /*  2 - P1.6 */
   BV(5),     /*  3 - P2.5 */
   BV(6),     /*  4 - P2.6 */
   BV(2),     /*  5 - P2.2 */
   BV(4),     /*  6 - P5.4 */
   BV(5),     /*  7 - P3.5 */
   BV(5),     /*  8 - P4.5 */
   BV(3),     /*  9 - P1.3 */
   BV(2),     /* 10 - P1.2 */
   BV(4),     /* 11 - P2.4 */
   BV(7),     /* 12 - P2.7 */
   BV(2),     /* 13 - P4.2 */
   BV(6),     /* 14 - P3.6 */
   BV(2),     /* 15 - P3.2 */
   NOT_A_PIN, /* 16 - RST  */
   BV(0),     /* 17 - P2.0 */
   BV(1),     /* 18 - P2.1 */
   BV(6),     /* 19 - P4.6 */
   NOT_A_PIN, /* 20 - GND  */
   NOT_A_PIN, /* 21 - 5.0v */
   NOT_A_PIN, /* 22 - GND  */
   BV(7),     /* 23 - P1.7 */
   BV(3),     /* 24 - P4.3 */
   BV(4),     /* 25 - P4.4 */
   BV(3),     /* 26 - P5.3 */
   BV(0),     /* 27 - P1.0 */
   BV(1),     /* 28 - P1.1 */
   BV(7),     /* 29 - P5.7 */
   BV(7),     /* 30 - P3.7 */
   BV(1),     /* 31 - P3.1 */
   BV(1),     /* 32 - P4.1 */
   BV(2),     /* 33 - P6.2 */
   BV(1),     /* 34 - P6.1 */
   BV(3),     /* 35 - P3.3 */
   BV(0),     /* 36 - P6.0 */
   BV(7),     /* 37 - P4.7 */
   BV(0),     /* 38 - P5.0 */
   BV(1),     /* 39 - P5.1 */
   BV(2),     /* 40 - P5.2 */
   BV(4),     /* 41 - P1.4 */
   BV(5),     /* 42 - P1.5 */
   BV(0),     /* 43 - P4.0 */
   BV(3),     /* 44 - P2.3 */
};

const uint32_t digital_pin_to_analog_in[] = {
        NOT_ON_ADC,   /*  dummy */
        NOT_ON_ADC,   /*  1 - 3.3v */
        6,            /*  2 - P1.6 */
        NOT_ON_ADC,   /*  3 - P2.5 */
        NOT_ON_ADC,   /*  4 - P2.6 */
        NOT_ON_ADC,   /*  5 - P2.2 */
        11,           /*  6 - P5.4 */
        NOT_ON_ADC,   /*  7 - P3.5 */
        NOT_ON_ADC,   /*  8 - P4.5 */
        NOT_ON_ADC,   /*  9 - P1.3 */
        NOT_ON_ADC,   /* 10 - P1.2 */
        NOT_ON_ADC,   /* 11 - P2.4 */
        NOT_ON_ADC,   /* 12 - P2.7 */
        NOT_ON_ADC,   /* 13 - P4.2 */
        NOT_ON_ADC,   /* 14 - P3.6 */
        NOT_ON_ADC,   /* 15 - P3.2 */
        NOT_ON_ADC,   /* 16 - RST  */
        NOT_ON_ADC,   /* 17 - P2.0 */
        NOT_ON_ADC,   /* 18 - P2.1 */
        NOT_ON_ADC,   /* 19 - P4.6 */
        NOT_ON_ADC,   /* 20 - GND  */
        NOT_ON_ADC,   /* 21 - 5.0v */
        NOT_ON_ADC,   /* 22 - GND  */
        7,            /* 23 - P1.7 */
        8,            /* 24 - P4.3 */
        9,            /* 25 - P4.4 */
        10,           /* 26 - P5.3 */
        0,            /* 27 - P1.0 */
        1,            /* 28 - P1.1 */
        NOT_ON_ADC,   /* 29 - P5.7 */
        NOT_ON_ADC,   /* 30 - P3.7 */
        NOT_ON_ADC,   /* 31 - P3.1 */
        NOT_ON_ADC,   /* 32 - P4.1 */
        NOT_ON_ADC,   /* 33 - P6.2 */
        NOT_ON_ADC,   /* 34 - P6.1 */
        NOT_ON_ADC,   /* 35 - P3.3 */
        NOT_ON_ADC,   /* 36 - P6.0 */
        NOT_ON_ADC,   /* 37 - P4.7 */
        NOT_ON_ADC,   /* 38 - P5.0 */
        NOT_ON_ADC,   /* 39 - P5.1 */
        NOT_ON_ADC,   /* 40 - P5.2 */
        NOT_ON_ADC,   /* 41 - P1.4 */
        NOT_ON_ADC,   /* 42 - P1.5 */
        NOT_ON_ADC,   /* 43 - P4.0 */
        NOT_ON_ADC,   /* 44 - P2.3 */
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h