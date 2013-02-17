/*
 * adc.c
 *
 *  Created on: Feb 16, 2013
 *      Author: qeledah
 */

#include "defines.h"

extern uint ADCValue;

int read_adc(int channel) {
	int value = 0;

	ADC10CTL0 &= ~ENC;							// Disable ADC
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;	// 16 clock ticks, ADC On, enable ADC interrupt
	ADC10CTL1 = ADC10SSEL_3 + channel;			// Set channel, SMCLK
	ADC10CTL0 |= ENC + ADC10SC;					// Enable and start conversion

	__bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
	value = ADCValue;

	return value;
}
