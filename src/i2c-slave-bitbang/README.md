# i2c slave bitbang

ATTiny13Aに簡易i2c slaveにする

* 8ビットの送受信
* Raspberry Piからi2cdetect, i2cget, i2csetでコントロール
* データは i2c_datas[] を介して行われる。すべて読み書き可能
* i2c_data[]の配列はデータアドレスに対応している

メモリ使用状況

	AVR Memory Usage
	----------------
	Device: attiny13
	
	Program:     618 bytes (60.4% Full)
	(.text + .data + .bootloader)
	
	Data:         34 bytes (53.1% Full)
	(.data + .bss + .noinit)
	
簡単なデモコードで60.4%消費。

# ビルド

	$ make

# フューズビットの設定

	$ make fuse

# アップロード

	$ make flash


# 回路図

![schematics](./schematics/schematics.png)

