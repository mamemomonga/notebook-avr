#include "i2c.h"
#include "config.h"
#include "usart.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/twi.h>

static uint8_t addr_device;
static uint8_t addr_data;

#define TWCR_ACK  TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA)
#define TWCR_NACK TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)

void start_i2c_slave(uint8_t addr_d) {
	// デバイスアドレス
	addr_device = addr_d;

	//  TWAR: TWI (Slave) Address Register
	//  末尾はTWGCEなので1つずらす
	TWAR = (addr_device << 1);

	TWAMR = 0x00;
	TWDR = 0xFF;

	// TWCR: TWI Control Register
	//    TWIE  割り込み有効
	//    TWINT 割り込みフラグ
	//    TWEN  TWI有効化
	//    TWEA  ACK有効
	TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);
}

void stop_i2c_slave(void) {
	TWCR &= ~((1<<TWEA) | (1<<TWEN));
}

ISR(TWI_vect){
	// TWSRからTWS* を取得
	switch(TWSR & 0xF8) {

	// 受信要求
	case TW_SR_SLA_ACK:
		addr_data = 0xFF;
		TWCR_ACK;
		break;

	// 受信したデータ
	case TW_SR_DATA_ACK:
		if(addr_data == 0xFF) {
			// データアドレスが空なら、それはデータアドレス
			addr_data = TWDR;
			TWCR_ACK;
		} else {
			TWCR_ACK;
			cb_i2c_recieve(addr_data, TWDR);
		}
		break;

	// 終了
	case TW_SR_STOP:
		TWCR_ACK;
		break;

	// 送信要求
	case TW_ST_SLA_ACK:
		TWDR = cb_i2c_send(addr_data);
		TWCR_ACK;
		break;

	// 8ビット以上の要求がきたときは0
	case TW_ST_DATA_ACK:
		TWDR = 0x00;
		TWCR_ACK;
		break;

	// よくわからんのはとりあえずACK
	default:
		TWCR_ACK;
		break;
	}
}

