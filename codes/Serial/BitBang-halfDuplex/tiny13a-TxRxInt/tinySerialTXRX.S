/* 
 * This code based on BasicSerial3.zip by Ralph Doncaster
 *   http://nerdralph.blogspot.com/2014/01/avr-half-duplex-software-uart.html
*/

#include "config.h"

#define delayCount r18
#define UART_Port (PORTB - __SFR_OFFSET)

#ifndef UART_Rx
#define UART_Rx 1
#endif

#ifndef UART_Tx
#define UART_Tx 1
#endif

.global RxTimedByte
RxTimedByte:
	cbi UART_Port-1, UART_Rx
#ifdef RX_PULLUP
	sbi UART_Port, UART_Rx
#endif
	mov delayCount, r24
	ldi r24, 0x80
WaitStart:
	sbic UART_Port-2, UART_Rx
	rjmp WaitStart
	cli
RxBit:
	subi delayCount, 1
	brne RxBit

	mov delayCount, r22
	sbic UART_Port-2, UART_Rx
	sec
	ror r24
	brcc RxBit
StopBit:
	dec delayCount
	brne StopBit
	reti

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
