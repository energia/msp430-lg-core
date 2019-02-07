#include "Energia.h"
#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__) \
 || defined(__MSP430_HAS_EUSCI_A0__)|| defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__) 
#include "usci_isr_handler.h"
/* This dummy function ensures that, when called from any module that 
 * is interested in having the USCIAB0TX_VECTOR and USCIAB0TX_VECTOR
 * installed, the linker won't strip the vectors.*/
void usci_isr_install(){}
__attribute__((weak))
uint16_t i2c_state_isr(){return 0;}
__attribute__((weak))
uint16_t i2c_txrx_isr(){return 0;}
__attribute__((weak))
uint16_t eusci_isr_handler(){return 0;}

__attribute__((weak))
void spi_rx_isr(uint16_t offset){return;}
__attribute__((weak))
void spi_tx_isr(uint16_t offset){return;}

static boolean still_asleep;  // Used to validate whether a user ISR has issued wakeup() inside LPM3/LPM4 sleep modes.

#if defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__) || defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__) || defined(__MSP430_HAS_EUSCI_A2__) || defined(__MSP430_HAS_EUSCI_A3__)
#ifndef USCI_UART_UCRXIFG
#define USCI_UART_UCRXIFG USCI_UCRXIFG
#endif
#ifndef USCI_UART_UCTXIFG
#define USCI_UART_UCTXIFG USCI_UCTXIFG
#endif

#if defined(__MSP430_BASEADDRESS_EUSCI_A1__) && defined(__MSP430_BASEADDRESS_EUSCI_A0__)
#define XUSCI_A1_OFFSET (__MSP430_BASEADDRESS_EUSCI_A1__ - __MSP430_BASEADDRESS_EUSCI_A0__)
#endif
#if defined(__MSP430_BASEADDRESS_USCI_A1__) && defined(__MSP430_BASEADDRESS_USCI_A0__)
#define XUSCI_A1_OFFSET (__MSP430_BASEADDRESS_USCI_A1__ - __MSP430_BASEADDRESS_USCI_A0__)
#endif
#if defined(__MSP430_BASEADDRESS_EUSCI_A2__) && defined(__MSP430_BASEADDRESS_EUSCI_A0__)
#define XUSCI_A2_OFFSET (__MSP430_BASEADDRESS_EUSCI_A2__ - __MSP430_BASEADDRESS_EUSCI_A0__)
#endif
#if defined(__MSP430_BASEADDRESS_EUSCI_A3__) && defined(__MSP430_BASEADDRESS_EUSCI_A0__)
#define XUSCI_A3_OFFSET (__MSP430_BASEADDRESS_EUSCI_A3__ - __MSP430_BASEADDRESS_EUSCI_A0__)
#endif

#if defined(__MSP430_BASEADDRESS_EUSCI_B1__) && defined(__MSP430_BASEADDRESS_EUSCI_B0__)
#define XUSCI_B1_OFFSET (__MSP430_BASEADDRESS_EUSCI_B1__ - __MSP430_BASEADDRESS_EUSCI_B0__)
#endif
#if defined(__MSP430_BASEADDRESS_USCI_B1__) && defined(__MSP430_BASEADDRESS_USCI_B0__)
#define XUSCI_B1_OFFSET (__MSP430_BASEADDRESS_USCI_B1__ - __MSP430_BASEADDRESS_USCI_B0__)
#endif

#if defined(__MSP430_BASEADDRESS_EUSCI_B2__) && defined(__MSP430_BASEADDRESS_EUSCI_B0__)
#define XUSCI_B2_OFFSET (__MSP430_BASEADDRESS_EUSCI_B2__ - __MSP430_BASEADDRESS_EUSCI_B0__)
#endif
#if defined(__MSP430_BASEADDRESS_USCI_B2__) && defined(__MSP430_BASEADDRESS_USCI_B0__)
#define XUSCI_B2_OFFSET (__MSP430_BASEADDRESS_USCI_B2__ - __MSP430_BASEADDRESS_USCI_B0__)
#endif

#if defined(__MSP430_BASEADDRESS_EUSCI_B3__) && defined(__MSP430_BASEADDRESS_EUSCI_B0__)
#define XUSCI_B3_OFFSET (__MSP430_BASEADDRESS_EUSCI_B3__ - __MSP430_BASEADDRESS_EUSCI_B0__)
#endif
#if defined(__MSP430_BASEADDRESS_USCI_B3__) && defined(__MSP430_BASEADDRESS_USCI_B0__)
#define XUSCI_B3_OFFSET (__MSP430_BASEADDRESS_USCI_B3__ - __MSP430_BASEADDRESS_USCI_B0__)
#endif

extern CHardwareSerial *Serial;
#ifdef SERIAL1_AVAILABLE
extern CHardwareSerial *Serial1;
#endif

__attribute__((interrupt(USCI_A0_VECTOR)))
void USCIA0_ISR(void)
{
	still_asleep = stay_asleep;

	switch ( UCA0IV )
	{
		case USCI_UART_UCRXIFG: uart_rx_isr(0); break;
		case USCI_UART_UCTXIFG: uart_tx_isr(0); break;
	}

	if (still_asleep != stay_asleep)
		__bic_SR_register_on_exit(LPM4_bits);
}

