#include "stdlib.h"

// Pointer to first data in heap
mem_block *memData = NULL;


/*
    Allocates size bytes of uninitialized storage.

    @param  size    number of bytes to allocate

    @retval On success, returns the pointer to the beginning of newly 
    allocated memory. To avoid a memory leak, the returned pointer must 
    be deallocated with free() or realloc(). On failure, returns a null 
    pointer.

    RN : Assumes infinite memory, no error checking

*/
void* malloc(size_t size) {

    mem_block *currNode = NULL;
    mem_block *newNode = NULL;

    // Align the memory block by adding to the size of bytes allocated
    if (size % sizeof(void*)) {
        size += sizeof(void*) - (size % sizeof(void*));
    }

    // Check if there has been any heap allocation
    if (memData == NULL) {

        // Fisrt heap block will go to beggining to heap
        currNode = &memData;
        newNode = (mem_block*)&_ebss;
        goto allocateMem;
    }

    // Check if block can be allocated before first block
    if ((size_t)currNode - (size_t)_ebss > size + sizeof(mem_block)) {
        newNode = (mem_block*)&_ebss;
        newNode->next = memData;
        newNode->size = size;
        memData = newNode;
        return (void*)((size_t)(newNode) + sizeof(mem_block));
    }

    currNode = memData;

    // Scan through the linked list. See if there is a gap large enough for the new memory. If not, add one to the end
    while (currNode->next != NULL) {

        size_t availableMem = (size_t)currNode->next - (size_t)currNode - currNode->size - sizeof(mem_block);
        size_t requiredMem = sizeof(mem_block) + size;
        
        if (availableMem >= requiredMem) {

            // The is the address of the new node, which is at the end of currNode
            newNode = (mem_block*)(((size_t)(currNode)) + sizeof(mem_block) + currNode->size);
            goto allocateMem;

        }

        currNode = currNode->next;
    }


    // If there is no place between blocks to allocate memory, then add a block to the end.
    newNode = (mem_block*)(((size_t)(currNode)) + sizeof(mem_block) + currNode->size);

  allocateMem:
    newNode->size = size;
    newNode->next = currNode->next;
    currNode->next = newNode;
    return (void*)((size_t)(newNode) + sizeof(mem_block));

}

/*
    Allocates memory for an array of num objects of size and 
    initializes all bytes in the allocated storage to zero.

    @param  num Number of objects
    @param  size Size of each object

    @retval On success, returns the pointer to the beginning of newly 
    allocated memory. To avoid a memory leak, the returned pointer must be deallocated with free() or realloc().
    On failure, returns a null pointer.

*/
void* calloc(size_t num, size_t size) {

    size_t bytes = num * size;
    char *data = (char*) malloc(bytes);
    
    // Zero out memory
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }

    return (void*)data;

}


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
void *realloc(void *ptr, size_t new_size) {

    mem_block *arrInfo = (mem_block*)((size_t)ptr - sizeof(mem_block));
    size_t oldSize = arrInfo->size;

    // Align the memory block by adding to the size of bytes allocated
    if (new_size % sizeof(void*)) {
        new_size += sizeof(void*) - (new_size % sizeof(void*));
    }

    // If lessening the size, this is easy. Just reduce size in mem_block
    if (new_size <= arrInfo->size) {
        arrInfo->size = new_size;
        return ptr;
    }

    free(ptr);
    void *newPtr = malloc(new_size);

    // It can be assumed that the old data is preserved because only sizeof(mem_block)
    // can be changed which can only override the old mem_block.
    memcpy(newPtr, ptr, oldSize);

    return newPtr;
}

/*
    Deallocates the space previously allocated by malloc(), calloc(), or realloc().
    The behavior is undefined if the value of ptr does not equal a value returned 
    earlier by malloc(), calloc(), realloc().

    @param  ptr  pointer to the memory to deallocate

*/
void free(void *ptr) {

    mem_block *currBlock = memData;
    mem_block *freeBlock = (mem_block*)((size_t)ptr - sizeof(mem_block));

    // Only one block total
    if (currBlock == freeBlock && freeBlock->next == NULL) {
        memData = NULL;
        return;
    }

    // Removing the first block
    if (currBlock == freeBlock) {
        memData = freeBlock->next;
        return;
    }

    // Remove the reference to the freed block of memory
    while (currBlock->next != freeBlock) {
        currBlock = currBlock->next;
    }

    currBlock->next = freeBlock->next;
    
}

