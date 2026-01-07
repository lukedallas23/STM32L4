#ifndef DES_DEF
#define DES_DEF

//
// DES Module Base Addresses
//
#define     R_DES_UDID_BASE         0x1FFF7590
#define     R_DES_FSDR_BASE         0x1FFF75E0
#define     R_DES_PDR_BASE          0x1FFF7500

//
// Unique Device ID Register (96 Bits) definitions
//
#define     N_LOT_NUM       0
#define     N_WAF_NUM       40

#define     S_LOT_NUM       40
#define     S_WAF_NUM       56


//
// Flash Size Data Register definitions
//
#define     N_FLASH_SIZE        0
#define     S_FLASH_SIZE        16


//
// Package Data Register definitions
//
#define     N_PKG               0
#define     S_PKG               5

typedef enum {
    LQFP64              = 0,
    WLCSP64             = 1,
    LQFP100             = 2,
    WLCSP36             = 5,
    UFQFPN32            = 8,
    LQFP432             = 9,
    UFQFPN48            = 10,
    LQFP48              = 11,
    WLCSP49             = 12,
    UFBGA64             = 13,
    UFBGA100            = 14,
    WLCSP36_EX_SMPS     = 15,
    LQFP64_EX_SMPS      = 22 
} DES_PKG_TYPE;



#endif