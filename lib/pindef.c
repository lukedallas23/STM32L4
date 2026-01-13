#include "pindef.h"

/*
    Checks if a pin is supported

    @param  pin Pin to check

    @retval `EXIT_UNSUPPORTED` The pin is not supported
    @retval `EXIT_SUCCESS` The pin is supported
*/
EXIT_STATUS pinSupported(PIN pin) {

    if (!pin) return EXIT_UNSUPPORTED;
    return EXIT_SUCCESS;

}


/*
    Checks if a pin is compatible for a particular function.

    @param  pin Pin to check
    @param  fn  Alternate function to check

    @retval `EXIT_UNSUPPORTED` The pin does not contain the function or is not supported
    @retval `EXIT_SUCCESS` The pin does contain the function

*/
EXIT_STATUS pinFunctionCheck(PIN pin, FUNCTION fn) {
    
    if (pinSupported(pin) != EXIT_SUCCESS) return EXIT_UNSUPPORTED;

    if ((uint8_t)(fn & 0xFF) == pin || 
        (uint8_t)((fn >> 8) & 0xFF) == pin ||
        (uint8_t)((fn >> 16) & 0xFF) == pin ||
        (uint8_t)((fn >> 24) & 0xFF) == pin) 
    {
        return EXIT_SUCCESS;
    }

    if (fn == ALL_PINS) {
        return EXIT_SUCCESS;
    }

    return EXIT_UNSUPPORTED;

}


/*
    Checks if an alternate function module is supported.

    @param  module Module to check

    @retval `EXIT_UNSUPPORTED` The module is not supported
    @retval `EXIT_SUCCESS` The module is supported
*/
EXIT_STATUS moduleSupported(MODULE module) {

    if (module == FN_NOT_SUPPORTED) return EXIT_UNSUPPORTED;
    return EXIT_SUCCESS;

}