# 動作デバイス ( リスト: avr-as -mlist-devices )
DEVICE := atmega48

# ATmega48 8MHz内臓オシレータ 8MHz動作
# Int. RC Osc. 8MHz CKDIV=0, PWRDWN/RESET: 6CK/14CK+65ms
CLOCK := 8000000
FUSES := -U lfuse:w:0xE2:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m

# ATmega48 16MHzクリスタル 16MHz動作
# Ext. Crystal Osc. 8MHz CKDIV=0, PWRDWN/RESET: 16KCK/14CK+65ms
# CLOCK := 16000000
# FUSES := -U lfuse:w:0xFF:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m

# 使用オリジナルライブラリ
EXTERNAL_LIBDIR :=

include ../../build.mk
