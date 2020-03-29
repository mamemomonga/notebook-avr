#include "main.h"

void init() {
	cli();
	usart_init();
	sei();
}

int main(void) {
	init();
	for(;;) {
		menu();
		_delay_ms(50);
	}
}

// --------------------------------------------------------

void menu() {
	printf_P(PSTR("\r\n"));
	printf_P(PSTR("\r\n"));
	printf_P(PSTR("**************************************\r\n"));
	printf_P(PSTR("** MENU                             **\r\n"));
	printf_P(PSTR("**************************************\r\n"));
	printf_P(PSTR("  1: Hello World!\r\n"));
	printf_P(PSTR("  2: ACTION 2\r\n"));
	printf_P(PSTR("  3: ACTION 3\r\n"));
	printf_P(PSTR("  4: ACTION 4\r\n"));
	printf_P(PSTR("> "));
	char c;
	while(c == -1) {
		c = usart_recieve_char();
	}
	printf_P(PSTR("%c\r\n\r\n"),c);

	switch(c) {
		case '1':
			printf_P(PSTR("*** Hello World ***\r\n"));
			hello_world();
			break;
		case '2':
			printf_P(PSTR("*** ACTION 2 ***\r\n"));
			printf_P(PSTR("do nothing.\r\n"));
			break;
		case '3':
			printf_P(PSTR("*** ACTION 3 ***\r\n"));
			printf_P(PSTR("do nothing.\r\n"));
			break;
		case '4':
			printf_P(PSTR("*** ACTION 4 ***\r\n"));
			printf_P(PSTR("do nothing.\r\n"));
			break;
		default:
			break;
	}
	_delay_ms(500);
}

// --------------------------------------------------------

void hello_world() {
	printf_P(PSTR("*** Press any key to stop ***\r\n\r\n"));
	usart_recieve_int_enable(hello_world_int);
	action = 0;
	while(!action) {
		printf_P(PSTR("Hello World!\r\n"));
		_delay_ms(500);
	}
	printf_P(PSTR("\r\n*** STOP ***\r\n\r\n"));
}

void hello_world_int(char c) {
	action = 1;
	usart_recieve_int_disable();
}

