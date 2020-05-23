#include "i2c-slave.h"
#include "config.h"
#include <avr/interrupt.h>

#define I2C_WRITE_ADDR (I2C_ADDR<<1)
#define I2C_READ_ADDR  (I2C_WRITE_ADDR+1)

void i2c_init() {
	SDA_IN;
	SCL_IN;

#if defined (ATtiny13)
	// The low level of INT0 generates an interrupt request.
	MCUCR &=~ (1<<ISC01)|(1<<ISC00);
	// INT0: External Interrupt Request 0 Enable
	GIMSK |= (1<<INT0);
#endif

#if defined (ATtiny10)
	// External Interrupt Control Register A
	// INT0がLowのとき割込
	EICRA = 0;
	// External Interrupt Mask Register
	// INT0割込有効
	EIMSK = (1<<INT0);
#endif
	for(uint8_t i=0; i<sizeof(i2c_datas);i++) {
		i2c_datas[i]=0;
	}
}

void i2c_send_ack_nack() {
	SCL_IN;
	while(SCL_IS_L);
	while(SCL_IS_H);
}

uint8_t i2c_process() {
	// 読込
	uint8_t data=0;
	uint8_t i=8;
	SDA_IN;

	while(SCL_IS_L);
	while(i--) {
		uint8_t sdav=SDA_IS_H;
		while(SCL_IS_H) {
			// SCLがHIGHの間にSDAがLOWからHIGHに変わったらSTOPである
			if(!sdav && SDA_IS_H) {
				return 1;
			// SCLがHIGHの間にSDAがHIGHからLOWに変わったらSTARTである
			} else if (sdav && SDA_IS_L) {
				i2c_step = I2C_STEP_CHIP;
				return 0;
			}
		}
		// ビットの読込
		if(sdav) data |= (1<<i);
		// 最後はLOWが終わるのを待たない
		if(i > 0) while(SCL_IS_L);
	}
	// SCLはLOW, バスをビジーにして、ACK/NACKを送る準備
	SCL_OUT; SCL_L;

	// 分岐
	switch(i2c_step) {
		case I2C_STEP_CHIP:

			if(data == I2C_WRITE_ADDR) {
				i2c_step = I2C_STEP_ADDR;
				// ACK
				SDA_OUT; SDA_L;
				break;

			} else if (data == I2C_READ_ADDR) {
				i2c_step = I2C_STEP_SEND;
				// ACK
				SDA_OUT; SDA_L;
				break;

			} else {
				// NACK
				SDA_IN;
				break;
			}

		case I2C_STEP_ADDR:
			if( data > sizeof(i2c_datas)) {
				// NACK
				SDA_IN;
			} else {
				i2c_data_addr = data;
				// ACK
				SDA_OUT; SDA_L;
			}
			i2c_step=I2C_STEP_DATA;
			break;

		case I2C_STEP_DATA:
			i2c_step = I2C_STEP_RECV;
			i2c_datas[i2c_data_addr] = data;
			// ACK
			SDA_OUT; SDA_L;
			break;
	}

	// ビジーを解除して、ACK/NACKを送る
	i2c_send_ack_nack();

	if( i2c_step == I2C_STEP_SEND) {
		data=i2c_datas[i2c_data_addr];
		i=8;
		while(i--) {
			if( (data>>i) & 1 ) { SDA_H; } else { SDA_L; }
			while(SCL_IS_L);
			while(SCL_IS_H);
		}
		// NACK
		i2c_send_ack_nack();
	}
	return 0;

}

ISR(INT0_vect,ISR_BLOCK) {
	// INT0でSDAのLowを検出しているので、Start Conditionが明確にはわからない
	if(SCL_IS_L) return;

	// 連続で32バイトまで繰り返すが
	// 読み込むのは最大3バイト(Chip + DataAddr + Data)なので、データは1バイト
	uint8_t ct = 32;
	i2c_step = I2C_STEP_CHIP;
	while(ct--) {
		while(SCL_IS_H);
		if( i2c_process() ) break;
	}
}

