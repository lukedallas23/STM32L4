#include "reg.h"

/*
    Gets the value of a bit field within a register.

    @param  address     Memory address to read.
    @param  off         Bit offset of least significant bit in the bit field.
    @param  len         Amount of bits to read.

    @retval The bit field value requested.    

*/
uint32_t getRegVal(uint32_t address, uint8_t off, uint8_t len) {

    return (*(uint32_t*)address >> off) & (0xFFFFFFFF >> (32 - len));
}


/*
    Sets the value of a bit field within a register.

    @param  address     Memory address to set
    @param  val         Value to write
    @param  off         Bit offset of least significant bit in the bit field
    @param  len         Length of bits to write

*/
void setRegVal(uint32_t address, uint32_t val, uint8_t off, uint8_t len) {

    *(uint32_t*)address = (*(uint32_t*)address & ~((0xFFFFFFFF >> (32-len)) << off)) | ((val & (0xFFFFFFFF >> (32-len))) << off); 
}


/*
    Gets the value of a bit field within a register.

    @param  address     Memory address to read.
    @param  off         Bit offset of least significant bit in the bit field.
    @param  len         Amount of bits to read.

    @retval The bit field value requested.    

*/
uint16_t getRegVal16(uint32_t address, uint8_t off, uint8_t len) {

    return (*(uint16_t*)address >> off) & (0xFFFF >> (16 - len));
}


/*
    Sets the value of a bit field within a register.

    @param  address     Memory address to set
    @param  val         Value to write
    @param  off         Bit offset of least significant bit in the bit field
    @param  len         Length of bits to write

*/
void setRegVal16(uint32_t address, uint16_t val, uint8_t off, uint8_t len) {

    *(uint16_t*)address = (*(uint16_t*)address & ~((0xFFFF >> (16-len)) << off)) | ((val & (0xFFFF >> (16-len))) << off); 
}


/*
    Gets the value of a bit field within a register.

    @param  address     Memory address to read.
    @param  off         Bit offset of least significant bit in the bit field.
    @param  len         Amount of bits to read.

    @retval The bit field value requested.    

*/
uint8_t getRegVal8(uint32_t address, uint8_t off, uint8_t len) {

    return (*(uint8_t*)address >> off) & (0xFF >> (8 - len));
}


/*
    Sets the value of a bit field within a register.

    @param  address     Memory address to set
    @param  val         Value to write
    @param  off         Bit offset of least significant bit in the bit field
    @param  len         Length of bits to write

*/
void setRegVal8(uint32_t address, uint8_t val, uint8_t off, uint8_t len) {

    *(uint8_t*)address = (*(uint8_t*)address & ~((0xFF >> (8-len)) << off)) | ((val & (0xFF >> (8-len))) << off); 
}