# avr-gccでよく使う表現

## よく使うレジスタ

レジスタ | 名称                 | 役割
---------|----------------------|----------
PORTx    | Port x Data Register | ピンの書込
DDRx     | Port x Data Direction Register | 入出力選択
PINx     | Port x Input Pins Address | ピンの状態

## ビット演算

3ビット目が1である( \_BV(1)と同じ )

	( 1 << 2 )

PORTBの2ビット目を1にする

	PORTB |= ( 1 << 2 )

PORTBの2ビット目を0にする

	PORTB &=~ ( 1 << 2 )

PORTBの2ビット目を反転する

	PORTB ^= ( 1 << 2 )

PINBの2ビット目が1である

	( PINB & 2 )

以下のようにマクロを書いておくと便利

main.h

	#ifndef _MAIN_H_
	#define _MAIN_H_
	#include <avr/io.h>

	// LED1 PB5
	//   LED1_INIT: 初期化
	//   LED1_H:    HIGHにする
	//   LED1_L:    LOWにする
	//   LED1_I:    反転する
	#define LED1      ( 1<<PB5 )
	#define LED1_INIT DDRB  |=  LED1
	#define LED1_H    PORTB |=  LED1
	#define LED1_L    PORTB &=~ LED1
	#define LED1_I    PORTB ^=  LED1
	#endif

	// ボタン1 PB1
	// IC内部でプルアップ有功
	//   BTN1_INIT:  初期化
	//   BTN1_IS_H:  BTN2はHIGHである
	#define BTN1      ( 1<<PB1 )
	#define BTN1_INIT { DDRB &=~ BTN1; PORTB |= BTN1; }
	#define BTN1_IS_H ( PINB & BTN1 )

main.c

	#include "main.h"
	int main(void) {
		LED1_INIT; 
		LED1_H;
		return 0;
	}


