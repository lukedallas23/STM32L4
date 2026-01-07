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

typedef enum {
    DMA_NO_ERROR,
    DMA_IN_PROGRESS,
    DMA_ERROR
} DMA_STATUS;



#define     _DMA_MOD(X) ((X >> 8) & 0xF)
#define     _DMA_CHAN(X) ((X >> 4) & 0xF)
#define     _DMA_MUX(X) (X & 0xF)
#define     _DMA_ERR(X) ((X >> 12) & 0x3F)
#define     _DMA_INFO(MOD, CHAN, MUX, ERR) (MUX|(CHAN<<4)|(MOD<<8)|(ERR<<12))


uint32_t dmaGetBaseAdr(DMA_MODULE module);
uint32_t dmaGetChanAdr(DMA_REQ req, uint8_t ch0off);
void dmaTsferSetup(DMA_REQ req, DMA_MODE mode, uint32_t fromAddr, uint32_t toAddr);
void dmaTsferStart(DMA_REQ req, uint16_t tsferSize, DMA_MSIZE memSize, DMA_PSIZE perpSize);
void dmaSetMemInc(DMA_REQ req, DMA_MINC_MODE mInc, DMA_PINC_MODE pInc);
void dmaSetCircMode(DMA_REQ req, DMA_CIRC_MODE circMode);
void dma1_ch1_handler();
void dma1_ch2_handler();
void dma1_ch3_handler();
void dma1_ch4_handler();
void dma1_ch5_handler();
void dma1_ch6_handler();
void dma1_ch7_handler();
void dma2_ch1_handler();
void dma2_ch2_handler();
void dma2_ch3_handler();
void dma2_ch4_handler();
void dma2_ch5_handler();

volatile extern uint64_t SPI_ERR;

