#include "i2clib.h"

/*
    Gets the base address of a I2C module.

    @param  module      Module to get the base address of

    @retval The base address of the SPI module
    @retval `0` on error.

*/
uint32_t i2cGetBaseAdr(I2C_MODULE module) {

    switch (module) {
        case 1:
            return R_I2C1_BASE;
        case 2:
            return R_I2C2_BASE;
        case 3:
            return R_I2C3_BASE;
        case 4:
            return R_I2C4_BASE;
        default:
            return 0;
    }

}

EXIT_STATUS i2cMasterModuleInit(I2C_MODULE module, GPIO_PIN sda, GPIO_PIN scl) {

    uint32_t baseAdr = i2cGetBaseAdr(module);
    
    // Check if module is supported and configure pins
    switch (module) {
        case 1:
            if ((moduleSupported(AF_I2C1) == EXIT_UNSUPPORTED) || (pinFunctionCheck(sda, I2C1_SDA) == EXIT_UNSUPPORTED) ||
                (pinFunctionCheck(scl, I2C1_SCL) == EXIT_UNSUPPORTED)) 
                {
                    return EXIT_UNSUPPORTED;
                }
            break;
        case 2:
            if ((moduleSupported(AF_I2C2) == EXIT_UNSUPPORTED) || (pinFunctionCheck(sda, I2C2_SDA) == EXIT_UNSUPPORTED) ||
                (pinFunctionCheck(scl, I2C2_SCL) == EXIT_UNSUPPORTED)) 
                {
                    return EXIT_UNSUPPORTED;
                }
            break;
        case 3:
            if ((moduleSupported(AF_I2C3) == EXIT_UNSUPPORTED) || (pinFunctionCheck(sda, I2C3_SDA) == EXIT_UNSUPPORTED) ||
                (pinFunctionCheck(scl, I2C3_SCL) == EXIT_UNSUPPORTED)) 
                {
                    return EXIT_UNSUPPORTED;
                }
            break;
        case 4:
            if ((moduleSupported(AF_I2C4) == EXIT_UNSUPPORTED) || (pinFunctionCheck(sda, I2C4_SDA) == EXIT_UNSUPPORTED) ||
                (pinFunctionCheck(scl, I2C4_SCL) == EXIT_UNSUPPORTED)) 
                {
                    return EXIT_UNSUPPORTED;
                }
            break;
        default:
            return EXIT_UNSUPPORTED;
    }

    // Set Pins as alternate functions
    gpioPinInit(sda, GPIO_MODE_ALT_FN);
    gpioPinInit(scl, GPIO_MODE_ALT_FN);

    // Reset Module and start peripheral clock
    switch (module) {
        case 1:
            rccReset(RCC_RST_I2C1);
            rccSetClock(RCC_CLK_I2C1, RCC_CLOCK_EN);
            gpioSetAltFn(sda, AF_I2C1);
            gpioSetAltFn(scl, AF_I2C1); 
            EnableIRQ(P_INT_I2C1_ER);
            EnableIRQ(P_INT_I2C1_EV); break;
        case 2:
            rccReset(RCC_RST_I2C2);
            rccSetClock(RCC_CLK_I2C2, RCC_CLOCK_EN);
            gpioSetAltFn(sda, AF_I2C2);
            gpioSetAltFn(scl, AF_I2C2); 
            EnableIRQ(P_INT_I2C2_ER);
            EnableIRQ(P_INT_I2C2_EV); break;
        case 3:
            rccReset(RCC_RST_I2C3);
            rccSetClock(RCC_CLK_I2C3, RCC_CLOCK_EN);
            gpioSetAltFn(sda, AF_I2C3);
            gpioSetAltFn(scl, AF_I2C3); 
            EnableIRQ(P_INT_I2C3_ER);
            EnableIRQ(P_INT_I2C3_EV); break;
        case 4:
            rccReset(RCC_RST_I2C4);
            rccSetClock(RCC_CLK_I2C4, RCC_CLOCK_EN);
            gpioSetAltFn(sda, AF_I2C4);
            gpioSetAltFn(scl, AF_I2C4); 
            EnableIRQ(P_INT_I2C4_ER);
            EnableIRQ(P_INT_I2C4_EV); break;
        default:
            return EXIT_UNKNOWN; break;
    }

    // Initilize I2C Module
    /*
        1. Clear PE Bit
        2. Configure ANOFF and DNF in CR1
            - Both of these will be off for now
        3. Configure PRESC, SDADEL, SCLDEL, SCLH, SCLL in TIMINGR
        4. Configure NOSTRECTCH in CR1
        5. Set PE bit
    */
    
}