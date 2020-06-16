# 動作デバイス ( リスト: avr-as -mlist-devices )
DEVICE := atmega168p

# Int. RC 8MHz
FUSES := -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m
CLOCK := 8000000

# # Full-swing Crystal CKSEL-1111 SUT=111
# FUSES := -U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m
# CLOCK := 16000000

# プログラマ
PROGRAMMER := -c avrisp2

# ------------------------------------

HDRS    := $(shell find . -type f -name '*.h')
SRCC    := $(shell find . -type f -name '*.c')
SRCA    := $(shell find . -type f -name '*.S')
OBJS    := $(SRCC:%.c=%.o) $(SRCA:%.S=%.o)
DEPS    := $(OBJS:%.o=%.d)
AVRDUDE := avrdude $(PROGRAMMER) -p $(DEVICE) 
COMPILE := avr-gcc -Wall -Os -std=gnu99 -I . -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

all:	main.hex

-include $(DEPS)

%.o: %.c
	$(COMPILE) -c -MMD -MP $<

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJS) $(OBJS:.o=.d)

main.elf: $(OBJS) $(HDRS)
	$(COMPILE) -o main.elf $(OBJS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

disasm:	main.elf
	avr-objdump -d main.elf
cpp:
	$(COMPILE) -E main.c

