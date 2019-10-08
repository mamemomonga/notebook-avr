#include "main.h"
#include "serial.h"
#include "i2c-slave.h"

void usart_recieve(char buf) {
	printf("\r\nRECIEVE: %c\r\n",buf);
}

void i2c_slave_recieve(uint8_t addr, uint8_t data) {
	// ここではシリアルが使える
	printf("\r\nI2C RECV: 0x%0X 0x%0X\r\n",addr, data);
}

uint8_t i2c_slave_send(uint8_t addr) {
	// スレーブアドレスに1くわえて返す
	// ここでシリアルを使うのは望ましくない
	return addr+1;
}

int main(void) {

	i2c_slave_init(i2c_slave_send, i2c_slave_recieve);
	usart_init(usart_recieve);
	sei();

	LED1_INIT;
	LED1_H;

	printf_P(PSTR("\r\nSTARTUP\r\n"));

	for(;;) {
		cli();
		LED1_I;
		printf_P(PSTR("."));
		sei();
		_delay_ms(500);
	}

}

