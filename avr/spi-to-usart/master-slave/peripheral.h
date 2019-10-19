#ifndef  _PERIPHERAL_H_
#define _PERIPHERAL_H_

#include <stdio.h>

FILE usart_write_stream;
void usart_send_char(char c);
void init_usart(void);
void usart_send_char(char c);

#endif
