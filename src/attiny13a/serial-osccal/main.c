#include "main.h"
#include "tinySerial.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

void serial_recieve(const char c) {
	LED1_I;
	OSCCAL++;
	// スペース
	if(c == 0x20) {
		cli(); serOutP("OSCAL: 0x"); serOutInt8Hex(OSCCAL); serOutP("\r\n"); sei();
	}
}

int main(void) {
	LED1_INIT;
	LED1_L;

	OSCCAL=0;
	// シリアル割り込み有効
	serial_interrupt(serial_recieve);

	for(;;) {
		_delay_ms(500);
	}

}

