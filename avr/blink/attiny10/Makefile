# 動作デバイス ( リスト: avr-as -mlist-devices )
DEVICE := attiny10

# ATTiny10の動作設定はプログラム内で行う
FUSES = -U BYTE0:w:0xFF:m
CLOCK := 8000000

# 使用オリジナルライブラリ
EXTERNAL_LIBDIR :=

include ../../build.mk
