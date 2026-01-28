#include "dev/W5500/w5500.h"
#include <string.h>

#define W5500_MAIN_DEAFULT {1, GPIO_A7, GPIO_A6, GPIO_A5, GPIO_A4, \
400000, {1, 2, 3, 4}, {255, 255, 255, 0}, {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54}, {5, 6, 7, 8}}

int main() {

    gpioPinInit(GPIO_B3, GPIO_MODE_OUTPUT); // Heartbeat LED
    gpioSetPinLevel(GPIO_B3, GPIO_VAL_HIGH);

    w5500_info w5500 = W5500_MAIN_DEAFULT;

    w5500_init_device(&w5500);

    uint8_t rec[60] = {
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99
    };

    w5500_read(&w5500, W5500_MR | W5500_CR, &rec[4], 50);

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
