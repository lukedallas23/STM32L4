#spi.elf: main.c
#	arm-none-eabi-gcc main.c startup.c lib/gpio/def.h lib/gpio/gpiolib.h lib/gpio/gpiolib.c lib/spi/def.h lib/spi/spilib.h lib/spi/spilib.c lib/pindef.c lib/pindef.h interruptTable.h interruptTable.c lib/reg.c lib/reg.h lib/rcc/def.h lib/rcc/rcclib.c lib/rcc/rcclib.h lib/dma/def.h lib/dma/dmalib.h lib/dma/dmalib.c lib/des/def.h lib/des/deslib.h lib/des/deslib.c -T linker_script.ld -o spi.elf -mcpu=cortex-m4 -mthumb -nostdlib

#lib/rcc/rcc.o:  


lib/reg.o:
	arm-none-eabi-gcc -c reg.c -o reg.o

