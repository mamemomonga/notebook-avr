#include "main.h"
#include "tinySerial.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

void serial_recieve(const char c) {
	LED1_I;
	cli(); serOutP("Recieve: ["); serOutC(c); serOutP("]\r\n"); sei();
}

int main(void) {
	LED1_INIT;
	LED1_L;

	// シリアル割り込み有効
	serial_interrupt(serial_recieve);

	// list_osccalを実行すると、文字化けとOSCCALリストが繰り返し出力される
	// 正しく表示されたリストの中から選択すると
	// シリアル入出力に最適な動作周波数に調整できる。
	// list_osccal();

	// list_osccalからOSCCALの値を設定する
	OSCCAL=0x62;
	
	_delay_ms(5000);
	cli(); serOutP("Current OSCCAL = 0x"); serOutInt8Hex(OSCCAL); serOutP("\r\n"); sei();
	LED1_L;

	for(;;) {
		LED1_I;
		serOutPB("Hello World\r\n");
		_delay_ms(500);
	}

}

void list_osccal(void) {
	for(;;) {
		for(uint8_t i=0;i<0x7f;i++) {
			OSCCAL=i;
			cli(); serOutP("OSCCAL = 0x"); serOutInt8Hex(i); serOutP("\r\n"); sei();
			_delay_ms(1);
		}
		for(uint8_t i=0;i<10;i++) {
			_delay_ms(1000);
		}
	}
}

