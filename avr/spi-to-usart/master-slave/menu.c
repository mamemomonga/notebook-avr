#include "menu.h"
#include "config.h"

#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

// 指定した文字をフィルタリング 候補は最大32文字
static uint8_t usart_read_wait_match(char *buf) {
	uint8_t b[32]; int b_ct=0;
	while(*buf) { b[b_ct]=*buf++; b_ct++; }
	if(!bit_is_clear(UCSR0A,FE0)) return 0xFF;
	while (!(UCSR0A & (1<<RXC0)));
	uint8_t s = UDR0;
	for(uint8_t i=0; i< b_ct;i++) {
		if(s == b[i]) return s;
	}
	return 0xFF;
	
}
// 番号を選ぶ
static uint8_t select_num(uint8_t df, char *target) {
	uint8_t c=usart_read_wait_match(target);
	switch(c) {
	case 0xFF:
		printf_P(PSTR("\r\n"));
		return 0xFF;
	case 'd':
		return df;
	case 'c':
		printf_P(PSTR(" canceled\r\n\r\n"));
		return 0xFE;
	default:
		return (uint8_t)c-'0';
	}
}

void setup(void) {
	LED1_H;
	printf_P(PSTR("------------------------------\r\n"));
	printf_P(PSTR(" SETUP \r\n"));
	printf_P(PSTR("------------------------------\r\n"));

	/* MASTER-SLAVE */
	for(;;) {
		printf_P(PSTR("  MASTER-SLAVE:\r\n"));
		printf_P(PSTR("    0: SLAVE(default)\r\n"));
		printf_P(PSTR("    1: MASTER\r\n"));
		printf_P(PSTR("    c: cancel\r\n"));
		printf_P(PSTR("    d: default\r\n"));
		printf_P(PSTR(" > "));
		uint8_t r = select_num(0,"01cd");
		if(r == 0xFE) return;
		if(r == 0xFF) continue;
		cfg_master = r;
		switch(r) {
		case 0: printf_P(PSTR(" SLAVE\r\n\r\n")); break;
		case 1: printf_P(PSTR(" MASTER\r\n\r\n")); break;
		}
		break;
	}

	/* TEST-MODE */
	for(;;) {
		printf_P(PSTR("  TEST-MODE:\r\n"));
		printf_P(PSTR("    0: disable(default)\r\n"));
		printf_P(PSTR("    1: enable\r\n"));
		printf_P(PSTR("    c: cancel\r\n"));
		printf_P(PSTR("    d: default\r\n"));
		printf_P(PSTR(" > "));
		uint8_t r = select_num(0,"01cd");
		if(r == 0xFE) return;
		if(r == 0xFF) continue;
		cfg_test_mode = r;
		switch(r) {
		case 0: printf_P(PSTR(" Disable\r\n\r\n")); break;
		case 1: printf_P(PSTR(" Enable\r\n\r\n")); break;
		}
		break;
	}

	/* SPI-MODE */
	for(;;) {
		printf_P(PSTR("  SPI-MODE:\r\n"));
		printf_P(PSTR("    0: MODE0 CPOL=0, CPHA=0\r\n"));
		printf_P(PSTR("    1: MODE1 CPOL=0, CPHA=1\r\n"));
		printf_P(PSTR("    2: MODE2 CPOL=1, CPHA=0(default)\r\n"));
		printf_P(PSTR("    3: MODE3 CPOL=1, CPHA=1\r\n"));
		printf_P(PSTR("    c: cancel\r\n"));
		printf_P(PSTR("    d: default\r\n"));
		printf_P(PSTR(" > "));
		uint8_t r = select_num(2,"0123cd");
		if(r == 0xFE) return;
		if(r == 0xFF) continue;
		cfg_spi_mode = r;
		printf_P(PSTR(" SPI-MODE: %d\r\n\r\n"),cfg_spi_mode);
		break;
	}

	/* SPI-SPEED */
	for(;;) {
		printf_P(PSTR("  SPI-SPEED:\r\n"));
		printf_P(PSTR("    0: fosc/2 \r\n"));
		printf_P(PSTR("    1: fosc/8\r\n"));
		printf_P(PSTR("    2: fosc/16\r\n"));
		printf_P(PSTR("    3: fosc/32(default)\r\n"));
		printf_P(PSTR("    4: fosc/64\r\n"));
		printf_P(PSTR("    5: fosc/128\r\n"));
		printf_P(PSTR("    c: cancel\r\n"));
		printf_P(PSTR("    d: default\r\n"));
		printf_P(PSTR(" > "));
		uint8_t r = select_num(3,"012345cd");
		if(r == 0xFE) return;
		if(r == 0xFF) continue;
		cfg_spi_speed = r;
		printf_P(PSTR(" SPI-SPEED: %d\r\n\r\n"),cfg_spi_speed);
		break;
	}

	eeprom_busy_wait();
	eeprom_update_byte((uint8_t *)EEP_MASTER,cfg_master);

	eeprom_busy_wait();
	eeprom_update_byte((uint8_t *)EEP_TEST_MODE,cfg_test_mode);

	eeprom_busy_wait();
	eeprom_update_byte((uint8_t *)EEP_SPI_MODE,cfg_spi_mode);

	eeprom_busy_wait();
	eeprom_update_byte((uint8_t *)EEP_SPI_SPEED,cfg_spi_speed);

	eeprom_busy_wait();
	eeprom_update_byte((uint8_t *)EEP_CONFIGURED,0x01);

	printf_P(PSTR(" SAVE EEPROM\r\n"));

	return;
}

void config_load(void) {

	for(;;) {
		eeprom_busy_wait();
		if(eeprom_read_byte((uint8_t *)EEP_CONFIGURED) == 0x01) break; 
		setup();
	}

	printf_P(PSTR("------------------------------\r\n"));
	printf_P(PSTR(" CONFIG \r\n"));
	printf_P(PSTR("------------------------------\r\n"));

	cfg_master     = eeprom_read_byte((uint8_t *)EEP_MASTER);
	cfg_test_mode  = eeprom_read_byte((uint8_t *)EEP_TEST_MODE);
	cfg_spi_mode   = eeprom_read_byte((uint8_t *)EEP_SPI_MODE);
	cfg_spi_speed  = eeprom_read_byte((uint8_t *)EEP_SPI_SPEED);

	switch(cfg_master) {
	case 0: printf_P(PSTR("  MODE: SLAVE\r\n")); break;
	case 1: printf_P(PSTR("  MODE: MASTER\r\n")); break;
	}
	switch(cfg_test_mode) {
	case 0: printf_P(PSTR("  TEST-MODE: DISABLE\r\n")); break;
	case 1: printf_P(PSTR("  TEST-MODE: ENABLE\r\n")); break;
	}
	printf_P(PSTR("  SPI-MODE: %d\r\n"),cfg_spi_mode);
	switch(cfg_spi_speed) {
	case 0: printf_P(PSTR("  SPI-SPEED:\r\n")); break;
	case 1: printf_P(PSTR("  SPI-SPEED: fosc/2 \r\n")); break;
	case 2: printf_P(PSTR("  SPI-SPEED: fosc/8\r\n")); break;
	case 3: printf_P(PSTR("  SPI-SPEED: fosc/16\r\n")); break;
	case 4: printf_P(PSTR("  SPI-SPEED: fosc/32\r\n")); break;
	case 5: printf_P(PSTR("  SPI-SPEED: fosc/64\r\n")); break;
	case 6: printf_P(PSTR("  SPI-SPEED: fosc/128\r\n")); break;
	}
}

