#include "tSerial.h"

static t_serial_recieve fp_serial_recieve;

// INT0割り込み
ISR(INT0_vect,ISR_BLOCK) {
	fp_serial_recieve(RxByte());
}

void serial_send(const char* c) {
	while (*c) TxByte (*c++);
}

void serial_send_P(const char *p) {
	char c;
	while ((c=pgm_read_byte(p++)) != 0) TxByte (c);
}

void serial_init(t_serial_recieve fp_sr) {
	// コールバックの設定
	fp_serial_recieve = fp_sr;

	// INT0割り込み有効化
	cli();
	MCUCR |=  (1<<ISC01);
	MCUCR &=~ (1<<ISC00);
	GIMSK = (1<<INT0);
	sei();

}


