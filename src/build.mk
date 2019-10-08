# オブジェクトファイル
OBJECTS = $(addsuffix .o, $(basename $(shell find . -type f -name '*.c'))) $(shell for i in $(MLIBS); do echo "../../lib/$$i.o"; done)

# AVRDUDE
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE) 

# コンパイル
COMPILE = avr-gcc -Wall -Os -std=gnu99 -I $(PWD)/../../include -L $(PWD)/../../lib -DF_CPU=$(CLOCK) -DBAUD=$(BAUD) -mmcu=$(DEVICE)

all:	main.hex

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
	rm -f main.hex main.elf $(OBJECTS)

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c

