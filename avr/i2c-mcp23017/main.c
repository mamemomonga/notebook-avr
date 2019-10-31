#include "main.h"
#include "i2c-master.h"

#include "usart.h"
#include <stdio.h>
#include <avr/pgmspace.h>

#include <avr/io.h>
#include <util/delay.h>

// MCP23017 ポートマルチプレクサ
// A0,A1,A2 をすべてGNDに接続すると、アドレスは0x20
#define MPX_ADDR   0x20
#define MPX_IODIRA 0x00
#define MPX_IODIRB 0x01
#define MPX_GPPUA  0x0c
#define MPX_GPPUB  0x0d
#define MPX_OLATA  0x14
#define MPX_OLATB  0x15
#define MPX_GPIOA  0x12
#define MPX_GPIOB  0x13

// MCP23017 リセット(ActiveLow)
// 周辺機器のリセット全体につかうとよいかも
#define MPX_RST      ( 1<<PC3 )
#define MPX_RST_INIT DDRC  |=  MPX_RST
#define MPX_RST_H    PORTC |=  MPX_RST
#define MPX_RST_L    PORTC &=~ MPX_RST

void handle_error(uint8_t rv) {
	if(rv) {
		printf_P(PSTR("ERROR: 0x%02x\r\n"),rv);
		for(;;) {LED1_I; _delay_ms(100); }
	}
}

void init(void) {

	// リセット
	MPX_RST_INIT;
	MPX_RST_L;
	_delay_ms(10);
	MPX_RST_H;
	_delay_ms(100);

	// i2c初期化
	i2c_master_init();

	// PortB 全て入力
	handle_error( i2c_master_set(MPX_ADDR, MPX_IODIRB, 0xFF) );
	_delay_ms(10);

	// PortB 全てプルアップ
	handle_error( i2c_master_set(MPX_ADDR, MPX_GPPUB, 0xFF) );
	_delay_ms(10);

	// PortA 全て出力
	handle_error( i2c_master_set(MPX_ADDR, MPX_IODIRA, 0x00) );
	_delay_ms(10);

	// PortA すべて点灯
	handle_error( i2c_master_set(MPX_ADDR, MPX_OLATA, 0xFF) );
	_delay_ms(1000);

	// PortAすべて消灯
	handle_error( i2c_master_set(MPX_ADDR, MPX_OLATA, 0x00) );
	_delay_ms(1000);
}

int main(void) {
	LED1_INIT;
	LED1_L;

	init();
	init_usart();

	printf_P(PSTR("Startup\r\n"));

	LED1_H;

	for(;;) {
		LED1_I;

		// PortA 点滅
		for(uint8_t i=0;i<8;i++) {
			handle_error( i2c_master_set(MPX_ADDR, MPX_OLATA, (1<<i)) );
			_delay_ms(50);
		}
		for(uint8_t i=0;i<8;i++) {
			handle_error( i2c_master_set(MPX_ADDR, MPX_OLATA, (1<<(7-i))) );
			_delay_ms(50);
		}

		// PortBの値を読む
		uint8_t val=0x00;
		handle_error( i2c_master_get(MPX_ADDR, MPX_GPIOB, &val) );
		printf_P(PSTR("GPIOB: 0x%02x\r\n"),val);

	}

    return 0;
}
