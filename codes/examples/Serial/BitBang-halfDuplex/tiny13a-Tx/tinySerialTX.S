/* 
 * This code based on BasicSerial3.zip by Ralph Doncaster
 *   http://nerdralph.blogspot.com/2014/01/avr-half-duplex-software-uart.html
*/

#include "config.h"

#define delayCount r18
#define UART_Port (PORTB - __SFR_OFFSET)

#ifndef UART_Tx
#define UART_Tx 1
#endif

.global TxTimedByte
TxTimedByte:
	cli
	sbi UART_Port-1, UART_Tx
	cbi UART_Port, UART_Tx
	in r0, UART_Port
	ldi r25, 3
TxLoop:
	mov delayCount, r22
TxDelay:
	dec delayCount
	brne TxDelay

	bst r24, 0
	bld r0, UART_Tx
	lsr r25
	ror r24
	out UART_Port, r0
	brne TxLoop
	reti
