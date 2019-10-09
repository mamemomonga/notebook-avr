#include "main.h"

int main(void) {
	LED1_INIT;
	LED1_L;

    for(;;){
		LED1_I;
		_delay_ms(500);
    }
    return 0;
}
