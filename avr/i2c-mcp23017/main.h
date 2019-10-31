#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>

/*
 ATmega328P 28PDIP

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

#define LED1      ( 1<<PB1 )
#define LED1_INIT DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1

#endif

