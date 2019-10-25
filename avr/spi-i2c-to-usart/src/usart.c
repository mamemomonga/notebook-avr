#include "usart.h"
#include "config.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

static FILE usart_write_stream;

static void usart_read_default(char c) {
	return;
}

void init_usart(void) {
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

	// デフォルトのコールバック
	usart_read_cb=usart_read_default;

}
void usart_send_char(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0); // データレジスタが空になるのを待つ
	UDR0 = c; // USART送信
}

// USART割り込み(SPI Master)
ISR(USART_RX_vect) {
	if(bit_is_clear(UCSR0A,FE0)){ // フレームエラーなし
		usart_read_cb((char)UDR0);
	}
}

