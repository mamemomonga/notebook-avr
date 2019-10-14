#ifndef _TSERIAL_H_
#define _TSERIAL_H_

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "tinySerial.h"

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

// コールバックの型
typedef void (* t_serial_recieve)(const char);
// 初期化
void serial_init(t_serial_recieve fp_sr);

void serial_send(const char* c);
void serial_send_P(const char *p);

#endif
