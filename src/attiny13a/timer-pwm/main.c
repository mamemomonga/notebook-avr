#include "main.h"
#include <util/delay.h>
#include <avr/interrupt.h>

// PWMの周波数
#define PWM_HZ 75

// タイマーカウンタ
uint8_t timer_ct0 = 0;

// 1秒カウンタ
uint8_t timer_ct0;
ISR(TIM0_COMPA_vect) {
	timer_ct0++;
	if(timer_ct0 == PWM_HZ) {
		LED1_I;
		timer_ct0=0;
	}
}

void init_timer(void) {
	// Mode2: CTC
	TCCR0A = (0<<COM0A1)|(0<<COM0A0)
	       | (0<<COM0B1)|(0<<COM0B0)
	       | (1<<WGM01)|(0<<WGM00);
	TCCR0B = (0<<WGM02);

	TCCR0B |= (1<<CS02)|(0<<CS01)|(1<<CS00); // clkio/1024
	OCR0A=0x7c; // 75Hz = 1秒間に75回割り込みがかかる

	// Timer/Counter Interrupt Mask Register
	// OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable
	TIMSK0 = (1<<OCIE0A);
}

int main(void) {

	// 初期化
	LED1_INIT;

	// 個体差によって微調整が必要
	OSCCAL=0x61;

	cli();
	init_timer();
	sei();

	for(;;){}
	return 0;
}

