#ifndef STD_STRING_H
#define STD_STRING_H

#include <stddef.h>

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
void* memcpy(void *dest, const void *src, size_t count);


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
void *memset(void *dest, int ch, size_t count);


// Unimplemented string functions
void *memchr(const void *str, int c, size_t n);
int memcmp(const void *str1, const void *str2, size_t n);
void *memmove(void *dest, const void *src, size_t n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strchr(const char *str, int c);
int strcmp(const char *str1, const char *str2);
int strcoll(const char *dest, const char *src);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
size_t strcspn(const char *str1, const char *str2);
char *strerror(int errnum);
size_t strlen(const char *str);
char *strpbrk(const char *str1, const char *str2);
char *strrchr(const char *str, int c);
size_t strspn(const char *str1, const char *str2);
char *strstr(const char *haystack, const char *needle);
char *strtok(char *str, const char *delim);
size_t strxfrm(char *dest, const char *src, size_t n);

#endif