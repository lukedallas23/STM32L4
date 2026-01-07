#include "gpiolib.h"


/*
    Gets the base address of a GPIO port.

    @param  pin         Pin (or port) to get the base address of

    @retval The base address of the GPIO module
    @retval `0` on error.

*/
uint32_t gpioGetPortBaseAddress(GPIO_PIN pin) {

    switch (pin & GPIO_PORT) {
        case GPIO_A:
            return R_GPIOA_BASE;
        case GPIO_B:
            return R_GPIOB_BASE;
        case GPIO_C:
            return R_GPIOC_BASE;
        case GPIO_D:
            return R_GPIOD_BASE;
        case GPIO_H:
            return R_GPIOH_BASE;
        default:
            return 0;
    }

}


/*
    Set the mode of a GPIO pin as input, output, analog, or special function.

    @param  pin         GPIO pin to set mode.
    @param  pinMode     Mode to set

    @retval `0` on success
    @retval `1` on failure

*/
int gpioSetMode(GPIO_PIN pin, GPIO_PIN_MODE pinMode) {

    setRegVal(
        gpioGetPortBaseAddress(pin) + R_GPIO_MODER_OFF, 
        pinMode, 
        (pin & GPIO_PIN_NO) * S_MODE,
        S_MODE
    );

    return 0;
}


/*
    Initializes a given GPIO pin. This will initialize the given pin as an
    input or output. To avoid undefined behaviour, a pin should not be 
    initialized twice.

    @param pin          GPIO pin to initialize
    @param pinMode      Define the pin as input, output, analog or special function.

    @retval `0` on success
    @retval `1` on failure

*/
int gpioPinInit(GPIO_PIN pin, GPIO_PIN_MODE pinMode) {

    uint32_t baseAddress = gpioGetPortBaseAddress(pin);
    uint8_t rccPinOff;     

    // Set the RCC pin for the GPIO port
    switch (pin & GPIO_PORT) {
        case GPIO_A:
            rccSetClock(RCC_CLK_GPIOA, RCC_CLOCK_EN); break;
        case GPIO_B:
            rccSetClock(RCC_CLK_GPIOB, RCC_CLOCK_EN); break;
        case GPIO_C:
            rccSetClock(RCC_CLK_GPIOC, RCC_CLOCK_EN); break;
        case GPIO_D:
            rccSetClock(RCC_CLK_GPIOD, RCC_CLOCK_EN); break;
        case GPIO_H:
            rccSetClock(RCC_CLK_GPIOH, RCC_CLOCK_EN); break;
        default:
            break;
    }
    //*(uint32_t*)0x4002104C |= 0x2;
    gpioSetMode(pin, pinMode);

    return 0;

}


/*
    Sets a GPIO pin's output type as Push Pull or Open Drain. If the pin
    is not set as output, then this function will have no effect and return
    with error.

    @param  pin         GPIO pin to set
    @param  outputType  Output type to set

    @retval `0` on success
    @retval `1` on failure or if pin is not output


*/
int gpioSetOutputType(GPIO_PIN pin, GPIO_OUT_TYPE outputType) {

    setRegVal(
        gpioGetPortBaseAddress(pin) + R_GPIO_OTYPER_OFF, 
        outputType, 
        (pin & GPIO_PIN_NO) * S_OT,
        S_OT
    );    

    return 0;

}


/*
    Sets a GPIO pin's output speed. If the pin is not set as output, 
    then this function will have no effect and return with error.

    @param  pin         GPIO pin to set
    @param  outputSpeed Output speed to set

    @retval `0` on success
    @retval `1` on failure or if pin is not output


*/
int gpioSetOutputSpeed(GPIO_PIN pin, GPIO_OUT_SPEED outputSpeed) {

    setRegVal(
        gpioGetPortBaseAddress(pin) + R_GPIO_OSPEEDR_OFF, 
        outputSpeed, 
        (pin & GPIO_PIN_NO) * S_OSPEED,
        S_OSPEED
    ); 

    return 0;
}


/*
    Sets a GPIO pin's pull up or pull down status. If the pin is not set 
    as input, then this function will have no effect and return with error.

    @param  pin         GPIO pin to set
    @param  pullUpDown  Pull up, pull down, or neither

    @retval `0` on success
    @retval `1` on failure or if pin is not input

*/
int gpioSetPullUpDown(GPIO_PIN pin, GPIO_PULL_UP_DOWN pullUpDown) {

    setRegVal(
        gpioGetPortBaseAddress(pin) + R_GPIO_PUPDR_OFF, 
        pullUpDown, 
        (pin & GPIO_PIN_NO) * S_PUPD,
        S_PUPD
    ); 

    return 0;
}


/*
    Gets a GPIO pin's logic level.

    @param  pin         GPIO pin to read

    @retval GPIO pin logic level read

*/
GPIO_PIN_VAL gpioGetPinLevel(GPIO_PIN pin) {

    return getRegVal(
        gpioGetPortBaseAddress(pin) + R_GPIO_IDR_OFF,
        pin & GPIO_PIN_NO,
        1      
    );
}


/*
    Sets a GPIO pin's logic level. If the pin is not set as output, 
    then this function will have no effect and return with error.

    @param  pin         GPIO pin to set
    @param  level       Logic level to set.

    @retval `0` on success
    @retval `1` on failure or if pin is not input

*/
int gpioSetPinLevel(GPIO_PIN pin, GPIO_PIN_VAL level) {

    setRegVal(
        gpioGetPortBaseAddress(pin) + R_GPIO_ODR_OFF,
        level,
        pin & GPIO_PIN_NO,
        1
    );

}


/*
    Set the alternate function of a pin. Pin must already be
    set to be an alternate function.

    @param  pin         Pin of alternate function to set.
    @param  fn          Alternate function number to set.

    @retval `0` on success
    @retval `1` on failure or if pin is not input

*/
int gpioSetAltFn(GPIO_PIN pin, ALT_FN fn) {

    if ((pin & GPIO_PIN_NO) > 7) {
        setRegVal(
            gpioGetPortBaseAddress(pin) + R_GPIO_AFRH_OFF,
            fn,
            ((pin & GPIO_PIN_NO) - 8) * (S_AFSEL),
            S_AFSEL
        );
    } else {
        setRegVal(
            gpioGetPortBaseAddress(pin) + R_GPIO_AFRL_OFF,
            fn,
            (pin & GPIO_PIN_NO) * (S_AFSEL),
            S_AFSEL
        );
    }

    return 0;
}
