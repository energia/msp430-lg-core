/*
  ************************************************************************
  *	pins_energia.h
  *
  *	Pin definition functions for LaunchPad w/ msp430fr2355
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
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
#define PLACE_IN_FRAM __attribute__((section(".text")))


#if defined(__MSP430_HAS_EUSCI_B0__)
static const uint8_t SS      = 8;   /* P3.4 */
static const uint8_t SCK     = 7;   /* P4.5 */
static const uint8_t MOSI    = 15;  /* P4.6 aka SIMO */
static const uint8_t MISO    = 14;  /* P4.7 aka SOMI */
static const uint8_t TWISCL0  = 9;   /* P1.3 SW I2C */
static const uint8_t TWISDA0  = 10;  /* P1.2 SW I2C */
static const uint8_t TWISDA1  = 15;  /* P4.6 UCB1 */
static const uint8_t TWISCL1  = 14;  /* P4.7 UCB1 */
#define TWISDA0_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL0_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISDA1_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL1_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define SPISCK_SET_MODE  (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
/* Define the default I2C settings */
#define DEFAULT_I2C 0 
#define TWISDA TWISDA0
#define TWISCL TWISCL0
#define TWISDA_SET_MODE  TWISDA0_SET_MODE
#define TWISCL_SET_MODE  TWISCL0_SET_MODE
#endif

#if defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
static const uint8_t DEBUG_UARTRXD = 22;  /* Receive  Data (RXD) at P4.2 */
static const uint8_t DEBUG_UARTTXD = 21;  /* Transmit Data (TXD) at P4.3 */
static const uint8_t AUX_UARTRXD = 3;     /* Receive  Data (RXD) at P1.6 */
static const uint8_t AUX_UARTTXD = 4;     /* Transmit Data (TXD) at P1.7 */
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define AUX_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define AUX_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define DEBUG_UART_MODULE_OFFSET 0x20
#define AUX_UART_MODULE_OFFSET 0x00
#define SERIAL1_AVAILABLE 1
#endif

/* Enable P2.6/7 as XTAL pins = FR2311 */
#define INIT_LFXTAL_PINS P2SEL0 = BIT6 | BIT7


/* Analog pins */

static const uint8_t A0  = 43;
static const uint8_t A1  = 28;
static const uint8_t A2  = 10;
static const uint8_t A3  = 9;
static const uint8_t A4  = 23;
static const uint8_t A5  = 2;
static const uint8_t A6  = 3;
static const uint8_t A7  = 4;
static const uint8_t A8  = 26;
static const uint8_t A9  = 25;
static const uint8_t A10 = 6;
static const uint8_t A11 = 24;
static const uint8_t A12 = 128 + 13; // Not available on BoosterPack header
static const uint8_t A13 = 128 + 13; // Not available on BoosterPack header
static const uint8_t A14 = 128 + 14; // Not available on BoosterPack header
static const uint8_t A15 = 128 + 15; // Not available on BoosterPack header

//-------------------------------------------

/* Layout of the 2 - 10 pin headers.

   All pins support digitalWrite() and attachInterrupt()
   Pins marked with PWM support anaglogWrite()
   Pins marked with Ax support analogRead()

                                          +---\/---+
                                   VCC0  1|        |21  5.0V
                            (A5)   P1.5  2|        |22  GND
(PWM) (UCA0RXD -> Serial1)         P1.6  3|        |23  P1.4            (A4) 
(PWM) (UCA0TXD -> Serial1)         P1.7  4|        |24  P5.3            (A11)
                                   P3.6  5|        |25  P5.1            (A9)
(PWM)                       (A10)  P5.2  6|        |26  P5.0            (A8)
(PWM) (SCLK)                       P4.5  7|        |27  P5.4
                                   P3.4  8|        |28  P1.1            (A1)
(PWM) (SCL)                        P1.3  9|        |29  P3.5            (OA3O)
(PWM) (SDA)                        P1.2 10|        |30  P3.1            (OA2O)
                                          +--------+

										  
										  
                                          +---\/---+
(PWM)                              P2.1 40|        |20  GND
(PWM)                              P6.0 39|        |19  P2.0                 (PWM)
(PWM)                              P6.1 38|        |18  P2.2                 (PWM)
(PWM)                              P6.2 37|        |17  P4.0
(PWM)                              P6.3 36|        |16  RST
(PWM)                              P6.4 35|        |15  P4.6 (SDA) (MOSI)
                                   P3.7 34|        |14  P4.7 (SCL) (MISO)
                                   P2.4 33|        |13  P4.4
                     (OA2+)        P3.3 32|        |12  P2.5
                     (OA2-)        P3.2 31|        |11  P3.0
                                          +--------+
										  
										  

                                               ----+
                                                   |41  DebugUART TX  (P4.3)
                     J13 eZ-FET Connector          |42  DebugUART RX  (P4.2)
                                               ----+
                                               ----+
                                                   |43  LED1       (P1.0)
                     Extra LED's and Switches      |44  LED2       (P6.6)
                                                   |45  PUSH1      (P4.1)
                                                   |46  PUSH2      (P2.3)
                                               ----+
*/

