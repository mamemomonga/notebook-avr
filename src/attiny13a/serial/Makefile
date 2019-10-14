DEVICE     := attiny13
CLOCK      := 9600000
PROGRAMMER := -c avrisp2
FUSES      := -U hfuse:w:0xff:m -U lfuse:w:0x7a:m
APPEND_OBJECTS := 

OBJECTS :=  $(addsuffix .o, $(basename $(shell find . -name '*.c' -o -name '*.S')) $(APPEND_OBJECTS))
AVRDUDE := avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE := avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -std=gnu99


all: main.hex

DEPS = $(OBJS:%.o=%.d)
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
	rm -f main.hex main.elf *.d $(OBJECTS)

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
