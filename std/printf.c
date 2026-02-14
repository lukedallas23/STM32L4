#include <stdarg.h>
#include "../stm32/systemTable.h"

// PLACEHOLDER-WILL CHANGE
int *buf = NULL;
void print_text(char *str, int len){return;}

#define STM32_ITOA_SIGNED       0
#define STM32_ITOA_UNSIGNED     1


// Signed = 0
// Unsigned = 1
// Translates a char, short, int, or long to a string
// Return the length of the new string
int stm32_itoa(char *strBuf, long long val, int sign) {

    int len = 0;
    int strPtr = 0; // Tracks how long the string is
    int neg = 0;
    unsigned long long uVal = (unsigned long long) val;

    // Negative sign
    if (sign == STM32_ITOA_SIGNED && val < 0) {
        neg = 1;
        strBuf[0] = '-';
        uVal = -val;
    }

    // Get the string length
    do {
        uVal /= 10;
        strPtr++;
    } while (uVal);
    
    if (sign == STM32_ITOA_SIGNED && val < 0) uVal = -val;
    else uVal = val;
    
    // Print string
    len = neg + strPtr;
    strBuf[neg+strPtr--] = '\0';
    while (strPtr >= 0) {
        strBuf[neg+strPtr--] = (uVal % 10) + '0';
        uVal /= 10;
    }

    return len;

}


int stm32_ftoa(char *strBuf, double val, int precision) {
    return 0;
}

int stm32_printf(const char *format, ...){

    va_list args;
    va_start(args, format);

    // This is the index of the next value in the string that has to be printed
    int next = 0;
    int len;
    char numBuffer[21] = {{'\0'}};
    
    int i;
    for (i = 0; format[i]; i++) {

        if (format[i] == '%') {

            switch(format[i+1]) {
                case '%': // %% means print "%", skip over second one
                    print_text(&format[next], i - next);
                    next = i + 1;
                    i++; 
                    break;

                case 'i':
                case 'd': // %d means integer
                    print_text(&format[next], i - next);
                    len = stm32_itoa(numBuffer, va_arg(args, int), STM32_ITOA_SIGNED);
                    print_text(numBuffer, len);
                    next = i + 2;
                    i++;
                    break;

                case 'u': // %u means unsigned integer
                    print_text(&format[next], i - next);
                    len = stm32_itoa(numBuffer, va_arg(args, int), STM32_ITOA_UNSIGNED);
                    print_text(numBuffer, len);
                    next = i + 2;
                    i++;
                    break;
                
                case 'f': // %f means floating point
                case 'e': // %e is float in exponential (1.0e10)
                case 'E': // %E is float in exponential (1.0E10)
                case 'o': // %o is unsigned octal integer
                case 'x': // %x is unsigned hex integer (lowercase)
                case 'X': // %X is unsigned hex integer (uppercase)
                case 's': // %s is string
                case 'p': // %p is address/pointers
            }

        }

    }

    // Print rest of the string
    print_text(&format[next], i - next);

    return 0;

}

/*
    Format specifiers
    %c - char
    %d or %i - signed int
    %e or %E - Float in scientific notation
    %f - Float type
    %g or %G - Float type with current precision
    %ld or %li - Long
    %lf - Double
    %Lf - long double
    %lli or llu - long long 
    %llu - Unsigned long long
    %o - Octal
    %p - pointer
    %s - String
    %u - Unsigned int
    %x or %X - Hex Representation
    %n - Nothing
    %% - '%'


*/