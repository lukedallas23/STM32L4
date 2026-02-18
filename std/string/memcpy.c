#include "string.h"

/*
    Copies count characters from the object pointed to by src to the object pointed to 
    by dest. Both objects are interpreted as arrays of unsigned char.
 
    The behavior is undefined if access occurs beyond the end of the dest array. If the 
    objects overlap (which is a violation of the restrict contract)(since C99), the 
    behavior is undefined. The behavior is undefined if either dest or src is an invalid 
    or null pointer.

    @param dest	 pointer to the object to copy to
    @param src pointer to the object to copy from
    @param count number of bytes to copy

    @retval Returns a copy of dest


*/
void* memcpy(void *dest, const void *src, size_t count) {

    for (int i = 0; i < count; i++) {
        ((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
    }

    return dest;
}