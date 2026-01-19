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
#define     R_RCC_CCIPR_OFF         0x88
#define     R_RCC_BDCR_OFF          0x90
#define     R_RCC_CSR_OFF           0x94
#define     R_RCC_CRRCR_OFF         0x98
#define     R_RCC_CCIPR2_OFF        0x9C


//
// Clock Control Register (RCC_CR) definitions
//
#define     N_PLLSAI1RDY    27
#define     N_PLLSAI1ON     26
#define     N_PLLRDY        25
#define     N_PLLON         24
#define     N_CSSON         19
#define     N_HSEBYP        18
#define     N_HSERDY        17
#define     N_HSEON         16
#define     N_HSIASFS       11
#define     N_HSIRDY        10
#define     N_HSIKERON      9
#define     N_HSION         8
#define     N_MSIRANGE      4
#define     N_MSIRGSEL      3
#define     N_MSIPLLEN      2
#define     N_MSIRDY        1
#define     N_MSION         0

#define     S_PLLSAI1RDY    1
#define     S_PLLSAI1ON     1
#define     S_PLLRDY        1
#define     S_PLLON         1
#define     S_CSSON         1
#define     S_HSEBYP        1
#define     S_HSERDY        1
#define     S_HSEON         1
#define     S_HSIASFS       1
#define     S_HSIRDY        1
#define     S_HSIKERON      1
#define     S_HSION         1
#define     S_MSIRANGE      4
#define     S_MSIRGSEL      1
#define     S_MSIPLLEN      1
#define     S_MSIRDY        1
#define     S_MSION         1

typedef enum {
    RCC_PLL_UNLOCKED    = 0,
    RCC_PLL_LOCKED      = 1
} RCC_PLLSAI1RDY_STATUS;

typedef enum {
    RCC_PLLSAI1_OFF     = 0,
    RCC_PLLSAI1_ON      = 1
} RCC_PLLSAI1_MODE;

typedef enum {
    RCC_PLL_UNLOCK      = 0,
    RCC_PLL_LOCK        = 1
} RCC_PLLRDY_MODE;

typedef enum {
    RCC_PLL_OFF         = 0,
    RCC_PLL_ON          = 1
} RCC_PLLON_MODE;

typedef enum {
    RCC_CSS_OFF         = 0,
    RCC_CSS_ON          = 1
} RCC_CSSON_MODE;

typedef enum {
    RCC_HSE_CRS_NOT_BYP = 0,
    RCC_HSE_CRS_BYP     = 1
} RCC_HSEBYP_MODE;

typedef enum {
    RCC_HSE_NOT_READY   = 0,
    RCC_HSE_READY       = 1
} RCC_HSERDY_STATUS;

typedef enum {
    RCC_HSE_OSC_OFF     = 0,
    RCC_HSE_OSC_ON      = 1
} RCC_HSEON_MODE;

typedef enum {
    RCC_HSI16_NOT_EN    = 0,
    RCC_HSI16_EN        = 1
} RCC_HSIASFS_MODE;

typedef enum {
    RCC_HSI16_NOT_RDY   = 0,
    RCC_HSI16_RDY       = 1
} RCC_HSIRDY_MODE;

typedef enum {
    RCC_HSI16_NO_EFF    = 0,
    RCC_HSI16_FORCE_ON  = 1
} RCC_HSIKERON_MODE;

typedef enum {
    RCC_HSI16_CLK_OFF   = 0,
    RCC_HSI16_CLK_ON    = 1
} RCC_HSION_MODE;

typedef enum {
    RCC_MSIRNG_100K     = 0,
    RCC_MSIRNG_200K     = 1,
    RCC_MSIRNG_400K     = 2,
    RCC_MSIRNG_800K     = 3,
    RCC_MSIRNG_1M       = 4,
    RCC_MSIRNG_2M       = 5,
    RCC_MSIRNG_4M       = 6,
    RCC_MSIRNG_8M       = 7,
    RCC_MSIRNG_16M      = 8,
    RCC_MSIRNG_24M      = 9,
    RCC_MSIRNG_32M      = 10,
    RCC_MSIRNG_48M      = 11
} RCC_MSIRANGE_MODE;

