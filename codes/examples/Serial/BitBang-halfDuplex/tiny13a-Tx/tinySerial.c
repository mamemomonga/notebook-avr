#include "tinySerial.h"

void serial_send(const char* c) {
	while (*c) TxByte (*c++);
}

void serial_send_P(const char *p) {
	char c;
	while ((c=pgm_read_byte(p++)) != 0) TxByte (c);
}
