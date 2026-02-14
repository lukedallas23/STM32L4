#ifndef UARTLIB_H
#define UARTLIB_H

#include "def.h"
#include "../rcc/rcclib.h"
#include "../gpio/gpiolib.h"
#include "../../stm32/interruptTable.h"
#include "../reg.h"
#include "../pindef.h"

typedef uint8_t UART_MODULE;

typedef struct {
	
	UART_MODULE		module;
	GPIO_PIN		tx;
	GPIO_PIN		rx;
	uint32_t		baudRate;
	
	
} uartInfo;

uint32_t usartGetBaseAddr(UART_MODULE module);
void uartInitModule(uartInfo *info);
void uartTx(uartInfo *info, uint8_t *buf, uint32_t len);

#endif