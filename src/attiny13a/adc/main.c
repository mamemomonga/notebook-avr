#include "main.h"
#include "tinySerial.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t adc1ReadByte(void) {
	// Digital Input Disable Register 0
	DIDR0 |= (1<<ADC1D); // ADC1(PB1)

	// ADC Multiplexer Selection Register
	//   REFS0: Reference Selection Bit
	//   ADLAR: ADC Left Adjust Result
	//   MUX0, MUX1: Analog Channel Selection Bits
	ADMUX = (1<<ADLAR)|(0<<MUX1)|(1<<MUX0); // Ref:Vcc, ADC1(PB1)

	// ADC Control and Status Register A
	ADCSRA = (1<<ADEN) // ADC Enable
	 | (1<<ADSC) // ADC Start Conversion
	 | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // ADC Prescaler /128

	loop_until_bit_is_set(ADCSRA,ADIF); // ADIFになるまで待つ

	return ADCH;
}

int main(void) {
	LED1_INIT;
	LED1_H;
	
	OSCCAL=0x60;

	for(;;) {
		LED1_I;
		serOutP("ADC1 Value:"); serOutInt8( adc1ReadByte() ); serOutP("\r\n");
		_delay_ms(500);
	}

}