// Pin names based on the silkscreen
//

static const uint8_t P1_0 = 43;
static const uint8_t P1_1 = 28;
static const uint8_t P1_2 = 10;
static const uint8_t P1_3 = 9;
static const uint8_t P1_4 = 23;
static const uint8_t P1_5 = 2;
static const uint8_t P1_6 = 3;
static const uint8_t P1_7 = 4;

static const uint8_t P2_0 = 19;
static const uint8_t P2_1 = 40;
static const uint8_t P2_2 = 18;
static const uint8_t P2_3 = 46;
static const uint8_t P2_4 = 33;
static const uint8_t P2_5 = 12;
//static const uint8_t P2_6 = ;
//static const uint8_t P2_7 = ;

static const uint8_t P3_0 = 11;
static const uint8_t P3_1 = 30;
static const uint8_t P3_2 = 31;
static const uint8_t P3_3 = 32;
static const uint8_t P3_4 = 8;
static const uint8_t P3_5 = 29;
static const uint8_t P3_6 = 5;
static const uint8_t P3_7 = 34;

static const uint8_t P4_0 = 17;
static const uint8_t P4_1 = 45;
static const uint8_t P4_2 = 42;
static const uint8_t P4_3 = 41;
static const uint8_t P4_4 = 13;
static const uint8_t P4_5 = 7;
static const uint8_t P4_6 = 15;
static const uint8_t P4_7 = 14;

static const uint8_t P5_0 = 26;
static const uint8_t P5_1 = 25;
static const uint8_t P5_2 = 6;
static const uint8_t P5_3 = 24;
static const uint8_t P5_4 = 27;
//static const uint8_t P5_5 = ;
//static const uint8_t P5_6 = ;
//static const uint8_t P5_7 = ;

static const uint8_t P6_0 = 39;
static const uint8_t P6_1 = 38;
static const uint8_t P6_2 = 37;
static const uint8_t P6_3 = 36;
static const uint8_t P6_4 = 35;
//static const uint8_t P6_5 = ;
static const uint8_t P6_6 = 44;
//static const uint8_t P6_7 = ;


static const uint8_t LED1 = 43;
static const uint8_t LED2 = 44;
/* For LaunchPad compatability */
static const uint8_t RED_LED = 43;
static const uint8_t GREEN_LED = 44;

