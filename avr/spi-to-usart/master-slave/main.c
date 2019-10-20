#include "main.h"
#include "config.h"
#include "peripheral.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>


/* --- MAIN --- */
int main(void) {
	cli();

	LED1_INIT;
	LED1_H;
	FLG_SPI_MASTER_INIT;
	init_usart();

	_delay_ms(1000);

	printf_P(PSTR("\r\n"));
	printf_P(PSTR("START: USART - SPI "));
	
	if(SPI_MODE_MASTER) {
		printf_P(PSTR("[MASTER] "));
		init_spi_master();
	} else {
		printf_P(PSTR("[SLAVE] "));
		init_spi_slave();
	}
	if(TEST_MODE_ON) {
		printf_P(PSTR("[TEST]\r\n"));
		// ここで処理されたことがわかるように、
		// リセット直後のSPDRの値に0x20をいれておく
		SPDR = 0x20;
	}
	printf_P(PSTR("\r\n"));

	sei();
	LED1_L;

    for(;;){
		_delay_ms(5000);
		if(TEST_MODE_ON) {
			if(SPI_MODE_MASTER) {
				printf_P(PSTR("\r\nRUNNING: MASTER\r\n"));
				spi_putstr("MASTER: Hello World!(spi_putstr)\r\n");
				fprintf_P(spi_wh,PSTR("MASTER: Hello World!(fprintf_P)\r\n"));
			} else {
				printf_P(PSTR("\r\nRUNNING: SLAVE\r\n"));
			}
		}
	}
    return 0;
}

