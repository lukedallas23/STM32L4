#include "dev/W5500/w5500.h"
#include "lib/usart/usartlib.h"
//#include <string.h>

#define W5500_MAIN_DEAFULT {1, GPIO_A7, GPIO_A6, GPIO_A5, GPIO_A4, \
400000, {192, 168, 1, 1}, {0, 0, 0, 0}, {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54}, {102, 72, 84, 21}}

char str[14] = "Hello World\n\r\0";

int main() {

    gpioPinInit(GPIO_B3, GPIO_MODE_OUTPUT); // Heartbeat LED
    gpioSetPinLevel(GPIO_B3, GPIO_VAL_HIGH);

    uartInfo info;
    info.tx = GPIO_A9;
    info.rx = GPIO_A10;
    info.module = 1;
    info.baudRate = 9600;

    uartInitModule(&info);

    //w5500_info w5500 = W5500_MAIN_DEAFULT;
    //w5500_socket sock0 = {0, W5500_UDP_MODE, 55554, {192, 168, 1, 1}, 55555, 2, 2, 0, 0};

    //w5500_init_device(&w5500);
    //w5500_open_socket(&w5500, &sock0);

    while (1) {
        
        volatile int j = 2500000;
        for (volatile int i = 0; i < j; i++);
        gpioSetPinLevel(GPIO_B3, !gpioGetPinLevel(GPIO_B3));

        uartTx(&info, str, 13);
    }
        
    return 0;
}
