#include "usartlib.h"

uint32_t usartGetBaseAddress(UART_MODULE module) {
    switch (module) {
        case 1: return R_USART1_BASE;
        case 2: return R_USART2_BASE;
        case 3: return R_USART3_BASE;
        case 4: return R_UART4_BASE;
        default: return 0;
    }
}