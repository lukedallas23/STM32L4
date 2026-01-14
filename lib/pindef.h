#include <stdint.h>
#include "reg.h"

/*
    Support for up to 13 ports with 16 pins each and a
    15th and 16th port which has up to 15 pins

    Port 0  (0x01 to 0x0F)  --> 0x00 is reserved
    Ports 1-14 are supported
    Port 15 (0xF0 to 0xFE)  --> 0xFF is reserved

    
*/


//
// Type Definitions
//
typedef uint8_t PIN;
typedef uint32_t FUNCTION;
typedef uint8_t MODULE;


//
// Used for when alternate function maps to all pins 
//
#define     ALL_PINS            0xFFFFFFFF

//
// Used for when an alternate function exists but is not supported on
// a particular platform
//
#define     FN_NOT_SUPPORTED    0xFF


//
// Pin Definitions
//
// Most siginificant four bits are the port (A,B,C, ...)
// Least siginificant four bits are pins within port (PA0, PA1, ...)
// Unused pins should be 0x00
// 0xFF should not be used. 
//
#define     PA0     0x10
#define     PA1     0x11
#define     PA2     0x12
#define     PA3     0x13
#define     PA4     0x14
#define     PA5     0x15
#define     PA6     0x16
#define     PA7     0x17
#define     PA8     0x18
#define     PA9     0x19
#define     PA10    0x1A
#define     PA11    0x1B
#define     PA12    0x1C
#define     PA13    0x1D
#define     PA14    0x1E
#define     PA15    0x1F
#define     PB0     0x20
#define     PB1     0x21
#define     PB2     0x00
#define     PB3     0x23
#define     PB4     0x24
#define     PB5     0x25
#define     PB6     0x26
#define     PB7     0x27
#define     PB8     0x00
#define     PB9     0x00
#define     PB10    0x00
#define     PB11    0x00
#define     PB12    0x00
#define     PB13    0x00
#define     PB14    0x00
#define     PB15    0x00
#define     PC0     0x00
#define     PC1     0x00
#define     PC2     0x00
#define     PC3     0x00
#define     PC4     0x00
#define     PC5     0x00
#define     PC6     0x00
#define     PC7     0x00
#define     PC8     0x00
#define     PC9     0x00
#define     PC10    0x00
#define     PC11    0x00
#define     PC12    0x00
#define     PC13    0x00
#define     PC14    0x3E
#define     PC15    0x3F
#define     PD0     0x00
#define     PD1     0x00
#define     PD2     0x00
#define     PD3     0x00
#define     PD4     0x00
#define     PD5     0x00
#define     PD6     0x00
#define     PD7     0x00
#define     PD8     0x00
#define     PD9     0x00
#define     PD10    0x00
#define     PD11    0x00
#define     PD12    0x00
#define     PD13    0x00
#define     PD14    0x00
#define     PD15    0x00
#define     PH0     0x00
#define     PH1     0x00
#define     PH2     0x00
#define     PH3     0x83
#define     PH4     0x00
#define     PH5     0x00
#define     PH6     0x00
#define     PH7     0x00
#define     PH8     0x00
#define     PH9     0x00
#define     PH10    0x00
#define     PH11    0x00
#define     PH12    0x00
#define     PH13    0x00
#define     PH14    0x00
#define     PH15    0x00

#define     PORTA   0x10
#define     PORTB   0x20
#define     PORTC   0x30
#define     PORTD   0x40
#define     PORTH   0x80


