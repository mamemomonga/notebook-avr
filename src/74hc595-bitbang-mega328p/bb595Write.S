#include <avr/io.h>
#include "config.h"

#define BB595W_PORT   _SFR_IO_ADDR(BB595_PORT)
#define BB595W_MOSI   BB595_MOSI
#define BB595W_BVSCK  (1<<BB595_SCK)
#define BB595W_BVMOSI (1<<BB595_MOSI)

// 16MHzクロックのAVRではSCKが1MHzほどになる 

.global bb595_write_chip

bb595_write_chip:
	// 引数はr25,r24,r23,r22... というふうに渡される
	// ワード(16ビット)単位で渡されるのでバイト(8ビット)ならばr24
	in	r25, BB595W_PORT             ; ポートの現在の状態をr25にコピー
	ldi r26, 0xFF                    ; r26で8つ数えたい

	SPIWriteLoop:
		bst  r24, 0                  ; r24の1ビット目をTに複写
		bld  r25,  BB595W_MOSI       ; r25のMOSIピンにTの状態をセット
		andi r25,  ~BB595W_BVSCK     ; SCKをLOW
		out  BB595W_PORT, r25        ; 出力:MOSI,SCK
		nop
		nop 
		nop 
		nop 
		lsr  r24                     ; データを右シフト
		ori  r25,BB595W_BVSCK        ; SCKをHIGH
		lsr  r26                     ; r26を右シフト
		out  BB595W_PORT, r25        ; 出力:SCK
		nop
		nop 
		brne SPIWriteLoop            ; r26が空になるまでジャンプ

	nop
	nop 
	andi r25, ~BB595W_BVMOSI         ; MOSIをLOW
	andi r25, ~BB595W_BVSCK          ; SCKをLOW
	out  BB595W_PORT, r25            ; 出力
	ret

