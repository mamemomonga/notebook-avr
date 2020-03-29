#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "usart-serial.h"
#include "config.h"

uint8_t action=0;

void menu();
void hello_world();
void hello_world_int(char c);

#endif