static const uint8_t PUSH1 = 45;
static const uint8_t PUSH2 = 46;
static const uint8_t TEMPSENSOR = 128 + 30; // depends on chip

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
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER,  /*  0 - pin count starts at 1 */
	NOT_ON_TIMER,  /*  1 - Vcc */
	NOT_ON_TIMER,  /*  2 - P1.5 */
	T0B1,          /*  3 - P1.6 */
	T0B2,          /*  4 - P1.7 */
	NOT_ON_TIMER,  /*  5 - P3.6 */
	NOT_ON_TIMER,  /*  6 - P5.2 */
	NOT_ON_TIMER,  /*  7 - P4.5 */
	NOT_ON_TIMER,  /*  8 - P3.4 */
	NOT_ON_TIMER,  /*  9 - P1.3 */
	NOT_ON_TIMER,  /* 10 - P1.2 */
	NOT_ON_TIMER,  /* 11 - P3.0 */
	NOT_ON_TIMER,  /* 12 - P2.5 */
	NOT_ON_TIMER,  /* 13 - P4.4 */
	NOT_ON_TIMER,  /* 14 - P4.7 */
	NOT_ON_TIMER,  /* 15 - P4.6 */
	NOT_ON_TIMER,  /* 16 - RST */
	NOT_ON_TIMER,  /* 17 - P4.0 */
	NOT_ON_TIMER,  /* 18 - P2.2 */
	T1B1,          /* 19 - P2.0 */
	NOT_ON_TIMER,  /* 20 - GND */
	
	NOT_ON_TIMER,  /* 21 - 5.0V */
	NOT_ON_TIMER,  /* 22 - GND */
	NOT_ON_TIMER,  /* 23 - P1.4 */
	NOT_ON_TIMER,  /* 24 - P5.3 */
	T2B2,          /* 25 - P5.1 */
	T2B1,          /* 26 - P5.0 */
	NOT_ON_TIMER,  /* 27 - P5.4 */
	NOT_ON_TIMER,  /* 28 - P1.1 */
	NOT_ON_TIMER,  /* 29 - P3.5 */
	NOT_ON_TIMER,  /* 30 - P3.1 */
	NOT_ON_TIMER,  /* 31 - P3.2 */
	NOT_ON_TIMER,  /* 32 - P3.3 */
	NOT_ON_TIMER,  /* 33 - P2.4 */
	NOT_ON_TIMER,  /* 34 - P3.7 */
	T3B5,          /* 35 - P6.4 */
	T3B4,          /* 36 - P6.3 */
	T3B3,          /* 37 - P6.2 */
	T3B2,          /* 38 - P6.1 */
	T3B1,          /* 39 - P6.0 */
	T1B2,          /* 40 - P2.1 */
	
	NOT_ON_TIMER,  /* 41 - P4.3 */
	NOT_ON_TIMER,  /* 42 - P4.2 */
	NOT_ON_TIMER,  /* 43 - P1.0 */
	NOT_ON_TIMER,  /* 44 - P6.6 */
	NOT_ON_TIMER,  /* 45 - P4.1 */
	NOT_ON_TIMER,  /* 46 - P2.3 */
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN,   /*  0 - pin count starts at 1 */
	NOT_A_PIN,   /*  1 - Vcc */
	P1,          /*  2 - P1.5 */
	P1,          /*  3 - P1.6 */
	P1,          /*  4 - P1.7 */
	P3,          /*  5 - P3.6 */
	P5,          /*  6 - P5.2 */
	P4,          /*  7 - P4.5 */
	P3,          /*  8 - P3.4 */
	P1,          /*  9 - P1.3 */
	P1,          /* 10 - P1.2 */
	P3,          /* 11 - P3.0 */
	P2,          /* 12 - P2.5 */
	P4,          /* 13 - P4.4 */
	P4,          /* 14 - P4.7 */
	P4,          /* 15 - P4.6 */
	NOT_A_PIN,   /* 16 - RST */
	P4,          /* 17 - P4.0 */
	P2,          /* 18 - P2.2 */
	P2,          /* 19 - P2.0 */
	NOT_A_PIN,   /* 20 - GND */

	NOT_A_PIN,   /* 21 - 5.0V */
	NOT_A_PIN,   /* 22 - GND */
	P1,          /* 23 - P1.4 */
	P5,          /* 24 - P5.3 */
	P5,          /* 25 - P5.1 */
	P5,          /* 26 - P5.0 */
	P5,          /* 27 - P5.4 */
	P1,          /* 28 - P1.1 */
	P3,          /* 29 - P3.5 */
	P3,          /* 30 - P3.1 */
	P3,          /* 31 - P3.2 */
	P3,          /* 32 - P3.3 */
	P2,          /* 33 - P2.4 */
	P3,          /* 34 - P3.7 */
	P6,          /* 35 - P6.4 */
	P6,          /* 36 - P6.3 */
	P6,          /* 37 - P6.2 */
	P6,          /* 38 - P6.1 */
	P6,          /* 39 - P6.0 */
	P2,          /* 40 - P2.1 */
	
	P4,          /* 41 - P4.3 */
	P4,          /* 42 - P4.2 */
	P1,          /* 43 - P1.0 */
	P6,          /* 44 - P6.6 */
	P4,          /* 45 - P4.1 */
	P2,          /* 46 - P2.3 */
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN,   /*  0 - pin count starts at 1 */
	NOT_A_PIN,   /*  1 - Vcc */
	BV(5),       /*  2 - P1.5 */
	BV(6),       /*  3 - P1.6 */
	BV(7),       /*  4 - P1.7 */
	BV(6),       /*  5 - P3.6 */
	BV(2),       /*  6 - P5.2 */
	BV(5),       /*  7 - P4.5 */
	BV(4),       /*  8 - P3.4 */
	BV(3),       /*  9 - P1.3 */
	BV(2),       /* 10 - P1.2 */
	BV(0),       /* 11 - P3.0 */
	BV(5),       /* 12 - P2.5 */
	BV(4),       /* 13 - P4.4 */
	BV(7),       /* 14 - P4.7 */
	BV(6),       /* 15 - P4.6 */
	NOT_A_PIN,   /* 16 - RST */
	BV(0),       /* 17 - P4.0 */
	BV(2),       /* 18 - P2.2 */
	BV(0),       /* 19 - P2.0 */
	NOT_A_PIN,   /* 20 - GND */

	NOT_A_PIN,   /* 21 - 5.0V */
	NOT_A_PIN,   /* 22 - GND */
	BV(4),       /* 23 - P1.4 */
	BV(3),       /* 24 - P5.3 */
	BV(1),       /* 25 - P5.1 */
	BV(0),       /* 26 - P5.0 */
	BV(4),       /* 27 - P5.4 */
	BV(1),       /* 28 - P1.1 */
	BV(5),       /* 29 - P3.5 */
	BV(1),       /* 30 - P3.1 */
	BV(2),       /* 31 - P3.2 */
	BV(3),       /* 32 - P3.3 */
	BV(4),       /* 33 - P2.4 */
	BV(7),       /* 34 - P3.7 */
	BV(4),       /* 35 - P6.4 */
	BV(3),       /* 36 - P6.3 */
	BV(2),       /* 37 - P6.2 */
	BV(1),       /* 38 - P6.1 */
	BV(0),       /* 39 - P6.0 */
	BV(1),       /* 40 - P2.1 */
	
	BV(3),       /* 41 - P4.3 */
	BV(2),       /* 42 - P4.2 */
	BV(0),       /* 43 - P1.0 */
	BV(6),       /* 44 - P6.6 */
	BV(1),       /* 45 - P4.1 */
	BV(3),       /* 46 - P2.3 */
};

