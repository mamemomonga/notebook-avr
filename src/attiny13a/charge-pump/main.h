#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
 ATtiny13A 8PDIP

 /RST | 1    8 | VCC
P PB3 | 2    7 | PB2 ADC1
N PB4 | 3    6 | PB1 P
  GND | 4    5 | PB0 N
*/

#define CLK1P ( 1<<PB3 )
#define CLK1P_INIT DDRB  |=  CLK1P 
#define CLK1P_H    PORTB |=  CLK1P 
#define CLK1P_L    PORTB &=~ CLK1P 
#define CLK1P_I    PORTB ^=  CLK1P

#define CLK1N ( 1<<PB4 )
#define CLK1N_INIT DDRB  |=  CLK1N
#define CLK1N_H    PORTB |=  CLK1N
#define CLK1N_L    PORTB &=~ CLK1N
#define CLK1N_I    PORTB ^=  CLK1N

#define CLK2P ( 1<<PB1 )
#define CLK2P_INIT DDRB  |=  CLK2P 
#define CLK2P_H    PORTB |=  CLK2P 
#define CLK2P_L    PORTB &=~ CLK2P 
#define CLK2P_I    PORTB ^=  CLK2P

#define CLK2N ( 1<<PB0 )
#define CLK2N_INIT DDRB  |=  CLK2N 
#define CLK2N_H    PORTB |=  CLK2N 
#define CLK2N_L    PORTB &=~ CLK2N 
#define CLK2N_I    PORTB ^=  CLK2N

// 10Vが欲しい場合、20K - 10K なので 3等分なので3.33V
// (255/5) * (10/3) = 170
#define COMP_OUTV 170 - 4

#endif

