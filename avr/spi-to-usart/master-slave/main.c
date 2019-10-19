#include "main.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

/* --- USART --- */
static FILE usart_write_stream; // stdoutの実体

static void usart_send_char(char c);
static void init_usart(void) {
	// ボーレート設定(setbaud.hで設定)
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	// USART control and status register n A
	// U2Xn: 2xモード(setbaud.hで設定)
#if USE_2X
	UCSR0A |= (1<<U2X0);
#else
	UCSR0A &= ~((1<<U2X0));
#endif

	// USART control and status register n B
	// RXCIEn: RX割り込み有効(USART_RXC_vect)
	// RXENn:  RX有効
	// TXENn:  TX有効
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);

	// USART control and status register n C
	// UCSZn0, UCSZn1, UCSZn2: Character size
	// 0,1,1 = 8bit
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

	// stdoutをシリアルに設定
	FILE* stream=&usart_write_stream;
	*stream=(FILE)FDEV_SETUP_STREAM(usart_send_char, NULL, _FDEV_SETUP_WRITE);
	stdout=stream;

}
static void usart_send_char(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0); // データレジスタが空になるのを待つ
	UDR0 = c; // USART送信
}

// USART割り込み(SPI Master)
ISR(USART_RX_vect) {
	if(bit_is_clear(UCSR0A,FE0)){ // フレームエラーなし
		LED1_H;
		SPI_SS_L;
		SPDR = UDR0; // SPIにUSARTをセット
		while(!(SPSR & (1<<SPIF))); // 転送完了まで待つ
		// スレーブから受け取ったSPIデータを表示する
		printf_P(PSTR("From Slave: 0x%02x \r\n"),SPDR);
		SPI_SS_H;
		LED1_L;
	}
}

/* --- SPI --- */

static int spi_putchar(char c) {
	LED1_H;
	SPI_SS_L;
	SPDR = (uint8_t)c;
	while(!(SPSR & (1<<SPIF))); // 転送完了まで待つ
	SPI_SS_H;
	_delay_ms(1); // 1ミリ秒のディレイ
	return 0;
}

static void spi_putstr(const char* c) {
	while (*c) spi_putchar(*c++);
}


static FILE spi_ws = FDEV_SETUP_STREAM(spi_putchar, NULL,_FDEV_SETUP_WRITE);

static void init_spi_master(void) {
	SPCR = 0; // SPI無効化
	DDRB &=~ (1 << PB4); // MISO(入力)
	DDRB |= (1<<PB3)|(1<<PB5); // MOSI(出力),SCK(出力)
	SPI_SS_MASTER; SPI_SS_H; // SSの設定
	SPCR = (1<<SPE)|(1<<MSTR); // SPE: SPI有効, マスターモード
	SPI_MODE2; SPI_SCK_32; // 速度とモードの設定
}

static void init_spi_slave(void) {
	SPCR = 0; // SPI無効化
	DDRB &=~ (1 << PB3)|(1<<PB5); // MOSI(出力),SCK(入力)
	DDRB |= (1<<PB4); // MISO(出力)
	SPI_SS_SLAVE; // SSの設定
	SPCR = (1<<SPE)|(1<<SPIE); // SPE: SPI有効 SPIE: SPI割り込み有効
	SPI_MODE2; SPI_SCK_32; // 速度とモードの設定
}

// SPI割り込み(SPI Slave)
ISR(SPI_STC_vect) {
	LED1_H;
	loop_until_bit_is_set(UCSR0A, UDRE0);

// printf_P(PSTR("CHR: 0x%02x\r\n"),SPDR);

	// USART送信(表示)
	// \rがきたら、\r\nに変換する
	loop_until_bit_is_set(UCSR0A, UDRE0);
	if(SPDR == 0x0D) {
		printf_P(PSTR("\r\n"));
	} else {
		UDR0 = SPDR;
	}

	// テストモードの場合、
	// 割り込みがあったということは、前のSPDRの値はすでに送信されている
	// ここで処理したことがわかるように、受信したSPDRの値(ASCIIコード)に
	// 1くわえたものをSPDRレジスタにいれておく
	// 次回マスターから受信したときにこの値が送信される
	if(TEST_MODE_ON) SPDR = SPDR+1;

	LED1_L;
}

/* --- MAIN --- */
int main(void) {
	cli();

	LED1_INIT;
	LED1_H;
	FLG_SPI_MASTER_INIT;
	init_usart();

	_delay_ms(1000);

	printf_P(PSTR("\r\n"));
	printf_P(PSTR("START: USART - SPI "));
	
	if(SPI_MODE_MASTER) {
		printf_P(PSTR("[MASTER] "));
		init_spi_master();
	} else {
		printf_P(PSTR("[SLAVE] "));
		init_spi_slave();
	}
	if(TEST_MODE_ON) {
		printf_P(PSTR("[TEST]\r\n"));
		// ここで処理されたことがわかるように、
		// リセット直後のSPDRの値に0x20をいれておく
		SPDR = 0x20;
	}
	printf_P(PSTR("\r\n"));

	sei();
	LED1_L;

    for(;;){
		_delay_ms(5000);
		if(TEST_MODE_ON) {
			if(SPI_MODE_MASTER) {
				printf_P(PSTR("\r\nRUNNING: MASTER\r\n"));
				spi_putstr("MASTER: Hello World!(spi_putstr)\r\n");
				fprintf_P(&spi_ws,PSTR("MASTER: Hello World!(fprintf_P)\r\n"));
			} else {
				printf_P(PSTR("\r\nRUNNING: SLAVE\r\n"));
			}
		}
	}
    return 0;
}

