#ifndef _TINYSERIAL_H_
#define _TINYSERIAL_H_

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "config.h"

// デフォルトのボーレートは38400
#ifndef BAUD
#define BAUD 38400
#endif

#ifdef F_CPU
	/* account for integer truncation by adding 3/2 = 1.5 */
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

// PROGMEM型のchar[]を送信
#define serOutP(a) { serial_send_P(PSTR(a)); }

// char[]を送信
#define serOutS(a) { serial_send(a); }

// charを送信
#define serOutC(a) { TxByte(a); }

// uint8_tを文字列にして送信
#define serOutInt8(n)    { char buf[4]; itoa(n, buf, 10); serial_send(buf); }

// uint8_tを16進数にして送信
#define serOutInt8Hex(n) { char buf[4]; itoa(n, buf, 16); serial_send(buf); }

// ブロッキングしてserOutPを実行
#define serOutPB(a) { cli(); serOutP(a); sei(); }

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void TxTimedByte(char, char);
char RxTimedByte(char, char); /* 1.5 bit delay, 1 bit delay */

// コールバック型
typedef void (* t_serial_recieve)(const char);
// 割り込み有効
void serial_interrupt(t_serial_recieve fp_sr);

void serial_send(const char* c);
void serial_send_P(const char *p);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
