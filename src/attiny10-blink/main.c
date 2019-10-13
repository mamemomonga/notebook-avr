#include "main.h"

int main(void) {
	// internal 8MHz
	CCP = 0xD8;
	CLKMSR = 0;

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;

	LED1_INIT;
	LED1_L;

    for(;;){
		LED1_I;
		_delay_ms(500);
    }
    return 0;
}
