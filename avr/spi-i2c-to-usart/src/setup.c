#include "setup.h"
#include "config.h"

#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

/* -------------------------------------------------- */

static uint8_t configured=0;

typedef uint8_t (* F_MENU_READ)(void);
typedef uint8_t (* F_MENU_SET)(uint8_t);

typedef struct {
	const char*  title;
	const char *const *list;
	const uint8_t num;
	const uint8_t def;
	F_MENU_READ  read;
	F_MENU_SET   set;
} MenuT;

/* -------------------------------------------------- */
/*  me_type                                           */
/* -------------------------------------------------- */
const char    me_type_t[] PROGMEM = "TYPE";
const char    me_type_0[] PROGMEM = "SPI Master";
const char    me_type_1[] PROGMEM = "SPI Slave";
const char    me_type_2[] PROGMEM = "I2C Master";
const char    me_type_3[] PROGMEM = "I2C Slave";
const uint8_t me_type_d   PROGMEM = 0;
const uint8_t me_type_n   PROGMEM = 3;
const char *const me_type_l[] PROGMEM = { me_type_0, me_type_1, me_type_2, me_type_3 };

static uint8_t me_type_r(void) {
	switch( 0b00001111 & (cfg1 >> 4)) {
	// 3:CFG1_I2C_MSTR 2:CFG1_I2C_EN 1:CFG1_SPI_MSTR 0:CFG1_SPI_EN
	case 0b00000011: return 0;
	case 0b00000001: return 1;
	case 0b00001100: return 2;
	case 0b00000100: return 3;
	default: return 0xFF;
	}
};

static uint8_t me_type_s(uint8_t cv) {
	switch(cv) {
	// 3:CFG1_I2C_MSTR 2:CFG1_I2C_EN 1:CFG1_SPI_MSTR 0:CFG1_SPI_EN
	case 0: cv = 0b00000011; break;
	case 1: cv = 0b00000001; break;
	case 2: cv = 0b00001100; break;
	case 3: cv = 0b00000100; break;
	default: return 0xFF;
	}
	cfg1 &=~ ( 0b00001111 << 4);
	cfg1 |= (cv << 4);
	return 0;
};

static MenuT me_type(void) {
	MenuT rv = { me_type_t, me_type_l, me_type_n, me_type_d, me_type_r, me_type_s };
	return rv;
};

/* -------------------------------------------------- */
/*  me_spim                                           */
/* -------------------------------------------------- */
const char    me_spim_t[]  PROGMEM = "SPI Mode";
const char    me_spim_0[]  PROGMEM = "MODE0: CPOL=0, CPHA=0";
const char    me_spim_1[]  PROGMEM = "MODE1: CPOL=0, CPHA=1";
const char    me_spim_2[]  PROGMEM = "MODE2: CPOL=1, CPHA=0";
const char    me_spim_3[]  PROGMEM = "MODE3: CPOL=1, CPHA=1";
const uint8_t me_spim_d    PROGMEM = 2;
const uint8_t me_spim_n    PROGMEM = 3;
const char *const me_spim_l[] PROGMEM = { me_spim_0, me_spim_1, me_spim_2, me_spim_3 };

static uint8_t me_spim_r(void) {
	switch( 0b00000011 & cfg2 ) {
	// 1:CPOL 0:CPHA
	case 0b00000000: return 0;
	case 0b00000001: return 1;
	case 0b00000010: return 2;
	case 0b00000011: return 3;
	default: return 0xFF;
	}
};

static uint8_t me_spim_s(uint8_t cv) {
	switch(cv) {
	// 1:CPOL 0:CPHA
	case 0: cv=0b00000000; break;
	case 1: cv=0b00000001; break;
	case 2: cv=0b00000010; break;
	case 3: cv=0b00000011; break;
	default: return 0xFF;
	}
	cfg2 &=~ 0b00000011;
	cfg2 |= cv;
	return 0;
};

static MenuT me_spim(void) {
	MenuT rv = { me_spim_t, me_spim_l, me_spim_n, me_spim_d, me_spim_r, me_spim_s };
	return rv;
};

