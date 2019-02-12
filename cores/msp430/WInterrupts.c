/*
  ************************************************************************
  *	WInterrupts.c
  *
  *	Arduino core files for MSP430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *
  ***********************************************************************
  Derived from:

  WInterrupts.c Part of the Wiring project - http://wiring.uniandes.edu.co

  Copyright (c) 2004-05 Hernando Barragan

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

  Modified 24 November 2006 by David A. Mellis
  Modified 1 August 2010 by Mark Sproul
*/

#include <inttypes.h>
#include <stdio.h>

#include "wiring_private.h"

#ifndef BV
#define BV(x) (1 << (x))
#endif

#define bit_pos(A) ((A) == 1u << 0 ? 0 \
: (A) == 1u << 1 ? 1 \
: (A) == 1u << 2 ? 2 \
: (A) == 1u << 3 ? 3 \
: (A) == 1u << 4 ? 4 \
: (A) == 1u << 5 ? 5 \
: (A) == 1u << 6 ? 6 \
: (A) == 1u << 7 ? 7 \
: 0)

#define NUM_INTS_PER_PORT 8
static volatile voidFuncPtr intFuncP1[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP1 = 0x00;
#if defined(PORT2_VECTOR)
static volatile voidFuncPtr intFuncP2[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP2 = 0x00;
#endif
#if defined(PORT3_VECTOR)
static volatile voidFuncPtr intFuncP3[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP3 = 0x00;
#endif
#if defined(PORT4_VECTOR)
static volatile voidFuncPtr intFuncP4[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP4 = 0x00;
#endif
#if defined(PORT5_VECTOR)
static volatile voidFuncPtr intFuncP5[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP5 = 0x00;
#endif
#if defined(PORT6_VECTOR)
static volatile voidFuncPtr intFuncP6[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP6 = 0x00;
#endif
#if defined(PORT7_VECTOR)
static volatile voidFuncPtr intFuncP7[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP7 = 0x00;
#endif
#if defined(PORT8_VECTOR)
static volatile voidFuncPtr intFuncP8[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP8 = 0x00;
#endif
#if defined(PORT9_VECTOR)
static volatile voidFuncPtr intFuncP9[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP9 = 0x00;
#endif
#if defined(PORT10_VECTOR)
static volatile voidFuncPtr intFuncP10[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP10 = 0x00;
#endif
#if defined(PORT11_VECTOR)
static volatile voidFuncPtr intFuncP11[NUM_INTS_PER_PORT];
static volatile uint8_t intChangeVectP11 = 0x00;
#endif

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {
	uint8_t bit = digitalPinToBitMask(interruptNum);
	uint8_t port = digitalPinToPort(interruptNum);

	if ((port == NOT_A_PIN) || !((mode == FALLING) || (mode == RISING)
		|| (mode == CHANGE))) return;

	__dint();
	switch(port) {
	case P1:
		if(mode != CHANGE) {
			P1IES = mode ? P1IES | bit : P1IES & ~bit;
		} else {
			intChangeVectP1 |= bit;
			P1IES = (P1IN & bit) ? (P1IES | bit) : (P1IES & ~bit);
		}
		P1IFG &= ~bit;
		intFuncP1[bit_pos(bit)] = userFunc;
		P1IE |= bit;
		break;
	#if defined(PORT2_VECTOR)
	case P2:
		if(mode != CHANGE) {
			P2IES = mode ? P2IES | bit : P2IES & ~bit;
		} else {
			intChangeVectP2 |= bit;
			P2IES = (P2IN & bit) ? (P2IES | bit) : (P2IES & ~bit);
		}
		P2IFG &= ~bit;
		intFuncP2[bit_pos(bit)] = userFunc;
		P2IE |= bit;
		break;
	#endif
    #if defined(PORT3_VECTOR)
    case P3:
		if(mode != CHANGE) {
			P3IES = mode ? P3IES | bit : P3IES & ~bit;
		} else {
			intChangeVectP3 |= bit;
			P3IES = (P3IN & bit) ? (P3IES | bit) : (P3IES & ~bit);
		}
		P3IFG &= ~bit;
		intFuncP3[bit_pos(bit)] = userFunc;
		P3IE |= bit;
		break;
    #endif
    #if defined(PORT4_VECTOR)
    case P4:
		if(mode != CHANGE) {
			P4IES = mode ? P4IES | bit : P4IES & ~bit;
		} else {
			intChangeVectP4 |= bit;
			P4IES = (P4IN & bit) ? (P4IES | bit) : (P4IES & ~bit);
		}
		P4IFG &= ~bit;
		intFuncP4[bit_pos(bit)] = userFunc;
		P4IE |= bit;
		break;
    #endif
    #if defined(PORT5_VECTOR)
    case P5:
        if(mode != CHANGE) {
            P5IES = mode ? P5IES | bit : P5IES & ~bit;
        } else {
            intChangeVectP5 |= bit;
            P5IES = (P5IN & bit) ? (P5IES | bit) : (P5IES & ~bit);
        }
        P5IFG &= ~bit;
        intFuncP5[bit_pos(bit)] = userFunc;
        P5IE |= bit;
        break;
    #endif
    #if defined(PORT6_VECTOR)
    case P6:
        if(mode != CHANGE) {
            P6IES = mode ? P6IES | bit : P6IES & ~bit;
        } else {
            intChangeVectP6 |= bit;
            P6IES = (P6IN & bit) ? (P6IES | bit) : (P6IES & ~bit);
        }
        P6IFG &= ~bit;
        intFuncP6[bit_pos(bit)] = userFunc;
        P6IE |= bit;
        break;
    #endif
    #if defined(PORT7_VECTOR)
    case P7:
        if(mode != CHANGE) {
            P7IES = mode ? P7IES | bit : P7IES & ~bit;
        } else {
            intChangeVectP7 |= bit;
            P7IES = (P7IN & bit) ? (P7IES | bit) : (P7IES & ~bit);
        }
        P7IFG &= ~bit;
        intFuncP7[bit_pos(bit)] = userFunc;
        P7IE |= bit;
        break;
    #endif
    #if defined(PORT8_VECTOR)
    case P8:
        if(mode != CHANGE) {
            P8IES = mode ? P8IES | bit : P8IES & ~bit;
        } else {
            intChangeVectP8 |= bit;
            P8IES = (P8IN & bit) ? (P8IES | bit) : (P8IES & ~bit);
        }
        P8IFG &= ~bit;
        intFuncP8[bit_pos(bit)] = userFunc;
        P8IE |= bit;
        break;
    #endif
    #if defined(PORT9_VECTOR)
    case P9:
        if(mode != CHANGE) {
            P9IES = mode ? P9IES | bit : P9IES & ~bit;
        } else {
            intChangeVectP9 |= bit;
            P9IES = (P9IN & bit) ? (P9IES | bit) : (P9IES & ~bit);
        }
        P9IFG &= ~bit;
        intFuncP9[bit_pos(bit)] = userFunc;
        P9IE |= bit;
        break;
    #endif
    #if defined(PORT10_VECTOR)
    case P10:
        if(mode != CHANGE) {
            P10IES = mode ? P10IES | bit : P10IES & ~bit;
        } else {
            intChangeVectP10 |= bit;
            P10IES = (P10IN & bit) ? (P10IES | bit) : (P10IES & ~bit);
        }
        P10IFG &= ~bit;
        intFuncP10[bit_pos(bit)] = userFunc;
        P10IE |= bit;
        break;
    #endif
    #if defined(PORT11_VECTOR)
    case P11:
        if(mode != CHANGE) {
            P11IES = mode ? P11IES | bit : P11IES & ~bit;
        } else {
            intChangeVectP11 |= bit;
            P11IES = (P11IN & bit) ? (P11IES | bit) : (P11IES & ~bit);
        }
        P11IFG &= ~bit;
        intFuncP11[bit_pos(bit)] = userFunc;
        P11IE |= bit;
        break;
    #endif

    default:
		break;
	}

	__eint();
}

void detachInterrupt(uint8_t interruptNum) {
	uint8_t bit = digitalPinToBitMask(interruptNum);
	uint8_t port = digitalPinToPort(interruptNum);

	if (port == NOT_A_PIN) return;

	switch(port) {
	case P1:
		P1IE &= ~bit;
		intFuncP1[bit_pos(bit)] = 0;
		intChangeVectP1 &= ~(bit);
		break;
    #if defined(PORT2_VECTOR)
	case P2:
		P2IE &= ~bit;
		intFuncP2[bit_pos(bit)] = 0;
		intChangeVectP2 &= ~(bit);
		break;
	#endif
	#if defined(PORT3_VECTOR)
	case P3:
		P3IE &= ~bit;
		intFuncP3[bit_pos(bit)] = 0;
		intChangeVectP3 &= ~(bit);
		break;
	#endif
	#if defined(PORT4_VECTOR)
	case P4:
		P4IE &= ~bit;
		intFuncP4[bit_pos(bit)] = 0;
		intChangeVectP4 &= ~(bit);
		break;
	#endif
	default:
		break;
	}
}

__attribute__((interrupt(PORT1_VECTOR)))
void Port_1(void)
{
	uint8_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P1IFG & BV(i)) && intFuncP1[i]) {
			intFuncP1[i]();
			if(intChangeVectP1 & BV(i)) {
				P1IES ^= BV(i);
				P1IFG = ((P1IN & BV(i)) == (P1IES & BV(i))) ? \
					(P1IFG & ~BV(i)) : P1IFG;
			} else {
				P1IFG &= ~BV(i);
			}
		}
	}

	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}

#if defined(PORT2_VECTOR)
__attribute__((interrupt(PORT2_VECTOR)))
void Port_2(void)
{
	uint8_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P2IFG & BV(i)) && intFuncP2[i]) {
			intFuncP2[i]();
			if(intChangeVectP2 & BV(i)){
				P2IES ^= BV(i);
				P2IFG = ((P2IN & BV(i)) == (P2IES & BV(i))) ? \
					(P2IFG & ~BV(i)) : P2IFG;
			} else {
				P2IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT3_VECTOR)
__attribute__((interrupt(PORT3_VECTOR)))
void Port_3(void)
{
	uint8_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P3IFG & BV(i)) && intFuncP3[i]) {
			intFuncP3[i]();
			if(intChangeVectP3 & BV(i)){
				P3IES ^= BV(i);
				P3IFG = ((P3IN & BV(i)) == (P3IES & BV(i))) ? \
					(P3IFG & ~BV(i)) : P3IFG;
			} else {
				P3IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT4_VECTOR)
__attribute__((interrupt(PORT4_VECTOR)))
void Port_4(void)
{
	uint8_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P4IFG & BV(i)) && intFuncP4[i]) {
			intFuncP4[i]();
			if(intChangeVectP4 & BV(i)){
				P4IES ^= BV(i);
				P4IFG = ((P4IN & BV(i)) == (P4IES & BV(i))) ? \
					(P4IFG & ~BV(i)) : P4IFG;
			} else {
				P4IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT5_VECTOR)
__attribute__((interrupt(PORT5_VECTOR)))
void Port_5(void)
{
	uint8_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P5IFG & BV(i)) && intFuncP5[i]) {
			intFuncP5[i]();
			if(intChangeVectP5 & BV(i)){
				P5IES ^= BV(i);
				P5IFG = ((P5IN & BV(i)) == (P5IES & BV(i))) ? \
					(P5IFG & ~BV(i)) : P5IFG;
			} else {
				P5IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT6_VECTOR)
__attribute__((interrupt(PORT6_VECTOR)))
void Port_6(void)
{
	uint8_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P6IFG & BV(i)) && intFuncP6[i]) {
			intFuncP6[i]();
			if(intChangeVectP6 & BV(i)){
				P6IES ^= BV(i);
				P6IFG = ((P6IN & BV(i)) == (P6IES & BV(i))) ? \
					(P6IFG & ~BV(i)) : P6IFG;
			} else {
				P6IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT7_VECTOR)
__attribute__((interrupt(PORT7_VECTOR)))
void Port_7(void)
{
	uint8_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P7IFG & BV(i)) && intFuncP7[i]) {
			intFuncP7[i]();
			if(intChangeVectP7 & BV(i)){
				P7IES ^= BV(i);
				P7IFG = ((P7IN & BV(i)) == (P7IES & BV(i))) ? \
					(P7IFG & ~BV(i)) : P7IFG;
			} else {
				P7IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT8_VECTOR)
__attribute__((interrupt(PORT8_VECTOR)))
void Port_8(void)
{
	uint8_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P8IFG & BV(i)) && intFuncP8[i]) {
			intFuncP8[i]();
			if(intChangeVectP8 & BV(i)){
				P8IES ^= BV(i);
				P8IFG = ((P8IN & BV(i)) == (P8IES & BV(i))) ? \
					(P8IFG & ~BV(i)) : P8IFG;
			} else {
				P8IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT9_VECTOR)
__attribute__((interrupt(PORT9_VECTOR)))
void Port_9(void)
{
	uint9_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P9IFG & BV(i)) && intFuncP9[i]) {
			intFuncP9[i]();
			if(intChangeVectP9 & BV(i)){
				P9IES ^= BV(i);
				P9IFG = ((P9IN & BV(i)) == (P9IES & BV(i))) ? \
					(P9IFG & ~BV(i)) : P9IFG;
			} else {
				P9IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT10_VECTOR)
__attribute__((interrupt(PORT10_VECTOR)))
void Port_10(void)
{
	uint10_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P10IFG & BV(i)) && intFuncP10[i]) {
			intFuncP10[i]();
			if(intChangeVectP10 & BV(i)){
				P10IES ^= BV(i);
				P10IFG = ((P10IN & BV(i)) == (P10IES & BV(i))) ? \
					(P10IFG & ~BV(i)) : P10IFG;
			} else {
				P10IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif

#if defined(PORT11_VECTOR)
__attribute__((interrupt(PORT11_VECTOR)))
void Port_11(void)
{
	uint11_t i;
	boolean still_sleeping = stay_asleep;

	for(i = 0; i < 8; i++) {
		if((P11IFG & BV(i)) && intFuncP11[i]) {
			intFuncP11[i]();
			if(intChangeVectP11 & BV(i)){
				P11IES ^= BV(i);
				P11IFG = ((P11IN & BV(i)) == (P11IES & BV(i))) ? \
					(P11IFG & ~BV(i)) : P11IFG;
			} else {
				P11IFG &= ~BV(i);
			}
		}
	}
	if (stay_asleep != still_sleeping) {
		__bic_SR_register_on_exit(LPM4_bits);
	}
}
#endif
