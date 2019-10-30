#ifndef _SPI_H_
#define _SPI_H_

#include <stdio.h>

FILE* spi_wh; // SPIの書込ファイル
int spi_putchar(char c); // SPIに一文字送る
void spi_putstr(const char* c); // SPIに文字列を送る
void start_spi_master(void); // SPIをマスターモードで起動
void start_spi_slave(void); // SPIをスレーブモードで初期化
void stop_spi(void);

#endif
