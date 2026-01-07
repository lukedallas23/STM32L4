#ifndef RCC_DEF_H
#define RCC_DEF_H

//
// RCC Module Base Addresse
//
#define     R_RCC_BASE          0x40021000

//
//  RCC Register Offsets
//
#define     R_RCC_CR_OFF            0x00
#define     R_RCC_ICSCR_OFF         0x04
#define     R_RCC_CFGR_OFF          0x08
#define     R_RCC_PLLCFGR_OFF       0x0C
#define     R_RCC_PLLSAI1CFGR_OFF   0x10
#define     R_RCC_CIER_OFF          0x18
#define     R_RCC_CIFR_OFF          0x1C
#define     R_RCC_CICR_OFF          0x20
#define     R_RCC_AHB1RSTR_OFF      0x28
#define     R_RCC_AHB2RSTR_OFF      0x2C
#define     R_RCC_AHB3RSTR_OFF      0x30
#define     R_RCC_APB1RSTR1_OFF     0x38
#define     R_RCC_APB1RSTR2_OFF     0x3C
#define     R_RCC_APB2RSTR_OFF      0x40
#define     R_RCC_AHB1ENR_OFF       0x48
#define     R_RCC_AHB2ENR_OFF       0x4C
#define     R_RCC_AHB3ENR_OFF       0x50
#define     R_RCC_APB1ENR1_OFF      0x58
#define     R_RCC_APB1ENR2_OFF      0x5C
#define     R_RCC_APB2ENR_OFF       0x60
#define     R_RCC_AHB1SMENR_OFF     0x68
#define     R_RCC_AHB2SMENR_OFF     0x6C
#define     R_RCC_AHB3SMENR_OFF     0x70
#define     R_RCC_APB1SMENR1_OFF    0x78
#define     R_RCC_APB1SMENR2_OFF    0x7C
#define     R_RCC_APB2SMENR_OFF     0x80
#define     R_RCC_CCIPR             0x88
#define     R_RCC_BDCR              0x90
#define     R_RCC_CSR               0x94
#define     R_RCC_CRRCR             0x98
#define     R_RCC_CCIPR2            0x9C


//
// AHB1 Peripheral Reset Register (RCC_AHB1RSTR) definitions
//
#define     N_TSCRST        16
#define     N_CRCRST        12
#define     N_FLASHRST      8
#define     N_DMA2RST       1
#define     N_DMA1RST       0

#define     S_RCC_RST_ST    1

typedef enum {
    RCC_CLEAR_RST           = 0,
    RCC_RESET               = 1
} RCC_RST_STATE;


//
// AHB2 Peripheral Reset Register (RCC_AHB2RSTR) definitions
//
#define     N_RNGRST        18
#define     N_AESRST        16
#define     N_ADCRST        13
#define     N_GPIOHRST      7
#define     N_GPIOERST      4
#define     N_GPIODRST      3
#define     N_GPIOCRST      2
#define     N_GPIOBRST      1
#define     N_GPIOARST      0


//
// AHB3 Peripheral Reset Register (RCC_AHB3RSTR) definitions
//
#define     N_QSPIRST       8


//
// APB1 Peripheral Reset Register 1 (RCC_APB1RSTR1) definitions
//
#define     N_LPTIM1RST     31
#define     N_OPAMPRST      30
#define     N_DAC1RST       29
#define     N_PWRRST        28
#define     N_USBFSRST      26
#define     N_CAN1RST       25
#define     N_CRSRST        24
#define     N_I2C3RST       23
#define     N_I2C2RST       22
#define     N_I2C1RST       21
#define     N_UART4RST      19
#define     N_USART3RST     18
#define     N_USART2RST     17
#define     N_SPI3RST       15
#define     N_SPI2RST       14
#define     N_LCDRST        9
#define     N_TIM7RST       5
#define     N_TIM6RST       4
#define     N_TIM3RST       1
#define     N_TIM2RST       0


//
// APB1 Peripheral Reset Register 2 (RCC_APB1RSTR2) definitions
//
#define     N_LPTIM2RST     5
#define     N_SWPMI1RST     2
#define     N_I2C4RST       1
#define     N_LPUART1RST    0


//
// APB2 Peripheral Reset Register (RCC_APB2RSTR) definitions
//
#define     N_DFSDM1RST     24
#define     N_SAI1RST       21
#define     N_TIM16RST      17
#define     N_TIM15RST      16
#define     N_USART1RST     14
#define     N_SPI1RST       12
#define     N_TIM1RST       11
#define     N_SDMMC1RST     10
#define     N_SYSCFGRST     0


//
// AHB1 Peripheral Clock Enable Register (RCC_AHB1ENR) definitions
//
#define     N_TSCEN         16
#define     N_CRCEN         12
#define     N_FLASHEN       8
#define     N_DMA2EN        1
#define     N_DMA1EN        0

#define     S_RCC_CLK_ST    1

typedef enum {
    RCC_CLOCK_DIS       = 0,
    RCC_CLOCK_EN        = 1
} RCC_CLK_STATE;


//
// AHB2 Peripheral Clock Enable Register (RCC_AHB2ENR) definitions
//
#define     N_RNGEN         18
#define     N_AESEN         16
#define     N_ADCEN         13
#define     N_GPIOHEN       7
#define     N_GPIOEEN       4
#define     N_GPIODEN       3
#define     N_GPIOCEN       2
#define     N_GPIOBEN       1
#define     N_GPIOAEN       0


//
// AHB3 Peripheral Clock Enable Register (RCC_AHB3ENR) definitions
//
#define     N_QSPIEN        8


//
// APB1 Peripheral Clock Enable Register 1 (RCC_APB1ENR1) definitions
//
#define     N_LPTIM1EN      31
#define     N_OPAMPEN       30
#define     N_DAC1EN        29
#define     N_PWREN         28
#define     N_USBFSEN       26
#define     N_CAN1EN        25
#define     N_CRSEN         24
#define     N_I2C3EN        23
#define     N_I2C2EN        22
#define     N_I2C1EN        21
#define     N_UART4EN       19
#define     N_USART3EN      18
#define     N_USART2EN      17
#define     N_SPI3EN        15
#define     N_SPI2EN        14
#define     N_WWDGEN        11
#define     N_RTCAPBEN      10
#define     N_LCDEN         9
#define     N_TIM7EN        5
#define     N_TIM6EN        4
#define     N_TIM3EN        1
#define     N_TIM2EN        0


//
// APB1 Peripheral Clock Enable Register 2 (RCC_APB1ENR2) definitions
//
#define     N_LPTIM2EN      5
#define     N_SWPMI1EN      2
#define     N_I2C4EN        1
#define     N_LPUART1EN     0


//
// APB2 Peripheral Clock Enable Register (RCC_APB2ENR) definitions
//
#define     N_DFSDM1EN      24
#define     N_SAI1EN        21
#define     N_TIM16EN       17
#define     N_TIM15EN       16
#define     N_USART1EN      14
#define     N_SPI1EN        12
#define     N_TIM1EN        11
#define     N_SDMMC1EN      10
#define     N_FWEN          7
#define     N_SYSCFGEN      0


#endif