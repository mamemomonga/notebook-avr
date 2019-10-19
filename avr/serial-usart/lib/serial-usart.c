#include "serial-usart.h"
#include <stdio.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>

static FILE usart_serialstream;
static T_USART_RECIEVE fp_usart_recieve;

// USART割り込み
ISR(USART_RX_vect) {
	if(bit_is_clear(UCSR0A,FE0)){ // フレームエラーなし
		char buf=UDR0;
		fp_usart_recieve(buf);
	}
}

// 初期化
void init_usart(T_USART_RECIEVE fp_ur) {

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
	FILE* stream=&usart_serialstream;
	stdout=stream;
	*stream=(FILE)FDEV_SETUP_STREAM(usart_send_char, NULL, _FDEV_SETUP_WRITE);

	// シリアル入力時のコールバック
	if(fp_ur != NULL) {
		fp_usart_recieve=fp_ur;
	}

}

void usart_send_char(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

