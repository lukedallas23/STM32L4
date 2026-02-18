#ifndef STD_STDLIB_H
#define STD_STDLIB_H

#include <stdint.h>
#include "../string/string.h"

extern uint32_t _ebss; // This is the end of .bss section in SRAM
extern mem_block *memData; // Pointer to first data in heap



typedef struct {

    size_t      size;   // Size of malloced memory
    mem_block   *next;  // Address of next block

} mem_block;



/*
    Allocates size bytes of uninitialized storage.

    @param  size    number of bytes to allocate

    @retval On success, returns the pointer to the beginning of newly 
    allocated memory. To avoid a memory leak, the returned pointer must 
    be deallocated with free() or realloc(). On failure, returns a null 
    pointer.

    RN : Assumes infinite memory, no error checking

*/
void* malloc(size_t size);

/*
    Allocates memory for an array of num objects of size and 
    initializes all bytes in the allocated storage to zero.

    @param  num Number of objects
    @param  size Size of each object

    @retval On success, returns the pointer to the beginning of newly 
    allocated memory. To avoid a memory leak, the returned pointer must be deallocated with free() or realloc().
    On failure, returns a null pointer.

*/
void* calloc(size_t num, size_t size);


/*
    Reallocates the given area of memory. If ptr is not NULL, it must be previously 
    allocated by malloc, calloc or realloc and not yet freed with a call to free or 
    realloc. Otherwise, the results are undefined.

    @param ptr pointer to the memory area to be reallocated
    @param new_size new size of the array in bytes

    @retval On success, returns the pointer to the beginning of newly allocated memory. 
    To avoid a memory leak, the returned pointer must be deallocated with free or realloc. 
    The original pointer ptr is invalidated and any access to it is undefined behavior (even 
    if reallocation was in-place). On failure, returns a null pointer. The original pointer 
    ptr remains valid and may need to be deallocated with free or realloc.

*/
void *realloc(void *ptr, size_t new_size);


/*
    Deallocates the space previously allocated by malloc(), calloc(), or realloc().
    The behavior is undefined if the value of ptr does not equal a value returned 
    earlier by malloc(), calloc(), realloc().

    @param  ptr  pointer to the memory to deallocate

*/
void free(void *ptr);



#endif

