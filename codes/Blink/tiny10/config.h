#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <avr/io.h>

/*
 ATtiny10 SOT32

 PB0 | 1   6 | PB3
 GND | 2   5 | VCC
 PB1 | 3   4 | PB2 LED

*/

#define LED       ( 1<<PB2 )
#define LED_OUT     DDRB  |=  LED 
#define LED_IN    { DDRB  &=~ LED; PUEB &=~ LED; }
#define LED_INPU  { DDRB  &=~ LED; PUEB |=  LED; }
#define LED_H       PORTB |=  LED 
#define LED_L       PORTB &=~ LED 
#define LED_I       PORTB ^=  LED 
#define LED_IS_H  ( PINB  &   LED )
#define LED_IS_L !( PINB  &   LED )

#endif

