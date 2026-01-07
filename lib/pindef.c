#include "pindef.h"

/*
    Checks if a pin is supported

    @param  pin Pin to check

    @retval `0` The pin is not supported
    @retval `1` The pin is supported
*/
int pinSupported(PIN pin) {

    if (!pin) return 0;
    return 1;

}


/*
    Checks if a pin is compatible for a particular function.

    @param  pin Pin to check
    @param  fn  Alternate function to check

    @retval `0` The pin does not contain the function or is not supported
    @retval `1` The pin does contain the function

*/
int pinFunctionCheck(PIN pin, FUNCTION fn) {
    
    if (!pinSupported(pin)) return 0;

    if (fn & 0xFF == pin || (fn >> 8) & 0xFF == pin  ||
       (fn >> 16) & 0xFF == pin || (fn >> 24) & 0xFF == pin) {
    
        return 1;
    }

    if (fn == ALL_PINS) {
        return 1;
    }

    return 0;

}


/*
    Checks if an alternate function module is supported.

    @param  module Module to check

    @retval `0` The module is not supported
    @retval `1` The module is supported
*/
int moduleSupported(MODULE module) {

    if (module == FN_NOT_SUPPORTED) return 0;
    return 1;

}