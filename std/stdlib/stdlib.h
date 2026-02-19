#ifndef STD_STDLIB_H
#define STD_STDLIB_H

#include <stdint.h>
#include <stddef.h>
#include "../string/string.h"

typedef struct mem_block_t {

    size_t              size;   // Size of malloced memory
    struct mem_block_t  *next;  // Address of next block

} mem_block;


extern uint32_t _ebss; // This is the end of .bss section in SRAM
extern mem_block *memData; // Pointer to first data in heap



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


// Unimplemented stdlib functions
typedef int div_t;
typedef long ldiv_t;
typedef char schar_t;
//typedef char wchar_t;

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
#define RAND_MAX 0x7FFFFFFF
#define MB_CUR_MAX 4

double atof(const char *str);
int atoi(const char *str);
long int atol(const char *str);
double strtod(const char *str, char **endptr);
long int strtol(const char *str, char **endptr, int base);
unsigned long int strtoul(const char *str, char **endptr, int base);
void abort(void);
int atexit(void (*func)(void));
void exit(int status);
char *getenv(const char *name);
int system(const char *string);
void *bsearch(const void *key, const void *base, size_t nitems, 
size_t size, int (*compar)(const void *, const void *));
void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
int abs(int x);
div_t div(int number, int denom);
long int labs(long int x);
ldiv_t ldiv(long int number, long int denom);
int rand(void);
void srand(unsigned int seed);
int mblen(const char *str, size_t n);
size_t mbstowcs(schar_t *pwcs, const char *str, size_t n);
int mbtowc(wchar_t *str, const wchar_t *pwcs, size_t n);
int wctomb(char *str, wchar_t wchar);



#endif

