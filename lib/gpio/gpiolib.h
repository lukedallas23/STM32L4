#ifndef GPIOLIB_H
#define GPIOLIB_H

#include <stdint.h>
#include "def.h"
#include "../pindef.h"
#include "../reg.h"
#include "../rcc/rcclib.h"

//
// GPIO Pin Definitions
//
#define     GPIO_A0     PA0
#define     GPIO_A1     PA1
#define     GPIO_A2     PA2
#define     GPIO_A3     PA3
#define     GPIO_A4     PA4
#define     GPIO_A5     PA5
#define     GPIO_A6     PA6
#define     GPIO_A7     PA7
#define     GPIO_A8     PA8
#define     GPIO_A9     PA9
#define     GPIO_A10    PA10
#define     GPIO_A11    PA11
#define     GPIO_A12    PA12
#define     GPIO_A13    PA13
#define     GPIO_A14    PA14
#define     GPIO_A15    PA15
#define     GPIO_B0     PB0
#define     GPIO_B1     PB1
#define     GPIO_B2     PB2
#define     GPIO_B3     PB3
#define     GPIO_B4     PB4
#define     GPIO_B5     PB5
#define     GPIO_B6     PB6
#define     GPIO_B7     PB7
#define     GPIO_B8     PB8
#define     GPIO_B9     PB9
#define     GPIO_B10    PB10
#define     GPIO_B11    PB11
#define     GPIO_B12    PB12
#define     GPIO_B13    PB13
#define     GPIO_B14    PB14
#define     GPIO_B15    PB15
#define     GPIO_C0     PC0
#define     GPIO_C1     PC1
#define     GPIO_C2     PC2
#define     GPIO_C3     PC3
#define     GPIO_C4     PC4
#define     GPIO_C5     PC5
#define     GPIO_C6     PC6
#define     GPIO_C7     PC7
#define     GPIO_C8     PC8
#define     GPIO_C9     PC9
#define     GPIO_C10    PC10
#define     GPIO_C11    PC11
#define     GPIO_C12    PC12
#define     GPIO_C13    PC13
#define     GPIO_C14    PC14
#define     GPIO_C15    PC15
#define     GPIO_D0     PD0
#define     GPIO_D1     PD1
#define     GPIO_D2     PD2
#define     GPIO_D3     PD3
#define     GPIO_D4     PD4
#define     GPIO_D5     PD5
#define     GPIO_D6     PD6
#define     GPIO_D7     PD7
#define     GPIO_D8     PD8
#define     GPIO_D9     PD9
#define     GPIO_D10    PD10
#define     GPIO_D11    PD11
#define     GPIO_D12    PD12
#define     GPIO_D13    PD13
#define     GPIO_D14    PD14
#define     GPIO_D15    PD15
#define     GPIO_H0     PH0
#define     GPIO_H1     PH1
#define     GPIO_H2     PH2
#define     GPIO_H3     PH3
#define     GPIO_H4     PH4
#define     GPIO_H5     PH5
#define     GPIO_H6     PH6
#define     GPIO_H7     PH7
#define     GPIO_H8     PH8
#define     GPIO_H9     PH9
#define     GPIO_H10    PH10
#define     GPIO_H11    PH11
#define     GPIO_H12    PH12
#define     GPIO_H13    PH13
#define     GPIO_H14    PH14
#define     GPIO_H15    PH15

//
// GPIO Pin Ports
//
#define     GPIO_A      PORTA
#define     GPIO_B      PORTB
#define     GPIO_C      PORTC
#define     GPIO_D      PORTD
#define     GPIO_H      PORTH

//
// GPIO Port Masks
//
#define     GPIO_PORT   0xF0
#define     GPIO_PIN_NO 0x0F

//
// Data type for holding GPIO information for a single pin.
//
typedef struct GPIO_PIN_INFO_t {

    uint32_t    pin         : 8;    // GPIO Pin
    uint32_t    pinMode     : 2;    // Input, output, or alternate fn.
    uint32_t    outputType  : 1;    // Output push-pull or open-drain
    uint32_t    outputSpeed : 2;    // I/O output speed
    uint32_t    pullUpDown  : 2;    // Pull up, pull down or none
    uint32_t    function    : 4;    // Alternate function

} GPIO_PIN_INFO;

typedef uint8_t GPIO_PIN;


/*
    Gets the base address of a GPIO port.

    @param  pin         Pin (or port) to get the base address of

    @retval The base address of the GPIO module
    @retval `0` on error.

*/
uint32_t gpioGetPortBaseAddress(GPIO_PIN pin);


/*
    Set the mode of a GPIO pin as input, output, analog, or special function.

    @param  pin         GPIO pin to set mode.
    @param  pinMode     Mode to set

    @retval `0` on success
    @retval `1` on failure

*/
int gpioSetMode(GPIO_PIN pin, GPIO_PIN_MODE pinMode);


/*
    Initializes a given GPIO pin. This will initialize the given pin as an
    input or output. To avoid undefined behaviour, a pin should not be 
    initialized twice.

    @param pin          GPIO pin to initialize
    @param pinMode      Define the pin as input, output, analog or special function.

    @retval `0` on success
    @retval `1` on failure
    
*/
int gpioPinInit(GPIO_PIN pin, GPIO_PIN_MODE pinMode);


/*
    Sets a GPIO pin's output type as Push Pull or Open Drain. If the pin
    is not set as output, then this function will have no effect and return
    with error.

    @param  pin         GPIO pin to set
    @param  outputType  Output type to set

    @retval `0` on success
    @retval `1` on failure or if pin is not output


*/
int gpioSetOutputType(GPIO_PIN pin, GPIO_OUT_TYPE outputType);


/*
    Sets a GPIO pin's output speed. If the pin is not set as output, 
    then this function will have no effect and return with error.

    @param  pin         GPIO pin to set
    @param  outputSpeed Output speed to set

    @retval `0` on success
    @retval `1` on failure or if pin is not output


*/
int gpioSetOutputSpeed(GPIO_PIN pin, GPIO_OUT_SPEED outputSpeed);


/*
    Sets a GPIO pin's pull up or pull down status. If the pin is not set 
    as input, then this function will have no effect and return with error.

    @param  pin         GPIO pin to set
    @param  pullUpDown  Pull up, pull down, or neither

    @retval `0` on success
    @retval `1` on failure or if pin is not input

*/
int gpioSetPullUpDown(GPIO_PIN pin, GPIO_PULL_UP_DOWN pullUpDown);


/*
    Gets a GPIO pin's logic level.

    @param  pin         GPIO pin to read

    @retval GPIO pin logic level read

*/
GPIO_PIN_VAL gpioGetPinLevel(GPIO_PIN pin);


/*
    Sets a GPIO pin's logic level. If the pin is not set as output, 
    then this function will have no effect and return with error.

    @param  pin         GPIO pin to set
    @param  level       Logic level to set.

    @retval `0` on success
    @retval `1` on failure or if pin is not input

*/
int gpioSetPinLevel(GPIO_PIN pin, GPIO_PIN_VAL level);


/*
    Set the alternate function of a pin. Pin must already be
    set to be an alternate function.

    @param  pin         Pin of alternate function to set.
    @param  fn          Alternate function number to set.

    @retval `0` on success
    @retval `1` on failure or if pin is not input

*/
int gpioSetAltFn(GPIO_PIN pin, ALT_FN fn);

#endif
