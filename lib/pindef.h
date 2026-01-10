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
#define     PB2     0x22
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
#define     SPI1            5
#define     SPI2            FN_NOT_SUPPORTED
#define     SPI3            6
#define     EVENTOUT        15




//
// Alternate Function 5
//
#define     SPI1_SCK        PA1 | (PA5 << 8) | (PB3 << 16)
#define     SPI1_NSS        PA4 | (PA15 << 8) | (PB0 << 16)
#define     SPI1_MISO       PA6 | (PA11 << 8) | (PB4 << 16)
#define     SPI1_MOSI       PA7 | (PA12 << 8) | (PB5 << 16)

//
// Alternate Function 6
//
#define     SPI3_SCK        PB3
#define     SPI3_NSS        PA4 | (PA15 << 8)
#define     SPI3_MISO       PB4
#define     SPI3_MOSI       PB5
#define     COMP1_OUT       PA6 | (PA11 << 8)

//
// Alternate Function 15
//
#define     EVENTOUT_       ALL_PINS

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
