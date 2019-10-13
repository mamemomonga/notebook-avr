# ATTiny13Aサンプルコード

デジタル入出力・INT0割り込み・スリープのサンプル

* マクロでLED,ボタンの挙動を定義しています
* INT0の割り込みによる電源ON/OFF
---
* 2つのLEDを交互に点滅します
* ボタン1で電源ON/OFF
* ボタン2が押されている間は一時停止します
---

# ビルド/書き込み環境

* OSX El Capitan
* Crosspack AVR
* AVRISP mk2

# 配線

	ATTiny13A

	PIN1(PB5): AVRispRST
	PIN2(PB3): LED1 - 1Kohm - GND
	PIN3(PB4): LED2 - 1Kohm - GND
	PIN4(GND): GND
	PIN5(PB0): AVRispMOSI
	PIN6(PB1): AVRispMISO
	           BTN1(POWER) - GND
	PIN7(PB2): AVRispSCK
	           BTN2(FUNC)  - GND
	PIN8(VCC): VCC
	           0.1uF - GND

