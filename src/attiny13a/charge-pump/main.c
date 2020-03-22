#include "main.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ISR(TIM0_OVF_vect) {
ISR(TIM0_COMPA_vect) {
	PORTB ^= (CLK1P|CLK2P|CLK1N|CLK2N);
}

void adc1Init(void) {
	// Digital Input Disable Register 0
	DIDR0 |= (1<<ADC1D); // ADC1(PB2)

	// ADC Multiplexer Selection Register
	//   REFS0: Reference Selection Bit
	//   ADLAR: ADC Left Adjust Result
	//   MUX0, MUX1: Analog Channel Selection Bits
	ADMUX = (1<<ADLAR)|(0<<MUX1)|(1<<MUX0); // Ref:Vcc, ADC1(PB2)

	// ADC Control and Status Register A
	ADCSRA = (1<<ADEN) // ADC Enable
	 | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // ADC Prescaler /128
}

uint8_t adc1ReadByte(void) {
	// ADC Control and Status Register A
	ADCSRA |= (1<<ADSC); // ADC Start Conversion
	loop_until_bit_is_set(ADCSRA,ADIF); // ADIFになるまで待つ
	return ADCH;
}

void init_timer(void) {
	// Mode2: CTC
	TCCR0A = (0<<COM0A1)|(0<<COM0A0)
	       | (0<<COM0B1)|(0<<COM0B0)
	       | (1<<WGM01)|(0<<WGM00);
	TCCR0B = (0<<WGM02);

	// TCCR0B |= (1<<CS02)|(0<<CS01)|(1<<CS00); // clkio/1024
	TCCR0B |= (0<<CS02)|(1<<CS01)|(0<<CS00); // clkio/8
	OCR0A=0x02; // 割り込み: 400kHz 出力: 200KHz

	// Timer/Counter Interrupt Mask Register
	// OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable
	TIMSK0 = (1<<OCIE0A);
}

int main(void) {

	cli();

	// シングルモードの場合はCLK1のみ有効にする
	// デキュアルモードならCLK2も有効にする
	CLK1P_OUT; CLK1N_OUT;
	CLK2P_OUT; CLK2N_OUT;

	// 個体差によって微調整が必要
	// オシレータの精度が不要な場合は設定不要
	OSCCAL=0x61;

	init_timer();
	adc1Init();

	CLK1P_H; CLK1N_L;
	CLK2P_H; CLK2N_L;

	sei();

	for(;;){
		uint8_t adcv = adc1ReadByte();
		if(adcv > COMP_OUTV) {
			TIMSK0 &=~ (1<<OCIE0A);  
		} else {
			TIMSK0 |= (1<<OCIE0A);  
		}
	}
	return 0;
}