#if defined( __MSP430_HAS_USCI_A1__ ) || defined(__MSP430_HAS_EUSCI_A1__)
__attribute__((interrupt(USCI_A1_VECTOR)))
void USCIA1_ISR(void)
{
	still_asleep = stay_asleep;
	
	if (((UCA1CTLW0 & UCSYNC) == UCSYNC)){
		switch ( UCA1IV ) 
		{
			case USCI_UART_UCRXIFG: spi_rx_isr(XUSCI_A1_OFFSET); break;
			case USCI_UART_UCTXIFG: spi_tx_isr(XUSCI_A1_OFFSET); break;
		}  
	}else{
		switch ( UCA1IV ) 
		{
			case USCI_UART_UCRXIFG: uart_rx_isr(XUSCI_A1_OFFSET); break;
			case USCI_UART_UCTXIFG: uart_tx_isr(XUSCI_A1_OFFSET); break;
		}  
	}

	if (still_asleep != stay_asleep)
		__bic_SR_register_on_exit(LPM4_bits);
}
#endif

#if defined( __MSP430_HAS_USCI_A2__ ) || defined(__MSP430_HAS_EUSCI_A2__)
__attribute__((interrupt(USCI_A2_VECTOR)))
void USCIA2_ISR(void)
{
	still_asleep = stay_asleep;

	if (((UCA2CTLW0 & UCSYNC) == UCSYNC)){
		switch ( UCA2IV ) 
		{
			case USCI_UART_UCRXIFG: spi_rx_isr(XUSCI_A2_OFFSET); break;
			case USCI_UART_UCTXIFG: spi_tx_isr(XUSCI_A2_OFFSET); break;
		}  
	}else{
		switch ( UCA2IV ) 
		{
			case USCI_UART_UCRXIFG: uart_rx_isr(XUSCI_A2_OFFSET); break;
			case USCI_UART_UCTXIFG: uart_tx_isr(XUSCI_A2_OFFSET); break;
		}  
	}

	if (still_asleep != stay_asleep)
		__bic_SR_register_on_exit(LPM4_bits);
}
#endif

#if defined( __MSP430_HAS_USCI_A3__ ) || defined(__MSP430_HAS_EUSCI_A3__)
__attribute__((interrupt(USCI_A3_VECTOR)))
void USCIA3_ISR(void)
{
	still_asleep = stay_asleep;

	if (((UCA3CTLW0 & UCSYNC) == UCSYNC)){
		switch ( UCA3IV ) 
		{
			case USCI_UART_UCRXIFG: spi_rx_isr(XUSCI_A3_OFFSET); break;
			case USCI_UART_UCTXIFG: spi_tx_isr(XUSCI_A3_OFFSET); break;
		}  
	}else{
		switch ( UCA3IV ) 
		{
			case USCI_UART_UCRXIFG: uart_rx_isr(XUSCI_A3_OFFSET); break;
			case USCI_UART_UCTXIFG: uart_tx_isr(XUSCI_A3_OFFSET); break;
		}  
	}

	if (still_asleep != stay_asleep)
		__bic_SR_register_on_exit(LPM4_bits);
}
#endif

#endif //defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__) || defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__) || defined(__MSP430_HAS_EUSCI_A2__) || defined(__MSP430_HAS_EUSCI_A3__)

#if defined(__MSP430_HAS_USCI_B0__)
__attribute__((interrupt(USCI_B0_VECTOR)))
void USCIB0_ISR(void)
{
	still_asleep = stay_asleep;

	/* USCI_B0 I2C state change interrupt. */
	if ((UCB0CTL0 & UCMODE_3) == UCMODE_3 && (UCB0IFG & (UCALIFG | UCNACKIFG | UCSTTIFG | UCSTPIFG)) != 0)
		i2c_state_isr(); 
	/* USCI_B0 I2C TX RX interrupt. */
	if ((UCB0CTL0 & UCMODE_3) == UCMODE_3 && (UCB0IFG & (UCTXIFG | UCRXIFG)) != 0)
		i2c_txrx_isr();

	if (still_asleep != stay_asleep)
		__bic_SR_register_on_exit(LPM4_bits);
}
#endif
#if defined(__MSP430_HAS_USCI_B1__)
__attribute__((interrupt(USCI_B1_VECTOR)))
void USCIB1_ISR(void)
{
	still_asleep = stay_asleep;

	/* USCI_B1 I2C state change interrupt. */
	if ((UCB1CTL0 & UCMODE_3) == UCMODE_3 && (UCB1IFG & (UCALIFG | UCNACKIFG | UCSTTIFG | UCSTPIFG)) != 0)
		i2c_state_isr(); 
	/* USCI_B1 I2C TX RX interrupt. */
	if ((UCB1CTL0 & UCMODE_3) == UCMODE_3 && (UCB1IFG & (UCTXIFG | UCRXIFG)) != 0)
		i2c_txrx_isr();

	if (still_asleep != stay_asleep)
		__bic_SR_register_on_exit(LPM4_bits);
}
#endif

