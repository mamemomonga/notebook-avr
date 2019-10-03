# クロック速度の選定

* RC内部オシレータ(8MHzか9.6MHz)を使うか、外部クリスタルを使うか。
* 外部クロックにはクリスタルと12pF〜22pFのコンデンサ2つあればよい。
* USART(シリアル通信・MIDI通信)を使う場合は、動作クロックがエラー率に影響する。
* USBモデルは16MHzが無難。
* 動作電圧で動作クロックの制限がある。〜10MHzで2.7V〜5.5V, 〜20MHzで4.5V〜5.5V (ATmega48は14.7456MHz@3.3Vででもうまく動作していた)
* 8ピンICは外部クロックを使うとピンを消費してしまうのでもったいない。
* 詳しくはデータシートを読むこと。

# 便利ツール

* [AVR UART Baud Rate Calculator](https://trolsoft.ru/en/uart-calc)
* [UBBR値計算ツール](ubbr-calc.pl)

## 代表的な動作クロックとUSART使用時のU2XnとUBBRの設定値

* シリアル通信で利用する代表的なビットレートである 9600, 38400, 115200と、MIDIで使用する313500
* エラーレート0.5%未満のもの

## FCPU: 128000 (128 KHz)

* 内臓RCオシレータ
* たぶんUSARTは使えないんじゃないだろうか

## FCPU: 8000000 (8.000000 MHz)

* 内臓RCオシレータ
* 不安定なのでUSARTには不向き、OSCALの調整が必要

 Baudrate | U2Xn, UBBR | ERROR 
----------|------------|-------
9600 | U2Xn: 0 UBBR: 0x0033 | ERROR: 0.160000 %
9600 | U2Xn: 1 UBBR: 0x0067 | ERROR: 0.160000 %
38400 | U2Xn: 0 UBBR: 0x000c | ERROR: 0.160000 %
38400 | U2Xn: 1 UBBR: 0x0019 | ERROR: 0.160000 %
31250 | U2Xn: 0 UBBR: 0x000f | ERROR: 0.000000 %
31250 | U2Xn: 1 UBBR: 0x001f | ERROR: 0.000000 %

## FCPU: 9600000 (9.600000 MHz)

* ATTiny13A
* 内臓RCオシレータ
* 不安定なのでUSARTには不向き、OSCALの調整が必要

 Baudrate | U2Xn, UBBR | ERROR 
----------|------------|-------
9600 | U2Xn: 1 UBBR: 0x007c | ERROR: 0.000000 %

## FCPU: 7372800 (7.372800 MHz)

* 3.3Vでのシリアル通信に最適
* MIDIには不向き

 Baudrate | U2Xn, UBBR | ERROR 
----------|------------|-------
9600 | U2Xn: 0 UBBR: 0x002f | ERROR: 0.000000 %
9600 | U2Xn: 1 UBBR: 0x005f | ERROR: 0.000000 %
38400 | U2Xn: 0 UBBR: 0x000b | ERROR: 0.000000 %
38400 | U2Xn: 1 UBBR: 0x0017 | ERROR: 0.000000 %
115200 | U2Xn: 0 UBBR: 0x0003 | ERROR: 0.000000 %
115200 | U2Xn: 1 UBBR: 0x0007 | ERROR: 0.000000 %

## FCPU: 10000000 (10.000000 MHz)

* 3.3Vでの最高クロック
* MIDIに最適

 Baudrate | U2Xn, UBBR | ERROR 
----------|------------|-------
9600 | U2Xn: 0 UBBR: 0x0040 | ERROR: 0.160000 %
9600 | U2Xn: 1 UBBR: 0x0081 | ERROR: 0.160000 %
31250 | U2Xn: 0 UBBR: 0x0013 | ERROR: 0.000000 %
31250 | U2Xn: 1 UBBR: 0x0027 | ERROR: 0.000000 %

## FCPU: 11059200 (11.059200 MHz)

* シリアル通信での範囲広い
* MIDIには不向き

 Baudrate | U2Xn, UBBR | ERROR 
----------|------------|-------
9600 | U2Xn: 0 UBBR: 0x0047 | ERROR: 0.000000 %
9600 | U2Xn: 1 UBBR: 0x008f | ERROR: 0.000000 %
38400 | U2Xn: 0 UBBR: 0x0011 | ERROR: 0.000000 %
38400 | U2Xn: 1 UBBR: 0x0023 | ERROR: 0.000000 %
115200 | U2Xn: 0 UBBR: 0x0005 | ERROR: 0.000000 %
115200 | U2Xn: 1 UBBR: 0x000b | ERROR: 0.000000 %

## FCPU: 14745600 (14.745600 MHz)

* 5VでのUSARTに最適
* MIDIも良好

 Baudrate | U2Xn, UBBR | ERROR 
----------|------------|-------
9600 | U2Xn: 0 UBBR: 0x005f | ERROR: 0.000000 %
9600 | U2Xn: 1 UBBR: 0x00bf | ERROR: 0.000000 %
38400 | U2Xn: 0 UBBR: 0x0017 | ERROR: 0.000000 %
38400 | U2Xn: 1 UBBR: 0x002f | ERROR: 0.000000 %
115200 | U2Xn: 0 UBBR: 0x0007 | ERROR: 0.000000 %
115200 | U2Xn: 1 UBBR: 0x000f | ERROR: 0.000000 %
31250 | U2Xn: 1 UBBR: 0x003a | ERROR: 0.029831 %

## FCPU: 16000000 (16.000000 MHz)

* Arduino UNO搭載クロック

 Baudrate | U2Xn, UBBR | ERROR 
----------|------------|-------
9600 | U2Xn: 0 UBBR: 0x0067 | ERROR: 0.160000 %
9600 | U2Xn: 1 UBBR: 0x00cf | ERROR: 0.160000 %
31350 | U2Xn: 0 UBBR: 0x001f | ERROR: 0.318979 %
31350 | U2Xn: 1 UBBR: 0x003f | ERROR: 0.318979 %
38400 | U2Xn: 0 UBBR: 0x0019 | ERROR: 0.160000 %
38400 | U2Xn: 1 UBBR: 0x0033 | ERROR: 0.160000 %

## FCPU: 20000000 (20.000000 MHz)

* 5Vでの最高クロック
* MIDIに最適 

 Baudrate | U2Xn, UBBR | ERROR 
----------|------------|-------
9600 | U2Xn: 0 UBBR: 0x0081 | ERROR: 0.160000 %
9600 | U2Xn: 1 UBBR: 0x0103 | ERROR: 0.160000 %
38400 | U2Xn: 1 UBBR: 0x0040 | ERROR: 0.160000 %
31250 | U2Xn: 0 UBBR: 0x0027 | ERROR: 0.000000 %
31250 | U2Xn: 1 UBBR: 0x004f | ERROR: 0.000000 %


# 参考になるサイト

* [Wikipedia(en):Crystal oscillator frequencies](https://en.wikipedia.org/wiki/Crystal_oscillator_frequencies)


