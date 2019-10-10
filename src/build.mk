# オブジェクトファイル

LIBDIR=$(PWD)/../lib

OBJS = $(addsuffix .o, $(basename $(shell find . -type f -name '*.c'))) $(shell for i in $(MLIBS); do echo "$(LIBDIR)/$$i.o"; done)

DEPS = $(OBJS:%.o=%.d)

AVRDUDE= avrdude $(PROGRAMMER) -p $(DEVICE) 

COMPILE = avr-gcc -Wall -Os -std=gnu99 -I $(PWD)/../include -I . -L $(LIBDIR) -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

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
	rm -f main.hex main.elf $(OBJS)

main.elf: $(OBJS)
	$(COMPILE) -o main.elf $(OBJS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c

