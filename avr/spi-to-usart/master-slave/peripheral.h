#ifndef  _PERIPHERAL_H_
#define _PERIPHERAL_H_

#include <stdio.h>

typedef void (* T_CB_USART_READ)(char); // コールバックの型
T_CB_USART_READ uart_read_cb; // コールバック

void usart_send_char(char c); // USARTに一文字送る
void init_usart(void); // USART初期化

FILE* spi_wh; // SPIの書込ファイル
int spi_putchar(char c); // SPIに一文字送る
void spi_putstr(const char* c); // SPIに文字列を送る
void init_spi_master(void); // SPIをマスターモードで起動
void init_spi_slave(void); // SPIをスレーブモードで初期化

#endif
