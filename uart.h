/*
 * uart.h
 *
 *  Created on: Feb 7, 2013
 *      Author: qeledah
 */

#ifndef UART_H_
#define UART_H_

void setup_usci(void);


/*
 * Send a log message to to the serial terminal
 */
inline void serial_log(const char *str)
{
    P1OUT |= BIT6;  // green led

    uint i;
    uint len = strlen(str);
    for (i = 0; i < len; i++) {
        // wait for TXBUF to complete last send...
        // UCA0TXIFG is high when UCA0TXBUF is empty
        while (!(IFG2 & UCA0TXIFG));
        UCA0TXBUF = str[i];
    }

    P1OUT &= ~BIT6;
}

#endif /* UART_H_ */
