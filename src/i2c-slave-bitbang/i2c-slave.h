#ifndef _I2C_SLAVE_H_
#define _I2C_SLAVE_H_

#include <avr/io.h>

void i2c_init();
uint8_t i2c_datas[32];
uint8_t i2c_data_addr;

uint8_t i2c_step;

#define I2C_STEP_NONE 0x00
#define I2C_STEP_CHIP 0x01
#define I2C_STEP_ADDR 0x02
#define I2C_STEP_DATA 0x03
#define I2C_STEP_SEND 0x04
#define I2C_STEP_RECV 0x05

#endif
