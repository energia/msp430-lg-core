/*
  ************************************************************************
  *    pins_energia.h
  *
  *    Pin definition functions for SocketBoard w/ msp430g2955
  *        Copyright (c) 2015 Robert Wessels. All right reserved.
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

#include <msp430fr5xx_6xxgeneric.h>

// Attribute for placing R/W variables in FRAM
// Example
//      uint8_t DisplayBuffer[LCD_MAXIMUM_Y][LCD_MAXIMUM_X] PLACE_IN_FRAM;
#define PLACE_IN_FRAM __attribute__((section(".text")))


static const uint8_t SS      = 11;   /* P3.0 */
static const uint8_t SCK     = 14;   /* P3.3 */
static const uint8_t MOSI    = 12;   /* P3.1 aka SIMO */
static const uint8_t MISO    = 13;   /* P3.2 aka SOMI */
static const uint8_t TWISDA0  = 12;  /* P3.1 UCB0 */
static const uint8_t TWISCL0  = 13;  /* P3.2 UCB0 */
#define TWISDA0_SET_MODE (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL0_SET_MODE (PORT_SELECTION0 | INPUT_PULLUP)
#define SPISCK_SET_MODE  (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
/* Define the default I2C settings */
#define DEFAULT_I2C 0
#define TWISDA TWISDA0
#define TWISCL TWISCL0
#define TWISDA_SET_MODE  TWISDA0_SET_MODE
#define TWISCL_SET_MODE  TWISCL0_SET_MODE

static const uint8_t DEBUG_UARTRXD = 26;  /* Receive  Data (RXD) at P3.5 */
static const uint8_t DEBUG_UARTTXD = 25;  /* Transmit Data (TXD) at P3.4 */
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define DEBUG_UART_MODULE_OFFSET 0x00


/* Analog pins */

static const uint8_t A0  = 8;
static const uint8_t A1  = 9;
static const uint8_t A2  = 10;
static const uint8_t A3  = 29;
static const uint8_t A4  = 30;
static const uint8_t A5  = 11;
static const uint8_t A6  = 27;
static const uint8_t A7  = 28;
static const uint8_t A8  = 128+8; /* Not available */
static const uint8_t A9  = 128+9; /* Not available */
static const uint8_t A10 = 128+10; /* Not available */
static const uint8_t A11 = 128+11; /* Not available */
static const uint8_t A12 = 20;
static const uint8_t A13 = 21;
static const uint8_t A14 = 22;
static const uint8_t A15 = 23;

/*
 G2955 LaunchPad pin mapping - for all functions see docu
      
                                     +---\/---+
                                TST  |1     38| P1.7 (T0A2)
                                3.3v |2     37| P1.6 (T0A1)
                                P2.5 |3     36| P1.5
                                GND  |4     35| P1.4
                                P2.7 |5     34| P1.3 (T0A2)
                                P2.6 |6     33| P1.2 (T0A1)
                                RST  |7     32| P1.1
                    (A0)        P2.0 |8     31| P1.0
                    (A1)        P2.1 |9     30| P2.4 (T0A2)(A4)
                    (A2)        P2.2 |10    29| P2.3 (T0A1)(A3)
                    (A5)(TB0.6) P3.0 |11    28| P3.7 (T1A2)(A7)
     (UCB0SIMO)(UCB0SDA)(TB0.5) P3.1 |12    27| P3.6 (T1A1)(A6)
     (UCB0SOMI)(UCB0SCL)(TA1.1) P3.2 |13    26| P3.5             (UCA0RXD -> Serial1)
     (UCB0SCK)          (TB0.2) P3.3 |14    25| P3.4             (UCA0TXD -> Serial1)
                                GND  |15    24| P4.7 
                                3.3v |16    23| P4.6        (A15)
                                P4.0 |17    22| P4.5 (TB0.2)(A14)
                        (TB0.1) P4.1 |18    21| P4.4 (TB0.1)(A13)
                        (TB0.2) P4.2 |19    20| P4.3        (A12)         							   
                                     +--------+

*/

/* Pin names based on the silkscreen */

