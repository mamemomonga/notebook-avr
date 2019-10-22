#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>

/*
 ATmega481P 20PDIP

      PB0 | 1   20 | PA0
      PB1 | 2   19 | PA1
      PB2 | 3   18 | PA2
      PB3 | 4   17 | PA3
      VCC | 5   16 | GND
      GND | 6   15 | AVCC
XTAL1 PB4 | 7   14 | PA4
XTAL2 PB5 | 8   13 | PA5
 LED  PB6 | 9   12 | PA6
   /RESET | 10  11 | PA7

*/

// LED1 PB6
//   LED1_INIT: 初期化
//   LED1_H:    HIGHにする
//   LED1_L:    LOWにする
//   LED1_I:    反転する
#define LED1      ( 1<<PB6 )
#define LED1_INIT DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1

#endif

