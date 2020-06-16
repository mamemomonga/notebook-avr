#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>

/*
 ATtiny13A 8PDIP

/RST | 1    8 | VCC
 PB3 | 2    7 | PB2
 PB4 | 3    6 | PB1
 GND | 4    5 | PB0
*/

#define LED1      ( 1<<PB0 )
#define LED1_INIT DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1

#endif

