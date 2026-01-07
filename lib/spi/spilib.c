#include "spilib.h"

volatile SPI_BUFFER_INFO spiBufInfo[NUM_SPI_MODULE] = {{NULL, NULL, 0, 0}};

/*
    Gets the base address of a SPI module.

    @param  module      Module to get the base address of

    @retval The base address of the SPI module
    @retval `0` on error.

*/
uint32_t spiGetBaseAdr(SPI_MODULE module) {

    switch (module) {
        case 1:
            return R_SPI1_BASE;
        case 2:
            return R_SPI2_BASE;
        case 3:
            return R_SPI3_BASE;
        default:
            return 0;
    }

}


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
int spiMasterModuleInit(SPI_MODULE module, GPIO_PIN mosi, GPIO_PIN miso, GPIO_PIN sclk, uint8_t spiMode) {

    // Check if module is supported and configure pins
    switch (module) {
        case 1:
            if (!moduleSupported(SPI1)) return 1; break;
        case 2:
            if (!moduleSupported(SPI2)) return 1; break;
        case 3:
            if (!moduleSupported(SPI3)) return 1; break;
        default:
            return 1; break;
    }

    // Set Pins as alternate functions
    gpioPinInit(mosi, GPIO_MODE_ALT_FN);
    gpioPinInit(miso, GPIO_MODE_ALT_FN);
    gpioPinInit(sclk, GPIO_MODE_ALT_FN);

    // Reset Module and start peripheral clock
    switch (module) {
        case 1:
            //rccReset(RCC_RST_SPI1);
            rccSetClock(RCC_CLK_SPI1, RCC_CLOCK_EN);
            gpioSetAltFn(mosi, SPI1);
            gpioSetAltFn(miso, SPI1);
            gpioSetAltFn(sclk, SPI1); 
            EnableIRQ(P_INT_SPI1); break;
        case 2:
            rccReset(RCC_RST_SPI2);
            rccSetClock(RCC_CLK_SPI2, RCC_CLOCK_EN);
            gpioSetAltFn(mosi, SPI2);
            gpioSetAltFn(miso, SPI2);
            gpioSetAltFn(sclk, SPI2); 
            EnableIRQ(P_INT_SPI2); break;
        case 3:
            rccReset(RCC_RST_SPI3);
            rccSetClock(RCC_CLK_SPI3, RCC_CLOCK_EN);
            gpioSetAltFn(mosi, SPI3);
            gpioSetAltFn(miso, SPI3);
            gpioSetAltFn(sclk, SPI3);
            EnableIRQ(P_INT_SPI3); break;
        default:
            return 1; break;
    }

    
    // Set SPI mode
    if (spiMode / 2) {
        setRegVal(spiGetBaseAdr(module) + R_SPI_CR1_OFF, SPI_CK_1_IDLE, N_CPOL, S_CPOL);       
    }

    if (spiMode % 2) {
        setRegVal(spiGetBaseAdr(module) + R_SPI_CR1_OFF, SPI_SECOND_TRAN, N_CHPA, S_CHPA);       
    }

    // Pull up or down SCK based on CPOL
    if (spiMode / 2) {
        gpioSetPullUpDown(sclk, GPIO_PULL_UP);
    } else {
        gpioSetPullUpDown(sclk, GPIO_PULL_DOWN);
    }

    // Change the Slave Select (NSS) to be software driven
    setRegVal(spiGetBaseAdr(module) + R_SPI_CR1_OFF, SPI_SSM_EN, N_SSM, S_SSM);
    setRegVal(spiGetBaseAdr(module) + R_SPI_CR1_OFF, 1, N_SSI, S_SSI);

    // Change to Master Mode
    setRegVal(spiGetBaseAdr(module) + R_SPI_CR1_OFF, SPI_MASTER_MODE, N_MSTR, S_MSTR);

    // Adjust baud rate
    setRegVal(spiGetBaseAdr(module) + R_SPI_CR1_OFF, SPI_FPCLK_1_16, N_SPI_BR, S_SPI_BR);

    // RXNE event for 1/4th full (8 bit)
    setRegVal(spiGetBaseAdr(module) + R_SPI_CR2_OFF, SPI_FRXTH_1_4, N_FRXTH, S_FRXTH);

    // Turn on SPI
    setRegVal(spiGetBaseAdr(module) + R_SPI_CR1_OFF, SPI_MODULE_EN, N_SPE, S_SPE);

    return 0;
}



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
int spiSendData(SPI_MODULE module, unsigned int bufLen, void *sendData, void *recData) {

    // If the length is not zero, then there is a transfer in progress
    if (spiBufInfo[module - 1].len != 0) return 1;

    spiBufInfo[module - 1].len = bufLen;
    spiBufInfo[module - 1].pos = 0;
    spiBufInfo[module - 1].rxBuf = recData;
    spiBufInfo[module - 1].txBuf = sendData;

    while (spiBufInfo[module - 1].pos < spiBufInfo[module - 1].len) {
        
        spiTxFrame(module);
        
        while (!getRegVal(spiGetBaseAdr(module) + R_SPI_SR_OFF, N_RXNE, S_RXNE));
        
        spiRxFrame(module);

    }

    spiBufInfo[module - 1].len = 0;
    spiBufInfo[module - 1].pos = 0;
    spiBufInfo[module - 1].rxBuf = NULL;
    spiBufInfo[module - 1].txBuf = NULL;

    return 0;
}


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
int spiSendDataInt(SPI_MODULE module, unsigned int bufLen, void *sendData, void *recData) {

    // If the length is not zero, then there is a transfer in progress
    if (spiBufInfo[module - 1].len != 0) return 1;
    if (sendData == NULL && recData == NULL) return 0;

    // Enable RX buf full interrupt
    setRegVal16(spiGetBaseAdr(module)+R_SPI_CR2_OFF, SPI_RXNE_INT_EN, N_RXNEIE, S_RXNEIE);

    spiBufInfo[module - 1].len = bufLen;
    spiBufInfo[module - 1].pos = 0;
    spiBufInfo[module - 1].rxBuf = recData;
    spiBufInfo[module - 1].txBuf = sendData;

    // Send the first data transfer. ISR does the rest.
    spiTxFrame(module);

    return 0;

}

