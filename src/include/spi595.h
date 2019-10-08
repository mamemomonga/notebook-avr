#ifndef _SPI595_H_
#define _SPI595_H_

#include <avr/io.h>
#include "config.h"

// 以下はconfig.hで設定可能
// ------------------
//   /SSのポート設定
#ifndef SPI595_SS_PIN
#define SPI595_SS_PIN PB2
#endif

#ifndef SPI595_SS_DDR
#define SPI595_SS_DDR DDRB
#endif

#ifndef SPI595_SS_PORT
#define SPI595_SS_PORT PORTB
#endif

//   75HC595 チップの数
#ifndef SPI595_CHIP_NUM
#define SPI595_CHIP_NUM 1
#endif
// ------------------

// /SSポートの設定
#define SPI595_SS      ( 1 << (SPI595_SS_PIN) )
#define SPI595_SS_INIT (SPI595_SS_DDR)  |=  SPI595_SS
#define SPI595_SS_H    (SPI595_SS_PORT) |=  SPI595_SS
#define SPI595_SS_L    (SPI595_SS_PORT) &=~ SPI595_SS

// 状態
uint8_t spi595_state[SPI595_CHIP_NUM-1];

// 初期化
void spi595_init(void);

// 反映
void spi595_apply(void);

#endif
