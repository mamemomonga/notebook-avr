#include "main.h"
#include "config.h"
#include "usart.h"
#include "i2c.h"
#include "spi.h"
#include "setup.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

int main(void) {

	cli();
	FLG_ENTER_SETUP_INIT;
	LED1_INIT;
	init_usart();
	sei();

	printf_P(PSTR("------------------------------\r\n"));
	printf_P(PSTR(" Hello World! \r\n"));
	printf_P(PSTR("------------------------------\r\n"));


	_delay_ms(1000);

	LED1_L;
	setup_load();

	for(;;) {
		LED1_I;
		_delay_ms(500);
		setup_wc_enter();
	}
    return 0;
}

