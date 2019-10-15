DEVICE := attiny13

# プログラム書き換え時にEEPROMを削除する
# FUSES := -U hfuse:w:0xff:m -U lfuse:w:0x7a:m

# プログラム書き換え時にEEPROMを削除しない
FUSES := -U lfuse:w:0x3a:m -U hfuse:w:0xff:m

CLOCK := 9600000
PROGRAMMER := -c avrisp2
EXTERNAL_LIBS := ../serial/tinySerial ../serial/tinySerialAsm

include ./build.mk
