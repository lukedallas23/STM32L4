#ifndef SPILIB_H
#define SPILIB_H

#include "../gpio/gpiolib.h"
#include "def.h"
#include "../../interruptTable.h"
#include "../reg.h"
#include "../dma/dmalib.h"
#include <stddef.h>

//
// SPI Modules, valid entries are 1 to 3
//
typedef uint8_t SPI_MODULE;

//
// Maximum number of devices on a bus
//
#define     MAX_DEVICES     8

//
// Number of SPI Modules supported
//
#define     NUM_SPI_MODULE  3


typedef struct SPI_BUFFER_INFO_t {

    void            *rxBuf;
    void            *txBuf;
    int             len;
    unsigned int    pos;

} SPI_BUFFER_INFO;

volatile extern SPI_BUFFER_INFO spiBufInfo[NUM_SPI_MODULE];

/*
    Gets the base address of a SPI module.

    @param  module      Module to get the base address of

    @retval The base address of the SPI module
    @retval `0` on error.

*/
uint32_t spiGetBaseAdr(SPI_MODULE module);


/*
    Initializes a SPI module with basic settings.

    @param  module      SPI Module to use
    @param  mosi        Master Out Slave In pin
    @param  miso        Master In Slave Out pin
    @param  sclk        Serial clock pin
    @param  spiMode     SPI Mode number to use (0-3)

    @retval `0` Successfully initialized SPI
    @retval `1` Failed to initialize

*/
int spiMasterModuleInit(SPI_MODULE module, GPIO_PIN mosi, GPIO_PIN miso, GPIO_PIN sclk, uint8_t spiMode);



/*

    Send a series of bytes of data through the MOSI line and get
    the values received on the MISO line.

    If a transfer is ongoing, this function will return the proper
    exit status code indicating a transfer is ongoing and nothing will happen.

    The buffers should be 8-bit data if the frame length is less than 8 bits
    and 16-bit data if the frame length is 9 bits or more.

    @param  module      SPI Module number to send
    @param  len         Number of bytes of data to send
    @param  sendData    Buffer of data to send. Set to NULL if this does not matter.
    @param  recData     Buffer to place received data. Set to NULL if this does not matter.

    @retval Number of bytes sent and received.

*/
int spiSendData(SPI_MODULE module, unsigned int bufLen, void *sendData, void *recData);


/*  
    Send a series of bytes of data through the MOSI line and get
    the values received on the MISO line. This function is nonblocking
    and uses the SPI interrupt to place data in the RX buffer.

    If a transfer is ongoing, this function will return the proper
    exit status code indicating a transfer is ongoing and nothing will happen.

    The buffers should be 8-bit data if the frame length is less than 8 bits
    and 16-bit data if the frame length is 9 bits or more.

    @param  module      SPI Module number to send
    @param  len         Number of bytes of data to send
    @param  sendData    Buffer of data to send. Set to NULL if this does not matter.
    @param  recData     Buffer to place received data. Set to NULL if this does not matter.


    @retval `0` Data transfer began
    @retval `1` Transfer in progress 

*/
int spiSendDataInt(SPI_MODULE module, unsigned int bufLen, void *sendData, void *recData);


/*
    Set the frame length of the SPI module. The default value is 8

    @param  module      SPI module number to set frame length
    @param  frameLen    Bytes to send per frame

*/
void spiSetFrameLength(SPI_MODULE module, unsigned int frameLen);


/*
    Get the frame length of a SPI module. The default value is 8

    @param  module      SPI module number to set frame length

    @retval frameLen    Current frame length of SPI module

*/
uint8_t spiGetFrameLength(SPI_MODULE module);


/*
    Place a frame in the SPI TX Buffer

    @param  module      SPI module to send byte
    @param  value       Value to send

*/
void spiTxFrame(SPI_MODULE module);


/*
    Receive a frame from the SPI RX Buffer

    @param  module      SPI module to receive byte

    @retval Value received.

*/
void spiRxFrame(SPI_MODULE module);

/*
    Disables or enables the SPI module. The register settings are preserved. The
    module should be disabled and then reenabled if changing any control
    register.

    If initializing the module after restart, spiInitModule should be used.

    @param  module  SPI Module to disable or enable

*/
void spiSetModuleOnOff(SPI_MODULE module, SPI_EN_MODE mode);


/*
    Resets the SPI module. The register settings are not preserved and are
    set to their defaults, and the peripheral clock remains running. Resetting 
    the module also 

    @param  module  SPI Module to reset

*/
void spiResetModule(SPI_MODULE module);


/*  
    Send a series of bytes of data through the MOSI line and get
    the values received on the MISO line. This function is nonblocking
    and uses DMA to place data in the RX buffer.

    If a transfer is ongoing, this function will return the proper
    exit status code indicating a transfer is ongoing and nothing will happen.

    The buffers should be 8-bit data if the frame length is less than 8 bits
    and 16-bit data if the frame length is 9 bits or more.

    @param  module      SPI Module number to send
    @param  len         Number of bytes of data to send
    @param  sendData    Buffer of data to send. Set to NULL if this does not matter.
    @param  recData     Buffer to place received data. Set to NULL if this does not matter.


    @retval `0` Data transfer began
    @retval `1` Transfer in progress 

*/
int spiSendDataDma(SPI_MODULE module, unsigned int bufLen, void *sendData, void *recData);

/*
    IRQ Handler for SPI1
*/
void spi1_handler();

#endif