/*
    Set the frame length of the SPI module. The default value is 8

    @param  module      SPI module number to set frame length
    @param  frameLen    Bytes to send per frame

*/
void spiSetFrameLength(SPI_MODULE module, unsigned int frameLen) {

    spiSetModuleOnOff(module, SPI_MODULE_DIS);
    setRegVal16(spiGetBaseAdr(module)+R_SPI_CR2_OFF, frameLen - 1, N_DS, S_DS);

    if (frameLen <= 8) {
        setRegVal16(spiGetBaseAdr(module)+R_SPI_CR2_OFF, SPI_FRXTH_1_4, N_FRXTH, S_FRXTH);
    } else {
        setRegVal16(spiGetBaseAdr(module)+R_SPI_CR2_OFF, SPI_FRXTH_1_2, N_FRXTH, S_FRXTH);
    }

    spiSetModuleOnOff(module, SPI_MODULE_EN);

}


/*
    Get the frame length of a SPI module. The default value is 8

    @param  module      SPI module number to set frame length

    @retval frameLen    Current frame length of SPI module

*/
uint8_t spiGetFrameLength(SPI_MODULE module) {

    return getRegVal16(spiGetBaseAdr(module)+R_SPI_CR2_OFF, N_DS, S_DS) + 1;

}


/*
    Place a frame in the SPI TX Buffer

    @param  module      SPI module to send byte
    @param  value       Value to send

*/
void spiTxFrame(SPI_MODULE module) {

    if (spiBufInfo[module-1].txBuf == NULL) {
        if (spiGetFrameLength(module) <= 8) {
            setRegVal8(spiGetBaseAdr(module)+R_SPI_DR_OFF, 0xFF, 0, 8);
        } else {
            setRegVal16(spiGetBaseAdr(module)+R_SPI_DR_OFF, 0xFFFF, 0, 16);
        }
    }

    if (spiGetFrameLength(module) <= 8) {
        setRegVal8(
            spiGetBaseAdr(module)+R_SPI_DR_OFF, 
            ((uint8_t*)(spiBufInfo[module-1].txBuf))[spiBufInfo[module-1].pos], 
            0, 
            8
        );
    } else {
        setRegVal16(
            spiGetBaseAdr(module)+R_SPI_DR_OFF, 
            ((uint16_t*)(spiBufInfo[module-1].txBuf))[spiBufInfo[module-1].pos], 
            0, 
            16
        );
    }
}


