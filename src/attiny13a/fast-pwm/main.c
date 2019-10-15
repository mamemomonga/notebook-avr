#include "main.h"
#include <avr/eeprom.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_pwm() {

	// Output: OC0B(PB1)
	DDRB |= (1<<PB1);

	// Mode7: Fast PWM
	// Compare Output Mode: Clear OC0B on Compare Match, set OC0B at TOP

	TCCR0A = (0<<COM0A1)|(0<<COM0A0)
	       | (1<<COM0B1)|(0<<COM0B0)
	       | (1<<WGM01)|(1<<WGM00);
	TCCR0B = (1<<WGM02);

// 小数点以下を含まない周波数
// デューティー比 50%

	TCCR0B |= (0<<CS02)|(1<<CS01)|(1<<CS00); // clkio/64
//	OCR0A=0x02; OCR0B=0x01;
//	OCR0A=0x04; OCR0B=0x02;
	OCR0A=0x0e; OCR0B=0x07;
//	OCR0A=0x18; OCR0B=0x0c;
//	OCR0A=0x4a; OCR0B=0x25;
//	OCR0A=0x7c; OCR0B=0x3e;

}

int main(void) {

	// 個体差によって微調整が必要
	OSCCAL=0x61;

	init_pwm();
	for(;;){
		_delay_ms(1000);
	}
	return 0;
}
