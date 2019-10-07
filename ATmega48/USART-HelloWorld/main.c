#include "main.h"
#include "libs/serial.h"

void usart_recieve(char buf) {
	LED1_H;
	printf("recieve: %c\r\n",buf);
	LED1_L;
}

int main(void) {

	LED1_INIT;
	LED1_H;
	serial_init(usart_recieve);
	sei();

	_delay_ms(1000);
	LED1_L;

	// printf_Pを使うとプログラムメモリからフォーマットを呼び出すことができる。
	printf_P(PSTR("\r\n --- start --- \r\n"));

	uint8_t count=0;
    for(;;){
		LED1_H;
		// 以下の cli() sei() はprint中に割り込みのprintが実行されると
		// 文字化けしてしまうので、それを防止するため。
		cli();
		printf_P(PSTR("Hello World! %2d\r\n"),count);
		sei();

		count++;
		_delay_ms(500);
		LED1_L;
	}

}
