# 動作デバイス ( リスト: avr-as -mlist-devices )
DEVICE := atmega328p

# 動作クロック(Hz)
CLOCK  := 16000000

# ヒューズ ATmega328P
FUSES = -U lfuse:w:0xce:m -U hfuse:w:0xd9:m -U efuse:w:0x07:m

# 使用オリジナルライブラリ
EXTERNAL_LIBDIR := ../lib

include ../../build.mk
