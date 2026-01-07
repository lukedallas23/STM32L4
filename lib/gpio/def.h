#ifndef GPIO_DEF_H
#define GPIO_DEF_H

//
// GPIO Base Addresses
//
#define     R_GPIOA_BASE            0x48000000
#define     R_GPIOB_BASE            0x48000400
#define     R_GPIOC_BASE            0x48000800
#define     R_GPIOD_BASE            0x48000C00
#define     R_GPIOH_BASE            0x48001C00


//
// GPIO Register Offsets
//
#define     R_GPIO_MODER_OFF        0x00
#define     R_GPIO_OTYPER_OFF       0x04
#define     R_GPIO_OSPEEDR_OFF      0x08
#define     R_GPIO_PUPDR_OFF        0x0C
#define     R_GPIO_IDR_OFF          0x10
#define     R_GPIO_ODR_OFF          0x14
#define     R_GPIO_BSRR_OFF         0x18
#define     R_GPIO_LCKR_OFF         0x1C
#define     R_GPIO_AFRL_OFF         0x20
#define     R_GPIO_AFRH_OFF         0x24
#define     R_GPIO_BRR_OFF          0x28


//
// GPIO Port Mode Register (GPIOx_MODER) definitions
//
#define     N_MODE15                30
#define     N_MODE14                28
#define     N_MODE13                26
#define     N_MODE12                24
#define     N_MODE11                22
#define     N_MODE10                20
#define     N_MODE9                 18
#define     N_MODE8                 16
#define     N_MODE7                 14
#define     N_MODE6                 12
#define     N_MODE5                 10
#define     N_MODE4                 8
#define     N_MODE3                 6
#define     N_MODE2                 4
#define     N_MODE1                 2
#define     N_MODE0                 0

#define     S_MODE                  2

typedef enum {
    GPIPO_MODE_INPUT     = 0b00,
    GPIO_MODE_OUTPUT     = 0b01,
    GPIO_MODE_ALT_FN     = 0b10,
    GPIO_MODE_ANALOG     = 0b11
} GPIO_PIN_MODE;


//
// GPIO Port Output Type Register (GPIOx_OTYPER) definitions
//
#define     N_OT15                  15
#define     N_OT14                  14
#define     N_OT13                  13
#define     N_OT12                  12
#define     N_OT11                  11
#define     N_OT10                  10
#define     N_OT9                   9
#define     N_OT8                   8
#define     N_OT7                   7
#define     N_OT6                   6
#define     N_OT5                   5
#define     N_OT4                   4
#define     N_OT3                   3
#define     N_OT2                   2
#define     N_OT1                   1
#define     N_OT0                   0

#define     S_OT                    1

typedef enum {
    GPIO_OT_PUSH_PULL     = 0,
    GPIO_OT_OPEN_DRAIN    = 1
} GPIO_OUT_TYPE;



//
// GPIO Port Output Speed Register (GPIOx_OSPEEDR) definitions
//
#define     N_OSPEED15              30
#define     N_OSPEED14              28
#define     N_OSPEED13              26
#define     N_OSPEED12              24
#define     N_OSPEED11              22
#define     N_OSPEED10              20
#define     N_OSPEED9               18
#define     N_OSPEED8               16
#define     N_OSPEED7               14
#define     N_OSPEED6               12
#define     N_OSPEED5               10
#define     N_OSPEED4               8
#define     N_OSPEED3               6
#define     N_OSPEED2               4
#define     N_OSPEED1               2
#define     N_OSPEED0               0

#define     S_OSPEED                2

typedef enum {
    GPIO_SPEED_LOW         = 0,
    GPIO_SPEED_MEDIUM      = 1,
    GPIO_SPEED_HIGH        = 2,
    GPIO_SPEED_VERY_HIGH   = 3
} GPIO_OUT_SPEED;


//
// GPIO Port Pull-up/Pull-down Register (GPIOx_PUPDR) definitions
//
#define     N_PUPD15                30
#define     N_PUPD14                28
#define     N_PUPD13                26
#define     N_PUPD12                24
#define     N_PUPD11                22
#define     N_PUPD10                20
#define     N_PUPD9                 18
#define     N_PUPD8                 16
#define     N_PUPD7                 14
#define     N_PUPD6                 12
#define     N_PUPD5                 10
#define     N_PUPD4                 8
#define     N_PUPD3                 6
#define     N_PUPD2                 4
#define     N_PUPD1                 2
#define     N_PUPD0                 0

#define     S_PUPD                  2

typedef enum {
    GPIO_NO_PUPD          = 0,
    GPIO_PULL_UP          = 1,
    GPIO_PULL_DOWN        = 2
} GPIO_PULL_UP_DOWN;

//
// GPIO Port Input Data Register (GPIOx_IDR) definitions
//
#define     N_ID15                  15
#define     N_ID14                  14
#define     N_ID13                  13
#define     N_ID12                  12
#define     N_ID11                  11
#define     N_ID10                  10
#define     N_ID9                   9
#define     N_ID8                   8
#define     N_ID7                   7
#define     N_ID6                   6
#define     N_ID5                   5
#define     N_ID4                   4
#define     N_ID3                   3
#define     N_ID2                   2
#define     N_ID1                   1
#define     N_ID0                   0

