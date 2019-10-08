# i2c Slave

* i2cで受信すると、データアドレスに1くわえたものを返す
* i2cで要求されると、その値をシリアルに出力する

シリアルによるprintの挿入箇所によっては動作に支障がでるので注意

# 接続

* TXD, RXD, GNDをhost1に接続
* SDA, SCL, GNDをhost2に接続

# テスト

	[host1]$ screen /dev/cu.SLAB_USBtoUART 38400

	[host2]$ sudo i2cget -y 1 0x30 0x01
	0x02

	[host2]$ sudo i2cset -y 1 0x30 0x01 0x02
	[host1]I2C RECV: 0x1 0x2


