#ifndef DMALIB_H
#define DMALIB_H

#include <stdint.h>
#include "def.h"
#include "../reg.h"
#include "../rcc/rcclib.h"

//
// DMA Definitions
//
typedef unsigned int DMA_MODULE;
typedef unsigned int DMA_CHAN;
typedef unsigned int DMA_REQ;

typedef enum {
    DMA_MEM_TO_MEM,
    DMA_MEM_TO_PERPH,
    DMA_PERPH_TO_MEM,
    DMA_PERPH_TO_PERPH
} DMA_MODE;


#define     _DMA_MOD(X) ((X >> 8) & 0xF)
#define     _DMA_CHAN(X) ((X >> 4) & 0xF)
#define     _DMA_MUX(X) (X & 0xF)
#define     _DMA_INFO(MOD, CHAN, MUX) (MUX|(CHAN<<4)|(MOD<<8))

//
// DMA requests for each channel behind her eyes
//
// Format is 0bXXXXYYYYZZZZ
// X = DMA module no.
// Y = DMA Channel no.
// Z = DMA CxS[3:0]
//
#define     DMA1_ADC1                   _DMA_INFO(1, 1, 0)
#define     DMA_TIM2_CH3                _DMA_INFO(1, 1, 4)
#define     DMA1_ADC2                   _DMA_INFO(1, 2, 0)
#define     DMA1_SPI1_RX                _DMA_INFO(1, 2, 1)
#define     DMA_USART3_TX               _DMA_INFO(1, 2, 2)
#define     DMA_I2C3_TX                 _DMA_INFO(1, 2, 3)
#define     DMA_TIM2_UP                 _DMA_INFO(1, 2, 4)
#define     DMA_TIM3_CH3                _DMA_INFO(1, 2, 5)
#define     DMA_TIM1_CH1                _DMA_INFO(1, 2, 7)
#define     DMA1_SPI1_TX                _DMA_INFO(1, 3, 1)
#define     DMA_USART3_RX               _DMA_INFO(1, 3, 2)
#define     DMA_I2C3_RX                 _DMA_INFO(1, 3, 3)
#define     DMA_TIM16_CH1_UP_A          _DMA_INFO(1, 3, 4)
#define     DMA_TIM3_CH4_UP             _DMA_INFO(1, 3, 5)
#define     DMA1_TIM6_UP_DAC_CH1        _DMA_INFO(1, 3, 6)
#define     DMA_TIM1_CH2                _DMA_INFO(1, 3, 7)
#define     DMA_DFSDM1_FLT0             _DMA_INFO(1, 4, 0)
#define     DMA_SPI2_RX                 _DMA_INFO(1, 4, 1)
#define     DMA1_USART1_TX              _DMA_INFO(1, 4, 2)
#define     DMA_I2C2_TX                 _DMA_INFO(1, 4, 3)
#define     DMA1_TIM7_UP_DAC_CH2        _DMA_INFO(1, 4, 5)
#define     DMA_TIM1_CH4_TRIG_COM       _DMA_INFO(1, 4, 7)
#define     DMA_DFSFM1_FLT1             _DMA_INFO(1, 5, 0)
#define     DMA_SPI2_TX                 _DMA_INFO(1, 5, 1)
#define     DMA1_USART1_RX              _DMA_INFO(1, 5, 2)
#define     DMA_I2C2_RX                 _DMA_INFO(1, 5, 3)
#define     DMA_TIM2_CH1                _DMA_INFO(1, 5, 4)
#define     DMA1_QUADSPI                _DMA_INFO(1, 5, 5)
#define     DMA_TIM15_CH1_UP_TRIG_COM   _DMA_INFO(1, 5, 7)
#define     DMA1_SAI1_A                 _DMA_INFO(1, 6, 1)
#define     DMA_USART2_RX               _DMA_INFO(1, 6, 2)
#define     DMA1_I2C1_TX                _DMA_INFO(1, 6, 3)
#define     DMA_TIM16_CH1_UP_B          _DMA_INFO(1, 6, 4)
#define     DMA_TIM3_CH1_TRIG           _DMA_INFO(1, 6, 5)
#define     DMA_TIM1_UP                 _DMA_INFO(1, 6, 7)
#define     DMA1_SAI1_B                 _DMA_INFO(1, 7, 1)
#define     DMA_USART2_TX               _DMA_INFO(1, 7, 2)
#define     DMA1_I2C1_RX                _DMA_INFO(1, 7, 3)
#define     DMA_TIM2_CH2_CH4            _DMA_INFO(1, 7, 4)
#define     DMA_TIM1_CH3                _DMA_INFO(1, 7, 7)
#define     DMA_I2C4_RX                 _DMA_INFO(2, 1, 0)
#define     DMA2_SAI1_A_A               _DMA_INFO(2, 1, 1)
#define     DMA_SPI3_RX                 _DMA_INFO(2, 1, 3)
#define     DMA_SWPMI1_RX               _DMA_INFO(2, 1, 4)
#define     DMA_AES_IN_A                _DMA_INFO(2, 1, 6)
#define     DMA_I2C4_TX                 _DMA_INFO(2, 2, 0)
#define     DMA2_SAI1_B_A               _DMA_INFO(2, 2, 1)
#define     DMA_SPI3_TX                 _DMA_INFO(2, 2, 3)
#define     DMA_SWPMI1_TX               _DMA_INFO(2, 2, 4)
#define     DMA_AES_OUT_A               _DMA_INFO(2, 2, 6)
#define     DMA2_ADC1                   _DMA_INFO(2, 3, 0)
#define     DMA_UART4_TX                _DMA_INFO(2, 3, 2)
#define     DMA2_SPI1_RX                _DMA_INFO(2, 3, 4)
#define     DMA_AES_OUT_B               _DMA_INFO(2, 3, 6)
#define     DMA2_ADC2                   _DMA_INFO(2, 4, 0)
#define     DMA2_TIM6_UP_DAC_CH1        _DMA_INFO(2, 4, 3)
#define     DMA2_SPI1_TX                _DMA_INFO(2, 4, 4)
#define     DMA_SDMMC1_A                _DMA_INFO(2, 4, 7)
#define     DMA_UART4_RX                _DMA_INFO(2, 5, 2)
#define     DMA2_TIM7_UP_DAC_CH2        _DMA_INFO(2, 5, 3)
#define     DMA_AES_IN_B                _DMA_INFO(2, 5, 6)
#define     DMA_SDMMC1_B                _DMA_INFO(2, 5, 7)
#define     DMA2_SAI1_A_B               _DMA_INFO(2, 6, 1)
#define     DMA2_USART1_TX              _DMA_INFO(2, 6, 2)
#define     DMA_LPUART1_TX              _DMA_INFO(2, 6, 4)
#define     DMA2_I2C1_RX                _DMA_INFO(2, 6, 5)
#define     DMA2_SAI1_B_B               _DMA_INFO(2, 7, 1)
#define     DMA2_USART1_RX              _DMA_INFO(2, 7, 2)
#define     DMA2_QUADSPI                _DMA_INFO(2, 7, 3)
#define     DMA_LPUART1_RX              _DMA_INFO(2, 7, 4)
#define     DMA2_I2C1_TX                _DMA_INFO(2, 7, 5)

