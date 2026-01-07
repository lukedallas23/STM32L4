#include "lib/gpio/gpiolib.h"
#include "lib/spi/spilib.h"

// Read the version register from the W5500.
// The rec data should equal {0xFF, 0xFF, 0xFF, 0x04}

int main() {

    gpioPinInit(GPIO_A4, GPIO_MODE_OUTPUT); // Chip select
    gpioPinInit(GPIO_B3, GPIO_MODE_OUTPUT); // Heartbeat LED
    gpioSetPinLevel(GPIO_A4, GPIO_VAL_HIGH);
    gpioSetPinLevel(GPIO_B3, GPIO_VAL_HIGH);

    spiMasterModuleInit(1, GPIO_A7, GPIO_A6, GPIO_A5, 0);
    uint8_t data[4] = {0x00, 0x39, 0x01, 0xFF};
    uint8_t rec[60] = {
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99
    };

    /*
    gpioSetPinLevel(GPIO_A4, GPIO_VAL_LOW);
    spiSendDataInt(1, 4, data, &rec[4]);
    while (spiSendDataInt(1, 0, NULL, NULL) == 1);
    spiSendDataInt(1, 4, data, &rec[8]);
    while (spiSendDataInt(1, 0, NULL, NULL) == 1);
    gpioSetPinLevel(GPIO_A4, GPIO_VAL_HIGH);
    */
    gpioSetPinLevel(GPIO_A4, GPIO_VAL_LOW);
    spiSendDataDma(1, 4, data, &rec[4]);

    while (1) {
        
        volatile int j = 250000;
        if (rec[7] == 0x04) {
            j = 50000;
        }
        for (volatile int i = 0; i < j; i++);
        gpioSetPinLevel(GPIO_B3, !gpioGetPinLevel(GPIO_B3));;
    }
    return 0;
}

/*
void hard_fault_handler() {
    gpioPinInit(GPIO_B3, GPIO_MODE_OUTPUT);
    while (1) {
        for (volatile int i = 0; i < 250000; i++);
        gpioSetPinLevel(GPIO_B3, !gpioGetPinLevel(GPIO_B3));
    }

}
*/