#if defined(__MSP430_HAS_EUSCI_B0__)
__attribute__((interrupt(USCI_B0_VECTOR)))
void USCIB0_ISR(void)
{
	if ((UCB0CTLW0 & UCMODE_3) == UCMODE_3)
    {
        if (eusci_isr_handler()) 
            __bic_SR_register_on_exit(LPM4_bits); // Exit LPM
    }else{
		switch ( UCB0IV ) 
		{
			case USCI_UART_UCRXIFG: spi_rx_isr(0); break;
			case USCI_UART_UCTXIFG: spi_tx_isr(0); break;
		}  
        
    }
}
#endif

#if defined(__MSP430_HAS_EUSCI_B1__)
__attribute__((interrupt(USCI_B1_VECTOR)))
void USCIB1_ISR(void)
{
	if ((UCB1CTLW0 & UCMODE_3) == UCMODE_3)
    {
        if (eusci_isr_handler()) 
            __bic_SR_register_on_exit(LPM4_bits); // Exit LPM
    }else{
		switch ( UCB1IV ) 
		{
			case USCI_UART_UCRXIFG: spi_rx_isr(XUSCI_B1_OFFSET); break;
			case USCI_UART_UCTXIFG: spi_tx_isr(XUSCI_B1_OFFSET); break;
		}  
        
    }
}
#endif

#if defined(__MSP430_HAS_EUSCI_B2__)
__attribute__((interrupt(USCI_B2_VECTOR)))
void USCIB2_ISR(void)
{
    if ((UCB2CTLW0 & UCMODE_3) == UCMODE_3)
    {
        if (eusci_isr_handler())
            __bic_SR_register_on_exit(LPM4_bits); // Exit LPM
    }else{
        switch ( UCB2IV )
        {
            case USCI_UART_UCRXIFG: spi_rx_isr(XUSCI_B2_OFFSET); break;
            case USCI_UART_UCTXIFG: spi_tx_isr(XUSCI_B2_OFFSET); break;
        }

    }
}
#endif

#if defined(__MSP430_HAS_EUSCI_B3__)
__attribute__((interrupt(EUSCI_B3_VECTOR)))
void USCIB3_ISR(void)
{
    if ((UCB3CTLW0 & UCMODE_3) == UCMODE_3)
    {
        if (eusci_isr_handler())
            __bic_SR_register_on_exit(LPM4_bits); // Exit LPM
    }else{
        switch ( UCB3IV )
        {
            case USCI_UART_UCRXIFG: spi_rx_isr(XUSCI_B3_OFFSET); break;
            case USCI_UART_UCTXIFG: spi_tx_isr(XUSCI_B3_OFFSET); break;
        }

    }
}
#endif

#ifdef __MSP430_HAS_USCI__
/* USCI_Ax and USCI_Bx share the same TX interrupt vector.
 * UART: 
 *	USCIAB0TX_VECTOR services the UCA0TXIFG set in UC0IFG.
 *	USCIAB0RX_VECTOR services the UCA0RXIFG set in UC0IFG.
 * I2C: 
 *	USCIAB0TX_VECTOR services both UCB0TXIFG and UCB0RXIFG
 *	set in UC0IFG.
 *	USCIAB0RX_VECTOR services the state change interrupts
 *	UCSTTIFG, UCSTPIFG, UCIFG, UCALIFG set in UCB0STAT.*/

__attribute__((interrupt(USCIAB0TX_VECTOR))) 
void USCIAB0TX_ISR(void)
{
	uint16_t stay_active = false;
	still_asleep = stay_asleep;

	/* USCI_A0 UART interrupt? */
	if (UC0IFG & UCA0TXIFG)
		uart_tx_isr(0);

	/* USCI_B0 I2C TX RX interrupt. */
	if ((UCB0CTL0 & UCMODE_3) == UCMODE_3 && (UC0IFG & (UCB0TXIFG | UCB0RXIFG)) != 0)
		stay_active = i2c_txrx_isr();

	if (still_asleep != stay_asleep || stay_active)
		__bic_SR_register_on_exit(LPM4_bits);
}

__attribute__((interrupt(USCIAB0RX_VECTOR)))
void USCIAB0RX_ISR(void)
{
	uint16_t stay_active = false;
	still_asleep = stay_asleep;

	/* USCI_A0 UART interrupt? */
	if (UC0IFG & UCA0RXIFG)
		uart_rx_isr(0);

	/* USCI_B0 I2C state change interrupt. */
	if ((UCB0STAT & (UCALIFG | UCNACKIFG | UCSTTIFG | UCSTPIFG)) != 0)
		stay_active = i2c_state_isr(); 

	if (still_asleep != stay_asleep || stay_active)
		__bic_SR_register_on_exit(LPM4_bits);
}
#endif // __MSP430_HAS_USCI__
#endif // entire file
