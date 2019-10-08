#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include "spi595.h"

#define LED1      ( 1<<PC0 )
#define LED1_INIT DDRC  |=  LED1
#define LED1_H    PORTC |=  LED1
#define LED1_L    PORTC &=~ LED1
#define LED1_I    PORTC ^=  LED1

int main(void);

#endif
