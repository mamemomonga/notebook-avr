PROGRAMMER     := -c avrisp2
EXTLIB_DIR     := extlib/
EXTERNAL_FILES := $(wildcard $(EXTERNAL_LIBDIR)/*.c $(EXTERNAL_LIBDIR)/*.S $(EXTERNAL_LIBDIR)/*.h)
EXTLIB_SRCS    := $(addprefix $(EXTLIB_DIR), $(notdir $(filter %.c,$(EXTERNAL_FILES)) $(filter %.S,$(EXTERNAL_FILES))))
EXTLIB_OBJS    := $(addsuffix .o, $(basename $(EXTLIB_SRCS)))
LOCAL_OBJS     := $(addsuffix .o, $(basename $(wildcard *.c *.S)))
OBJS           := $(LOCAL_OBJS) $(EXTLIB_OBJS)
AVRDUDE        := avrdude $(PROGRAMMER) -p $(DEVICE)

CC     := avr-gcc
CFLAGS := -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -std=gnu99 -I . -I $(EXTLIB_DIR) -L $(EXTLIB_DIR)

all: main.hex

$(EXTLIB_SRCS): $(EXTERNAL_FILES)
	mkdir -p $(EXTLIB_DIR)
	cp $^ $(EXTLIB_DIR)

$(OBJS): $(EXTLIB_SRCS)
$(LOCAL_OBJS): $(EXTLIB_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf *.d $(OBJS)
	rm -rf $(EXTLIB_DIR)

main.elf: $(OBJS)
	$(CC) $(CFLAGS) -o main.elf $(OBJS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(CC) $(CFLAGS) -E main.c
