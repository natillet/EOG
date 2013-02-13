/*
 * uart.c
 *
 *  Created on: Feb 7, 2013
 *      Author: qeledah
 */

#include "defines.h"
#include "uart.h"


void setup_usci(void)
{
	/* USCI Setup */
	P1SEL = P1TX + P1RX;                    // Set pin modes to USCI_A0
	P1SEL2 = P1TX + P1RX;                   // Set pin modes to USCI_A0
	P1DIR |= P1RX;                          // Set 1.2 to output

	UCA0CTL1 |= UCSSEL_2;                   // SMCLK (sub-main clock)
	//http://processors.wiki.ti.com/images/8/81/MSP430_USART_Baud_Rate.pdf
	UCA0BR0 = 104;                          // 1 MHz -> 9600 (1000000/9600=~104)
	UCA0BR1 = 0;                            // 1 MHz -> 9600 (1000000/9600=~104, but it all fit in the 2bytes of UCA0BR0, so just 0 here)
	UCA0MCTL = UCBRS1;                      // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**

	IE2 |= UCA0RXIE;                        // Enable USCI_A0 RX interrupt
}