//
// Alternate Function Mappings
//
#define     AF_SYS_AF           0
#define     AF_TIM1             1
#define     AF_TIM2             1
#define     AF_LPTIM1           1
#define     AF_I2C1             4
#define     AF_I2C2             FN_NOT_SUPPORTED
#define     AF_I2C3             4
#define     AF_SPI1             5
#define     AF_SPI2             FN_NOT_SUPPORTED
#define     AF_SPI3             6
#define     AF_USART1           7
#define     AF_USART2           7
#define     AF_USART3           7
#define     AF_LPUART1          8
#define     AF_CAN1             9
#define     AF_TSC              9
#define     AF_USB              10
#define     AF_QUADSPI          10
#define     AF_COMP1            11
#define     AF_COMP2            11
#define     AF_SWPMI1           11
#define     AF_COMP1            12
#define     AF_COMP2            12
#define     AF_SWPMI1           12
#define     AF_SAI1             13
#define     AF_TIM15            14
#define     AF_TIM16            14
#define     AF_LPTIM2           14
#define     AF_EVENTOUT         15

#define     AF_TIM1_ALT         2
#define     AF_TIM2_ALT         2
#define     AF_USART2_ALT       3
#define     AF_COMP1_ALT        6
#define     AF_TIM2_ALT2        14



//
// Alternate Function 0 (SYS_AF)
//
#define     MCO             PA8
#define     JTMS_SWDIO      PA13
#define     JTCK_SWCLK      PA14
#define     JTDI            PA15
#define     JTDO_TRACESWO   PB3
#define     NJTRST          PB4


//
// Alternate Function 1 (TIM1/TIM2/LPTIM1)
//
#define     TIM2_CH1        PA0 | (PA5 << 8) | (PA15 << 16)
#define     TIM2_CH2        PA1 | (PB3 << 8)
#define     TIM2_CH3        PA2
#define     TIM2_CH4        PA3
#define     TIM1_BKIN       PA6
#define     TIM1_CH1N       PA7
#define     TIM1_CH1        PA8
#define     TIM1_CH2        PA9
#define     TIM1_CH3        PA10
#define     TIM1_CH4        PA11
#define     TIM1_ETR        PA12
#define     IR_OUT          PA13
#define     LPTIM1_OUT      PA14
#define     TIM1_CH2N       PB0
#define     TIM1_CH3N       PB1
#define     LPTIM1_IN1      PB5
#define     LPTIM1_ETR      PB6
#define     LPTIM1_IN2      PB7


//
// Alternate Function 2 (TIM1/TIM2)
//
#define     TIM2_ETR        PA5 | (PA15 << 8)
#define     TIM1_BKIN2      PA11


//
// Alternate Function 3 (USART2)
//
#define     USART2_RX_ALT   PA15


//
// Alternate Function 4 (I2C1/I2C2/I2C3)
//
#define     I2C1_SMBA       PA1 | (PA14 << 8) | (PB5 << 16)
#define     I2C3_SCL        PA7
#define     I2C1_SCL        PA9 | (PB6 << 8)
#define     I2C1_SDA        PA10 | (PB7 << 8)
#define     I2C3_SDA        PB4


//
// Alternate Function 5 (SPI1/SPI2)
//
#define     SPI1_SCK        PA1 | (PA5 << 8) | (PB3 << 16)
#define     SPI1_NSS        PA4 | (PA15 << 8) | (PB0 << 16)
#define     SPI1_MISO       PA6 | (PA11 << 8) | (PB4 << 16)
#define     SPI1_MOSI       PA7 | (PA12 << 8) | (PB5 << 16)


//
// Alternate Function 6 (SPI3)
//
#define     SPI3_SCK        PB3
#define     SPI3_NSS        PA4 | (PA15 << 8)
#define     SPI3_MISO       PB4
#define     SPI3_MOSI       PB5
#define     COMP1_OUT_ALT   PA6 | (PA11 << 8)


//
// Alternate Function 7 (USART1/USART2/USART3)
//
#define     USART2_CTS      PA0
#define     USART2_RTS_DE   PA1
#define     USART2_TX       PA2
#define     USART2_RX       PA3
#define     USART2_CK       PA4
#define     USART3_CTS      PA6
#define     USART1_CK       PA8 | (PB5 << 8)
#define     USART1_TX       PA9 | (PB6 << 8)
#define     USART1_RX       PA10 | (PB7 << 8)
#define     USART1_CTS      PA11 | (PB4 << 8)
#define     USART1_RTS_DE   PA12 | (PB3 << 8)
#define     USART3_RTS_DE   PA15 | (PB1 << 8)
#define     USART3_CK       PB0