/* PIN1 = TEST */
/* PIN2 is DVCC */
static const uint8_t P2_5 = 3;
/* PIN4 is GND */
static const uint8_t P2_7 = 5;
static const uint8_t P2_6 = 6;
/* PIN7 is RST */
static const uint8_t P2_0 = 8;
static const uint8_t P2_1 = 9;
static const uint8_t P2_2 = 10;

static const uint8_t P3_0 = 11;
static const uint8_t P3_1 = 12;
static const uint8_t P3_2 = 13;
static const uint8_t P3_3 = 14;
/* PIN15 is GND */
/* PIN16 is DVCC */
static const uint8_t P4_0 = 17;
static const uint8_t P4_1 = 18;
static const uint8_t P4_2 = 19;

static const uint8_t P4_3 = 20;
static const uint8_t P4_4 = 21;
static const uint8_t P4_5 = 22;
static const uint8_t P4_6 = 23;
static const uint8_t P4_7 = 24;
static const uint8_t P3_4 = 25;
static const uint8_t P3_5 = 26;
static const uint8_t P3_6 = 27;
static const uint8_t P3_7 = 28;
static const uint8_t P2_3 = 29;
static const uint8_t P2_4 = 30;

static const uint8_t P1_0 = 31;
static const uint8_t P1_1 = 32;
static const uint8_t P1_2 = 33;
static const uint8_t P1_3 = 34;
static const uint8_t P1_4 = 35;
static const uint8_t P1_5 = 36;
static const uint8_t P1_6 = 37;
static const uint8_t P1_7 = 38;

static const uint8_t PUSH1 = 31;
static const uint8_t PUSH2 = 32;
static const uint8_t RED_LED = 31;
static const uint8_t GREEN_LED = 31;
static const uint8_t TEMPSENSOR = 128 + 30;

#ifdef ARDUINO_MAIN
const uint16_t port_to_input[] = {
   NOT_A_PORT,
   (const uint16_t) (&P1IN),
   (const uint16_t) (&P2IN),
#ifdef __MSP430_HAS_PORT3_R__
   (const uint16_t) (&P3IN),
#endif
#ifdef __MSP430_HAS_PORT4_R__
   (const uint16_t) (&P4IN),
#endif
#ifdef __MSP430_HAS_PORT5_R__
   (const uint16_t) (&P5IN)),
#endif
#ifdef __MSP430_HAS_PORT6_R__
   (const uint16_t) (&P6IN),
#endif
#ifdef __MSP430_HAS_PORT7_R__
   (const uint16_t) (&P7IN),
#endif
#ifdef __MSP430_HAS_PORT8_R__
   (const uint16_t) (&P8IN)),
#endif
#ifdef __MSP430_HAS_PORT9_R__
   (const uint16_t) (&P9IN),
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (const uint16_t) (&P10IN),
#endif
#ifdef __MSP430_HAS_PORTJ_R__
   (const uint16_t) (&PJIN),
#endif
};

const uint16_t port_to_output[] = {
   NOT_A_PORT,
   (const uint16_t) (&P1OUT),
   (const uint16_t) (&P2OUT),
#ifdef __MSP430_HAS_PORT3_R__
   (const uint16_t) (&P3OUT),
#endif
#ifdef __MSP430_HAS_PORT4_R__
   (const uint16_t) (&P4OUT),
#endif
#ifdef __MSP430_HAS_PORT5_R__
   (const uint16_t) (&P5OUT),
#endif
#ifdef __MSP430_HAS_PORT6_R__
   (const uint16_t) (&P6OUT),
#endif
#ifdef __MSP430_HAS_PORT7_R__
   (const uint16_t) (&P7OUT),
#endif
#ifdef __MSP430_HAS_PORT8_R__
   (const uint16_t) (&P8OUT),
#endif
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) (P9_BASE+OFS_P9OUT),
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (const uint16_t) (&P10OUT),
#endif
#ifdef __MSP430_HAS_PORTJ_R__
   (const uint16_t) (&PJOUT),
#endif
};