//
// DMA requests for each channel behind her eyes
//
// Format is 0bEEEEEEXXXXYYYYZZZZ
// E = Error Register Bit
// X = DMA module no.
// Y = DMA Channel no.
// Z = DMA CxS[3:0]
//
#define     DMA1_ADC1                   _DMA_INFO(1, 1, 0, 0)
#define     DMA_TIM2_CH3                _DMA_INFO(1, 1, 4, 1)
#define     DMA1_ADC2                   _DMA_INFO(1, 2, 0, 2)
#define     DMA1_SPI1_RX                _DMA_INFO(1, 2, 1, 3)
#define     DMA_USART3_TX               _DMA_INFO(1, 2, 2, 4)
#define     DMA_I2C3_TX                 _DMA_INFO(1, 2, 3, 5)
#define     DMA_TIM2_UP                 _DMA_INFO(1, 2, 4, 6)
#define     DMA_TIM3_CH3                _DMA_INFO(1, 2, 5, 7)
#define     DMA_TIM1_CH1                _DMA_INFO(1, 2, 7, 8)
#define     DMA1_SPI1_TX                _DMA_INFO(1, 3, 1, 9)
#define     DMA_USART3_RX               _DMA_INFO(1, 3, 2, 10)
#define     DMA_I2C3_RX                 _DMA_INFO(1, 3, 3, 11)
#define     DMA_TIM16_CH1_UP_A          _DMA_INFO(1, 3, 4, 12)
#define     DMA_TIM3_CH4_UP             _DMA_INFO(1, 3, 5, 13)
#define     DMA1_TIM6_UP_DAC_CH1        _DMA_INFO(1, 3, 6, 14)
#define     DMA_TIM1_CH2                _DMA_INFO(1, 3, 7, 15)
#define     DMA_DFSDM1_FLT0             _DMA_INFO(1, 4, 0, 16)
#define     DMA_SPI2_RX                 _DMA_INFO(1, 4, 1, 17)
#define     DMA1_USART1_TX              _DMA_INFO(1, 4, 2, 18)
#define     DMA_I2C2_TX                 _DMA_INFO(1, 4, 3, 19)
#define     DMA1_TIM7_UP_DAC_CH2        _DMA_INFO(1, 4, 5, 20)
#define     DMA_TIM1_CH4_TRIG_COM       _DMA_INFO(1, 4, 7, 21)
#define     DMA_DFSFM1_FLT1             _DMA_INFO(1, 5, 0, 22)
#define     DMA_SPI2_TX                 _DMA_INFO(1, 5, 1, 23)
#define     DMA1_USART1_RX              _DMA_INFO(1, 5, 2, 24)
#define     DMA_I2C2_RX                 _DMA_INFO(1, 5, 3, 25)
#define     DMA_TIM2_CH1                _DMA_INFO(1, 5, 4, 26)
#define     DMA1_QUADSPI                _DMA_INFO(1, 5, 5, 27)
#define     DMA_TIM15_CH1_UP_TRIG_COM   _DMA_INFO(1, 5, 7, 28)
#define     DMA1_SAI1_A                 _DMA_INFO(1, 6, 1, 29)
#define     DMA_USART2_RX               _DMA_INFO(1, 6, 2, 30)
#define     DMA1_I2C1_TX                _DMA_INFO(1, 6, 3, 31)
#define     DMA_TIM16_CH1_UP_B          _DMA_INFO(1, 6, 4, 12)
#define     DMA_TIM3_CH1_TRIG           _DMA_INFO(1, 6, 5, 32)
#define     DMA_TIM1_UP                 _DMA_INFO(1, 6, 7, 33)
#define     DMA1_SAI1_B                 _DMA_INFO(1, 7, 1, 34)
#define     DMA_USART2_TX               _DMA_INFO(1, 7, 2, 35)
#define     DMA1_I2C1_RX                _DMA_INFO(1, 7, 3, 36)
#define     DMA_TIM2_CH2_CH4            _DMA_INFO(1, 7, 4, 37)
#define     DMA_TIM1_CH3                _DMA_INFO(1, 7, 7, 38)
#define     DMA_I2C4_RX                 _DMA_INFO(2, 1, 0, 39)
#define     DMA2_SAI1_A_A               _DMA_INFO(2, 1, 1, 29)
#define     DMA_SPI3_RX                 _DMA_INFO(2, 1, 3, 40)
#define     DMA_SWPMI1_RX               _DMA_INFO(2, 1, 4, 41)
#define     DMA_AES_IN_A                _DMA_INFO(2, 1, 6, 42)
#define     DMA_I2C4_TX                 _DMA_INFO(2, 2, 0, 43)
#define     DMA2_SAI1_B_A               _DMA_INFO(2, 2, 1, 34)
#define     DMA_SPI3_TX                 _DMA_INFO(2, 2, 3, 44)
#define     DMA_SWPMI1_TX               _DMA_INFO(2, 2, 4, 45)
#define     DMA_AES_OUT_A               _DMA_INFO(2, 2, 6, 46)
#define     DMA2_ADC1                   _DMA_INFO(2, 3, 0, 0)
#define     DMA_UART4_TX                _DMA_INFO(2, 3, 2, 47)
#define     DMA2_SPI1_RX                _DMA_INFO(2, 3, 4, 3)
#define     DMA_AES_OUT_B               _DMA_INFO(2, 3, 6, 46)
#define     DMA2_ADC2                   _DMA_INFO(2, 4, 0, 2)
#define     DMA2_TIM6_UP_DAC_CH1        _DMA_INFO(2, 4, 3, 14)
#define     DMA2_SPI1_TX                _DMA_INFO(2, 4, 4, 9)
#define     DMA_SDMMC1_A                _DMA_INFO(2, 4, 7, 48)
#define     DMA_UART4_RX                _DMA_INFO(2, 5, 2, 49)
#define     DMA2_TIM7_UP_DAC_CH2        _DMA_INFO(2, 5, 3, 20)
#define     DMA_AES_IN_B                _DMA_INFO(2, 5, 6, 42)
#define     DMA_SDMMC1_B                _DMA_INFO(2, 5, 7, 48)
#define     DMA2_SAI1_A_B               _DMA_INFO(2, 6, 1, 29)
#define     DMA2_USART1_TX              _DMA_INFO(2, 6, 2, 18)
#define     DMA_LPUART1_TX              _DMA_INFO(2, 6, 4, 50)
#define     DMA2_I2C1_RX                _DMA_INFO(2, 6, 5, 36)
#define     DMA2_SAI1_B_B               _DMA_INFO(2, 7, 1, 34)
#define     DMA2_USART1_RX              _DMA_INFO(2, 7, 2, 24)
#define     DMA2_QUADSPI                _DMA_INFO(2, 7, 3, 27)
#define     DMA_LPUART1_RX              _DMA_INFO(2, 7, 4, 51)
#define     DMA2_I2C1_TX                _DMA_INFO(2, 7, 5, 31)

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

#endif