//
// Alternate Function 8 (LPUART1)
//
#define     LPUART1_TX      PA2
#define     LPUART1_RX      PA3
#define     LPUART1_CTS     PA6
#define     LPUART1_RTS_DE  PB1


//
// Alternate Function 9 (CAN1/TSC)
//
#define     CAN1_RX         PA11
#define     CAN1_TX         PA12
#define     TSC_G3_IO1      PA15
#define     TSC_G2_IO1      PB4
#define     TSC_G2_IO2      PB5
#define     TSC_G2_IO3      PB6
#define     TSC_G2_IO4      PB7


//
// Alternate Function 10 (USB/QUADSPI)
//
#define     QUADSPI_BK1_NCS PA2
#define     QUADSPI_CLK     PA3
#define     QUADSPI_BK1_IO3 PA6
#define     QUADSPI_BK1_IO2 PA7
#define     USB_CRS_SYNC    PA10
#define     USB_DM          PA11
#define     USB_DP          PA12
#define     USB_NOE         PA13
#define     QUADSPI_BK1_IO1 PB0
#define     QUADSPI_BK1_IO0 PB1


//
// Alternate Function 12 (COMP1/COMP2/SWPMI1)
//
#define     COMP1_OUT       PA0 | (PB0 << 8)
#define     COMP2_OUT       PA2 | (PA7 << 8) | (PB5 << 16)
#define     TIM1_BKIN_COMP2 PA6
#define     SWPMI1_IO       PA8
#define     TIM1_BKIN2_COMP1 PA11
#define     SWPMI1_TX       PA13
#define     SWPMI1_RX       PA14
#define     SWPMI1_SUSPEND  PA15


//
// Alternate Function 13 (SAI1)
//
#define     SAI1_EXTCLK     PA0 | (PB0 << 8)
#define     SAI1_MCLK_A     PA3
#define     SAI1_FS_B       PA4
#define     SAI1_SCK_A      PA8
#define     SAI1_FS_A       PA9
#define     SAI1_SD_A       PA10
#define     SAI1_SD_B       PA13 | (PB5 << 8)
#define     SAI1_FS_B       PA14 | (PB6 << 8)
#define     SAI1_SCK_B      PB3
#define     SAI1_MCLK_B     PB4


//
// Alternate Function 14 (TIM2/TIM15/TIM16/LPTIM2)
//
#define     TIM2_ETR        PA0
#define     TIM15_CH1N      PA1
#define     TIM15_CH1       PA2
#define     TIM15_CH2       PA3
#define     LPTIM2_OUT      PA4 | (PA8 << 8)
#define     LPTIM2_ETR      PA5
#define     TIM16_CH1       PA6
#define     TIM15_BKIN      PA9
#define     LPTIM2_IN1      PB1
#define     TIM16_BKIN      PB5
#define     TIM16_CH1N      PB6


//
// Alternate Function 15
//
#define     EVENTOUT        ALL_PINS


//
// Unsupported Alternate Functions
//
#define     SPI2_SCK        0
#define     SPI2_NSS        0
#define     SPI2_MISO       0
#define     SPI2_MOSI       0


/*
    Checks if a pin is supported

    @param  pin Pin to check

    @retval `0` The pin is not supported
    @retval `1` The pin is supported
*/
EXIT_STATUS pinSupported(PIN pin);


/*
    Checks if a pin is compatible for a particular function,

    @param  pin Pin to check
    @param  fn  Alternate function to check

    @retval `0` The pin does not contain the function
    @retval `1` The pin does contain the function

*/
EXIT_STATUS pinFunctionCheck(PIN pin, FUNCTION fn);


/*
    Checks if an alternate function module is supported.

    @param  module Module to check

    @retval `0` The module is not supported
    @retval `1` The module is supported
*/
EXIT_STATUS moduleSupported(MODULE module);
