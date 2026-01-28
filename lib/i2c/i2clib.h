#ifndef I2CLIB_H
#define I2CLIB_H

#include "def.h"
#include <stdint.h>
#include "../reg.h"
#include "../gpio/gpiolib.h"
#include "../../interruptTable.h"

typedef uint8_t I2C_MODULE;

//
// I2C Timing Specifications
//
#define t_HD_DAT_MIN_Sm     0
#define t_HD_DAT_MIN_Fm     0
#define t_HD_DAT_MIN_Fmp    0
#define t_HD_DAT_MIN_SMBus  300
#define t_VD_DAT_MAX_Sm     3450
#define t_VD_DAT_MAX_Fm     900
#define t_VD_DAT_MAX_Fmp    450
#define t_VD_DAT_MAX_SMBus  3450
#define t_SU_DAT_MIN_Sm     250
#define t_SU_DAT_MIN_Fm     100
#define t_SU_DAT_MIN_Fmp    50
#define t_SU_DAT_MIN_SMBus  250
#define t_r_MAX_Sm          1000
#define t_r_MAX_Fm          300
#define t_r_MAX_Fmp         120
#define t_r_MAX_SMBus       1000
#define t_f_MAX_Sm          300
#define t_f_MAX_Fm          300
#define t_f_MAX_Fmp         120
#define t_f_MAX_SMBus       300

/*
SDADEL <= {t_VD_DAT_MAX_Sm - t_r_MAX_Sm - t_AF_MAX - [(DNF + 4) * t_I2CCLK]} / {(PRESC + 1) * t_I2CCLK}

{t_f_MAX_Sm + t_HD_DAT_MIN_Sm - t_AF_MIN - [(DNF + 3) * t_I2CCLK]} / {(PRESC + 1) * t_I2CCLK} <= SDADEL
{t_VD_DAT_MAX_Sm - t_r_MAX_Sm - t_AF_MAX - [(DNF + 4) * t_I2CCLK]} / {(PRESC + 1) * t_I2CCLK} >= SDADEL




*/

#endif