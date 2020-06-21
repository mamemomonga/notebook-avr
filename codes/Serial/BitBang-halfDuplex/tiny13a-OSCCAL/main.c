#include "main.h"
#include "config.h"
#include "tinySerial.h"
#include "tinySerialPlus.h"
#include <util/delay.h>

int main(void) {
	OSCCAL = 0x56;

	LED_OUT;
	LED_L;

	// 実行すると、文字化けとOSCCALリストが繰り返し出力される
	// 正しく表示されたリストの中から選択すると
	// シリアル入出力に最適な動作周波数に調整できる。
	for(;;) {
		LED_H;
		for(uint8_t i=0;i<0x7f;i++) {
			OSCCAL=i;
			serOutP("OSCCAL = 0x"); serOutInt8Hex(i); serOutP("\r\n");
			_delay_ms(1);
		}
		LED_L;
		for(uint8_t i=0;i<10;i++) {
			_delay_ms(1000);
		}
	}
    return 0;
}
