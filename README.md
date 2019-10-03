# AVR/Arduinoのメモ帳

* [ピンレイアウト](pins/)
* [配線例](wiring/)
* [ATTin13Aサンプル](ATTiny13A/Blink-Button)

# 開発環境

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [Atmel Studio](http://www.atmel.com/ja/jp/tools/ATMELSTUDIO.aspx)
* [CrossPack for AVR](https://www.obdev.at/products/crosspack/index.html)

# ツール

* [LUFA](http://www.fourwalledcubicle.com/LUFA.php)
* [AVRDUDE](http://www.nongnu.org/avrdude/)
* [dfu-programmer](https://dfu-programmer.github.io)


# AVRの手帳

AVRはATmel(現Microchip)の8ビットマイコンである。Arduinoの主要プロセッサ

## よく使うIC

* 入手が容易(秋月電子で買える)
* 安価
* できるだけDIP


 名前 | MEM | SRAM | EEPROM |  秋月電子 | 特徴
------|---- |------|--------|---------------|----------
[ATTiny13A](https://www.microchip.com/wwwproducts/en/ATTINY13A) | 1K | 64 | 64 | [50円](http://akizukidenshi.com/catalog/g/gI-02911/) | 安い
[ATTiny85](https://www.microchip.com/wwwproducts/en/ATtiny85) | 8K | 512 | 512 | [130円](http://akizukidenshi.com/catalog/g/gI-09573/) | SPI,I2C,SPWM
[ATmega48](https://www.microchip.com/wwwproducts/en/ATmega48) | 4K | 512 | 256 | [150円](http://akizukidenshi.com/catalog/g/gI-08437/) | 面実装だけど安い
[ATmega168](https://www.microchip.com/wwwproducts/en/ATmega168) | 16K | 1K | 512 | | 
[ATmega328P](https://www.microchip.com/wwwproducts/en/ATmega328P) | 32K | 2K | 1K | [230円](http://akizukidenshi.com/catalog/g/gI-03142/) | Arduino UNOの本体
[ATmega88V](https://www.microchip.com/wwwproducts/en/ATmega88) | 8K | 1K | 512 | [260円](http://akizukidenshi.com/catalog/g/gI-03655/) | 1.8Vから動く、最大10MHz
[ATmega32U4](https://www.microchip.com/wwwproducts/en/ATmega32U4) | 32K | 1K | 2.5K | [640円](http://akizukidenshi.com/catalog/g/gI-09835/) | USB、Arduino Micro, Leonardoの本体
[ATmega32U2](https://www.microchip.com/wwwproducts/en/ATmega32U2) | 400円(終売) | | USB
[AT90USB162](https://www.microchip.com/wwwproducts/en/AT90USB162) | 300円(終売) | | USB

## クロック速度の選定

* RC内部オシレータ(8MHzか9.6MHz)を使うか、外部クリスタルを使うか。
* 外部クロックにはクリスタルと12pF〜22pFのコンデンサ2つあればよい
* Arduinoは16MHzクロック搭載
* USBモデルは動作クロックからPLLでUSBに必要な48MHzを作っているので、16MHzが無難。
* 動作電圧で動作クロックの制限がある。~10MHzで2.7V~5.5V, ~20MHzで4.5V~5.5V (ATmega48は14.7456MHz@3.3Vでそれなりに動作していた)
* USARTを使用する場合、14.7456MHzまたは7.3728MHzの のクロックを使用すると多くのボーレートで安定した通信が行える。このサイトが参考になる。https://trolsoft.ru/en/uart-calc
* ATTiny13Aで外部クロックを使用すると1ピン消費してしまうので、主に内部オシレータをよく使用している。9.6MHzだがRCなので不安定。キャリブレーションが可能。

周波数 | 内容        | 9600
-------|-------------|------
128KHz | 内臓RCオシレータ(低電圧動作向け) | 
9.6MHz | 内臓RCオシレータ(ATTiny13A) | 
8MHz   | 内臓RCオシレータ
7.3728MHz | USARTに最適
10MHz  | 2.7Vから動作する最高クロック
11.0592MHz | USARTに最適
14.7456MHz | USARTに最適
18.432 MHz |  USARTに最適
20MHz  | 4.5Vから動作する最高クロック

USARTにおいて最適なものは9600, 38400, 115200においてエラーが0%であるとする

fCPU | bps | U2Xn=0 UBRR | Error | U2Xn=1 UBRR | Error
---|---|---|---|---|---
8 MHz | 9600 | 0x0033 | 0.20% | 0x0067 | 0.20%
8 MHz | 31.25 K | 0x000F | 0% | 0x001F | 0%
8 MHz | 38.4 K | 0x000C | 0.20% | 0x0019 | 0.20%
7.3728 MHz | 9600 | 0x002F | 0% | 0x005F | 0%
7.3728 MHz | 38.4 K | 0x000B | 0% | 0x0017 | 0%
7.3728 MHz | 115.2 K | 0x0003 | 0% | 0x0007 | 0%
7.3728 MHz | 9600 | 0x0040 | 0.20% | 0x0081 | 0.20%
10 MHz | 31.25 K | 0x0013 | 0% | 0x0027 | 0%
11.0592 MHz | 9600 | 0x0047 | 0% | 0x008F | 0%
11.0592 MHz | 31.25 K | 0x0015 | 0.50% | 0x002B | 0.50%
11.0592 MHz | 38.4 K | 0x0011 | 0% | 0x0023 | 0%
11.0592 MHz | 115.2 K | 0x0005 | 0% | 0x000B | 0%
14.7456 MHz | 9600 | 0x005F | 0% | 0x00BF | 0%
14.7456 MHz | 31.25 K |  |  | 0x003A | 0%
14.7456 MHz | 38.4 K | 0x0017 | 0% | 0x002F | 0%
14.7456 MHz | 115.2 K | 0x0007 | 0% | 0x000F | 0%
16MHz | 9600 | 0x0067 | 0.20% | 0x00CF | 0.20%
16MHz | 31.25 K | 0x001F | 0% | 0x003F | 0%
16MHz | 38.4 K | 0x0019 | 0.20% | 0x0033 | 0.20%
18.432 MHz | 9600 | 0x0077 | 0% | 0x00EF | 0%
18.432 MHz | 31.25 K | 0x0024 | -0.40% | 0x0049 | -0.40%
18.432 MHz | 38.4 K | 0x001D | 0% | 0x003B | 0%
18.432 MHz | 115.2 K | 0x0009 | 0% | 0x0013 | 0%
20 MHz | 9600 | 0x0081 | 0.20% | 0x0103 | 0.20%
20 MHz | 31.25 K | 0x0027 | 0% | 0x004F | 0%
20 MHz | 38.4 K |  |  | 0x0040 | 0.20%