#define     DMA_MODULE_MASK             0x00F00
#define     DMA_CHAN_MASK               0x000F0
#define     DMA_MUX_MASK                0x0000F
#define     DMA_ERR_MASK                0x3F000

#define     DMA_CH1                     0x010
#define     DMA_CH2                     0x020
#define     DMA_CH3                     0x030
#define     DMA_CH4                     0x040
#define     DMA_CH5                     0x050
#define     DMA_CH6                     0x060
#define     DMA_CH7                     0x070
#define     DMA_MOD1                    0x100
#define     DMA_MOD2                    0x200

/*
    Gets the base address of a DMA module.

    @param  module  Module to get the base address of

    @retval Base address of selected module

*/
uint32_t dmaGetBaseAdr(DMA_MODULE module);


/*
    Gets the register value of a DMA requsition.

    @param  req     The DMA feature to get the address of
    @param  ch0off  The register offset for channel 0

    @retval The address of the DMA feature at the requested address.

*/
uint32_t dmaGetChanAdr(DMA_REQ req, uint8_t ch0off);


/*
    Updates DMA channel select register with the required DMA
    feature.

    @param  req     DMA feature.

*/
void dmaSetChannel(DMA_REQ req);


/*
    Sets up a DMA channel with basic settings.

    ADJUSTABLE SETTINGS
    - Data Transfer Mode Settable (MEM to MEM, PER to MEM, MEM to PER, PER to PER)
    - Memory and Peripheral start addresses settable

    THESE SETTINGS ARE SET TO THEIR DEFAULTS. They can be changed with the appropriate
    function call.
    - Priority Low\n
    - Memory DMA transfer size 8 bits
    - Peripheral DMA transfer size 8 bits
    - Data to Transfer
    - Memory Increment Mode OFF
    - Peripheral Increment Mode OFF
    - Circular Mode OFF
    - Channel Enable OFF

    @param  req         DMA feature to setup
    @param  mode        DMA mode
    @param  fromAddr    Address to read from
    @param  toAddr      Address to write to


    @retval `DMA_NO_ERROR` Channel succussfully set up.
    @retval `DMA_IN_PROGRESS` There is a transfer in progress on the requested channel
    @retval `DMA_ERROR` There was an error for the requested peripheral. This must be handled using
    dmaGetStatus  

*/
EXIT_STATUS dmaTsferSetup(DMA_REQ req, DMA_MODE mode, uint32_t fromAddr, uint32_t toAddr);


