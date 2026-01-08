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
            if (!moduleSupported(SPI1)) return 1;
            if (pinFunctionCheck(mosi, SPI1_MOSI) == 0) return 1;
            if (pinFunctionCheck(miso, SPI1_MISO) == 0) return 1;
            if (pinFunctionCheck(sclk, SPI1_SCK) == 0) return 1; break;
        case 2:
            if (!moduleSupported(SPI2)) return 1;
            if (pinFunctionCheck(mosi, SPI2_MOSI) == 0) return 1;
            if (pinFunctionCheck(miso, SPI2_MISO) == 0) return 1;
            if (pinFunctionCheck(sclk, SPI2_SCK) == 0) return 1; break;
        case 3:
            if (!moduleSupported(SPI3)) return 1;
            if (pinFunctionCheck(mosi, SPI3_MOSI) == 0) return 1;
            if (pinFunctionCheck(miso, SPI3_MISO) == 0) return 1;
            if (pinFunctionCheck(sclk, SPI3_SCK) == 0) return 1; break;
        default:
            return 1;
    }

    // Set Pins as alternate functions
    gpioPinInit(mosi, GPIO_MODE_ALT_FN);
    gpioPinInit(miso, GPIO_MODE_ALT_FN);
    gpioPinInit(sclk, GPIO_MODE_ALT_FN);

    // Reset Module and start peripheral clock
    switch (module) {
        case 1:
            rccReset(RCC_RST_SPI1);
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

    if (1 == spiTsferInProgress(module)) return 1;

    spiEnableModule(module);

    spiBufInfo[module - 1].len = bufLen;
    spiBufInfo[module - 1].pos = 0;
    spiBufInfo[module - 1].rxBuf = recData;
    spiBufInfo[module - 1].txBuf = sendData;

    while (spiBufInfo[module - 1].pos < spiBufInfo[module - 1].len) {
        
        spiTxFrame(module);

        // Check if CRC should be sent
        if (spiBufInfo[module - 1].pos + 1 == spiBufInfo[module - 1].len) {

            if (spiGetCrcMode(module) == SPI_CRC_EN) {
                setRegVal(spiGetBaseAdr(module)+R_SPI_CR1_OFF, SPI_CRC_NEXT_CRC, N_CRCNEXT, S_CRCNEXT);
            }

        }
    
        while (!getRegVal(spiGetBaseAdr(module) + R_SPI_SR_OFF, N_RXNE, S_RXNE));
        
        spiRxFrame(module);

    }

    // If CRC mode is set, 1 or 2 more transfers are required to TX/RX the CRC
    if (spiGetCrcMode(module) == SPI_CRC_EN) {

        while (!getRegVal(spiGetBaseAdr(module) + R_SPI_SR_OFF, N_RXNE, S_RXNE));
        uint8_t garbage = getRegVal8(spiGetBaseAdr(module)+R_SPI_DR_OFF, 0, 8);

        // For CRC16 a second read is necessary
        if (spiGetCrcLength(module) == SPI_CRC_LEN_16) {
            while (!getRegVal(spiGetBaseAdr(module) + R_SPI_SR_OFF, N_RXNE, S_RXNE));
            uint8_t garbage = getRegVal8(spiGetBaseAdr(module)+R_SPI_DR_OFF, 0, 8);
        }

        setRegVal(spiGetBaseAdr(module)+R_SPI_CR1_OFF, SPI_CRC_NEXT_TX, N_CRCNEXT, S_CRCNEXT);

    }

    spiBufInfo[module - 1].len = 0;
    spiBufInfo[module - 1].pos = 0;
    spiBufInfo[module - 1].rxBuf = NULL;
    spiBufInfo[module - 1].txBuf = NULL;

    spiDisableModule(module);

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
    if (spiTsferInProgress(module)) return 1;

    spiEnableModule(module);

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

    spiDisableModule(module);

    setRegVal16(spiGetBaseAdr(module)+R_SPI_CR2_OFF, frameLen - 1, N_DS, S_DS);

    if (frameLen <= 8) {
        setRegVal16(spiGetBaseAdr(module)+R_SPI_CR2_OFF, SPI_FRXTH_1_4, N_FRXTH, S_FRXTH);
    } else {
        setRegVal16(spiGetBaseAdr(module)+R_SPI_CR2_OFF, SPI_FRXTH_1_2, N_FRXTH, S_FRXTH);
    }

    spiEnableModule(module);

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

    // If no buffer specified, send garbage
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

    // If no buffer provided, discard received data.
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
    Disables the SPI module by turning off the SPI enable flag.

    @param  module  SPI Module to disable

*/
void spiDisableModule(SPI_MODULE module) {

    while (getRegVal(spiGetBaseAdr(module)+R_SPI_SR_OFF, N_FTLVL, S_FTLVL) != SPI_FTLVL_EMPTY);
    while (getRegVal(spiGetBaseAdr(module)+R_SPI_SR_OFF, N_BSY, S_BSY) == SPI_BUSY);
    setRegVal(spiGetBaseAdr(module)+R_SPI_CR1_OFF, SPI_MODULE_DIS, N_SPE, S_SPE);
    while (getRegVal(spiGetBaseAdr(module)+R_SPI_SR_OFF, N_FRLVL, S_FRLVL) != SPI_FRLVL_EMPTY) {
        uint16_t garbage = getRegVal16(spiGetBaseAdr(module)+R_SPI_DR_OFF, 0, 16);
    }

}


/*
    Enables an SPI module by turning on the SPI enable flag.

    @param  module  SPI module to enable

*/
void spiEnableModule(SPI_MODULE module) {

    setRegVal(spiGetBaseAdr(module)+R_SPI_CR1_OFF, SPI_MODULE_EN, N_SPE, S_SPE);

}


/*
    Sets the baud rate prescaler of a SPI module.

    @param  module      Module to set baud rate
    @param  buadRate    Baud rate prescaler

*/
void spiSetBaudRate(SPI_MODULE module, SPI_BR_MODE baudRate) {

    spiDisableModule(module);
    setRegVal16(spiGetBaseAdr(module)+R_SPI_CR1_OFF, baudRate, N_SPI_BR, S_SPI_BR);
    spiEnableModule(module);

}


/*
    Gets the baud rate prescaler of a SPI module.

    @param  module      Module to get baud rate
    
    @retval Baud rate prescaler

*/
SPI_BR_MODE getBaudRate(SPI_MODULE module) {

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

    if (spiTsferInProgress(module) == 1) return 1;

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

    spiDisableModule(module);

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
    
    spiEnableModule(module);
    
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

    // The spiBufInfo length is >0 during a poll or interrupt transfer.
    if (spiBufInfo[module-1].len != 0) return 1;

    // For DMA transfers, check if the BSY flag is set
    if (SPI_BUSY == getRegVal16(spiGetBaseAdr(module) + R_SPI_SR_OFF, N_BSY, S_BSY)) return 1;

    return 0;
}


/*
    Set CRC mode for an SPI transfer. CRC mode is only available if the frame
    length is 8-bits or 16-bits

    @param  module      SPI Module to set
    @param  crcMode     On/off mode for CRC
    @param  crcLen      8 or 16 bit CRC length
    @param  crcPoly     CRC polynomial 

    @retval `EXIT_SUCCESS` CRC mode was set
    @retval `EXIT_BAD_PARAMETER` Polynomial was even. CRC was not changed.
    @retval `EXIT_TSFER_IN_PROGRESS` Transfer was in progress, CRC was not changed.
    @retval `EXIT_USUPPORTED` The frame length is not 8 or 16 bit.

*/
EXIT_STATUS spiSetCrc(SPI_MODULE module, SPI_CRC_MODE crcMode, SPI_CRC_LEN_MODE crcLen, uint16_t crcPoly) {

    if (spiGetFrameLength(module) != 8 && spiGetFrameLength(module) != 16) {
        return EXIT_UNSUPPORTED;
    }

    if (spiTsferInProgress(module) == 1) {
        return EXIT_TSFER_IN_PROGRESS;
    }

    // Check that the polynomial has odd parity
    int pol = 0;
    for (uint16_t i = crcPoly; i; i >>= 1) pol += (i & 1);
    if ((pol & 1) == 0) return EXIT_BAD_PARAMATER;

    setRegVal(spiGetBaseAdr(module)+R_SPI_CR1_OFF, crcMode, N_SPI_CRCEN, S_SPI_CRCEN);
    setRegVal(spiGetBaseAdr(module)+R_SPI_CR1_OFF, crcLen, N_CRCL, S_CRCL);
    setRegVal16(spiGetBaseAdr(module)+R_SPI_CRCPR_OFF, crcPoly, 0, 16);
    return EXIT_SUCCESS;
}


/*
    Gets the CRC enable mode for an SPI module

    @param  module      Module to get CRC enable

*/
SPI_CRC_MODE spiGetCrcMode(SPI_MODULE module) {

    return getRegVal(spiGetBaseAdr(module)+R_SPI_CR1_OFF, N_SPI_CRCEN, S_SPI_CRCEN);
}


/*
    Gets the CRC 8/16 bit mode for an SPI module

    @param  module      Module to get CRC length

*/
SPI_CRC_LEN_MODE spiGetCrcLength(SPI_MODULE module) {

    return getRegVal(spiGetBaseAdr(module)+R_SPI_CR1_OFF, N_CRCL, S_CRCL);
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


/*
    IRQ Handler for SPI2
*/
void spi2_handler() {

    ClearPendingIRQ(P_INT_SPI2);

    // If Receive Flag is active
    if (getRegVal16(R_SPI2_BASE + R_SPI_SR_OFF, N_RXNE, S_RXNE) &&
        getRegVal16(R_SPI2_BASE + R_SPI_CR2_OFF, N_RXNEIE, S_RXNEIE))
    {
        spiRxFrame(2);

        // Check if transfer is done
        if (spiBufInfo[1].pos == spiBufInfo[1].len) {
            spiBufInfo[1].pos = 0;
            spiBufInfo[1].len = 0;
            spiBufInfo[1].rxBuf = NULL;
            spiBufInfo[1].txBuf = NULL;
            return;
        }

        spiTxFrame(2);

        return;
    }

}


/*
    IRQ Handler for SPI3
*/
void spi3_handler() {

    ClearPendingIRQ(P_INT_SPI3);

    // If Receive Flag is active
    if (getRegVal16(R_SPI3_BASE + R_SPI_SR_OFF, N_RXNE, S_RXNE) &&
        getRegVal16(R_SPI3_BASE + R_SPI_CR2_OFF, N_RXNEIE, S_RXNEIE))
    {
        spiRxFrame(3);

        // Check if transfer is done
        if (spiBufInfo[2].pos == spiBufInfo[2].len) {
            spiBufInfo[2].pos = 0;
            spiBufInfo[2].len = 0;
            spiBufInfo[2].rxBuf = NULL;
            spiBufInfo[2].txBuf = NULL;
            return;
        }

        spiTxFrame(3);

        return;
    }

}


