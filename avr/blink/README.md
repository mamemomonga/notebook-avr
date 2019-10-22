# Blink

* Lチカ、500msごとに点滅する
* 基本的なフューズビットの設定

# 配線

1KΩの抵抗を介してLEDを接続する。接続先は main.h を参照

# フューズビットの書込

**フューズビットの書込には十分注意してください。間違ったビットを設定するとISPをつかったプログラミングができなくなります。**

最適なクロック源にあわせたフューズビットを書き込みます。Makefileで必要な部分のコメントを外して make fuse を実行してください。

設定内容をAtmel Studioや[Engbedded Atmel AVR® Fuse Calculator](http://www.engbedded.com/fusecalc/)で確認してください。

	avrdude: safemode: efuse changed! Was ff, and is now 1
	Would you like this fuse to be changed back? [y/n] 

Extended FuseのVerifyに失敗するようですが、一部ビットを書き込んだ内容と違うものを返すため問題ないようです。n で抜けて下さい。