const uint16_t port_to_dir[] = {
   NOT_A_PORT,
   (const uint16_t) (&P1DIR),
   (const uint16_t) (&P2DIR),
#ifdef __MSP430_HAS_PORT3_R__
   (const uint16_t) (&P3DIR),
#endif
#ifdef __MSP430_HAS_PORT4_R__
   (const uint16_t) (&P4DIR),
#endif
#ifdef __MSP430_HAS_PORT5_R__
   (const uint16_t) (&P5DIR),
#endif
#ifdef __MSP430_HAS_PORT6_R__
   (const uint16_t) (&P6DIR),
#endif
#ifdef __MSP430_HAS_PORT7_R__
   (const uint16_t) (&P7DIR),
#endif
#ifdef __MSP430_HAS_PORT8_R__
   (const uint16_t) (&P8DIR),
#endif
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) (P9_BASE+OFS_P9DIR),
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (const uint16_t) (&P10DIR),
#endif
#ifdef __MSP430_HAS_PORTJ_R__
   (const uint16_t) (&PJDIR),
#endif
};

const uint16_t port_to_ren[] = {
       NOT_A_PORT,
       (const uint16_t) (&P1REN),
       (const uint16_t) (&P2REN),
    #ifdef __MSP430_HAS_PORT3_R__
       (const uint16_t) (&P3REN),
    #endif
    #ifdef __MSP430_HAS_PORT4_R__
       (const uint16_t) (&P4REN),
    #endif
    #ifdef __MSP430_HAS_PORT5_R__
       (const uint16_t) (&P5REN),
    #endif
    #ifdef __MSP430_HAS_PORT6_R__
       (const uint16_t) (&P6REN),
    #endif
    #ifdef __MSP430_HAS_PORT7_R__
       (const uint16_t) (&P7REN),
    #endif
    #ifdef __MSP430_HAS_PORT8_R__
       (const uint16_t) (&P8REN),
    #endif
    #ifdef __MSP430_HAS_PORT9_R__
       (const uint16_t) (&P9REN),
    #endif
    #ifdef __MSP430_HAS_PORT10_R__
       (const uint16_t) (&P10REN),
    #endif
    #ifdef __MSP430_HAS_PORTJ_R__
       (const uint16_t) (&PJREN),
    #endif
};

const uint16_t port_to_sel0[] = {  /* put this PxSEL register under the group of PxSEL0 */
       NOT_A_PORT,
       (const uint16_t) (&P1SEL),
       (const uint16_t) (&P2SEL),
    #ifdef __MSP430_HAS_PORT3_R__
       (const uint16_t) (&P3SEL),
    #endif
    #ifdef __MSP430_HAS_PORT4_R__
       (const uint16_t) (&P4SEL),
    #endif
    #ifdef __MSP430_HAS_PORT5_R__
       (const uint16_t) (&P5SEL),
    #endif
    #ifdef __MSP430_HAS_PORT6_R__
       (const uint16_t) (&P6SEL),
    #endif
    #ifdef __MSP430_HAS_PORT7_R__
       (const uint16_t) (&P7SEL),
    #endif
    #ifdef __MSP430_HAS_PORT8_R__
       (const uint16_t) (&P8SEL),
    #endif
    #ifdef __MSP430_HAS_PORT9_R__
       (const uint16_t) (&P9SEL),
    #endif
    #ifdef __MSP430_HAS_PORT10_R__
       (const uint16_t) (&P10SEL),
    #endif
    #ifdef __MSP430_HAS_PORTJ_R__
       (const uint16_t) (&PJSEL),
    #endif
};

const uint16_t port_to_sel2[] = {
   NOT_A_PORT,
#if (defined(P1SEL2_) || defined(P1SEL2) || defined(__MSP430_HAS_P1SEL2__))
   (const uint16_t) (&P1SEL2),
#else
        NOT_A_PORT,
#endif
#if (defined(P2SEL2_) || defined(P2SEL2) || defined(__MSP430_HAS_P2SEL2__))
   (const uint16_t) (&P2SEL2),
#else 
        NOT_A_PORT,
#endif
#if (defined(P3SEL2_) || defined(P3SEL2) || defined(__MSP430_HAS_P3SEL2__))
   (const uint16_t) (&P3SEL2),
#else
        NOT_A_PORT,
#endif 
#if (defined(P4SEL2_) || defined(P4SEL2) || defined(__MSP430_HAS_P4SEL2__))
   (const uint16_t) (&P4SEL2),
#else
        NOT_A_PORT,
#endif 
}; 


