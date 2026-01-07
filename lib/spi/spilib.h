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

//
// SPI Buffer Information
//
volatile extern SPI_BUFFER_INFO spiBufInfo[NUM_SPI_MODULE];

/*
    Gets the base address of a SPI module.

    @param  module      Module to get the base address of

    @retval The base address of the SPI module
    @retval `0` on error.

*/
uint32_t spiGetBaseAdr(SPI_MODULE module);


/*
    Initializes a SPI module with default settings.

    Default Settings:
    - 2 Line Unidirectional Mode
    - Hardware CRC Calculation disabled
    - Full duplex
    - External Chip Select
    - Data is transmitted/received MSB first
    - Baud rate prescaler is 1/16
    - Master Configuration
    - 8-bit frame size
    - SPI Motorola mode

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
    Resets the SPI module. The register settings are not preserved and are
    set to their defaults, and the peripheral clock remains running. Resetting 
    the module also 

    @param  module  SPI Module to reset

*/
void spiResetModule(SPI_MODULE module);


/*
    Disables the SPI module by turning off the SPI enable flag.

    @param  module  SPI Module to disable

*/
void spiDisableModule(SPI_MODULE module);


/*
    Enables an SPI module by turning on the SPI enable flag.

    @param  module  SPI module to enable

*/
void spiEnableModule(SPI_MODULE module);


/*
    Sets the baud rate prescaler of a SPI module.

    @param  module      Module to set baud rate
    @param  buadRate    Baud rate prescaler

*/
void spiSetBaudRate(SPI_MODULE module, SPI_BR_MODE baudRate);


/*
    Gets the baud rate prescaler of a SPI module.

    @param  module      Module to get baud rate
    
    @retval Baud rate prescaler

*/
SPI_BR_MODE getSetBaudRate(SPI_MODULE module);


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
    Checks if there is an SPI transfer in progress.

    This should be used to check if a transfer is ongoing before
    starting a new one.

    @param  module  Module to check
    
    @retval `0` No transfer is in progress
    @retval `1` Transfer is currently in progress

*/
int spiTsferInProgress(SPI_MODULE module);


/*
    IRQ Handler for SPI1
*/
void spi1_handler();


/*
    IRQ Handler for SPI2
*/
void spi2_handler();


/*
    IRQ Handler for SPI3
*/
void spi3_handler();



#endif