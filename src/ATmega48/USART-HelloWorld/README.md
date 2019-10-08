# USART サンプル

* USARTによるシリアル接続
* stdoutをシリアルポートにする
* 500ミリ秒間隔で出力する
* 入力に反応する

# 接続

TXDをUSBシリアルインターフェイスのRXD, RXDをUSBシリアルインターフェイスのRXDに接続する。GNDの接続を忘れずに。

# テスト

	$ screen /dev/cu.SLAB_USBtoUART 38400

# メモ

ボーレートは38400、ボーレート設定は Makefileで行う。

