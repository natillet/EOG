/*
 *  main.c
 *
 *  Created on: Feb 8, 2013
 *      Author: qeledah
 *
 * Program that takes commands via Async Serial, which could be useful for debugging.
 * LEDs are green when transmitting data, and red when receiving data.
 *
 * G2553 Pinout:
 * 1.0 - red status led
 * 1.1 - uart input
 * 1.2 - uart output
 * 1.6 - green status led
 *
 * On the MSP-EXP430G2 Rev 1.5 board "J3" jumpers for RXD and TXD *must* be horizontal!!
 *
 * No crystal is needed for this program!
 */

#include "defines.h"
#include "uart.h"
#include "init_fncs.h"
#include "adc.h"
#include <stdio.h> // snprintf()

uint i;
uint right;
uint left;
uint up;
uint down;
char str[STR_LEN];
int result;

void main()
{
	disable_watchdog();
    setup_clock();
    setup_usci();
    setup_leds();
    ADC_init();

    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 50000;
    TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

    right = 0;
    left = 0;
    up = 0;
    down = 0;

    /* Main program */
    serial_log("Electrooculogram Data\r\n");

    while (ALWAYS)
    {
    	right = read_adc(INCH_4);
    	left = read_adc(INCH_5);
    	up = read_adc(INCH_6);
    	down = read_adc(INCH_7);

    	result = snprintf(str, STR_LEN, "R: %d\tL: %d\tU: %d\tD: %d\r\n", right, left, up, down);
    	_NOP();

    	serial_log(str);
    	//serial_log("THINGS\r\n");

    	go_low_power();
    }
}