/* -------------------------------------------------- */
/*  me_spis                                           */
/* -------------------------------------------------- */
const char    me_spis_t[] PROGMEM = "SPI Speed";
const char    me_spis_0[] PROGMEM = "fosc/2";
const char    me_spis_1[] PROGMEM = "fosc/4";
const char    me_spis_2[] PROGMEM = "fosc/8";
const char    me_spis_3[] PROGMEM = "fosc/16";
const char    me_spis_4[] PROGMEM = "fosc/32";
const char    me_spis_5[] PROGMEM = "fosc/64";
const char    me_spis_6[] PROGMEM = "fosc/128";
const uint8_t me_spis_d   PROGMEM = 4;
const uint8_t me_spis_n   PROGMEM = 6;
const char *const me_spis_l[] PROGMEM = { me_spis_0, me_spis_1, me_spis_2, me_spis_3, me_spis_4, me_spis_5, me_spis_6 };

static uint8_t me_spis_r(void) {
	switch( 0b00000111 & (cfg2 >> 2)) {
	// [2]SPI2X, [1]SPR1, [0]SPR0
	case 0b00000100: return 0; // fosc/2
	case 0b00000000: return 1; // fosc/4
	case 0b00000101: return 2; // fosc/8
	case 0b00000001: return 3; // fosc/16
	case 0b00000110: return 4; // fosc/32
	case 0b00000010: return 5; // fosc/64
	case 0b00000011: return 6; // fosc/128
	default: return 0xFF;
	}
};

static uint8_t me_spis_s(uint8_t cv) {
	switch(cv) {
	// [2]SPI2X, [1]SPR1, [0]SPR0
	case 0: cv=0b00000100; break; // fosc/2
	case 1: cv=0b00000000; break; // fosc/4
	case 2: cv=0b00000101; break; // fosc/8
	case 3: cv=0b00000001; break; // fosc/16
	case 4: cv=0b00000110; break; // fosc/32
	case 5: cv=0b00000010; break; // fosc/64
	case 6: cv=0b00000011; break; // fosc/128
	default: return 0xFF;
	};
	cfg2 &=~ ( 0b00000111 << 2 );
	cfg2 |= ( cv << 2 );
	return 0;
};

static MenuT me_spis(void) {
	MenuT rv = { me_spis_t, me_spis_l, me_spis_n, me_spis_d, me_spis_r, me_spis_s };
	return rv;
};

/* -------------------------------------------------- */

static void show_current(MenuT me) {
	char  buf[32];
	uint8_t cv = me.read();
	strcpy_P(buf, (char *)pgm_read_word(&(me.list[cv])));
	printf_P(PSTR("  %s\r\n"),buf);
}

static uint8_t menu_select(MenuT me) {
	char  buf[32];
	char* flg_cur;
	char* flg_def;
	uint8_t rv;

	uint8_t cv=me.def;
	if(configured) cv = me.read();
	if(cv == 0xFF) cv = me.def;

//	if(configured) printf_P(PSTR(" ***** configured *****\r\n"));
//	printf_P(PSTR(" ***** cfg1 0x%02x *****\r\n"),cfg1);

	for(;;) {
		strcpy_P(buf, me.title);
		printf_P(PSTR("[%s]\r\n"),buf);
		for (int i = 0; i <= me.num; i++) {
			strcpy_P(buf, (char *)pgm_read_word(&(me.list[i])));
			flg_cur=( cv == i ) ? "(c)" : "";
			flg_def=( me.def == i) ? "(d)" : "";
			printf_P(PSTR("   %d: %s %s%s\r\n"),i,buf,flg_cur,flg_def);
		}
		printf_P(PSTR("   d: default\r\n"));
		printf_P(PSTR("   c: current\r\n"));
		printf_P(PSTR("   x: cancel\r\n"));
		printf_P(PSTR(" > "));

		if(!bit_is_clear(UCSR0A,FE0)) { // フレームエラーあり
			printf_P(PSTR("\r\n\r\n"));
			continue;
		}

		while (!(UCSR0A & (1<<RXC0))); // USART入力待ち
		uint8_t c = UDR0; // USART入力

		switch(c){
		case 'd': rv=me.def; break;
		case 'c': rv=cv;     break;
		case 'x':
			printf_P(PSTR("CANCELED\r\n"));
			return 0xFF; // キャンセルは 0xFF
		default:
			rv=(uint8_t)c-'0'; // 文字コード0からの位置＝数字
			if(rv > me.num) { // 範囲外
				printf_P(PSTR("\r\n\r\n"));
				continue;
			}
			break;
		}
		strcpy_P(buf, (char *)pgm_read_word(&(me.list[rv])));
		printf_P(PSTR("%d %s\r\n\r\n"),rv,buf);
		_delay_ms(500);
		return me.set(rv);
	}
	return 0xFF;
}