typedef enum {
    RCC_MSIRNG_RCC_CSR  = 0,
    RCC_MSIRNG_RCC_CR   = 1
} RCC_MSIRGSEL_MODE;

typedef enum {
    RCC_MSI_NOT_RDY     = 0,
    RCC_MSI_RDY         = 1
} RCC_MSIRDY_STATUS;

typedef enum {
    RCC_MSI_OSC_OFF     = 0,
    RCC_MSI_OSC_ON      = 1
} RCC_MSION_MODE;


//
// Internal Clock Sources Calibration Register (RCC_ICSCR) definitions
//
#define     N_HSITRIM       24
#define     N_HSICAL        16
#define     N_MSITRIM       8
#define     N_MSICAL        0

#define     S_HSITRIM       7
#define     S_HSICAL        8
#define     S_MSITRIM       8
#define     S_MSICAL        8


//
// Clock Configuration Register (RCC_CFGR) definitions
//
#define     N_MCOPRE        28
#define     N_MCOSEL        24
#define     N_STOPWUCK      15
#define     N_PPRE2         11
#define     N_PPRE1         8
#define     N_HPRE          4
#define     N_SWS           2
#define     N_SW            0

#define     S_MCOPRE        3
#define     S_MCOSEL        4
#define     S_STOPWUCK      1
#define     S_PPRE2         3
#define     S_PPRE1         3
#define     S_HPRE          4
#define     S_SWS           2
#define     S_SW            2

typedef enum {
    RCC_MCO_FULL        = 0,
    RCC_MCO_1_2         = 1,
    RCC_MCO_1_4         = 2,
    RCC_MCO_1_8         = 3,
    RCC_MCO_1_16        = 4
} RCC_MCOPRE_MODE;

typedef enum {
    RCC_CLK_NO_MCO      = 0,
    RCC_CLK_SYSCLK      = 1,
    RCC_CLK_MSI         = 2,
    RCC_CLK_HSI16       = 3,
    RCC_CLK_HSE         = 4,
    RCC_CLK_MAIN_PLL    = 5,
    RCC_CLK_LSI         = 6,
    RCC_CLK_LSE         = 7,
    RCC_CLK_HSI48       = 8
} RCC_MCOSEL_MODE;

typedef enum {
    RCC_STOPWUCK_MSI    = 0,
    RCC_STOPWUCK_HSI16  = 1
} RCC_STOPWUCK_MODE;

typedef enum {
    RCC_PPRE_FULL       = 0,
    RCC_PPRE_1_2        = 4,
    RCC_PPRE_1_4        = 5,
    RCC_PPRE_1_8        = 6,
    RCC_PPRE_1_16       = 7
} RCC_PPRE_MODE;

typedef enum {
    RCC_SYSCLK_FULL     = 0,
    RCC_SYSCLK_1_2      = 8,
    RCC_SYSCLK_1_4      = 9,
    RCC_SYSCLK_1_8      = 10,
    RCC_SYSCLK_1_16     = 11,
    RCC_SYSCLK_1_64     = 12,
    RCC_SYSCLK_1_128    = 13,
    RCC_SYSCLK_1_256    = 14,
    RCC_SYSCLK_1_512    = 15,
} RCC_HPRE_MODE;

typedef enum {
    RCC_SWS_MSI         = 0,
    RCC_SWS_HSI16       = 1,
    RCC_SWS_HSE         = 2,
    RCC_SWS_PLL         = 3
} RCC_SWS_STATUS;

typedef enum {
    RCC_SW_MSI          = 0,
    RCC_SW_HSI16        = 1,
    RCC_SW_HSE          = 2,
    RCC_SW_PLL          = 3
} RCC_SW_MODE;


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


//
// 
//

#endif