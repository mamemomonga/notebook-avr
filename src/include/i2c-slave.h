#ifndef _I2C_SLAVE_H_
#define _I2C_SLAVE_H_

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "config.h"

#ifndef I2C_SLAVE_ADDR
#define I2C_SLAVE_ADDR 0x20
#endif

typedef uint8_t (* T_I2C_SLAVE_SEND)(uint8_t);
typedef void (* T_I2C_SLAVE_RECIEVE)(uint8_t, uint8_t);

void i2c_slave_init(T_I2C_SLAVE_SEND fp_send, T_I2C_SLAVE_RECIEVE fp_recv);
void i2c_slave_stop(void);

#endif
