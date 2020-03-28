#include "main.h"

uint8_t led_wait=0;

void menu_select(char b);
void menu(char b);

void menu_select(char b) {
	cli();
	switch(b) {
		case '1':
			printf_P(PSTR("1\r\n50msで点滅中\r\n"));
			led_wait=1;
			break;
		case '2':
			printf_P(PSTR("2\r\n100msで点滅中\r\n"));
			led_wait=2;
			break;
		case '3':
			printf_P(PSTR("3\r\n500msで点滅中\r\n"));
			led_wait=10;
			break;
		default:
			printf_P(PSTR("点滅しません\r\n"));
			led_wait=0;
			break;
	}
	printf_P(PSTR("何かキーを入力してください\r\n"));

	// キー入力でメニュー
	usart_serial_recieve_cb( menu );
	sei();

	// 何もしない
	if(led_wait == 0) {
		LED_L;
		for(;;) {
			_delay_ms(1000);
		}
	}

	// 点滅
	for(;;) {
		LED_I;
		for(uint8_t i=0;i<led_wait;i++) {
			_delay_ms(50);
		}
	}
}

void menu(char b) {
	cli();
	printf_P(PSTR("-- メニュー --\r\n"));
	printf_P(PSTR("  1: 50msでLED点滅\r\n"));
	printf_P(PSTR("  2: 100msでLED点滅\r\n"));
	printf_P(PSTR("  3: 500msでLED点滅\r\n"));
	printf_P(PSTR("  > "));

	// キー入力で点滅
	usart_serial_recieve_cb( menu_select );
	sei();

	LED_H;
	// 入力まち
	for(;;) { _delay_ms(1000); }
}

int main(void) {
	LED_OUT;
	LED_L;

	// 初期化と受信コールバックの設定
	cli();
	usart_serial_init();
	sei();
	menu(0);

	// メインのループはなし

    return 0;
}

