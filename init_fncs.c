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
	//P1DIR |= (LED_R | LED_G);
	//P1OUT &= ~(LED_R | LED_G);  // should be off already, but just be sure
	P1DIR |= LED_R;
	P1OUT &= ~LED_R;  // should be off already, but just be sure
}

void go_low_power(void)
{
	__bis_SR_register(LPM0_bits + GIE);
}

void setup_timer(void)
{
	CCTL0 = CCIE;                             // CCR0 interrupt enabled
	CCR0 = 50000;
	TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
}

void setup_ADC(void) {
    //16 x ADC10CLKs sample&hold time, turn on ADC, ADC interrupt enable
    ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;
    ADC10CTL1 = INCH_4;                       // input A1
    ADC10AE0 |= BIT4 | BIT5 | BIT6 | BIT7;    // PA.4/5/6/7 ADC option select
}


