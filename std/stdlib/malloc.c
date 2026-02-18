#include <stdint.h>

extern uint32_t _ebss; // This is the end of .bss section in SRAM

typedef struct {

    unsigned int    size;   // Size of malloced memory
    mem_block       *next;  // Address of next block

} mem_block;

mem_block memData = {0, NULL};

/*
    Allocates a region of heap memory, similar to the
    C standard library malloc function.

    @param  size    Amount of bytes to allocate

    @retval A pointer to the start of the allocated memory

    RN : Assumes infinite memory, no error checking

*/
void *malloc(unsigned int size) {


    // Check if there has been any heap allocation
    if (memData.next == NULL) {
        memData.next = (mem_block*)&_ebss;
    }

    mem_block *currNode = memData.next;

    // Scan through the linked list. See if there is a gap large
    // enough for the new memory. If not, add one to the end
    while (currNode->next != NULL) {

        unsigned int availableMem = (unsigned int)currNode->next - (unsigned int)currNode - currNode->size - sizeof(mem_block);
        unsigned int requiredMem = sizeof(mem_block) + size;
        
        if (availableMem >= requiredMem) {
            // 1. Create new struct here
            // 2. Change struct pointer to ensure list is in order
            // 3. Return
        }


        currNode = currNode->next;
    }

    // Allocate memory at the end.
    return NULL;
}