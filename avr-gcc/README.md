# avr-gccでよく使う表現

## よく使うレジスタ

レジスタ | 名称                 | 役割
---------|----------------------|----------
PORTx    | Port x Data Register           | ピンの書込
DDRx     | Port x Data Direction Register | 入出力選択
PINx     | Port x Input Pins Address      | ピンの状態

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

# テンプレート

## ATTiny13A, ATmega

main.h

	#ifndef _MAIN_H_
	#define _MAIN_H_

	#include <avr/io.h>

	// IO PB2
	// IO_OUT:  出力
	// IO_IN:   入力プルアップなし
	// IO_INPU: 入力プルアップ
	// IO_H:    出力をHIGHにする
	// IO_L:    出力をLOWにする
	// IO_I:    出力を反転する
	// IO_IS_H: 入力はHIGHである
	// IO_IS_L: 入力はHIGHである

	#define IO       ( 1<<PB2 )
	#define IO_OUT     DDRB  |=  IO 
	#define IO_IN    { DDRB  &=~ IO; PORTB &=~ IO; }
	#define IO_INPU  { DDRB  &=~ IO; PORTB |=  IO; }
	#define IO_H       PORTB |=  IO 
	#define IO_L       PORTB &=~ IO 
	#define IO_I       PORTB ^=  IO 
	#define IO_IS_H  ( PINB &    IO )
	#define IO_IS_L !( PINB &    IO )

	#endif

main.c

	#include "main.h"
	#include <util/delay.h>

	int main(void) {
		// IO初期化
		IO_OUT;

		for(;;) {
			IO_I;
			_delay_ms(500);
		}
		return 0;
	}

## ATTiny10

* ATTiny10はフューズビットの設定を起動時に行う。
* またプルアップの設定をPUExレジスタで指定する(事前にPUExを0で埋めておくこと)。

main.h

	#ifndef _MAIN_H_
	#define _MAIN_H_

	#include <avr/io.h>

	// IO PB2
	// IO_OUT:  出力
	// IO_IN:   入力プルアップなし
	// IO_INPU: 入力プルアップ
	// IO_H:    出力をHIGHにする
	// IO_L:    出力をLOWにする
	// IO_I:    出力を反転する
	// IO_IS_H: 入力はHIGHである
	// IO_IS_L: 入力はHIGHである

	#define IO       ( 1<<PB2 )
	#define IO_OUT     DDRB  |=  IO 
	#define IO_IN    { DDRB  &=~ IO; PUEB &=~ IO; }
	#define IO_INPU  { DDRB  &=~ IO; PUEB |=  IO; }
	#define IO_H       PORTB |=  IO 
	#define IO_L       PORTB &=~ IO 
	#define IO_I       PORTB ^=  IO 
	#define IO_IS_H  ( PINB  &   IO )
	#define IO_IS_L !( PINB  &   IO )

	#endif

main.c

	#include "main.h"
	#include <util/delay.h>

	int main(void) {
		// 内部クロック8MHz
		CCP = 0xD8;
		CLKMSR = 0;
	
		// プリスケーラなし
		CCP = 0xD8;
		CLKPSR = 0;
	
		// すべてのプルアップ無効
		PUEB=0;
	
		// IO初期化
		IO_OUT;

		for(;;) {
			IO_I;
			_delay_ms(500);
		}
		return 0;
	}

