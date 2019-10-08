#include "spi595.h"

// 初期化
void spi595_init(void) {
	// MOSI,SCKの設定
	DDRB |= (1<<PB3)|(1<<PB5);

	// SSの設定
	SPI595_SS_INIT;

	// SSをHIGH
	SPI595_SS_H;

	// SPCR(SPI control register)
	//   SPE: SPI有効
	//   MSTR: マスターモード
	//   CPOL: 1, CPHA: 0 =  SPI MODE2
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL);

	// SPSR(SPI status register)
	//   SPI2X: 1 (SPR1, SPR0と組み合わせて 速度は Fosc/2となる)
	SPSR = (1<<SPI2X);
	SPSR = (1<<SPI2X);

	for(uint8_t i=0;i<SPI595_CHIP_NUM;i++) {
		spi595_state[i]=0x00;
	}
	spi595_apply();
}

// spi595_state の値を反映する
void spi595_apply(void) {
	SPI595_SS_L;
	for(uint8_t i=0;i<SPI595_CHIP_NUM;i++) {
		SPDR = spi595_state[i];
		while(!(SPSR & (1<<SPIF)));
	}
	SPI595_SS_H;
}
