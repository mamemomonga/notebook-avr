#include "main.h"

#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIM0_COMPA_vect){
	LED1_I;
}

void init_timer(void) {
	// Mode4: CTC
	TCCR0A = (0<<COM0A1)|(0<<COM0A0)
	       | (0<<COM0B1)|(0<<COM0B0)
	       | (0<<WGM01)|(0<<WGM00);
	TCCR0B = (0<<WGM03)|(1<<WGM02);

	TCCR0B |= (0<<CS02)|(0<<CS01)|(1<<CS00); // clkio/1
	OCR0A=0xFF;

	// Timer/Counter Interrupt Mask Register
	// OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable
	TIMSK0 = (1<<OCIE0A);
}

int main(void) {
	// internal 8MHz
	// CCP = 0xD8;
	// CLKMSR = 0;

	// External clock(16MHz)
	CCP = 0xD8;
	CLKMSR = (1<<CLKMS1)|(0<<CLKMS0);

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;

	LED1_INIT;
	LED1_L;

	init_timer();
	sei();

    for(;;){
		_delay_ms(100);
    }
    return 0;
}
