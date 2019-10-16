#include "main.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIM0_COMPA_vect) {
	// 出力の反転
	PORTB ^= (CP|CN);
}

void init_timer(void) {
	// Mode2: CTC
	TCCR0A = (0<<COM0A1)|(0<<COM0A0)
	       | (0<<COM0B1)|(0<<COM0B0)
	       | (1<<WGM01)|(0<<WGM00);
	TCCR0B = (0<<WGM02);

//	TCCR0B |= (0<<CS02)|(1<<CS01)|(1<<CS00); // clkio/64
//	OCR0A=0x02; OCR0B=0x01; // 割込: 50KHz 出力: 25KHz

	TCCR0B |= (0<<CS02)|(0<<CS01)|(1<<CS00); // clkio/1
	OCR0A=0x4a; OCR0B=0x25; // 割込: 128KHz 出力: 64kHz	

	// Timer/Counter Interrupt Mask Register
	// OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable
	TIMSK0 = (1<<OCIE0A);
}

int main(void) {

	cli();

	CP_INIT; CN_INIT; LED_INIT;

	OSCCAL=0x61;
	init_timer();
	sei();

	CP_H; CN_L; LED_L;

	for(;;){

		// チャージポンプOFF
		TIMSK0 &=~ (1<<OCIE0A);
		CP_L; CN_L; LED_L;

		// 10秒待機
		for(uint8_t i=0;i<10;i++) {
			_delay_ms(1000);
		}

		// チャージポンプON
		CP_H; CN_L; LED_H;
		TIMSK0 |= (1<<OCIE0A);

		// 10秒待機
		for(uint8_t i=0;i<30;i++) {
			_delay_ms(1000);
		}

	}
	return 0;
}

