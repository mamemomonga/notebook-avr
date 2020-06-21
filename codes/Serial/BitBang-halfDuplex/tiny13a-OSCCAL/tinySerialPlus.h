#ifndef _TINYSERIAL_PLUS_H_
#define _TINYSERIAL_PLUS_H_

#include <stdlib.h>

// uint8_tを文字列にして送信
#define serOutInt8(n)    { char buf[4]; itoa(n, buf, 10); serial_send(buf); }

// uint8_tを16進数にして送信
#define serOutInt8Hex(n) { char buf[4]; itoa(n, buf, 16); serial_send(buf); }

#endif
