/*
 * interrupts.c
 *
 *  Created on: Feb 8, 2013
 *      Author: qeledah
 */

#include "defines.h"
#include "uart.h"

int one_sec = SEC_COUNT;
uint ADCValue;

/*
 *
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR()
{
	if (one_sec > 0)
	{
		one_sec--;
	}
	else
	{
		//LEDRG_OUT ^= LED_G;
		//serial_log("\r\nPrinting things!\r\n");
		one_sec = 20;
		__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
	}
}

/*
 * Accept a command entered on the serial terminal
 */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR()
{
    P1OUT |= BIT0;  // red led
    char cmd[CMDLEN];
    uint i;

    /*
     *  UCA0RXIFG is high when UCA0RXBUF has received a complete character.
     *  However, it rarely stays high more than one byte at a time.  Perhaps
     *  because I type too slow on my keyboard.  Because of this all the
     *  commands are a single character for now.
     */
    for (i = 0; (IFG2 & UCA0RXIFG) && i < CMDLEN; i++) {
        cmd[i] = UCA0RXBUF; // get it out of the buffer before it is overwritten with new traffic
    } // keep checking the buffer until it is clear or we have 79 characters

    cmd[i] = '\0';  // last character always terminates the string

    P1OUT &= ~BIT0;

    /*
     * Parse command
     */
    if (strcmp(cmd, "h") == 0)          // help
        serial_log("\r\nHelp?  There is only one commmand: 'v'\r\n");
    else if (strcmp(cmd, "v") == 0)     // version
        serial_log("\r\nUart Debug 1.0 by Matthew Cashdollar <matthew@cashdollar.org>\r\n");
    else {
        serial_log("\r\nBad command: ");
        serial_log(cmd);
        serial_log("\r\nType 'h' for help.\r\n");
    }
}


// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
	ADCValue = ADC10MEM;			// Saves measured value
	__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

/*
#pragma vector=COMPARATORA_VECTOR
__interrupt void COMPARATORA_ISR()
{
    serial_log("Error!  Unhandled interrupt COMPARATORA_ISR!\r\n");
}

#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR()
{
    serial_log("Error!  Unhandled interrupt NMI_ISR!\r\n");
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR()
{
    serial_log("Error!  Unhandled interrupt PORT1_ISR!\r\n");
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR()
{
    serial_log("Error!  Unhandled interrupt PORT2_ISR!\r\n");
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
    serial_log("Error!  Unhandled interrupt TIMER0_A1_ISR!\r\n");
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR()
{
    serial_log("Error!  Unhandled interrupt TIMER0_A0_ISR!\r\n");
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR()
{
    serial_log("Error!  Unhandled interrupt TIMER1_A1_ISR!\r\n");
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR()
{
    // FIXME serial_log() probably won't work if UCA0TXIFG is configured as an
    // interrupt because it is used by serial_log() for character sending!
    serial_log("Error!  Unhandled interrupt USCIAB0TX_ISR!\r\n");
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR()
{
    serial_log("Error!  Unhandled interrupt WDT_ISR!\r\n");
}*/
