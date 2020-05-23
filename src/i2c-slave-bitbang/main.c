#include "main.h"
#include "config.h"
#include "i2c-slave.h"
#include <avr/interrupt.h>

int main(void) {

	cli();

#if defined (ATtiny10)
	// internal 8MHz
	CCP = 0xD8;
	CLKMSR = 0;

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;
#endif

	LED1_OUT; LED1_L;
	LED2_OUT; LED2_L;

	i2c_init();
	sei();

	for(uint8_t i=0;i<20;i++) {
		LED1_H; LED2_L;
		_delay_ms(50);
		LED1_L; LED2_H;
		_delay_ms(50);
	}
	LED1_L; LED2_L;

	// データアドレス 0x02 に 0x3dを入れておく
	i2c_datas[0x02]=0x3d;

    for(;;){
		// データアドレス 0x01 に受信したらLEDをデータの回数だけ点滅させる
		if((i2c_step == I2C_STEP_RECV) && (i2c_data_addr == 0x01)) {
			// この処理は繰り返し実行しない
			i2c_step=I2C_STEP_NONE;
			// データを取り出す
			uint8_t data=i2c_datas[0x01];

			for(uint8_t i=0; i < data; i++) {
				LED1_H;
				_delay_ms(100);
				LED1_L;
				_delay_ms(300);
			}
		}
		LED2_I;
		_delay_ms(500);
    }
    return 0;
}