const uint8_t digital_pin_to_timer[] = {
    NOT_ON_TIMER, /*  dummy */
    NOT_ON_TIMER, /*  1 - TEST */
    NOT_ON_TIMER, /*  2 - 3.3v */
    NOT_ON_TIMER, /*  3 - P2.5 */
    NOT_ON_TIMER, /*  4 - GND */
    NOT_ON_TIMER, /*  5 - P2.7 */
    NOT_ON_TIMER, /*  6 - P2.6 */
    NOT_ON_TIMER, /*  7 - RST */
    NOT_ON_TIMER, /*  8 - P2.0 */
    NOT_ON_TIMER, /*  9 - P2.1 */
    NOT_ON_TIMER, /* 10 - P2.2 */
    NOT_ON_TIMER, /* 11 - P3.0 */
    NOT_ON_TIMER, /* 12 - P3.1 */
    NOT_ON_TIMER, /* 13 - P3.2 */
    NOT_ON_TIMER, /* 14 - P3.3 */
    NOT_ON_TIMER, /* 15 - GND */
    NOT_ON_TIMER, /* 16 - 3.3v */
    NOT_ON_TIMER, /* 17 - P4.0 */
    T0B1,         /* 18 - P4.1 */
    T0B2,         /* 19 - P4.2 */
    NOT_ON_TIMER, /* 20 - P4.3 */
    T0B1,         /* 21 - P4.4 */
    T0B2,         /* 22 - P4.5 */
    NOT_ON_TIMER, /* 23 - P4.6 */
    NOT_ON_TIMER, /* 24 - P4.7 */
    NOT_ON_TIMER, /* 25 - P3.4 */
    NOT_ON_TIMER, /* 26 - P3.5 */
    T1A1,         /* 27 - P3.6 */
    T1A2,         /* 28 - P3.7 */
    T0A1,         /* 29 - P2.3 */
    T0A2,         /* 30 - P2.4 */
    NOT_ON_TIMER, /* 31 - P1.0 */
    NOT_ON_TIMER, /* 32 - P1.1 */
    T0A1,         /* 33 - P1.2 */
    T0A2,         /* 34 - P1.3 */
    NOT_ON_TIMER, /* 35 - P1.4 */
    NOT_ON_TIMER, /* 36 - P1.5 */
    T0A1,         /* 37 - P1.6 */
    T0A2,         /* 38 - P1.7 */
};

const uint8_t digital_pin_to_port[] = {
    NOT_A_PIN, /*  dummy */
    NOT_A_PIN, /*  1 - TEST */
    NOT_A_PIN, /*  2 - 3.3v */
    P2,        /*  3 - P2.5 */
    NOT_A_PIN, /*  4 - GND */
    P2,        /*  5 - P2.7 */
    P2,        /*  6 - P2.6 */
    NOT_A_PIN, /*  7 - RST */
    P2,        /*  8 - P2.0 */
    P2,        /*  9 - P2.1 */
    P2,        /* 10 - P2.2 */
    P3,        /* 11 - P3.0 */
    P3,        /* 12 - P3.1 */
    P3,        /* 13 - P3.2 */
    P3,        /* 14 - P3.3 */
    NOT_A_PIN, /* 15 - GND */
    NOT_A_PIN, /* 16 - 3.3v */
    P4,        /* 17 - P4.0 */
    P4,        /* 18 - P4.1 */
    P4,        /* 19 - P4.2 */
    P4,        /* 20 - P4.3 */
    P4,        /* 21 - P4.4 */
    P4,        /* 22 - P4.5 */
    P4,        /* 23 - P4.6 */
    P3,        /* 24 - P4.7 */
    P3,        /* 25 - P3.4 */
    P3,        /* 26 - P3.5 */
    P3,        /* 27 - P3.6 */
    P3,        /* 28 - P3.7 */
    P2,        /* 29 - P2.3 */
    P3,        /* 30 - P2.4 */
    P1,        /* 31 - P1.0 */
    P1,        /* 32 - P1.1 */
    P1,        /* 33 - P1.2 */
    P1,        /* 34 - P1.3 */
    P1,        /* 35 - P1.4 */
    P1,        /* 36 - P1.5 */
    P1,        /* 37 - P1.6 */
    P1,        /* 38 - P1.7 */
};

