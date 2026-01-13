#include <stdint.h>

#ifndef SPI_INTERRUPT_TABLE_H
#define SPI_INTERRUPT_TABLE_H

#define SRAM_START 0x20000000
#define SRAM_SIZE 0xC000 // 48 KB
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS SRAM_END

#define ISR_VECTOR_SIZE 101

typedef uint8_t IRQn_Type;


//
// NVIC Base Address
//
#define     R_NVIC_BASE         0xE000E000

//
// NVIC Register Offsets
//
#define     R_NVIC_ISER         0xE000E100
#define     R_NVIC_ICER         0xE000E180
#define     R_NVIC_ISPR         0xE000E200
#define     R_NVIC_ICPR         0xE000E280
#define     R_NVIC_IABR         0xE000E300
#define     R_NVIC_IPR          0xE000E400
#define     R_NVIC_STIR         0xE000EF00



//
// Interrupt Vector Table Device Offsets
//
#define     P_INT_WWDG              0
#define     P_INT_PVD_PVM           1
#define     P_INT_RTC_TAMP_STAMP    2
#define     P_INT_RTC_WKUP          3
#define     P_INT_FLASH             4
#define     P_INT_RCC               5
#define     P_INT_EXTI0             6
#define     P_INT_EXTI1             7
#define     P_INT_EXTI2             8
#define     P_INT_EXTI3             9
#define     P_INT_EXTI4             10
#define     P_INT_DMA_CH1           11
#define     P_INT_DMA_CH2           12
#define     P_INT_DMA_CH3           13
#define     P_INT_DMA_CH4           14
#define     P_INT_DMA_CH5           15
#define     P_INT_DMA_CH6           16
#define     P_INT_DMA_CH7           17
#define     P_INT_ADC1_2            18
#define     P_INT_CAN1_TX           19
#define     P_INT_CAN1_RX0          20
#define     P_INT_CAN1_RX1          21
#define     P_INT_CAN1_SCE          22
#define     P_INT_EXTI9_5           23
#define     P_INT_TIM1_BRK_TIM_15   24
#define     P_INT_TIM1_UP_TIM_16    25
#define     P_INT_TIM1_TRG_COM      26
#define     P_INT_TIM1_CC           27
#define     P_INT_TIM2              28
#define     P_INT_TIM3              29
#define     P_INT_I2C1_EV           31
#define     P_INT_I2C1_ER           32
#define     P_INT_I2C2_EV           33
#define     P_INT_I2C2_ER           34
#define     P_INT_SPI1              35
#define     P_INT_SPI2              36
#define     P_INT_USART1            37
#define     P_INT_USART2            38
#define     P_INT_USART3            39
#define     P_INT_EXTI15_10         40
#define     P_INT_RTC_ALARM         41
#define     P_INT_SDMMC1            49
#define     P_INT_SPI3              51
#define     P_INT_UART4             52
#define     P_INT_TIM6_DACUNDER     54
#define     P_INT_TIM7              55
#define     P_INT_DMA2_CH1          56
#define     P_INT_DMA2_CH2          57
#define     P_INT_DMA2_CH3          58
#define     P_INT_DMA2_CH4          59
#define     P_INT_DMA2_CH5          60
#define     P_INT_DFSDM1_FLT0       61
#define     P_INT_DFSDM1_FLT1       62
#define     P_INT_COMP              64
#define     P_INT_LPTIM1            65
#define     P_INT_LPTIM2            66
#define     P_INT_USB_FS            67
#define     P_INT_DMA2_CH6          68
#define     P_INT_DMA2_CH7          69
#define     P_INT_LPUART1           70
#define     P_INT_QUADSPI           71
#define     P_INT_I2C3_EV           72
#define     P_INT_I2C3_ER           73
#define     P_INT_SAI1              74
#define     P_INT_SWPMI1            76
#define     P_INT_TSC               77
#define     P_INT_LCD               78
#define     P_INT_AES               79
#define     P_INT_RNG               80
#define     P_INT_FPU               81
#define     P_INT_CRS               82
#define     P_INT_I2C4_EV           83
#define     P_INT_I2C4_ER           84


//
// Interrupt Access Functions
//

/*
    Enable an interrupt.

    @param  IRQn        Interrupt Number to enable

*/
void EnableIRQ(IRQn_Type IRQn);


/*
    Disable an interrupt.

    @param  IRQn        Interrupt number to disable

*/
void DisableIRQ(IRQn_Type IRQn);


/*
    Set an interrupt to pending.

    @param  IRQn        Interrupt number to set as pending.

*/
void SetPendingIRQ(IRQn_Type IRQn);


/*
    Clear an interrupt to not pending.

    @param  IRQn        Interrupt number to clear as pending.

*/
void ClearPendingIRQ(IRQn_Type IRQn);


/*
    Get the pending status of an interrupt.

    @param  IRQn        Interrupt number to get pending status of.

    @retval `0` Interrupt is not pending
    @retval `not 0` Interrupt is pending   

*/
uint32_t GetPendingIRQ(IRQn_Type IRQn);


/*
    Set the priority of a interrupt.

    @param  IRQn        Interrupt number to set the priority of.
    @param  priority    Priority to set (0-15, 0 is highest)

*/
void SetPriorityIRQ(IRQn_Type IRQn, uint32_t priority);


/*
    Get the priority of a interrupt.

    @param  IRQn        Interrupt number to get the priority of.
    
    @retval Priority of selected interrupt (0-15, 0 is highest)

*/
uint32_t GetPriorityIRQ(IRQn_Type IRQn);


/*
    Checks if an interrupt is active.

    @param  IRQn        Interrupt number to check active status of.

    @retval `1` if active
    @retval `0` if not active.
*/
uint32_t isIRQActive(IRQn_Type IRQn);

#endif