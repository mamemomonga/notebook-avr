#ifndef _BB_595_H_
#define _BB_595_H_

#include <avr/io.h>
#include "config.h"

void bb595_init();
void bb595_write1(uint8_t b);
void bb595_write2(uint16_t b);

#endif
