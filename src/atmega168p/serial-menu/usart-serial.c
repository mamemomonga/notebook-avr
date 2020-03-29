#include "usart-serial.h"

static FILE usart_serialstream;
static T_USART_RECIEVE usart_recieve;

// USART割り込み
ISR(USART_RX_vect) {
	usart_recieve(usart_recieve_char());
}

// 受信:割込コールバックで何もしない
void usart_recieve_do_nothing(char c) {
	return;
}

// 受信:割込有効とコールバックの設定
void usart_recieve_int_enable(T_USART_RECIEVE fp) {
	// USART control and status register n B
	// RXCIEn: RX割り込み有効(USART_RXC_vect)
	// RXENn:  RX有効
	// TXENn:  TX有効
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);

	if(fp != NULL) {
		usart_recieve=fp;
	} else {
		usart_recieve=usart_recieve_do_nothing;
	}
}

// 受信:割込無効
void usart_recieve_int_disable() {
	// USART control and status register n B
	// RXENn:  RX有効
	// TXENn:  TX有効
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

// 受信:文字入力
char usart_recieve_char() {
	// データの到達を待つ
	while ( !(UCSR0A & (1<<RXC0)) );
	// フレームエラー
	if(!bit_is_clear(UCSR0A,FE0)) {
		return 0;
	}
	return UDR0;
}

// 送信
void usart_send_char(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

// 初期化
void usart_init() {

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

	usart_recieve_int_disable();

	// USART control and status register n C
	// UCSZn0, UCSZn1, UCSZn2: Character size
	// 0,1,1 = 8bit
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

	// stdoutをシリアルに設定
	FILE* stream=&usart_serialstream;
	stdout=stream;
	*stream=(FILE)FDEV_SETUP_STREAM(usart_send_char, NULL, _FDEV_SETUP_WRITE);
}

