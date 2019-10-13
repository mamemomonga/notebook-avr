#include "main.h"

int main(void) {
	LED1_INIT;
	LED1_L;

	spi595_init();

	_delay_ms(1000);

	// 0番をオン
	spi595_state[0] = 1<<0;
	spi595_apply();
	_delay_ms(1000);

	// 7番をオン
	spi595_state[0] = 1<<7;
	spi595_apply();
	_delay_ms(1000);

    for(;;){

		// 流れる
		for(uint8_t i=0; i<8; i++) {
			LED1_I;
			spi595_state[0] = 1<<i;
			spi595_apply();
			_delay_ms(80);
		}

    }
    return 0;
}
