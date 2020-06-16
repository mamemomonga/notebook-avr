#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <avr/io.h>

/*
 ATmega48 TQFP + ET-PCB TQFP32

    PD3 | 1      32 | PD2
    PD4 | 2      31 | PD1
    GND | 3      30 | PD0
    VCC | 4      29 | /RST
    GND | 5      28 | PC5
    VCC | 6      27 | PC4
  XTAL1 | 7      26 | PC3
  XTAL2 | 8      25 | PC2
    PD5 | 9      24 | PC1
    PD6 | 10     23 | PC0
    PD7 | 11     22 | ADC7
    PB0 | 12     21 | GND
    PB1 | 13     20 | AREF
    PB2 | 14     19 | ADC6
    PB3 | 15     18 | AVCC
    PB4 | 16     17 | PB5
*/

#define LED       ( 1<<PB5 )
#define LED_OUT     DDRB  |=  LED 
#define LED_IN    { DDRB  &=~ LED; PORTB &=~ LED; }
#define LED_INPU  { DDRB  &=~ LED; PORTB |=  LED; }
#define LED_H       PORTB |=  LED 
#define LED_L       PORTB &=~ LED 
#define LED_I       PORTB ^=  LED 
#define LED_IS_H  ( PINB &    LED )
#define LED_IS_L !( PINB &    LED )

#endif