const uint32_t digital_pin_to_analog_in[] = {
        NOT_ON_ADC,     /*  0 - pin count starts at 1 */
        NOT_ON_ADC,     /*  1 - Vcc */
        5,              /*  2 - P1.5 */
        6,              /*  3 - P1.6 */
        7,              /*  4 - P1.7 */
        NOT_ON_ADC,     /*  5 - P3.6 */
        10,             /*  6 - P5.2 */
        NOT_ON_ADC,     /*  7 - P4.5 */
        NOT_ON_ADC,     /*  8 - P3.4 */
        3,              /*  9 - P1.3 */
        2,              /* 10 - P1.2 */
        NOT_ON_ADC,     /* 11 - P3.0 */
        NOT_ON_ADC,     /* 12 - P2.5 */
        NOT_ON_ADC,     /* 13 - P4.4 */
        NOT_ON_ADC,     /* 14 - P4.7 */
        NOT_ON_ADC,     /* 15 - P4.6 */
        NOT_ON_ADC,     /* 16 - RST */
        NOT_ON_ADC,     /* 17 - P4.0 */
        NOT_ON_ADC,     /* 18 - P2.2 */
        NOT_ON_ADC,     /* 19 - P2.0 */
        NOT_ON_ADC,     /* 20 - GND */

        NOT_ON_ADC,     /* 21 - 5.0V */
        NOT_ON_ADC,     /* 22 - GND */
        4,              /* 23 - P1.4 */
        11,             /* 24 - P5.3 */
        9,              /* 25 - P5.1 */
        8,              /* 26 - P5.0 */
        NOT_ON_ADC,     /* 27 - P5.4 */
        1,              /* 28 - P1.1 */
        NOT_ON_ADC,     /* 29 - P3.5 */
        NOT_ON_ADC,     /* 30 - P3.1 */
        NOT_ON_ADC,     /* 31 - P3.2 */
        NOT_ON_ADC,     /* 32 - P3.3 */
        NOT_ON_ADC,     /* 33 - P2.4 */
        NOT_ON_ADC,     /* 34 - P3.7 */
        NOT_ON_ADC,     /* 35 - P6.4 */
        NOT_ON_ADC,     /* 36 - P6.3 */
        NOT_ON_ADC,     /* 37 - P6.2 */
        NOT_ON_ADC,     /* 38 - P6.1 */
        NOT_ON_ADC,     /* 39 - P6.0 */
        NOT_ON_ADC,     /* 40 - P2.1 */

        NOT_ON_ADC,     /* 41 - P4.3 */
        NOT_ON_ADC,     /* 42 - P4.2 */
        0,              /* 43 - P1.0 */
        NOT_ON_ADC,     /* 44 - P6.6 */
        NOT_ON_ADC,     /* 45 - P4.1 */
        NOT_ON_ADC,     /* 46 - P2.3 */
        
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
