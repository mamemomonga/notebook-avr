#ifndef _SERIAL_USART_H_
#define _SERIAL_USART_H_

#include <avr/io.h>
#include <stdio.h>
#include "config.h"

// BAUD と F_CPUマクロの設定が必要
// F_CPU は Makefile で設定

// BAUD は config.h で設定すること
// 未定義の場合は9600にする

#ifndef BAUD
#define BAUD 9600
#endif

// コールバックの型
typedef void (* T_USART_RECIEVE)(char);

// 受信コールバックの設定
void usart_serial_recieve_cb(T_USART_RECIEVE fp);

// 送信
void usart_send_char(char c);

// 初期化
void usart_serial_init();

#endif
