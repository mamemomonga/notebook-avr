#include "config.h"

#define PORT   _SFR_IO_ADDR(SR595_PORT)
#define MOSI   SR595_MOSI
#define BVSCK  (1<<SR595_SCK)

// 16MHzクロックのAVRではSCKが1MHzほどになる 

.global sr595_write_chip

sr595_write_chip:
	// 引数はr25,r24,r23,r22... というふうに渡される
	// ワード(16ビット)単位で渡されるのでバイト(8ビット)ならばr24

	in	r25, PORT             ; ポートの現在の状態をr25にコピー
	ldi r26, 0xFF             ; r26で8つ数えたい

	SPIWriteLoop:
		bst  r24, 0           ; r24の1ビット目をTに複写
		bld  r25,  MOSI       ; r25のMOSIピンにTの状態をセット
		andi r25,  ~BVSCK     ; SCKをLOW
		out  PORT, r25        ; 出力:MOSI,SCK
		nop                   ; タイミング調整
		nop
		nop 
		lsr  r24              ; データを右シフト
		ori  r25,BVSCK        ; SCKをHIGH
		lsr  r26              ; r26を右シフト
		out  PORT, r25        ; 出力:SCK
		nop                   ; タイミング調整
		nop 
		brne SPIWriteLoop     ; r26が空になるまでジャンプ

	ret

