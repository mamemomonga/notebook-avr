#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>

/*
 ATtiny10 SOT32

 PB0 | 1   6 | PB3
 GND | 2   5 | VCC
 PB1 | 3   4 | PB2 LED

*/

#define LED1      ( 1<<PB2 )
#define LED1_INIT DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1

#endif

