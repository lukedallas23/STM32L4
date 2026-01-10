#ifndef REGLIB_H
#define REGLIB_H

#include <stdint.h>


//
// Standard Error Codes - We'll move this to the stdlib later. Here
// for now because reg.h is included in basically everything.
//
typedef enum {

    EXIT_SUCCESS                = 0,
    EXIT_BAD_PARAMATER          = 1,
    EXIT_UNSUPPORTED            = 2,
    EXIT_TSFER_IN_PROGRESS      = 3,
    EXIT_UNKNOWN                = 4

} EXIT_STATUS;


/*
    Gets the value of a bit field within a register.

    @param  address     Memory address to read.
    @param  off         Bit offset of least significant bit in the bit field.
    @param  len         Amount of bits to read.

    @retval The bit field value requested.    

*/
uint32_t getRegVal(uint32_t address, uint8_t off, uint8_t len);


/*
    Sets the value of a bit field within a register.

    @param  address     Memory address to set
    @param  val         Value to write
    @param  off         Bit offset of least significant bit in the bit field
    @param  len         Length of bits to write

*/
void setRegVal(uint32_t address, uint32_t val, uint8_t off, uint8_t len);


/*
    Gets the value of a bit field within a register.

    @param  address     Memory address to read.
    @param  off         Bit offset of least significant bit in the bit field.
    @param  len         Amount of bits to read.

    @retval The bit field value requested.    

*/
uint16_t getRegVal16(uint32_t address, uint8_t off, uint8_t len);

/*
    Sets the value of a bit field within a register.

    @param  address     Memory address to set
    @param  val         Value to write
    @param  off         Bit offset of least significant bit in the bit field
    @param  len         Length of bits to write

*/
void setRegVal16(uint32_t address, uint16_t val, uint8_t off, uint8_t len);


/*
    Gets the value of a bit field within a register.

    @param  address     Memory address to read.
    @param  off         Bit offset of least significant bit in the bit field.
    @param  len         Amount of bits to read.

    @retval The bit field value requested.    

*/
uint8_t getRegVal8(uint32_t address, uint8_t off, uint8_t len);


/*
    Sets the value of a bit field within a register.

    @param  address     Memory address to set
    @param  val         Value to write
    @param  off         Bit offset of least significant bit in the bit field
    @param  len         Length of bits to write

*/
void setRegVal8(uint32_t address, uint8_t val, uint8_t off, uint8_t len);

#endif