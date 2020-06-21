#include "main.h"
#include "config.h"
#include "tinySerial.h"
#include <util/delay.h>

int main(void) {

	OSCCAL = 0x56;

	LED_OUT;
	LED_L;

    for(;;){
		LED_I;
		serOutP("Hello World!\r\n");
		_delay_ms(500);
    }
    return 0;
}
