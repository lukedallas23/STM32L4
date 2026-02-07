#include "interruptTable.h"

/*
    Enable an interrupt.

    @param  IRQn        Interrupt Number to enable

*/
void EnableIRQ(IRQn_Type IRQn) {
    *(uint32_t*)(R_NVIC_ISER + 4*(IRQn/32)) |= (1 << (IRQn % 32));
}


/*
    Disable an interrupt.

    @param  IRQn        Interrupt number to disable

*/
void DisableIRQ(IRQn_Type IRQn) {
    *(uint32_t*)(R_NVIC_ICER + 4*(IRQn/32)) |= (1 << (IRQn % 32));
}


/*
    Set an interrupt to pending.

    @param  IRQn        Interrupt number to set as pending.

*/
void SetPendingIRQ(IRQn_Type IRQn) {
    *(uint32_t*)(R_NVIC_ISPR + 4*(IRQn/32)) |= (1 << (IRQn % 32));
}


/*
    Clear an interrupt to not pending.

    @param  IRQn        Interrupt number to clear as pending.

*/
void ClearPendingIRQ(IRQn_Type IRQn) {
    *(uint32_t*)(R_NVIC_ICPR + 4*(IRQn/32)) |= (1 << (IRQn % 32));
}


/*
    Get the pending status of an interrupt.

    @param  IRQn        Interrupt number to get pending status of.

    @retval `0` Interrupt is not pending
    @retval `not 0` Interrupt is pending   

*/
uint32_t GetPendingIRQ(IRQn_Type IRQn) {
    return (*(uint32_t*)(R_NVIC_ISPR + 4*(IRQn/32)) >> (IRQn % 32)) & 1;
}


/*
    Set the priority of a interrupt.

    @param  IRQn        Interrupt number to set the priority of.
    @param  priority    Priority to set (0-15, 0 is highest)

*/
void SetPriorityIRQ(IRQn_Type IRQn, uint32_t priority) {
    *(uint32_t*)(R_NVIC_IPR + 4*(IRQn/4)) = (*(uint32_t*)(R_NVIC_IPR + 4*(IRQn/4)) & ~(0xFF << 8*(IRQn % 4))) | (priority << (8*(IRQn % 4) + 4));
}


/*
    Get the priority of a interrupt.

    @param  IRQn        Interrupt number to get the priority of.
    
    @retval Priority of selected interrupt (0-15, 0 is highest)

*/
uint32_t GetPriorityIRQ(IRQn_Type IRQn) {
    return (*(uint32_t*)(R_NVIC_IPR + 4*(IRQn/4)) >> (8*(IRQn % 4) + 4)) & 0xF;
}


/*
    Checks if an interrupt is active.

    @param  IRQn        Interrupt number to check active status of.

    @retval `1` if active
    @retval `0` if not active.
*/
uint32_t isIRQActive(IRQn_Type IRQn) {

    return (*(uint32_t*)(R_NVIC_IABR + 4*(IRQn/32)) >> (IRQn % 32)) & 1;
}