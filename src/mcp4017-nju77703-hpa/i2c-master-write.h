#ifndef _MASTER_WRITE_H_
#define _MASTER_WRITE_H_

#include "config.h"
#include <util/delay.h>

#define I2C_DELAY_L _delay_us(10)
#define I2C_DELAY_S _delay_us(5)

void i2c_send(uint8_t data);

#endif
