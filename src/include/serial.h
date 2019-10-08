#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <avr/io.h>
#include <stdio.h>
#include "config.h"

// BAUD と F_CPUマクロの設定が必要
// F_CPU は Makefile で設定
// BAUD は config.h で設定すること
// 未定義の場合は9600になる

#ifndef BAUD
#define BAUD 9600
#endif

// コールバックの型
typedef void (* T_USART_RECIEVE)(char);

// 初期化
// 受信用のコールバック関数を設定する
void usart_init(T_USART_RECIEVE fp_ur);

// 文字送信
void usart_send_char(char c);

#endif
