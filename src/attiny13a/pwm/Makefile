# 動作デバイス ( リスト: avr-as -mlist-devices )
DEVICE := attiny13

# 動作クロック(Hz)
CLOCK := 9600000

# プログラマ ( リスト: avrdude -c ? )
PROGRAMMER := -c avrisp2

# ヒューズ
FUSES := -U hfuse:w:0xff:m -U lfuse:w:0x7a:m

# 使用オリジナルライブラリ
MLIBS =

include ../../build.mk

