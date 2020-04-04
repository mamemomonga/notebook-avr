#include "spi595.h"

// 初期化
void spi595_init(void) {
	// MOSI,SCKの設定
	DDRB |= (1<<PB3)|(1<<PB5);

	// SSの設定
	SPI595_SS_OUT;

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

}

#ifdef SPI595_SINGLE
void spi595_write(uint8_t v) {
	SPI595_SS_L;
	SPDR = v
	while(!(SPSR & (1<<SPIF)));
	SPI595_SS_H;
}
#endif

#ifdef SPI595_DUAL
void spi595_write(uint16_t v) {
	SPI595_SS_L;
	SPDR = v & 0xFF;
	while(!(SPSR & (1<<SPIF)));
	SPDR =( v >> 8 ) & 0xFF;
	while(!(SPSR & (1<<SPIF)));
	SPI595_SS_H;
}
#endif

