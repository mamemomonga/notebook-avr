# SR595

74HC595をGPIOでコントロール

# 参考: SR595_write の別の実装例

C

	void sr595_write_chip(uint8_t byte) {
	
		for(uint8_t i=0;i<8;i++) {
			SR595_PORT &=~ (1<<SR595_SCK);
			if( ( byte << (7-i) ) & 0b10000000) {
				SR595_PORT |= (1<<SR595_MOSI);
			} else {
				SR595_PORT &=~ (1<<SR595_MOSI);
			}
			_delay_ms(1);
			SR595_PORT |= (1<<SR595_SCK);
			_delay_ms(1);
		}
	
	}

Inline Asm	

	void sr595_write_chip(uint8_t byte) {
		asm volatile(
			"in		r25, %[port]"        "\n\t" // ポートの現在の状態をr25にコピー
			"ldi r26, 0xFF"              "\n\t" // r26で8つ数えたい
			"SPIWriteLoop:"              "\n\t"
			"  bst  %[byte], 0"          "\n\t" // r24の1ビット目をTに複写
			"  bld  r25,     %[mosi]"    "\n\t" // r25のMOSIピンにTの状態をセット
			"  andi r25,     ~%[sck]"    "\n\t" // SCKをLOW
			"  out  %[port], r25"        "\n\t" // 出力:MOSI,SCK
			"  nop"                      "\n\t" 
			"  nop"                      "\n\t" 
			"  nop"                      "\n\t" 
			"  lsr  %[byte]"             "\n\t" // データを右シフト
			"  ori  r25,     %[sck]"     "\n\t" // SCKをHIGH
			"  lsr  r26"                 "\n\t" // r26を右シフト
			"  out  %[port], r25"        "\n\t" // 出力:SCK
			"  nop"                      "\n\t" 
			"  nop"                      "\n\t" 
			"  brne SPIWriteLoop"        "\n"   // r26が空になるまでジャンプ
			::
			   [port] "I" (_SFR_IO_ADDR(SR595_PORT)),
			   [mosi] "I" (SR595_MOSI),
			   [sck]  "I" (1<<SR595_SCK),
			   [byte] "r" (byte)
		);
 }

