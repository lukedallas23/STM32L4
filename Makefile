CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib -T linker_script.ld 

objects = lib/des/deslib.o \
lib/dma/dmalib.o \
lib/gpio/gpiolib.o \
lib/rcc/rcclib.o \
lib/spi/spilib.o \
lib/pindef.o \
lib/reg.o \
interruptTable.o \


main.elf: $(objects)
	$(CC) $(CFLAGS) $^ main.c startup.c -o main.elf 

$(objects): %.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm main.elf
	rm $(objects)
	