#include "main.h"
#include <util/delay.h>
#include "i2c-master-write.h"

int main(void) {
	// internal 8MHz
	CCP = 0xD8;
	CLKMSR = 0;

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;

	LED1_OUT;
	LED1_L;

    for(;;){
		LED1_H;
		i2c_send(0x00);
		_delay_ms(5000);
		LED1_L;
   		i2c_send(0x7F);
		_delay_ms(5000);
 	}
    return 0;
}