/* -------------------------------------------------- */

static void setup(void) {
	cli();
	LED1_H;
	configured = !(cfg1 & CFG1_NCONFIG);

	printf_P(PSTR("------------------------------\r\n"));
	printf_P(PSTR(" SETUP \r\n"));
	printf_P(PSTR("------------------------------\r\n"));

	if(menu_select(me_type())) { sei(); return; }
	if(( cfg1 & CFG1_SPI_EN ) && ( cfg1 & CFG1_SPI_MSTR )) {
		if(menu_select(me_spim())) { sei(); return; }
		if(menu_select(me_spis())) { sei(); return; }
	}

	cfg1 &=~ CFG1_NCONFIG;
	eeprom_busy_wait();
	eeprom_update_byte((uint8_t *)CFG1_ADDR_EEP,cfg1);
	eeprom_busy_wait();
	eeprom_update_byte((uint8_t *)CFG2_ADDR_EEP,cfg2);

	sei();
}

void setup_load(void) {
	eeprom_busy_wait();
	cfg1 = eeprom_read_byte((uint8_t *)CFG1_ADDR_EEP);
	eeprom_busy_wait();
	cfg2 = eeprom_read_byte((uint8_t *)CFG2_ADDR_EEP);
	eeprom_busy_wait();
	cfg3 = eeprom_read_byte((uint8_t *)CFG3_ADDR_EEP);

	for(;;) {
		if(!(cfg1 & CFG1_NCONFIG)) break;
		setup();
	}
	printf_P(PSTR("------------------------------\r\n"));
	printf_P(PSTR(" CURRENT CONFIG \r\n"));
	printf_P(PSTR("------------------------------\r\n"));

//	printf_P(PSTR(" CFG1_NCONFIG: %s \r\n"),(cfg1 & CFG1_NCONFIG) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG1_SPI_EN: %s \r\n"),(cfg1 & CFG1_SPI_EN) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG1_SPI_MSTR: %s \r\n"),(cfg1 & CFG1_SPI_MSTR) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG1_I2C_EN: %s \r\n"),(cfg1 & CFG1_I2C_EN) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG1_I2C_MSTR: %s \r\n"),(cfg1 & CFG1_I2C_MSTR) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG2_CPOL: %s \r\n"),(cfg2 & CFG2_CPOL) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG2_CPHA: %s \r\n"),(cfg2 & CFG2_CPHA) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG2_SPR0: %s \r\n"),(cfg2 & CFG2_SPR0) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG2_SPR1: %s \r\n"),(cfg2 & CFG2_SPR1) ? "TRUE" : "FALSE");
//	printf_P(PSTR(" CFG2_SPI2X: %s \r\n"),(cfg2 & CFG2_SPI2X) ? "TRUE" : "FALSE");

	show_current(me_type());
	if(( cfg1 & CFG1_SPI_EN ) && ( cfg1 & CFG1_SPI_MSTR )) {
		show_current(me_spim());
		show_current(me_spis());
	}

}

uint8_t setup_wc_enter(void) {
	if (FLG_ENTER_SETUP_IS_H) return 0;
	setup(); setup_load();
	return 1;
}
