#include "bb595.h"

void bb595_write_chip(uint8_t b);
static void bb595_start();
static void bb595_end();

void bb595_init() {
	BB595_DDR |= (1 << BB595_MOSI | 1 << BB595_SCK | 1 << BB595_SS);
}

static void bb595_start() {
	BB595_PORT &=~ (1<<BB595_MOSI | 1<<BB595_SS);
	BB595_PORT |=  (1<<BB595_SCK);
}

static void bb595_end() {
	BB595_PORT &=~ (1<<BB595_MOSI);
	BB595_PORT |=  (1<<BB595_SS | 1<<BB595_SCK);
}

#if defined(BB595_SINGLE)
void bb595_write(uint8_t b) {
	bb595_start();
	bb595_write_chip(b);
	bb595_end();	
}
#endif

#if defined(BB595_DUAL)
void bb595_write(uint16_t b) {
	bb595_start();
	bb595_write_chip(b & 0xFF);
	bb595_write_chip(( b >> 8 ) & 0xFF);
	bb595_end();	
}
#endif
