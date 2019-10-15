#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>

// -- 配線 --
// /RST |     | VCC
// PB3  |     | PB2 LED1
// PB4  |     | PB1
// GND  |     | PB0

#define LED1 ( 1<<PB2 )
#define LED1_INIT DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1

#endif
