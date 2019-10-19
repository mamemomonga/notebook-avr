#include "main.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

/* --- USART --- */
static FILE usart_serialstream;
void usart_send_char(char c);

// USART割り込み
ISR(USART_RX_vect) {
	if(bit_is_clear(UCSR0A,FE0)){ // フレームエラーなし
		LED1_H;
		SPI_SS_L;
		SPDR = UDR0; // SPIにUSARTをセット
		while(!(SPSR & (1<<SPIF))); // 転送完了まで待つ
		SPI_SS_H;
		LED1_L;
	}
}

// USART初期化
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
	FILE* stream=&usart_serialstream;
	stdout=stream;
	*stream=(FILE)FDEV_SETUP_STREAM(usart_send_char, NULL, _FDEV_SETUP_WRITE);

}

void usart_send_char(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}
/* --- SPI --- */
void init_spi(void) {
	// MOSI,SCKの設定
	DDRB |= (1<<PB3)|(1<<PB5);

	// SSの設定
	SPI_SS_INIT;

	// SSをHIGH
	SPI_SS_H;

	// SPCR(SPI control register)
	//   SPE: SPI有効
	//   MSTR: マスターモード
	//   CPOL: 1, CPHA: 0 =  SPI MODE2
	//   Leading Edge: Falling / Trailing Edge: Rising
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL)
		|(1<<SPR1)|(1<<SPR0);
	// SPSR(SPI status register) fosc/64
	SPSR = (1<<SPI2X);
}

/* --- MAIN --- */
int main(void) {
	LED1_INIT;
	LED1_L;

	// 初期化
	cli();
	init_usart();
	init_spi();
	sei();

	_delay_ms(1000);
	LED1_L;

	printf_P(PSTR("\r\n --- start --- \r\n"));

    for(;;){
		_delay_ms(1000);
		LED1_I;
	}
    return 0;
}

