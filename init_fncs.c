/*
 * init_fncs.c
 *
 *  Created on: Feb 7, 2013
 *      Author: qeledah
 */

#include "defines.h"

void disable_watchdog(void)
{
	WDTCTL = WDTPW + WDTHOLD;               // Stop WDT
}

void setup_clock(void)
{
	/* Clock Setup */
	BCSCTL1 = CALBC1_1MHZ;                  // Run at 1 MHz
	DCOCTL = CALDCO_1MHZ;                   // Run at 1 MHz
}

void setup_leds(void)
{
	/* LED Setup */
	P1DIR |= (LED_R | LED_G);
	P1OUT &= ~(LED_R | LED_G);  // should be off already, but just be sure
}

void go_low_power(void)
{
	__bis_SR_register(LPM0_bits + GIE);
}

