#include "string.h"

/*
    Copies the value (unsigned char)ch into each of the first count 
    characters of the object pointed to by dest. The behavior is undefined 
    if access occurs beyond the end of the dest array. The behavior is 
    undefined if dest is a null pointer.

    @param dest pointer to the object to fill
    @param ch fill byte
    @param count number of bytes to fill

    @retval A copy of dest


*/
void *memset(void *dest, int ch, size_t count) {

    for (int i = 0; i < count; count++) {
        ((unsigned char*)dest)[i] = (unsigned char)ch;
    }

    return dest;
}

