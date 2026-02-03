#ifndef UARTLIB_H
#define UARTLIB_H

#include "def.h"
#include <stdlib.h>
#include "../rcc/rcclib.h"
#include "../gpio/gpilib.h"
#include "../../interruptTable.h"
#include "../reg.h"
#include "../pindef.h"

typedef uint8_t UART_MODULE;

typedef struct {
	
	UART_MODULE		module;
	
	
} uartInfo;


#endif
