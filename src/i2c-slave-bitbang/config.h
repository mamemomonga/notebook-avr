#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <avr/io.h>

#if   defined (__AVR_ATtiny13__)
#define ATtiny13
#elif defined (__AVR_ATtiny13A__) 
#define ATtiny13
#elif defined (__AVR_ATtiny10__) 
#define ATtiny10
#endif

/* ------------------------------------------------------- */
#if defined (ATtiny13)
/*
 ATtiny13A 8PDIP

/RST | 1    8 | VCC
 PB3 | 2    7 | PB2      SCL
 PB4 | 3    6 | PB1 INT0 SDA
 GND | 4    5 | PB0      LED
*/

// PB0,INT0 SDA
#define SDA       ( 1<<PB1 )
#define SDA_IN    { DDRB  &=~ SDA; PORTB &=~ SDA; }
#define SDA_IS_H  ( PINB  &   SDA )
#define SDA_IS_L !( PINB  &   SDA )
#define SDA_OUT     DDRB  |=  SDA
#define SDA_H       PORTB |=  SDA
#define SDA_L       PORTB &=~ SDA

// PB2, SCL
#define SCL       ( 1<<PB2 )
#define SCL_IN    { DDRB  &=~ SCL; PORTB &=~ SCL; }
#define SCL_IS_H  ( PINB  &   SCL )
#define SCL_IS_L !( PINB  &   SCL )
#define SCL_OUT     DDRB  |=  SCL
#define SCL_H       PORTB |=  SCL
#define SCL_L       PORTB &=~ SCL

// LED 
#define LED1      ( 1<<PB0 )
#define LED1_OUT  DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1
#endif

// LED 
#define LED2      ( 1<<PB3 )
#define LED2_OUT  DDRB  |=  LED2
#define LED2_H    PORTB |=  LED2
#define LED2_L    PORTB &=~ LED2
#define LED2_I    PORTB ^=  LED2

#endif
/* ------------------------------------------------------- */
#if defined (ATtiny10)
/*
 ATtiny10 SOT32

  LED PB0 | 1   6 | PB3 RST
      GND | 2   5 | VCC
  SCL PB1 | 3   4 | PB2 INT0 SDA

*/

// PB2,INT0 SDA
#define SDA       ( 1<<PB2 )
#define SDA_IN    { DDRB  &=~ SDA; PUEB &=~ SDA; }
#define SDA_IS_H  ( PINB  &   SDA )
#define SDA_IS_L !( PINB  &   SDA )
#define SDA_OUT     DDRB  |=  SDA
#define SDA_H       PORTB |=  SDA
#define SDA_L       PORTB &=~ SDA

// PB1, SCL
#define SCL       ( 1<<PB1 )
#define SCL_IN    { DDRB  &=~ SCL; PUEB &=~ SCL; }
#define SCL_IS_H  ( PINB  &   SCL )
#define SCL_IS_L !( PINB  &   SCL )
#define SCL_OUT     DDRB  |=  SCL
#define SCL_H       PORTB |=  SCL
#define SCL_L       PORTB &=~ SCL

// LED 
#define LED1      ( 1<<PB0 )
#define LED1_OUT  DDRB  |=  LED1
#define LED1_H    PORTB |=  LED1
#define LED1_L    PORTB &=~ LED1
#define LED1_I    PORTB ^=  LED1
#endif
/* ------------------------------------------------------- */

#define I2C_ADDR 0x20

