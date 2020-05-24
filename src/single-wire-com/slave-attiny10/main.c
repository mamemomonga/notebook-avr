#include "main.h"
#include "config.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define SWC_STATE_NONE 0x00
#define SWC_STATE_S    0x01
#define SWC_STATE_R    0x02

#define DLY_A 10
#define DLY_B 50

uint8_t swc_data;
uint8_t swc_state;


void swc_recieve() {
	// Recieve
	swc_state = SWC_STATE_R;
	swc_data  = 0;
	uint8_t i = 8;
	while(i--) {
		uint8_t data=0;
		// -- Low --
		while(SER_IS_L);
		// -- High --
		while(SER_IS_H);
		// -- Low --
		_delay_us(DLY_A + 5);
		// -- Data --
		if(SER_IS_H) swc_data |= (1<<i);
		_delay_us(DLY_A+5);
		// -- High
		while(SER_IS_H);
	}
	while(SER_IS_L);
}

void low_high_wait_a() {
	SER_L; _delay_us(DLY_A);
	SER_H; _delay_us(DLY_A);
}


void swc_response() {
	// Response
	swc_state = SWC_STATE_S;
	uint8_t i = 8;

	SER_OUT; SER_H;
	_delay_us(100);

	while(i--) {
		low_high_wait_a();
		SER_L;
		uint8_t v=(swc_data>>i) & 1;
		_delay_us(DLY_A);
		// -- Data --
		if(v) { SER_H; } else { SER_L; }
		_delay_us(DLY_A);
		SER_H;
	}
	SER_H; _delay_us(DLY_A);
	low_high_wait_a();
	SER_IN;

}

void swc_process() {
	uint8_t read=0;
	swc_state  = SWC_STATE_NONE;

	// -- Low -- 割込 タイミング不定
	if(SER_IS_H) return;
	while(SER_IS_L);

	// -- High -- 準備OK
	_delay_us(DLY_B + 5);

	// -- 0:Write / 1:Read
	read = SER_IS_H;
	_delay_us(DLY_B + 5);

	// -- High --
	while(SER_IS_H);

	if(read) {
		swc_response();
	} else {
		swc_recieve();
	}
}


ISR(INT0_vect,ISR_BLOCK) {
	swc_process();
}

int main(void) {

	cli();

	// internal 8MHz
	CCP = 0xD8;
	CLKMSR = 0;

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;

	// External Interrupt Control Register A
	EICRA = 0;
	// External Interrupt Mask Register
	EIMSK = (1<<INT0);

	LED1_OUT;
	LED1_L;

	for(uint8_t i=0;i<20;i++) {
		LED1_I; _delay_ms(100);
	}

	sei();
	LED1_L;

    for(;;){
		LED1_I;
//		if(swc_state == SWC_STATE_R) {
//			LED1_L; _delay_ms(100);
//			for(uint8_t i=0; i<swc_data; i++) {
//				LED1_H;
//				_delay_ms(10);
//				LED1_L;
//				_delay_ms(50);
//			}
//			swc_state = SWC_STATE_NONE;
//			LED1_L; _delay_ms(100);
//		}
		_delay_ms(100);
    }
    return 0;
}
