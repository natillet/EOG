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

uint i;

void main()
{
	disable_watchdog();
    setup_clock();
    setup_usci();
    setup_leds();

    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 50000;
    TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

    /* Main program */
    serial_log("Electrooculogram Data\r\n");
    go_low_power();

/*    while (ALWAYS)
    {
    	LEDRG_OUT ^= LED_G;
    	serial_log("Printing stuff!\r\n");
    	for (i=0; i<20; i++)
    		__delay_cycles(50000);
    }*/
}


