#include "main.h"
#include "config.h"

#include <util/delay.h>

int main(void) {
	LED_OUT;
	LED_L;

    for(;;){
		LED_I;
		_delay_ms(500);
    }
    return 0;
}
