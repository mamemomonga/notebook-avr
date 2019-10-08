#include "i2c-slave.h"

// コールバック
static T_I2C_SLAVE_SEND    fp_i2c_slave_send;
static T_I2C_SLAVE_RECIEVE fp_i2c_slave_recieve;

// データーアドレス
static uint8_t i2c_slave_dataaddr;

void i2c_slave_init(T_I2C_SLAVE_SEND fp_send, T_I2C_SLAVE_RECIEVE fp_recv) {

	fp_i2c_slave_send    = fp_send;
	fp_i2c_slave_recieve = fp_recv;

	//  TWAR: TWI (Slave) Address Register
	//  末尾はTWGCEなので1つずらす
	TWAR = (I2C_SLAVE_ADDR << 1);

	TWAMR = 0x00;
	TWDR = 0xFF;

	// TWCR: TWI Control Register
	//    TWIE  割り込み有効
	//    TWINT 割り込みフラグ
	//    TWEN  TWI有効化
	//    TWEA  ACK有効
	TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);

	// enable interrupt
	sei();

}

void i2c_slave_stop(void) {
	TWCR &= ~((1<<TWEA) | (1<<TWEN));
}

#define TWCR_ACK    TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA)
#define TWCR_NO_ACK TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)

ISR(TWI_vect){
	// TWSRからTWS* を取得
	switch(TWSR & 0xF8) {

	// 受信要求
	case TW_SR_SLA_ACK:
		i2c_slave_dataaddr = 0xFF;
		TWCR_ACK;
		break;

	// 受信したデータ
	case TW_SR_DATA_ACK:
		if(i2c_slave_dataaddr == 0xFF) {
			// データアドレスが空なら、それはデータアドレス
			i2c_slave_dataaddr = TWDR;
			TWCR_ACK;
		} else {
			TWCR_ACK;
			fp_i2c_slave_recieve(i2c_slave_dataaddr, TWDR);
		}
		break;

	// 終了
	case TW_SR_STOP:
		TWCR_ACK;
		break;

	// 送信要求
	case TW_ST_SLA_ACK:
		TWDR = fp_i2c_slave_send(i2c_slave_dataaddr);
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

