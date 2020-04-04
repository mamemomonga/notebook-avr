#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <avr/io.h>

/*
 ATmega168P 28PDIP

 /RST | 1     28 | PC5
  PD0 | 2     27 | PC4
  PD1 | 3     26 | PC3
  PD2 | 4     25 | PC2
  PD3 | 5     24 | PC1
  PD4 | 6     23 | PC0
  VCC | 7     22 | GND
  GND | 8     21 | AREF
XTAL1 | 9     20 | AVCC
XTAL2 | 10    19 | PB5
  PD5 | 11    18 | PB4
  PD6 | 12    17 | PB3
  PD7 | 13    16 | PB2
  PB0 | 14    15 | PB1

*/

#define LED       ( 1<<PC5 )
#define LED_OUT     DDRC  |=  LED 
#define LED_IN    { DDRC  &=~ LED; PORTC &=~ LED; }
#define LED_INPU  { DDRC  &=~ LED; PORTC |=  LED; }
#define LED_H       PORTC |=  LED 
#define LED_L       PORTC &=~ LED 
#define LED_I       PORTC ^=  LED 
#define LED_IS_H  ( PINC  &   LED )
#define LED_IS_L !( PINC  &   LED )

/*

SN74HC595, 74HC595

  Q1,Qb | 1  16 | Vcc
  Q2,Qc | 2  15 | Q0, Qa
  Q3,Qd | 3  14 | DS, SER, MOSI
  Q4,Qe | 4  13 | /OE
  Q5,Qf | 5  12 | STCP, RCKL, SS
  Q6,Qg | 6  11 | SHCP, SRCLK, SCK
  Q7,Qh | 7  10 | /MR, /SRCLR
  GND   | 8   9 | Qh', Q7S

*/

#define BB595_DUAL
#define BB595_PORT PORTD
#define BB595_DDR  DDRD
#define BB595_MOSI PD2
#define BB595_SCK  PD3
#define BB595_SS   PD4

#endif
