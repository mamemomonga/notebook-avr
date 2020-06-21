/* 
 * This code based on BasicSerial3.zip by Ralph Doncaster
 *   http://nerdralph.blogspot.com/2014/01/avr-half-duplex-software-uart.html
*/

#ifndef _TINYSERIAL_H_
#define _TINYSERIAL_H_

#include <avr/pgmspace.h>
#include "config.h"

// PROGMEM型のchar[]を送信
#define serOutP(a) { serial_send_P(PSTR(a)); }

// char[]を送信
#define serOutS(a) { serial_send(a); }

// charを送信
#define serOutC(a) { TxByte(a); }

// デフォルトボーレート
#ifndef BAUD
#define BAUD 38400
#endif

#ifdef F_CPU
	#define TXDELAY (((F_CPU/BAUD)-7 +1.5)/3)
	#define RXDELAY (((F_CPU/BAUD)-5 +1.5)/3)
	#define RXROUNDED (((F_CPU/BAUD)-5 +2)/3)
#else
	#error CPU frequency F_CPU undefined
#endif

#if RXROUNDED > 127
	#error low baud rates unsupported - use higher BAUD
#endif

#define TxByte(C) TxTimedByte(C , TXDELAY)
#define RxByte() RxTimedByte((RXDELAY*1.5)-2.5, RXDELAY)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	void serial_send(const char* c);
	void serial_send_P(const char *p);

	void TxTimedByte(char, char);
	char RxTimedByte(char, char);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
