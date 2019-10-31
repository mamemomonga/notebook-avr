#include "main.h"
#include "i2c-master.h"

#include "usart.h"
#include <stdio.h>
#include <avr/pgmspace.h>

#include <avr/io.h>
#include <util/delay.h>

// MCP23017 ポートマルチプレクサ
// A0,A1,A2 をすべてGNDに接続すると、アドレスは0x20
#define PMPX_ADDR 0x20

#define PMPX_IODIRA 0x00
#define PMPX_IODIRB 0x01
#define PMPX_GPPUA  0x0c
#define PMPX_GPPUB  0x0d
#define PMPX_OLATA  0x14
#define PMPX_OLATB  0x15
#define PMPX_GPIOA  0x12
#define PMPX_GPIOB  0x13

void handle_error(uint8_t rv) {
	if(rv) {
		printf_P(PSTR("ERROR: 0x%02x\r\n"),rv);
		for(;;) {LED1_I; _delay_ms(100); }
	}
}

void init(void) {
	printf_P(PSTR("Startup\r\n"));

	// i2c初期化
	i2c_master_init();

	// PortA 全て出力
	handle_error( i2c_master_set(PMPX_ADDR, PMPX_IODIRA, 0x00) );

	// PortA すべて点灯
	handle_error( i2c_master_set(PMPX_ADDR, PMPX_OLATA, 0xFF) );

	// PortB 全て入力
	handle_error( i2c_master_set(PMPX_ADDR, PMPX_IODIRB, 0xFF) );

	// PortB 全てプルアップ
	handle_error( i2c_master_set(PMPX_ADDR, PMPX_GPPUB, 0xFF) );

	// PortAすべて消灯
	_delay_ms(1000);
	handle_error( i2c_master_set(PMPX_ADDR, PMPX_OLATA, 0x00) );

	_delay_ms(1000);
}

int main(void) {
	LED1_INIT;
	LED1_L;

	init_usart();
	init();

	printf_P(PSTR("Running\r\n"));
	LED1_H;

	for(;;) {
		LED1_I;

		// PortA 点滅
		for(uint8_t i=0;i<8;i++) {
			handle_error( i2c_master_set(PMPX_ADDR, PMPX_OLATA, (1<<i)) );
			_delay_ms(50);
		}
		for(uint8_t i=0;i<8;i++) {
			handle_error( i2c_master_set(PMPX_ADDR, PMPX_OLATA, (1<<(7-i))) );
			_delay_ms(50);
		}

		// PortBの値を読む
		uint8_t val=0x00;
		handle_error( i2c_master_get(PMPX_ADDR, PMPX_GPIOB, &val) );
		printf_P(PSTR("GPIOB: 0x%02x\r\n"),val);

	}

    return 0;
}
