#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>

// LED1 PB2
//   LED1_INIT: 初期化
//   LED1_H:    HIGHにする
//   LED1_L:    LOWにする
//   LED1_I:    反転する
#define LED1      ( 1<<PB2 )
#define LED1_INIT DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1

#endif