/*
    Receive a frame from the SPI RX Buffer

    @param  module      SPI module to receive byte

    @retval Value received.

*/
void spiRxFrame(SPI_MODULE module) {


    if (spiBufInfo[module-1].rxBuf == NULL) {
        if (spiGetFrameLength(module) <= 8) {
            uint8_t garbage = getRegVal8(spiGetBaseAdr(module)+R_SPI_DR_OFF, 0, 8);
        } else {
            uint16_t garbage = getRegVal16(spiGetBaseAdr(module)+R_SPI_DR_OFF, 0, 16);
        }
    }

    if (spiGetFrameLength(module) <= 8) {
        ((uint8_t*)(spiBufInfo[module-1].rxBuf))[spiBufInfo[module-1].pos++] = getRegVal8(
            spiGetBaseAdr(module)+R_SPI_DR_OFF,
            0,
            8
        );
    } else {
        ((uint16_t*)(spiBufInfo[module-1].rxBuf))[spiBufInfo[module-1].pos++] = getRegVal16(
            spiGetBaseAdr(module)+R_SPI_DR_OFF,
            0,
            16
        );
    }
}


/*
    Disables or enables the SPI module. The register settings are preserved. The
    module should be disabled and then reenabled if changing any control
    register.

    If initializing the module after restart, spiInitModule should be used.

    @param  module  SPI Module to disable or enable

*/
void spiSetModuleOnOff(SPI_MODULE module, SPI_EN_MODE mode) {

    setRegVal16(spiGetBaseAdr(module)+R_SPI_CR1_OFF, mode, N_SPE, S_SPE);

}


/*
    Resets the SPI module. The register settings are not preserved and are
    set to their defaults, and the peripheral clock remains running. Resetting 
    the module also 

    @param  module  SPI Module to reset

*/
void spiResetModule(SPI_MODULE module) {

    // Reset Module and start peripheral clock
    switch (module) {
        case 1:
            rccReset(RCC_RST_SPI1); 
            DisableIRQ(P_INT_SPI1); break;
        case 2:
            rccReset(RCC_RST_SPI2); 
            DisableIRQ(P_INT_SPI2); break;
        case 3:
            rccReset(RCC_RST_SPI3); 
            DisableIRQ(P_INT_SPI3); break;
        default:
            break;
    }
}


/*
    Disables the SPI module by turning off the peripheral clocks.

    @param  module  SPI Module to disable

*/
void spiDisableModule(SPI_MODULE module) {

    // Reset Module and start peripheral clock
    switch (module) {
        case 1:
            rccReset(RCC_RST_SPI1); 
            rccSetClock(RCC_CLK_SPI1, RCC_CLOCK_DIS); break;
        case 2:
            rccReset(RCC_RST_SPI2);
            rccSetClock(RCC_CLK_SPI2, RCC_CLOCK_DIS); break;
        case 3:
            rccReset(RCC_RST_SPI3);
            rccSetClock(RCC_CLK_SPI3, RCC_CLOCK_DIS); break;
        default:
            break;
    }

}


/*
    Sets the baud rate prescaler of a SPI module.

    @param  module      Module to set baud rate
    @param  buadRate    Baud rate prescaler

*/
void spiSetBaudRate(SPI_MODULE module, SPI_BR_MODE baudRate) {

    spiSetModuleOnOff(module, SPI_MODULE_DIS);
    setRegVal16(spiGetBaseAdr(module)+R_SPI_CR1_OFF, baudRate, N_SPI_BR, S_SPI_BR);
    spiSetModuleOnOff(module, SPI_MODULE_EN);

}


