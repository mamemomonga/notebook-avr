#include "i2c-master-write.h"

void i2c_send_bit(uint8_t sda) {
	if(sda) { SDA_H; } else { SDA_L; }
	I2C_DELAY_S;
	SCL_H;
	I2C_DELAY_L;
	SCL_L;
	I2C_DELAY_S;
}

uint8_t i2c_read_ack() {
	SDA_IN;
	SCL_H;
	I2C_DELAY_L;
	uint8_t ack = SDA_IS_L;
	SCL_L;
	SDA_OUT;
	I2C_DELAY_S;
	return ack;
}

void i2c_send(uint8_t data) {
	SDA_OUT; SDA_H;
	SCL_OUT; SCL_H;

	uint8_t target=(I2C_TARGET_ADDR<<1); // Write
	uint8_t ct=8;

	I2C_DELAY_L;

	// START
	SDA_L;
	I2C_DELAY_L;
	SCL_L;
	I2C_DELAY_L;

	// ADDR 
	ct=8;
	while(ct--) i2c_send_bit((target >> ct) & 1 ? 1 : 0);
	I2C_DELAY_S;

	uint8_t ack=i2c_read_ack();
	if(ack) {
		// DATA
		ct=8;
		while(ct--) i2c_send_bit((data >> ct) & 1 ? 1 : 0);
		I2C_DELAY_S;
		i2c_read_ack();
	}

	// STOP
	I2C_DELAY_S;
	SCL_H;
	I2C_DELAY_S;
	SDA_H;
}

