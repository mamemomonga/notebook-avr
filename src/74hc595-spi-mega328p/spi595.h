#ifndef _SPI595_H_
#define _SPI505_H_

#include <avr/io.h>
#include "config.h"

void spi595_init(void);

#ifdef SPI595_SINGLE
void spi595_write(uint8_t v);
#endif

#ifdef SPI595_DUAL
void spi595_write(uint16_t v);
#endif

#endif
