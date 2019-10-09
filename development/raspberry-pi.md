# Raspberry Pi Raspbian Buster にAVR開発環境を導入する

	$ sudo apt update
	$ sudo apt install -y gcc-avr avrdude avr-libc build-essential

## Linuxでsudoしないとavrdudeで書き込めないときの対策

AVRISPmk2などUSBのプログラマを使用する場合、USBデバイスのパーミッションの関係でsudoしないと実行できないことがあります。 以下の様にすれば書き込めるようになります。

以下は自分の所属しているグループが pi である場合の例です。

### グループ pi で実行できるようにする(一度のみ)

この方法はケーブルをつなぎ替えると元に戻ってしまいます。

	$ lsusb
	Bus 001 Device 004: ID 03eb:2104 Atmel Corp. AVR ISP mkII

	$ ls -al /dev/bus/usb/001/004
	crw-rw-r-- 1 root root 189, 3 Oct 10 03:28 /dev/bus/usb/001/004

ユーザroot グループrootになっています。

	$ sudo chown root:pi /dev/bus/usb/001/004

	$ ls -al /dev/bus/usb/001/004
	crw-rw-r-- 1 root pi 189, 3 Oct 10 03:28 /dev/bus/usb/001/004

これでユーザroot グループpi になるので、グループpi所属ユーザは利用できるようになります。

### AVRISPmk2は恒久的に グループpi になるようにする。

udevを設定することで差し替えてもグループ pi になるようにできます。

	$ sudo sh -c 'cat > /etc/udev/rules.d/50-avrisp-mk2.rules' << 'EOS'
	# AVR ISP mkII
	SUBSYSTEM=="usb", ATTR{idVendor}=="03eb", ATTR{idProduct}=="2104", GROUP="pi", MODE="0664"
	EOS

	$ sudo service udev restart


