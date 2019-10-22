#include "main.h"

int main(void) {
	// 内臓 8MHz クロック
	CCP = 0xD8;
	CLKMSR = 0;
	// プリスケールなし 8MHz動作
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
