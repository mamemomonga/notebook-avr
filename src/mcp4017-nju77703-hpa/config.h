#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <avr/io.h>

/*
 ATtiny10 SOT32

ADC0 PB0 | 1   6 | PB3
     GND | 2   5 | VCC
SDA  PB1 | 3   4 | PB2 SCL

*/

#define SDA      ( 1<<PB1 )
#define SDA_OUT  DDRB  |=  SDA 
#define SDA_H    PORTB |=  SDA 
#define SDA_L    PORTB &=~ SDA 
#define SDA_I    PORTB ^=  SDA 
#define SDA_IN    { DDRB  &=~ SDA; PUEB &=~ SDA; }
#define SDA_INPU  { DDRB  &=~ SDA; PUEB |=  SDA; }
#define SDA_IS_H  ( PINB  &   SDA )
#define SDA_IS_L !( PINB  &   SDA )

#define SCL      ( 1<<PB2 )
#define SCL_OUT  DDRB  |=  SCL 
#define SCL_H    PORTB |=  SCL 
#define SCL_L    PORTB &=~ SCL 
#define SCL_I    PORTB ^=  SCL 

#define I2C_TARGET_ADDR 0x2F

#endif

