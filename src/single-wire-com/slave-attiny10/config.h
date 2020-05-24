#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <avr/io.h>

/*
 ATtiny10 SOT32

  LED PB0 | 1   6 | PB3 RST
      GND | 2   5 | VCC
      PB1 | 3   4 | PB2 INT0 SER

*/

// PB2,INT0 SER
#define SER       ( 1<<PB2 )
#define SER_IN    { DDRB  &=~ SER; PUEB &=~ SER; }
#define SER_IS_H  ( PINB  &   SER )
#define SER_IS_L !( PINB  &   SER )
#define SER_OUT     DDRB  |=  SER
#define SER_H       PORTB |=  SER
#define SER_L       PORTB &=~ SER

// LED 
#define LED1      ( 1<<PB0 )
#define LED1_OUT  DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1
#endif
