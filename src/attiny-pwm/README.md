# タイマをつかったPWM

Waveform Generation Mode: 1(PWM (Phase Correct)) を使えば、PWM波と定期的な割り込みを発生させることができる。
TCNT0とOCR0Aが同じ値になったらISR(TIM0_COMPA_vect)が発生し、TCNT0がリセットされる。

# 1秒を求める

以下の方法で正確な周波数を求めることができる

`pwm-calc.pl fosc(MHz) prescale`

9.6MHzのクロックで、1024のプリスケーラを使った場合の最適な周波数を求める

	$ ../../bin/pwm-calc.pl 9.6 1024
	OCRBx: 0x01, Interval Freq: 9375 Hz
	OCRBx: 0x03, Interval Freq: 3125 Hz
	OCRBx: 0x05, Interval Freq: 1875 Hz
	OCRBx: 0x0f, Interval Freq: 625 Hz
	OCRBx: 0x19, Interval Freq: 375 Hz
	OCRBx: 0x4b, Interval Freq: 125 Hz
	OCRBx: 0x7d, Interval Freq: 75 Hz

# 注意

内部オシレータはRC回路なので精度く不正確。そのままでは時間を計るのには不適だが、OSCCALで校正できる。
