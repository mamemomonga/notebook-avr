#ifndef _BB_595_H_
#define _BB_595_H_

#include <avr/io.h>
#include "config.h"

void bb595_init();

#if defined(BB595_SINGLE)
void bb595_write(uint8_t b);
#endif

#if defined(BB595_DUAL)
void bb595_write(uint16_t b);
#endif

#endif
