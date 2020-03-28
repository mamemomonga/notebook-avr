#include "sr595.h"

static void sr595_write_chip(uint8_t b);
static void sr595_start();
static void sr505_end();

void sr595_init() {
	SR595_DDR |= (1 << SR595_MOSI | 1 << SR595_SCK | 1 << SR595_SS);
}

void sr595_start() {
	SR595_PORT &=~ (1<<SR595_MOSI | 1<<SR595_SS);
	SR595_PORT |=  (1<<SR595_SCK);
}

void sr595_end() {
	SR595_PORT &=~ (1<<SR595_MOSI);
	SR595_PORT |=  (1<<SR595_SS | 1<<SR595_SCK);
}

void sr595_write1(uint8_t b) {
	sr595_start();
	sr595_write_chip(b);
	sr595_end();	
}

void sr595_write2(uint16_t b) {

	sr595_start();
	sr595_write_chip(b & 0xFF);
	sr595_write_chip(( b >> 8 ) & 0xFF);
	sr595_end();	
}
