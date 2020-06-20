#include "i2c-master.h"
#include <util/twi.h>

#define FG_NACK  0 
#define FG_ACK   1
#define FG_READ  0
#define FG_WRITE 1

void i2c_master_init(void) {
	TWCR = 0; // TWCR: TWI Control Register
	TWSR = (0<<TWPS1)|(0<<TWPS0); // prescaler: 1
	TWBR = 0x48; // F_SCL: 100.00 kHz
}

// rw = 0:Read/1:Write
static uint8_t i2c_start(uint8_t hwaddr, uint8_t rw) {
	// 停止
	TWCR = 0;
	// スタートコンディション送信
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	// 送信完了待機
	while (!(TWCR & (1<<TWINT)));
	// スタートコンディションの確認
	{
		uint8_t twsr = (TWSR & 0xF8);
		if (twsr != TW_START) return twsr;
	}
	// ハードウェアアドレスの設定(7ビット指定) ビット0はR/W
	TWDR = (hwaddr << 1) | rw;
	// ハードウェアアドレスの送信
	TWCR = (1<<TWINT) | (1<<TWEN);
	// 送信完了待機
	while (!(TWCR & (1<<TWINT)));
	// 結果(TW_*)
	return (TWSR & 0xF8);
}

// ストップビット送信
static void i2c_stop(void) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

// 0:ACK 1:NACK 他:エラー(TWI Bit mask)
static uint8_t i2c_send(uint8_t data) {
	// データの設定
	TWDR = data;
	// データ送信開始
	TWCR = (1<<TWINT) | (1<<TWEN);
	// 送信完了待機
	while( !(TWCR & (1<<TWINT)) );
	// 結果(TW_*)
	return (TWSR & 0xF8);
}

// 0:NACK / 1:ACK
static uint8_t i2c_read(uint8_t ack) {
	if(ack) {
		// ACK
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	} else {
		// NACK
		TWCR = (1<<TWINT)|(1<<TWEN);	
	}
	// 送信完了待機
	while( !(TWCR & (1<<TWINT)) );
	return TWDR;
}

uint8_t i2c_master_set(uint8_t device, uint8_t addr, uint8_t val) {
	uint8_t rv;
	rv = i2c_start(device,FG_READ);
	if(rv != TW_MT_SLA_ACK) return rv;

	rv = i2c_send(addr);
	if(rv != TW_MT_DATA_ACK) return rv;

	rv = i2c_send(val);
	switch(rv) {
	case TW_MT_DATA_NACK: break;
	case TW_MT_DATA_ACK:  break;
	default: return rv;
	}

	i2c_stop();
	return 0;
}

uint8_t i2c_master_get(uint8_t device, uint8_t addr, uint8_t* pval) {
	uint8_t rv;
	rv = i2c_start(device,FG_READ);
	if(rv != TW_MT_SLA_ACK) return rv;

	rv = i2c_send(addr);
	if(rv != TW_MT_DATA_ACK) return rv;

	rv = i2c_start(device,FG_WRITE);
	if(rv != TW_MR_SLA_ACK) return rv;

	*pval = i2c_read(FG_NACK);
	i2c_stop();
	return 0;
}

