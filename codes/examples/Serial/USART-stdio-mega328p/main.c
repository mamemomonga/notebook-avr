#include "main.h"
#include "config.h"
#include "usart.h"

#include <util/delay.h>

#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void usart_recieve(char buf) {
	LED_H;
	printf("Recieve: %c\r\n",buf);
	LED_L;
}

int main(void) {
	LED_OUT;
	LED_L;

	// 初期化と受信コールバックの設定
	cli();
	usart_init(usart_recieve);
	sei();

	_delay_ms(1000);
	LED_L;

	// printf_Pを使うとプログラムメモリからフォーマットを呼び出すことができる。
	printf_P(PSTR("\r\n --- START --- \r\n"));

	uint8_t count=0;
    for(;;){
		LED_H;
		// 以下の cli() sei() はprint中に割り込みのprintが実行されると
		// 文字化けしてしまうので、それを防止するため。
		cli();
		printf_P(PSTR("Hello World! %2d\r\n"),count);
		sei();
		LED_L;

		count++;
		_delay_ms(500);
	}

    return 0;
}
