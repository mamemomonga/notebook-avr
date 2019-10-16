#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
 ATtiny13A 8PDIP

 /RST | 1    8 | VCC
P PB3 | 2    7 | PB2
N PB4 | 3    6 | PB1
  GND | 4    5 | PB0 LED
*/

#define CP ( 1<<PB3 )
#define CP_INIT DDRB  |=  CP 
#define CP_H    PORTB |=  CP 
#define CP_L    PORTB &=~ CP 
#define CP_I    PORTB ^=  CP

#define CN ( 1<<PB4 )
#define CN_INIT DDRB  |=  CN
#define CN_H    PORTB |=  CN
#define CN_L    PORTB &=~ CN
#define CN_I    PORTB ^=  CN

#define LED ( 1<<PB0 )
#define LED_INIT DDRB  |=  LED 
#define LED_H    PORTB |=  LED 
#define LED_L    PORTB &=~ LED 
#define LED_I    PORTB ^=  LED

#endif

