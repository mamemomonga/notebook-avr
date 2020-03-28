#include "main.h"
#include "bb595.h"

int main(void) {

	bb595_init();
	LED_OUT;

    for(;;){
		LED_H;

		// Dual 74HC595
		// Qhを二本目の74HC595のSRCLに入れる

		bb595_write2(0);
		_delay_ms(100);

		for(uint8_t i=0; i<16; i++) {
			bb595_write2(1<<i);
			_delay_ms(50);
		}
		for(uint8_t i=0; i<16; i++) {
			bb595_write2(1<<(16-i));
			_delay_ms(50);
		}
		LED_L;
    }

    return 0;
}
