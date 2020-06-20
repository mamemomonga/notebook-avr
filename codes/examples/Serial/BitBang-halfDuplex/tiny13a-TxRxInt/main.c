#include "main.h"
#include "config.h"
#include "tinySerial.h"
#include <util/delay.h>

#include <avr/interrupt.h>

uint8_t serial_int_flag=0;

ISR(INT0_vect,ISR_BLOCK) {
	serial_int_flag=1;
}

// INT0割り込み有効化
void int0_init() {
	cli();
	MCUCR |=  (1<<ISC01);
	MCUCR &=~ (1<<ISC00);
	GIMSK = (1<<INT0);
	sei();
}

int main(void) {

	OSCCAL = 0x56;

	LED_OUT;
	LED_L;

	int0_init();

    for(;;){
		LED_I;
		serOutP("Hello World!\r\n");
		serial_int_flag=0;
		_delay_ms(500);
		if(serial_int_flag) {
			_delay_ms(100);
			serOutP("> ");
			char rx=RxByte();
			serOutC(rx);
			serOutP("\r\n");
			serial_int_flag=0;
		}

    }
    return 0;
}