/*
    Gets the baud rate prescaler of a SPI module.

    @param  module      Module to get baud rate
    
    @retval Baud rate prescaler

*/
SPI_BR_MODE getSetBaudRate(SPI_MODULE module) {

    return getRegVal16(spiGetBaseAdr(module)+R_SPI_CR1_OFF, N_SPI_BR, S_SPI_BR);

}


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
int spiSendDataDma(SPI_MODULE module, unsigned int bufLen, void *sendData, void *recData) {

    DMA_REQ dmaTx;
    DMA_REQ dmaRx;
    uint32_t spiBase = spiGetBaseAdr(module);

    switch (module) {
        case 1:
            dmaTx = DMA1_SPI1_TX;
            dmaRx = DMA1_SPI1_RX; break;
        case 2:
            dmaTx = DMA_SPI2_TX;
            dmaRx = DMA_SPI2_RX; break;
        case 3:
            dmaTx = DMA_SPI3_TX;
            dmaRx = DMA_SPI3_RX; break;
        default:
            break;
    }

    spiSetModuleOnOff(module, SPI_MODULE_DIS);

    setRegVal16(spiBase+R_SPI_CR2_OFF, SPI_RX_BUF_DMA_EN, N_RXDMAEN, S_RXDMAEN);

    // Setup the DMA for SPI
    dmaTsferSetup(dmaTx, DMA_MEM_TO_PERPH, (uint32_t)sendData, R_SPI1_BASE+R_SPI_DR_OFF);
    dmaTsferSetup(dmaRx, DMA_PERPH_TO_MEM, spiGetBaseAdr(module)+R_SPI_DR_OFF, (uint32_t)recData);
    dmaSetMemInc(dmaTx, DMA_MINC_EN, DMA_PINC_DIS);
    dmaSetMemInc(dmaRx, DMA_MINC_EN, DMA_PINC_DIS);

    if (spiGetFrameLength(module) <= 8) {
        dmaTsferStart(dmaTx, bufLen, DMA_MSIZE_8_BIT, DMA_PSIZE_8_BIT);
        dmaTsferStart(dmaRx, bufLen, DMA_MSIZE_8_BIT, DMA_PSIZE_8_BIT);
    } else {
        dmaTsferStart(dmaTx, bufLen, DMA_MSIZE_16_BIT, DMA_PSIZE_16_BIT);
        dmaTsferStart(dmaRx, bufLen, DMA_MSIZE_16_BIT, DMA_PSIZE_16_BIT);
    }
    
    setRegVal16(spiBase+R_SPI_CR2_OFF, SPI_TX_BUF_DMA_EN, N_TXDMAEN, S_TXDMAEN);
    
    spiSetModuleOnOff(module, SPI_MODULE_EN);
    
    return 0;
}


/*
    Checks if there is an SPI transfer in progress.

    This should be used to check if a transfer is ongoing before
    starting a new one.

    @param  module  Module to check
    
    @retval `0` No transfer is in progress
    @retval `1` Transfer is currently in progress

*/
int spiTsferInProgress(SPI_MODULE module) {

    // The spiBufInfo length is set to 1 during a poll or interrupt transfer.
    if (spiBufInfo->len != 0) return 1;

    // For DMA transfers, check if the BSY flag is set
    if (SPI_BUSY == getRegVal16(spiGetBaseAdr(module) + R_SPI_SR_OFF, N_BSY, S_BSY)) return 1;

    return 0;
}


/*
    IRQ Handler for SPI1
*/
void spi1_handler() {

    ClearPendingIRQ(P_INT_SPI1);

    // If Receive Flag is active
    if (getRegVal16(R_SPI1_BASE + R_SPI_SR_OFF, N_RXNE, S_RXNE) &&
        getRegVal16(R_SPI1_BASE + R_SPI_CR2_OFF, N_RXNEIE, S_RXNEIE))
    {
        spiRxFrame(1);

        // Check if transfer is done
        if (spiBufInfo[0].pos == spiBufInfo[0].len) {
            spiBufInfo[0].pos = 0;
            spiBufInfo[0].len = 0;
            spiBufInfo[0].rxBuf = NULL;
            spiBufInfo[0].txBuf = NULL;
            return;
        }

        spiTxFrame(1);

        return;
    }

}

