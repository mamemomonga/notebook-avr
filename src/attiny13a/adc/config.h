#ifndef _CONFIG_H_
#define _CONFIG_H_

// ボーレート 省略時は 38400
#define BAUD 38400 
// #define BAUD 115200

// 送受信ポート、PBx
// INT0割り込みを使う場合はPB1専用となる
#define UART_Tx 1
#define UART_Rx 1

#endif
