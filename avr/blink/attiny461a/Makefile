# 動作デバイス ( リスト: avr-as -mlist-devices )
DEVICE := attiny461

# ATTiny461A 8MHz内臓オシレータ 8MHz動作
# Int. RC Osc. 8MHz, CKDIV=0, PWRDWN/RESET: 6 CK/14CK+64ms
CLOCK := 8000000
FUSES := -U lfuse:w:0xE2:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m

# ATTiny461A 16MHzクリスタル 16MHz動作
# Ext. Crystal Osc. 8MHz~, CKDIV=8, PWRDWN/RESET: 16KCK/14CK+65ms
# CLOCK := 16000000
# FUSES := -U lfuse:w:0xFF:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m

# 使用オリジナルライブラリ
EXTERNAL_LIBDIR :=

include ../../build.mk
