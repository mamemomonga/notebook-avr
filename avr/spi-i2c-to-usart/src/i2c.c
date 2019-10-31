#include "i2c.h"
#include "config.h"
#include "usart.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/twi.h>

#include <stdio.h>
#include <avr/pgmspace.h>

static uint8_t addr_device;
static uint8_t addr_data;

#define F_SCL 100000UL
#define TWBR_PRESCALER 1
#define TWBR_VAL ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

#define TWCR_ACK  TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA)
#define TWCR_NACK TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)

void start_i2c_master(uint8_t addr_d) {
	printf_P(PSTR("*** I2C_MASTER ***\r\n"));

	// TWCR: TWI Control Register
	// リセット
	TWCR = 0;

	// TWBR: TWI Bit Rate Register
	TWBR = (uint8_t)TWBR_VAL;

	// TWCR: TWI Control Register
	//    TWINT: TWI Interrupt Flag
	//    TWSTA: TWI START Condition Bit
	//    TWEN:  TWI Enable Bit
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	// 転送完了を待つ
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the start condition was successfully transmitted
	if((TWSR & 0xF8) != TW_START){ return ; }
	
	// load slave address into data register
	TWDR = addr_d;
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the device has acknowledged the READ / WRITE mode
	uint8_t twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

}


void start_i2c_slave(uint8_t addr_d) {
	printf_P(PSTR("*** I2C_SLAVE ***\r\n"));

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

void stop_i2c(void) {
	TWCR &= ~((1<<TWEA) | (1<<TWEN));
}

ISR(TWI_vect){
	// TWSRからTWS* を取得
	switch(TWSR & 0xF8) {

	// Slave: 受信要求
	case TW_SR_SLA_ACK:
		addr_data = 0xFF;
		TWCR_ACK;
		break;

	// Slave: 受信したデータ
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

	// Slave: 終了
	case TW_SR_STOP:
		TWCR_ACK;
		break;

	// Slave: 送信要求
	case TW_ST_SLA_ACK:
		TWDR = cb_i2c_send(addr_data);
		TWCR_ACK;
		break;

	// Slave: 8ビット以上の要求がきたときは0
	case TW_ST_DATA_ACK:
		TWDR = 0x00;
		TWCR_ACK;
		break;

	// Slave: よくわからんのはとりあえずACK
	default:
		TWCR_ACK;
		break;
	}
}

