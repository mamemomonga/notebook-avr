#include "spi.h"
#include "config.h"
#include "usart.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

static FILE spi_write_stream;

int spi_putchar(char c) {
	LED1_H;
	SPI_SS_L;
	SPDR = (uint8_t)c;
	while(!(SPSR & (1<<SPIF))); // 転送完了まで待つ
	SPI_SS_H;
	_delay_ms(1); // 1ミリ秒のディレイ
	LED1_L;
	return 0;
}

void spi_putstr(const char* c) {
	while (*c) spi_putchar(*c++);
}

static void init_spi_mode(void) {
	// SPCR: [3]CPOL, [2]CPHA
	// cfg2: [1]CPOL, [0]CPHA
	SPCR &=~ ((1<<CPOL)|(1<<CPHA));
	SPCR |= (cfg2 & 0b00000011) << 2;
}

static void init_spi_speed(void) {
	// SPSR: [0]SPI2X, SPCR: [1]SPR1, [0]SPR0
	// cfg2: [4]SPI2X, [3]SPR1, [2]SPR0
	SPSR &=~ (1<<SPI2X);
	SPSR |= (cfg2 >> 4) & 0b00000001;
	SPCR &=~ ((1<<SPR1)|(1<<SPR0));
	SPCR |= (cfg2 >> 2) & 0b00000011;
}

// USART -> SPI (SPI Master)
static void usart_read_spi(char c) {
	LED1_H;
	SPI_SS_L;
	SPDR = c; // SPIにUSARTをセット
	while(!(SPSR & (1<<SPIF))); // 転送完了まで待つ
	// スレーブから受け取ったSPIデータを表示する
	printf_P(PSTR("Slave: 0x%02x \r\n"),SPDR);
	SPI_SS_H;
	LED1_L;
}

// SPI -> USART (SPI Slave)
ISR(SPI_STC_vect) {
	LED1_H;
	uint8_t spdr=SPDR;
	loop_until_bit_is_set(UCSR0A, UDRE0);

	if(cfg1 & CFG1_DISPHEX) {
		printf_P(PSTR("0x%02x\r\n"),spdr);
	} else {
		// USART送信(表示)
		// \rがきたら、\r\nに変換する
		if(spdr == 0x0D) {
			printf_P(PSTR("\r\n"));
		} else {
			UDR0 = spdr;
		}
	}
	// 次回返信するデータ
	// 省略時は受け取ったデータがそのまま帰る
	// SPDR=0;

	_delay_ms(1); // 1ミリ秒のディレイ
	LED1_L;
}
 
void start_spi_master(void) {
	SPCR = 0; // SPI無効化
	DDRB &=~ (1 << PB4); // MISO(入力)
	DDRB |= (1<<PB3)|(1<<PB5); // MOSI(出力),SCK(出力)
	SPI_SS_MASTER; SPI_SS_H; // SSの設定
	SPCR = (1<<SPE)|(1<<MSTR); // SPE: SPI有効, マスターモード
	init_spi_mode();
	init_spi_speed();

	// SPI書込ストリームの設定
	spi_wh = &spi_write_stream;
	*spi_wh=(FILE)FDEV_SETUP_STREAM(spi_putchar, NULL,_FDEV_SETUP_WRITE);

	usart_read_cb=usart_read_spi;

	printf_P(PSTR("SPI MASTER MODE\r\n"));
	printf_P(PSTR("    CPOL:  %d\r\n"),( SPCR & (1<<CPOL))  ? 1 : 0 );
	printf_P(PSTR("    CPHA:  %d\r\n"),( SPCR & (1<<CPHA))  ? 1 : 0 );
	printf_P(PSTR("    SPI2X: %d\r\n"),( SPSR & (1<<SPI2X)) ? 1 : 0 );
	printf_P(PSTR("    SPR1:  %d\r\n"),( SPCR & (1<<SPR1))  ? 1 : 0 );
	printf_P(PSTR("    SPR0:  %d\r\n"),( SPCR & (1<<SPR0))  ? 1 : 0 );

}

void start_spi_slave(void) {
	SPCR = 0; // SPI無効化
	DDRB &=~ (1 << PB3)|(1<<PB5); // MOSI(出力),SCK(入力)
	DDRB |= (1<<PB4); // MISO(出力)
	SPI_SS_SLAVE; // SSの設定
	SPCR = (1<<SPE)|(1<<SPIE); // SPE: SPI有効 SPIE: SPI割り込み有効
	init_spi_mode();
	usart_read_cb=usart_read_default;
	printf_P(PSTR("SPI SLAVE MODE\r\n"));
}

void stop_spi(void) {
	SPCR = 0; // SPI無効化
	DDRB  &=~ ((1 << PB4)|(1<<PB3)|(1<<PB5)); // MISO(HiZ), MOSI(HiZ), SCK(HiZ)
	PORTB &=~ ((1 << PB4)|(1<<PB3)|(1<<PB5)); // PullUp Off
	SPI_SS_SLAVE;
}

