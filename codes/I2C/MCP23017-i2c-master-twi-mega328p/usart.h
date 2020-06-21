#ifndef _USART_H_
#define _USART_H_

/*

	#include "usart.h"
	#include <stdio.h>
	#include <avr/pgmspace.h>

	int main(void) {
		init_usart();
		printf_P(PSTR("Hello Word!\r\n\r\n"));
	}

*/


// ボーレート
#define BAUD 38400

// コールバックの型
typedef void (* T_CB_USART_READ)(char);

// コールバック
T_CB_USART_READ usart_read_cb;

// USARTに一文字送る
void usart_send_char(char c);

// USART初期
void usart_init(void);

void usart_read_default(char c);

#endif
