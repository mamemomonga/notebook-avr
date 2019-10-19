#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <avr/io.h>

/*
 ATmega328P 28PDIP

         /RST | 1     28 | PC5
RXD       PD0 | 2     27 | PC4
TXD       PD1 | 3     26 | PC3
          PD2 | 4     25 | PC2
          PD3 | 5     24 | PC1
          PD4 | 6     23 | PC0
          VCC | 7     22 | GND
          GND | 8     21 | AREF
        XTAL1 | 9     20 | AVCC
        XTAL2 | 10    19 | PB5  SCK
          PD5 | 11    18 | PB4  MISO
          PD6 | 12    17 | PB3  MOSI
          PD7 | 13    16 | PB2  /SS(Slave動作 入力)
SPI_MSTR  PB0 | 14    15 | PB1  LED1
*/

// USART ボーレート
#define BAUD 38400

// PB0: High/Float:MASTER / Low:SLAVE
#define FLG_SPI_MASTER  ( 1 << PB0 )
#define FLG_SPI_MASTER_INIT { DDRB &=~ FLG_SPI_MASTER; PORTB |= FLG_SPI_MASTER; }
#define FLG_SPI_MASTER_IS_H ( PINB & FLG_SPI_MASTER )
#define SPI_MODE_MASTER ( FLG_SPI_MASTER_IS_H )
#define SPI_MODE_SLAVE  ( ! FLG_SPI_MASTER_IS_H )

// PD7: High/Float:NORMAL / Low:TEST MODE
#define FLG_TEST_MODE ( 1 << PD7 )
#define FLG_TEST_MODE_INIT { DDRD &=~ FLG_TEST_MODE; PORTD |= FLG_TEST_MODE; }
#define FLG_TEST_MODE_IS_H ( PIND & FLG_TEST_MODE )
#define TEST_MODE_ON  ( ! FLG_TEST_MODE_IS_H )
#define TEST_MODE_OFF ( FLG_TEST_MODDE_IS_H )

// LED1 PB1
#define LED1      ( 1<<PB1 )
#define LED1_INIT DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1

// /SSポート設定(変更できない)
#define SPI_SS        ( 1 << PB2 )
#define SPI_SS_MASTER (DDRB)  |=  SPI_SS
#define SPI_SS_SLAVE  { DDRB &=~ SPI_SS; PORTB &=~ SPI_SS; }
#define SPI_SS_H      (PORTB) |=  SPI_SS
#define SPI_SS_L      (PORTB) &=~ SPI_SS

// SPI Data Mode
#define SPI_MODE1 { SPCR &=~ (1<<CPOL); SPCR &=~ (1<<CPHA); }
#define SPI_MODE2 { SPCR &=~ (1<<CPOL); SPCR |=  (1<<CPHA); }
#define SPI_MODE3 { SPCR |=  (1<<CPOL); SPCR &=~ (1<<CPHA); }
#define SPI_MODE4 { SPCR |~  (1<<CPOL); SPCR |=  (1<<CPHA); }

// SPI Speed
#define SPI_SCK_4   { SPSR &=~ (1<<SPI2X); SPCR &=~ (1<<SPR1); SPCR &=~ (1<<SPR0); }
#define SPI_SCK_16  { SPSR &=~ (1<<SPI2X); SPCR &=~ (1<<SPR1); SPCR |=  (1<<SPR0); }
#define SPI_SCK_64  { SPSR &=~ (1<<SPI2X); SPCR |=  (1<<SPR1); SPCR &=~ (1<<SPR0); }
#define SPI_SCK_128 { SPSR &=~ (1<<SPI2X); SPCR |=  (1<<SPR1); SPCR |=  (1<<SPR0); }
#define SPI_SCK_2   { SPSR |=  (1<<SPI2X); SPCR &=~ (1<<SPR1); SPCR &=~ (1<<SPR0); }
#define SPI_SCK_8   { SPSR |=  (1<<SPI2X); SPCR &=~ (1<<SPR1); SPCR |=  (1<<SPR0); }
#define SPI_SCK_32  { SPSR |=  (1<<SPI2X); SPCR |=  (1<<SPR1); SPCR &=~ (1<<SPR0); }
// #define SPI_SCK_64  { SPSR |=  (1<<SPI2X); SPCR |=  (1<<SPR1); SPCR |=  (1<<SPR0); }

#endif

