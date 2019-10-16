#include "main.h"
#include "tinySerial.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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

int main(void) {
	
	OSCCAL=0x62;
	adc1Init();

	uint8_t adcp=0;

	for(;;) {
		uint8_t adc = adc1ReadByte();
		if(adc != adcp) {
			serOutP("ADC1 Value: "); serOutInt8(adc); serOutP("\r\n");
			adcp = adc;
			_delay_ms(10);
		}
	}
}

