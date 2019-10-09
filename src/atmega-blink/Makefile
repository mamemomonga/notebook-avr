# 動作デバイス ( リスト: avr-as -mlist-devices )

# DEVICE     := atmega48
DEVICE     := atmega328p

# 動作クロック(Hz)
CLOCK      := 16000000

# プログラマ ( リスト: avrdude -c ? )
PROGRAMMER := -c avrisp2

# ヒューズ

# ATmega48
# FUSES = -U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m

# ATmega328P
FUSES = -U lfuse:w:0xce:m -U hfuse:w:0xd9:m -U efuse:w:0x07:m

# 使用オリジナルライブラリ
MLIBS =

include ../build.mk

