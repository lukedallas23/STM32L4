CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib -T stm32/linker_script.ld 

objects = lib/des/deslib.o \
lib/dma/dmalib.o \
lib/gpio/gpiolib.o \
lib/rcc/rcclib.o \
lib/spi/spilib.o \
lib/pindef.o \
lib/reg.o \
stm32/interruptTable.o \
dev/W5500/w5500.o


main.elf: $(objects)
	$(CC) $(CFLAGS) $^ main.c stm32/startup.c -o main.elf 

$(objects): %.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm main.elf
	rm $(objects)
	