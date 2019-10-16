#include "main.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ISR(TIM0_OVF_vect) {
ISR(TIM0_COMPA_vect) {
	PORTB ^= (CP|CN);
}

void init_timer(void) {
	// Mode2: CTC
	TCCR0A = (0<<COM0A1)|(0<<COM0A0)
	       | (0<<COM0B1)|(0<<COM0B0)
	       | (1<<WGM01)|(0<<WGM00);
	TCCR0B = (0<<WGM02);

	TCCR0B |= (0<<CS02)|(1<<CS01)|(1<<CS00); // clkio/64
	OCR0A=0x02; OCR0B=0x01; // 50Khz = 25KHz


	// Timer/Counter Interrupt Mask Register
	// OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable
	TIMSK0 = (1<<OCIE0A);
}

int main(void) {

	cli();

	CP_INIT; CN_INIT; LED_INIT;

	// 個体差によって微調整が必要
	OSCCAL=0x61;
	init_timer();
	sei();

	CP_H; CN_L; LED_L;

	for(;;){
		TIMSK0 &=~ (1<<OCIE0A);
		CP_L; CN_L; LED_L;

		for(uint8_t i=0;i<5;i++) {
			_delay_ms(1000);
		}

		CP_H; CN_L; LED_H;
		TIMSK0 |= (1<<OCIE0A);

		for(uint8_t i=0;i<30;i++) {
			_delay_ms(1000);
		}
	}
	return 0;
}

