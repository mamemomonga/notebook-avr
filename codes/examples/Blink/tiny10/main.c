#include "main.h"
#include "config.h"

#include <util/delay.h>

int main(void) {

	// internal 8MHz
	CCP = 0xD8;
	CLKMSR = 0;

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;

	LED_OUT;
	LED_L;

    for(;;){
		LED_I;
		_delay_ms(500);
    }
    return 0;
}
