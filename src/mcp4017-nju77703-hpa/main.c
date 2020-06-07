#include "main.h"
#include <util/delay.h>
#include "i2c-master-write.h"

uint8_t read_adc0() {
	ADCSRA |= (1<<ADIF);
	ADCSRA |= (1<<ADSC);
	loop_until_bit_is_set(ADCSRA, ADIF);
	return ADCL;
}

int main(void) {

	// internal 8MHz
	CCP = 0xD8;
	CLKMSR = 0;

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;

	i2c_send(0x00);

	// ----------------------
	// ADC0(PB0)
	// ----------------------
	// -- Digital Input Disable Register 0
	DIDR0 = (1<<ADC0D);
	// -- ADC Multiplexer Selection Register
	ADMUX = 0;
	// -- ADC Control and Status Register A
	// ADC Prescaler Select Bits
	ADCSRA = (1<<ADPS2);
	// ADC Enable
	ADCSRA |= (1<<ADEN);

	uint8_t adcpv=0;
    for(;;){
		uint8_t adc = read_adc0();
		if((adc > (adcpv+4)) || (adc < (adcpv-4))) {
			i2c_send(adc/2);
			adcpv = adc;
		}
		_delay_ms(10);
 	}
    return 0;
}
