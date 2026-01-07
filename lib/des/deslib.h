/*
    lib/des/deslib.h

    STM32L41-46 Device Electronic Signature library.

    This library contains functions to read the unique device
    ID, flash size, and package.

    Date: 01/07/2026

*/

#ifndef DESLIB_H
#define DESLIB_H

#include "def.h"
#include "../reg.h"
#include <stdint.h>


//
// Unique Device ID Data Type
//
typedef struct {
    uint8_t     LOT_NUM[5];
    uint8_t     WAF_NUM[7];
} DES_UDID;


/*
    Get the Unique Device ID

    @param   Unique Device ID structure pointer

*/
void desGetUdid(DES_UDID *udid);


/*
    Get the flash size in KB

    @returns Flash size in KBytes

*/
uint16_t desGetFlashSizeKb();


/*
    Get the package type

    @returns Package type

*/
DES_PKG_TYPE desGetPkgType();

#endif