#define     S_ID                    1

typedef enum {
    GPIO_VAL_HIGH   = 1,
    GPIO_VAL_LOW    = 0
} GPIO_PIN_VAL;



//
// GPIO Port Output Data Register (GPIOx_ODR) definitions
//
#define     N_OD15                  15
#define     N_OD14                  14
#define     N_OD13                  13
#define     N_OD12                  12
#define     N_OD11                  11
#define     N_OD10                  10
#define     N_OD9                   9
#define     N_OD8                   8
#define     N_OD7                   7
#define     N_OD6                   6
#define     N_OD5                   5
#define     N_OD4                   4
#define     N_OD3                   3
#define     N_OD2                   2
#define     N_OD1                   1
#define     N_OD0                   0

#define     S_OD                    1


//
// GPIO Port Bit Set/Reset Register (GPIOx_BSRR) definitions
//
#define     N_BR15                  31
#define     N_BR14                  30
#define     N_BR13                  29
#define     N_BR12                  28
#define     N_BR11                  27
#define     N_BR10                  26
#define     N_BR9                   25
#define     N_BR8                   24
#define     N_BR7                   23
#define     N_BR6                   22
#define     N_BR5                   21
#define     N_BR4                   20
#define     N_BR3                   19
#define     N_BR2                   18
#define     N_BR1                   17   
#define     N_BR0                   16
#define     N_BS15                  15
#define     N_BS14                  14
#define     N_BS13                  13
#define     N_BS12                  12
#define     N_BS11                  11
#define     N_BS10                  10
#define     N_BS9                   9
#define     N_BS8                   8
#define     N_BS7                   7
#define     N_BS6                   6
#define     N_BS5                   5
#define     N_BS4                   4
#define     N_BS3                   3
#define     N_BS2                   2
#define     N_BS1                   1
#define     N_BS0                   0

#define     S_BR                    1
#define     S_BS                    1

typedef enum {
    GPIO_BS_NO_ACTION       = 0,
    GPIO_BS_SET             = 1
} GPIO_BS_MODE;

typedef enum {
    GPIO_BR_NO_ACTION       = 0,
    GPIO_BR_RESET           = 1
} GPIO_BR_MODE;


//
// GPIO Port Configuration Lock Register (GPIOx_LCKR) definitions
//
#define     N_LCKK                  16
#define     N_LCK15                 15
#define     N_LCK14                 14
#define     N_LCK13                 13
#define     N_LCK12                 12
#define     N_LCK11                 11
#define     N_LCK10                 10
#define     N_LCK9                  9
#define     N_LCK8                  8
#define     N_LCK7                  7
#define     N_LCK6                  6
#define     N_LCK5                  5
#define     N_LCK4                  4
#define     N_LCK3                  3
#define     N_LCK2                  2
#define     N_LCK1                  1
#define     N_LCK0                  0

#define     S_LCKR                  1

typedef enum {
    GPIO_LCKK_NOT_ACTIVE        = 0,
    GPIO_LCKK_ACTIVE            = 1
} GPIO_LCKK_MODE;

typedef enum {
    GPIO_LCK_NOT_LOCK          = 0,
    GPIO_LCK_LOCK              = 1
} GPIO_LCK_MODE;


//
// GPIO Alternate Function Registers (GPIOx_AFRL & GPIOx_ALRH) definitions
//
#define     N_AFSEL15               28
#define     N_AFSEL14               24
#define     N_AFSEL13               20
#define     N_AFSEL12               16
#define     N_AFSEL11               12
#define     N_AFSEL10               8
#define     N_AFSEL9                4
#define     N_AFSEL8                0
#define     N_AFSEL7                28
#define     N_AFSEL6                24
#define     N_AFSEL5                20
#define     N_AFSEL4                16
#define     N_AFSEL3                12
#define     N_AFSEL2                8
#define     N_AFSEL1                4
#define     N_AFSEL0                0

#define     S_AFSEL                 4

typedef enum {
    ALT_FN0         = 0,
    ALT_FN1         = 1,
    ALT_FN2         = 2,
    ALT_FN3         = 3,
    ALT_FN4         = 4,
    ALT_FN5         = 5,
    ALT_FN6         = 6,
    ALT_FN7         = 7,
    ALT_FN8         = 8,
    ALT_FN9         = 9,
    ALT_FN10        = 10,
    ALT_FN11        = 11,
    ALT_FN12        = 12,
    ALT_FN13        = 13,
    ALT_FN14        = 14,
    ALT_FN15        = 15
} ALT_FN;


//
// GPIO Port Bit Reset Register (GPIOx_BRR) definitions
//
#define     N_BRR15                  15
#define     N_BRR14                  14
#define     N_BRR13                  13
#define     N_BRR12                  12
#define     N_BRR11                  11
#define     N_BRR10                  10
#define     N_BRR9                   9
#define     N_BRR8                   8
#define     N_BRR7                   7
#define     N_BRR6                   6
#define     N_BRR5                   5
#define     N_BRR4                   4
#define     N_BRR3                   3
#define     N_BRR2                   2
#define     N_BRR1                   1
#define     N_BRR0                   0

#define     S_BRR                   1

#endif