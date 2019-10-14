/* 
 * tinySerial.h
 * based on BasicSerial3.zip by Ralph Doncaster
 *   http://nerdralph.blogspot.com/2014/01/avr-half-duplex-software-uart.html
*/

/* 
 * Optimized half-duplex serial uart implementation
 * timing within 2% using at 230.4kbps @ 8Mhz 
 * @author: Ralph Doncaster
 * @version: $Id$
 *
 */

// 入出力はPB1

#ifndef _TINYSERIAL_H_
#define _TINYSERIAL_H_

#define BAUD 38400

#ifdef F_CPU
  /* account for integer truncation by adding 3/2 = 1.5 */
  #define TXDELAY (((F_CPU/BAUD)-7 +1.5)/3)
  #define RXDELAY (((F_CPU/BAUD)-5 +1.5)/3)
  #define RXROUNDED (((F_CPU/BAUD)-5 +2)/3)
#else
  #error CPU frequency F_CPU undefined
#endif

#if RXROUNDED > 127
  #error low baud rates unsupported - use higher BAUD
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void TxTimedByte(char, char);
char RxTimedByte(char, char); /* 1.5 bit delay, 1 bit delay */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#define TxByte(C) TxTimedByte(C , TXDELAY)
#define RxByte() RxTimedByte((RXDELAY*1.5)-2.5, RXDELAY)

#endif
