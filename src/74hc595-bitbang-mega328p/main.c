#include "main.h"
#include "bb595.h"

int main(void) {

	bb595_init();
	LED_OUT;

    for(;;){
		LED_H;

		// Dual 74HC595
		// Qhを二本目の74HC595のSRCLに入れる

		bb595_write(0);
		_delay_ms(100);

		for(uint8_t i=0; i<16; i++) {
			bb595_write(1<<i);
			_delay_ms(50);
		}
		for(uint8_t i=0; i<16; i++) {
			bb595_write(1<<(16-i));
			_delay_ms(50);
		}

		for(uint8_t i=0; i<5; i++) {
			bb595_write(0b1010101010101010);
			_delay_ms(250);
			bb595_write(0b0101010101010101);
			_delay_ms(250);
		}

		for(uint8_t i=0; i<5; i++) {
			bb595_write(0b1111000011110000);
			_delay_ms(250);
			bb595_write(0b0000111100001111);
			_delay_ms(250);
		}

		for(uint8_t i=0; i<5; i++) {
			bb595_write(0b1100110011001100);
			_delay_ms(250);
			bb595_write(0b0011001100110011);
			_delay_ms(250);
		}
    }

    return 0;
}
