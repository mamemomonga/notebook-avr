#include "main.h"
#include "sr595.h"

int main(void) {

	sr595_init();
	LED_OUT;

    for(;;){
		LED_H;

		// Single 74HC595

//		sr595_write1(0xFF);
//		_delay_ms(500);
//
//		sr595_write1(0x00);
//		_delay_ms(500);
//
//		sr595_write1(0b10000000);
//		_delay_ms(500);
//
//		sr595_write1(0b01000000);
//		_delay_ms(500);
//
//		sr595_write1(0b00100000);
//		_delay_ms(500);
//
//		sr595_write1(0x00);

		// Dual 74HC595
		// Qhを二本目の74HC595のSRCLに入れる

		sr595_write2(0);
		_delay_ms(100);

		for(uint8_t i=0; i<16; i++) {
			sr595_write2(1<<i);
			_delay_ms(20);
		}
		for(uint8_t i=0; i<16; i++) {
			sr595_write2(1<<(16-i));
			_delay_ms(20);
		}
		LED_L;
    }

    return 0;
}


