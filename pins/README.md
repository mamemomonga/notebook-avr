# ピンレイアウトと配線サンプル

* 電源電圧・最大クロック周波数はモデルによって異なるが、細かな周波数にこだわらないなら(USARTなどに影響する) **5Vなら16MHz、3.3Vなら10MHz** で問題なし。
* AVRISP2の接続する部分には低インピーダンスの負荷をつなげない。
* VCCとGNDの間には0.1uFのコンデンサをできるだけ短い距離で接続する。

## ATmega168, 328P (28PDIP)
![ATmega328P-1](ATmega328P-1.png)

PCINT

![ATmega328P-2](ATmega328P-2.png)

Arduinoの場合のピンアサイン

![ATmega328P-3](ATmega328P-3.png)

## ATtiny 13A (8PDIP)
![ATtiny13A-1.png](ATtiny13A-1.png)

PCINT

![ATtiny13A-2.png](ATtiny13A-2.png)

## ATTiny 10 (SOT23)
![ATtiny10-1.png](ATtiny10-1.png)

PCINT

![ATtiny10-2.png](ATtiny10-2.png)

## AVRISP mk2 コネクタ
ボード側のピンを上から見た配置、コネクタの裏側からみた配置です。

![AVRISP2.png](AVRISP2.png)

SCK, MISO, MOSIが一列、VCC,GND,RSTを自由にできるコネクタをつくるとブレッドボードで利用できるので大変便利です。

## ATmega48 TQFP
![ATmega48-1.png](ATmega48-1.png)

ET-PCB TQFP32
![ATmega48-2.png](ATmega48-2.png)
