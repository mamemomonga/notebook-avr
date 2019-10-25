#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <avr/io.h>

/*

 ATmega328P 28PDIP

               /RST | 1     28 | PC5  SCL
            RXD PD0 | 2     27 | PC4  SDA
            TXD PD1 | 3     26 | PC3
                PD2 | 4     25 | PC2
                PD3 | 5     24 | PC1
                PD4 | 6     23 | PC0
                VCC | 7     22 | GND
                GND | 8     21 | AREF
              XTAL1 | 9     20 | AVCC
              XTAL2 | 10    19 | PB5  SCK
                PD5 | 11    18 | PB4  MISO
                PD6 | 12    17 | PB3  MOSI
                PD7 | 13    16 | PB2  /SS
FLG_ENTER_SETUP PB0 | 14    15 | PB1  LED1

*/

// USART ボーレート
#define BAUD 38400

// PB0: Enter SETUP
#define FLG_ENTER_SETUP      ( 1 << PB0 )
#define FLG_ENTER_SETUP_INIT { DDRB &=~ FLG_ENTER_SETUP; PORTB |= FLG_ENTER_SETUP; }
#define FLG_ENTER_SETUP_IS_H ( PINB & FLG_ENTER_SETUP )

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

// EEPROM ADDRESS
#define CFG1_ADDR_EEP  0x0020
#define CFG1_CONFIGURED (1 << 0)
#define CFG1_SPI_EN     (1 << 1)
#define CFG1_SPI_MSTR   (1 << 2)
#define CFG1_I2C_EN     (1 << 3)
#define CFG1_I2C_MSTR   (1 << 4)

#define CFG2_ADDR_EEP  0x0021
#define CFG2_CPHA      (1 << 0)
#define CFG2_CPOL      (1 << 1)
#define CFG2_SPR0      (1 << 2)
#define CFG2_SPR1      (1 << 3)
#define CFG2_SPI2X     (1 << 4)

#define CFG3_ADDR_EEP  0x0022

uint8_t cfg1;
uint8_t cfg2;
uint8_t cfg3;

#endif

