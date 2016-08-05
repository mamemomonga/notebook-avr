#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// 電源ボタン PIN6,PB1,INT0
// IC内部でプルアップ有功
//   BTN1_INIT:  初期化
//   BTN1_IS_H:  BTN2はHIGHである
#define BTN1      ( 1<<PB1 )
#define BTN1_INIT { DDRB &=~ BTN1; PORTB |= BTN1; }
#define BTN1_IS_H ( PINB & BTN1 )

// 機能ボタン PIN7,PB2
// IC内部でプルアップ有功
//   BTN2_INIT:  初期化
//   BTN2_IS_H:  BTN2はHIGHである
#define BTN2      ( 1<<PB2 )
#define BTN2_INIT { DDRB &=~ BTN2; PORTB |= BTN2; }
#define BTN2_IS_H ( PINB & BTN2 )

// LED1 PIN2, PB3
//   LED1_INIT: 初期化
//   LED1_H:    HIGHにする
//   LED1_L:    LOWにする
//   LED1_I:    反転する
#define LED1      ( 1<<PB3 )
#define LED1_INIT DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1

// LED2 PIN3, PB4
//   LED2_INIT: 初期化
//   LED2_H:    HIGHにする
//   LED2_L:    LOWにする
//   LED2_I:    反転する
#define LED2      ( 1<<PB4 )
#define LED2_INIT DDRB  |=  LED2
#define LED2_H    PORTB |=  LED2
#define LED2_L    PORTB &=~ LED2
#define LED2_I    PORTB ^=  LED2

#endif
