
APP  := main
SRCC := $(shell find . -type f -name '*.c')
OBJS := $(SRCC:%.c=%.o)
COMPILE := gcc -Wall -Os -std=gnu99 -lwiringPi

$(APP): $(OBJS)
	$(COMPILE) -o $@ $(OBJS)

.c.o:
	$(COMPILE) -c $< -o $@

clean:
	rm -f *.o $(APP)

