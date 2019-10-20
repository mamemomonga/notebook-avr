#include "main.h"
#include "config.h"
#include "peripheral.h"
#include "menu.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void init2() {
	if(cfg_master) {
		init_spi_master();
	} else {
		init_spi_slave();
	}
	if(cfg_test_mode) {
		// ここで処理されたことがわかるように、
		// リセット直後のSPDRの値に0x20をいれておく
		SPDR = 0x20;
	}
}

int main(void) {
	cli();
	LED1_INIT;
	LED1_H;
	FLG_ENTER_SETUP_INIT;

	init_usart();
	printf_P(PSTR("\r\n"));
	printf_P(PSTR("USART - SPI Utility\r\n"));

	config_load();
	init2();
	sei();

	for(;;) {
		if(!FLG_ENTER_SETUP_IS_H) {
			cli();
			setup();
			config_load();
			init2();
			sei();
		}
		if(cfg_test_mode) {
			if(cfg_master) {
				printf_P(PSTR("\r\nRUNNING: MASTER\r\n"));
				spi_putstr("MASTER: Hello World!(spi_putstr)\r\n");
				fprintf_P(spi_wh,PSTR("MASTER: Hello World!(fprintf_P)\r\n"));
			} else {
				printf_P(PSTR("\r\nRUNNING: SLAVE\r\n"));
			}
		}
		_delay_ms(5000);
	}
    return 0;
}

