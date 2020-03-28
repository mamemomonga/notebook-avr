#ifndef _SR_595_H_
#define _SR_595_H_

#include <avr/io.h>
#include "config.h"

void sr595_init();
void sr595_write_single(uint8_t b);

#endif
