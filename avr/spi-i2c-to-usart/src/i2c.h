#ifndef _I2C_H_
#define _I2C_H_

#include <avr/io.h>

typedef uint8_t (* T_I2C_SEND)(uint8_t);
typedef void (* T_I2C_RECIEVE)(uint8_t, uint8_t);

T_I2C_RECIEVE cb_i2c_recieve;
T_I2C_SEND cb_i2c_send;

void start_i2c_master(void);
void start_i2c_slave(uint8_t);
void stop_i2c(void);

#endif
