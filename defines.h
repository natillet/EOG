/*
 * defines.h
 *
 *  Created on: Feb 7, 2013
 *      Author: qeledah
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/* System headers */
#include <msp430.h>
#include <string.h>

typedef unsigned int uint;
#define ALWAYS		1
#define TRUE		1
#define FALSE		0

// maximum length of a user-entered command
#define CMDLEN 12

// LEDs
#define LED_R		BIT0
#define LED_G		BIT6
#define LEDRG_OUT	P1OUT
#define LEDRG_DIR	P1DIR

// Buttons
#define BUTTON		BIT3

// UART
#define P1TX        BIT1        // Tx on P1.1
#define P1RX        BIT2        // Rx on P1.2
#define STR_LEN		12

// Timer counter to 1 second based on 1 MHz (2^16/1000000 = 0.065536 count up to 50000 20 times)
#define SEC_COUNT 20
// Timer counter to 1/10 second based on 1 MHz
#define TENTH_SEC 2

#endif /* DEFINES_H_ */
