#ifndef _USART_SERIAL_H_
#define _USART_SERIAL_H_

#include "config.h"

#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>

// BAUD と F_CPUマクロの設定が必要
// F_CPU は Makefile で設定

// BAUD は config.h で設定すること
// 未定義の場合は9600にする

#ifndef BAUD
#define BAUD 9600
#endif

// コールバックの型
typedef void (* T_USART_RECIEVE)(char);

// 受信:割込コールバックで何もしない
void usart_recieve_do_nothing(char c);

// 受信:割込有効とコールバックの設定
void usart_recieve_int_enable(T_USART_RECIEVE fp);

// 受信:割込無効
void usart_recieve_int_disable();

// 送信
void usart_send_char(char c);

// 初期化
void usart_init();

// 受信:文字入力
char usart_recieve_char();

#endif
