# 動作デバイス ( リスト: avr-as -mlist-devices )
DEVICE     := atmega48

# 動作クロック(Hz)
CLOCK      := 16000000

# プログラマ ( リスト: avrdude -c ? )
PROGRAMMER := -c avrisp2

# ヒューズ
FUSES      = -U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m

# 使用オリジナルライブラリ
MLIBS = serial i2c-slave

include ../build.mk

