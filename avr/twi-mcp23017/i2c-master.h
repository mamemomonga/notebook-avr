#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#include <avr/io.h>

// TWI bit mask
//   https://www.nongnu.org/avr-libc/user-manual/group__util__twi.html

// 初期化
void i2c_master_init(void);

// 0:ACK 1:NACK 他:エラー(TWI Bit mask)
uint8_t i2c_master_set(uint8_t, uint8_t, uint8_t);

// 0:ACK 1:NACK(エラー) 他:エラー(TWI Bit mask)
uint8_t i2c_master_get(uint8_t, uint8_t, uint8_t*);

#endif

