# PWM出力

* OC0B(PB2)からPWMの矩形波を生成することができる。
* 細かな周波数の調整は OSCCAL の値で行う。

## 小数点以下を含まない周波数の出力

	$ ./calc-fast-pwm.pl 9.6 256

clkio = 9.6MHz

	TCCR0B |= (1<<CS02)|(0<<CS01)|(1<<CS00); // clkio/1024
	TCCR0B |= (1<<CS02)|(0<<CS01)|(0<<CS00); // clkio/256
	TCCR0B |= (0<<CS02)|(1<<CS01)|(1<<CS00); // clkio/64
	TCCR0B |= (0<<CS02)|(1<<CS01)|(0<<CS00); // clkio/8
	TCCR0B |= (0<<CS02)|(0<<CS01)|(1<<CS00); // clkio/1


OCR0A, OCR0B(duty:50%) | clkio/1 | clkio/8 | clkio/64 | clkio/256 | clkio/1024
-------------|---------|---------|----------|-----------|------------
OCR0A=0x02; OCR0B=0x01; | 3200 kHz  | 400 kHz | 50 kHz | 12500 Hz | 3125 Hz
OCR0A=0x04; OCR0B=0x02; | 1920 kHz  | 240 kHz | 30 kHz | 7500 Hz  | 1875 Hz
OCR0A=0x0e; OCR0B=0x07; | 640 kHz   | 8 kHz  | 10 kHz | 2500 Hz  | 625 Hz
OCR0A=0x18; OCR0B=0x0c; | 384 kHz   | 48000 Hz  | 6000 Hz  | 1500 Hz  | 375 Hz
OCR0A=0x4a; OCR0B=0x25; | 128 kHz   | 16000 Hz  | 2000 Hz  | 500 Hz   | 125 Hz
OCR0A=0x7c; OCR0B=0x3e; | 76800 Hz  | 9600 Hz   | 1200 Hz  | 300 Hz   | 75 Hz

