#include "main.h"
#include "config.h"
#include "tinySerial.h"
#include <util/delay.h>

#include <avr/interrupt.h>

uint8_t serial_int_flag=0;

ISR(INT0_vect,ISR_BLOCK) {
	serial_int_flag=1;
	LED_H;
}

void uart_int_init() {
	cli();
//	UART_INPU
	// INT0割り込み有効化
	MCUCR |=  (1<<ISC01);
	MCUCR &=~ (1<<ISC00);
	GIMSK = (1<<INT0);
	sei();
}

int main(void) {

	OSCCAL = 0x56;

	LED_OUT;
	LED_L;

	uart_int_init();

    for(;;){
		LED_L;

		serOutP("Hello World!\r\n");

		UART_INPU;
		serial_int_flag=0;
		_delay_ms(500);

		if(serial_int_flag) {
			serOutP("> ");
			_delay_ms(500);
			char rx=RxByte();
			_delay_ms(10);
			serOutC(rx);
			serOutP("\r\n");
		}

    }
    return 0;
}

