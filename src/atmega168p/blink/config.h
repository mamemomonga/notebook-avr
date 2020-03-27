#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
 ATmega168P 28PDIP

 /RST | 1     28 | PC5
  PD0 | 2     27 | PC4
  PD1 | 3     26 | PC3
  PD2 | 4     25 | PC2
  PD3 | 5     24 | PC1
  PD4 | 6     23 | PC0
  VCC | 7     22 | GND
  GND | 8     21 | AREF
XTAL1 | 9     20 | AVCC
XTAL2 | 10    19 | PB5
  PD5 | 11    18 | PB4
  PD6 | 12    17 | PB3
  PD7 | 13    16 | PB2
  PB0 | 14    15 | PB1

*/

#define LED       ( 1<<PB0 )
#define LED_OUT     DDRB  |=  LED 
#define LED_IN    { DDRB  &=~ LED; PORTB &=~ LED; }
#define LED_INPU  { DDRB  &=~ LED; PORTB |=  LED; }
#define LED_H       PORTB |=  LED 
#define LED_L       PORTB &=~ LED 
#define LED_I       PORTB ^=  LED 
#define LED_IS_H  ( PINB  &   LED )
#define LED_IS_L !( PINB  &   LED )

#endif