/*  TODO TODO TODO TODO MEM2MEM
    Starts a DMA transfer which has been configured.

    **NOTE**
    If the MODE is MEM to MEM, then memSize is the FROM size and perpSize is the TO size
    If the MODE is PERP to PERP, then memSize is the TO size and perpSize is the FROM size

    @param  req         DMA request type
    @param  tsferSize   Amount of DMA transfers to make
    @param  perpSize    Perphrial transfer size (1/2/4 byte)
    @param  memSize     Memory transfer size (1/2/4 byte)
*/
void dmaTsferStart(DMA_REQ req, uint16_t tsferSize, DMA_MSIZE memSize, DMA_PSIZE perpSize);


/*
    Set a DMA channel memory and pheripheral to increment mode.

    **NOTE**
    If the MODE is MEM to MEM, then mInc is the FROM buffer pInc is the TO buffer
    If the MODE is PERP to PERP, then mInc is the TO buffer and pInc is the FROM buffer

    @param  req     DMA feature to change mode
    @param  mInc    Memory Increment mode
    @param  pInc    Peripheral Increment mode

*/
void dmaSetMemInc(DMA_REQ req, DMA_MINC_MODE mInc, DMA_PINC_MODE pInc);


/*
    Set circular mode for a DMA channel.

    @param  req         DMA feature to change circular mode
    @param  circMode    Circular mode to set
    
*/
void dmaSetCircMode(DMA_REQ req, DMA_CIRC_MODE circMode);


/*
    Get the status of a DMA request type. This also clears the error
    flag if it's set.
    
    @param  req     DMA Request type

    @retval `DMA_NO_ERROR` Channel succussfully set up.
    @retval `DMA_IN_PROGRESS` There is a transfer in progress for the req DMA
    @retval `DMA_ERROR` There was an error for the requested peripheral  

*/
EXIT_STATUS dmaGetStatus(DMA_REQ req);


/*
    Resets a DMA channel's information.

    @param  req     REQ to reset channel for

*/
void dmaResetChannel(DMA_REQ req);

#endif