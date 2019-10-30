#ifndef _USART_H_
#define _USART_H_

// コールバックの型
typedef void (* T_CB_USART_READ)(char);

// コールバック
T_CB_USART_READ usart_read_cb;

// USARTに一文字送る
void usart_send_char(char c);

// USART初期
void init_usart(void);

void usart_read_default(char c);

#endif
