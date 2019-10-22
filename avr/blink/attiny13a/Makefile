# 動作デバイス ( リスト: avr-as -mlist-devices )
DEVICE := attiny13

# ATTiny13A 9.6MHz内臓オシレータ 9.6MHz動作
# Int. RC Osc. 8MHz, CKDIV=0, StartUp: 14CK+64ms
CLOCK := 9600000
FUSES := -U lfuse:w:0x7A:m -U hfuse:w:0xFF:m

# 使用オリジナルライブラリ
EXTERNAL_LIBDIR :=

include ../../build.mk