const uint8_t digital_pin_to_bit_mask[] = {
    NOT_A_PIN, /*  dummy */
    NOT_A_PIN, /*  1 - TEST */
    NOT_A_PIN, /*  2 - 3.3v */
    BV(5),     /*  3 - P2.5 */
    NOT_A_PIN, /*  4 - GND */
    BV(7),     /*  5 - P2.7 */
    BV(6),     /*  6 - P2.6 */
    BV(4),     /*  7 - RST */
    BV(0),     /*  8 - P2.0 */
    BV(1),     /*  9 - P2.1 */
    BV(2),     /* 10 - P2.2 */
    BV(0),     /* 11 - P3.0 */
    BV(1),     /* 12 - P3.1 */
    BV(2),     /* 13 - P3.2 */
    BV(3),     /* 14 - P3.3 */
    NOT_A_PIN, /* 15 - GND */
    NOT_A_PIN, /* 16 - 3.3v */
    BV(0),     /* 17 - P4.0 */
    BV(1),     /* 18 - P4.1 */
    BV(2),     /* 19 - P4.2 */
    BV(3),     /* 20 - P4.3 */
    BV(4),     /* 21 - P4.4 */
    BV(5),     /* 22 - P4.5 */
    BV(6),     /* 23 - P4.6 */
    BV(7),     /* 24 - P4.7 */
    BV(4),     /* 25 - P3.4 */
    BV(5),     /* 26 - P3.5 */
    BV(6),     /* 27 - P3.6 */
    BV(7),     /* 28 - P3.7 */
    BV(3),     /* 29 - P2.3 */
    BV(4),     /* 30 - P2.4 */
    BV(0),     /* 31 - P1.0 */
    BV(1),     /* 32 - P1.1 */
    BV(2),     /* 33 - P1.2 */
    BV(3),     /* 34 - P1.3 */
    BV(4),     /* 35 - P1.4 */
    BV(5),     /* 36 - P1.5 */
    BV(6),     /* 37 - P1.6 */
    BV(7),     /* 38 - P1.7 */
};

const uint32_t digital_pin_to_analog_in[] = {
        NOT_ON_ADC,     /*  dummy */
        NOT_ON_ADC,     /*  1 - TEST */
        NOT_ON_ADC,     /*  2 - 3.3v */
        NOT_ON_ADC,     /*  3 - P2.5 */
        NOT_ON_ADC,     /*  4 - GND */
        NOT_ON_ADC,     /*  5 - P2.7 */
        NOT_ON_ADC,     /*  6 - P2.6 */
        NOT_ON_ADC,     /*  7 - RST */
        0,              /*  8 - P2.0 */
        1,              /*  9 - P2.1 */
        2,              /* 10 - P2.2 */
        5,              /* 11 - P3.0 */
        NOT_ON_ADC,     /* 12 - P3.1 */
        NOT_ON_ADC,     /* 13 - P3.2 */
        NOT_ON_ADC,     /* 14 - P3.3 */
        NOT_ON_ADC,     /* 15 - GND */
        NOT_ON_ADC,     /* 16 - 3.3v */
        NOT_ON_ADC,     /* 17 - P4.0 */
        NOT_ON_ADC,     /* 18 - P4.1 */
        NOT_ON_ADC,     /* 19 - P4.2 */
        12,             /* 20 - P4.3 */
        13,             /* 21 - P4.4 */
        14,             /* 22 - P4.5 */
        15,             /* 23 - P4.6 */
        NOT_ON_ADC,     /* 24 - P4.7 */
        NOT_ON_ADC,     /* 25 - P3.4 */
        NOT_ON_ADC,     /* 26 - P3.5 */
        6,              /* 27 - P3.6 */
        7,              /* 28 - P3.7 */
        3,              /* 29 - P2.3 */
        4,              /* 30 - P2.4 */
        NOT_ON_ADC,     /* 31 - P1.0 */
        NOT_ON_ADC,     /* 32 - P1.1 */
        NOT_ON_ADC,     /* 33 - P1.2 */
        NOT_ON_ADC,     /* 34 - P1.3 */
        NOT_ON_ADC,     /* 35 - P1.4 */
        NOT_ON_ADC,     /* 36 - P1.5 */
        NOT_ON_ADC,     /* 37 - P1.6 */
        NOT_ON_ADC,     /* 38 - P1.7 */
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
