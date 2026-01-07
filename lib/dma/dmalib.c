#include "dmalib.h"

/*
    DMA Module TODO
    - MEM2MEM Mode
    - Perph to Perph mode
    - DMA Error Checking
        - Function calls should all check if startup
          has happened and there is no TIP.

*/

/*
    Gets the base address of a DMA module.

    @param  module  Module to get the base address of

    @retval Base address of selected module

*/
uint32_t dmaGetBaseAdr(DMA_MODULE module) {

    switch (module) {
        case 1:
            return R_DMA1_BASE;
        case 2:
            return R_DMA2_BASE;
        default:
            return 0;
    }

}


/*
    Gets the register value of a DMA requsition.

    @param  req     The DMA feature to get the address of
    @param  ch0off  The register offset for channel 0

    @retval The address of the DMA feature at the requested address.

*/
uint32_t dmaGetChanAdr(DMA_REQ req, uint8_t ch0off) {

    uint32_t baseAddress = dmaGetBaseAdr(_DMA_MOD(req));

    if (ch0off == R_DMA_ISR_OFF || ch0off == R_DMA_IFCR_OFF || ch0off == R_DMA_CSELR_OFF) {
        return baseAddress + ch0off;
    } 

    return baseAddress + 0x14 * (_DMA_CHAN(req) - 1) + ch0off;

}


/*
    Updates DMA channel select register with the required DMA
    feature.

    @param  req     DMA feature.

*/
void dmaSetChannel(DMA_REQ req) {

    switch (_DMA_MOD(req)) {
        case 1:
            setRegVal(
                R_DMA1_BASE+R_DMA_CSELR_OFF, 
                _DMA_MUX(req), 
                (_DMA_CHAN(req) - 1)* S_CS,
                S_CS
            ); break;
        case 2:
            setRegVal(
                R_DMA2_BASE+R_DMA_CSELR_OFF, 
                _DMA_MUX(req), 
                (_DMA_CHAN(req) - 1) * S_CS,
                S_CS
            ); break;
        default:
            return;
    }

}


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
DMA_STATUS dmaTsferSetup(DMA_REQ req, DMA_MODE mode, uint32_t fromAddr, uint32_t toAddr) {

    // Enable DMA clock
    switch (_DMA_MOD(req)) {
        case 1:
            rccSetClock(RCC_CLK_DMA1, RCC_CLOCK_EN); break;
        case 2:
            rccSetClock(RCC_CLK_DMA2, RCC_CLOCK_EN); break;
        default:
            break;
    }

    // Is there a transfer in progress on the channel
    if (getRegVal(dmaGetChanAdr(req, R_DMA_CNDTR_OFF), N_NDT, S_NDT) > 0) {
        return DMA_IN_PROGRESS;
    }

    // Is the error bit set on the channel
    if (getRegVal(dmaGetBaseAdr(_DMA_MOD(req))+R_DMA_ISR_OFF, N_TEIF1 + 4*(_DMA_CHAN(req)-1), S_TEIF) == DMA_TE_EVENT) {
        return DMA_ERROR;
    }

    dmaResetChannel(req);
    dmaSetChannel(req);

    // Set Peripheral and Memory Addresses
    if (mode == DMA_PERPH_TO_MEM) {
        setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), DMA_DIR_FROM_PER, N_DIR, S_DIR);
        setRegVal(dmaGetChanAdr(req, R_DMA_CPAR_OFF), fromAddr, N_PA, S_PA);
        setRegVal(dmaGetChanAdr(req, R_DMA_CMAR_OFF), toAddr, N_MA, S_MA);
    } else if (mode == DMA_MEM_TO_PERPH) {
        setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), DMA_DIR_FROM_MEM, N_DIR, S_DIR);
        setRegVal(dmaGetChanAdr(req, R_DMA_CPAR_OFF), toAddr, N_PA, S_PA);
        setRegVal(dmaGetChanAdr(req, R_DMA_CMAR_OFF), fromAddr, N_MA, S_MA);
    } else if (mode == DMA_MEM_TO_MEM) {
        setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), DMA_MEM2MEM_EN, N_MEM2MEM, S_MEM2MEM);
        setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), DMA_DIR_FROM_PER, N_DIR, S_DIR);
        setRegVal(dmaGetChanAdr(req, R_DMA_CPAR_OFF), fromAddr, N_PA, S_PA);
        setRegVal(dmaGetChanAdr(req, R_DMA_CMAR_OFF), toAddr, N_MA, S_MA);
    } else if (mode == DMA_PERPH_TO_PERPH) {
        setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), DMA_DIR_FROM_PER, N_DIR, S_DIR);
        setRegVal(dmaGetChanAdr(req, R_DMA_CPAR_OFF), toAddr, N_PA, S_PA);
        setRegVal(dmaGetChanAdr(req, R_DMA_CMAR_OFF), fromAddr, N_MA, S_MA);
    }
    setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), DMA_MINC_EN, N_MINC, S_MINC);
    return DMA_NO_ERROR;
}

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
void dmaTsferStart(DMA_REQ req, uint16_t tsferSize, DMA_MSIZE memSize, DMA_PSIZE perpSize) {


    setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), perpSize, N_PSIZE, S_PSIZE);
    setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), memSize, N_MSIZE, S_MSIZE);
    setRegVal(dmaGetChanAdr(req, R_DMA_CNDTR_OFF), tsferSize, N_NDT, S_NDT);
    setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), DMA_CHAN_EN, N_EN, S_EN);

}


/*
    Set a DMA channel memory and pheripheral to increment mode.

    **NOTE**
    If the MODE is MEM to MEM, then mInc is the FROM buffer pInc is the TO buffer
    If the MODE is PERP to PERP, then mInc is the TO buffer and pInc is the FROM buffer

    @param  req     DMA feature to change mode
    @param  mInc    Memory Increment mode
    @param  pInc    Peripheral Increment mode

*/
void dmaSetMemInc(DMA_REQ req, DMA_MINC_MODE mInc, DMA_PINC_MODE pInc) {

    setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), mInc, N_MINC, S_MINC);
    setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), pInc, N_PINC, S_PINC);
}


/*
    Set circular mode for a DMA channel.

    @param  req         DMA feature to change circular mode
    @param  circMode    Circular mode to set
    
*/
void dmaSetCircMode(DMA_REQ req, DMA_CIRC_MODE circMode) {

    setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), circMode, N_CIRC, S_CIRC);
}


/*
    Get the status of a DMA request type. This also clears the error
    flag if it's set.
    
    @param  req     DMA Request type

    @retval `DMA_NO_ERROR` Channel succussfully set up.
    @retval `DMA_IN_PROGRESS` There is a transfer in progress for the req DMA
    @retval `DMA_ERROR` There was an error for the requested peripheral  

*/
DMA_STATUS dmaGetStatus(DMA_REQ req) {

    // Check if the error bit is set in the ISR (and clear it)
    if (getRegVal(
        dmaGetBaseAdr(_DMA_MOD(req))+R_DMA_ISR_OFF, 
        N_TEIF1 + 4*(_DMA_CHAN(req)-1), 
        S_TEIF) == DMA_TE_EVENT
    ) {

        // Is the DMA on the channel the same as the req? If not
        // then ignore. If yes, check for error.
        if (getRegVal(
            dmaGetBaseAdr(_DMA_MOD(req))+R_DMA_CSELR_OFF,
            S_CS*(_DMA_CHAN(req)-1),
            S_CS) == _DMA_MUX(req)
        ) {
            setRegVal(
                dmaGetBaseAdr(_DMA_MOD(req))+R_DMA_IFCR_OFF,
                1,
                N_CTEIF1 + 4*(_DMA_CHAN(req)-1),
                S_CTEIF
            );
            return DMA_ERROR;
        }
    }

    // Check if there is a transfer in progress
    if (getRegVal(
        dmaGetBaseAdr(_DMA_MOD(req))+R_DMA_CSELR_OFF, 
        S_CS*(_DMA_CHAN(req)-1), 
        S_CS) == _DMA_MUX(req)
    ) {
        if (getRegVal(
            dmaGetChanAdr(req, R_DMA_CNDTR_OFF),
            N_NDT,
            S_NDT) > 0
        ) {
            return DMA_IN_PROGRESS;
        }
    }

    // If ERR bit is not set, and there is no tsfer in progress.
    return DMA_NO_ERROR;

}


/*
    Resets a DMA channel's information.

    @param  req     REQ to reset channel for

*/
void dmaResetChannel(DMA_REQ req) {

    // Reset Channel registers
    setRegVal(dmaGetChanAdr(req, R_DMA_CCR_OFF), 0, 0, 32);
    setRegVal(dmaGetChanAdr(req, R_DMA_CNDTR_OFF), 0, 0, 32);
    setRegVal(dmaGetChanAdr(req, R_DMA_CPAR_OFF), 0, 0, 32);
    setRegVal(dmaGetChanAdr(req, R_DMA_CMAR_OFF), 0, 0, 32);

    // Reset Channel No. and ISR
    setRegVal(
        dmaGetBaseAdr(_DMA_MOD(req)) + R_DMA_IFCR_OFF, 
        0xF,
        4*(_DMA_CHAN(req)-1),
        4
    );

    setRegVal(
        dmaGetBaseAdr(_DMA_MOD(req)) + R_DMA_CSELR_OFF,
        0,
        S_CS*(_DMA_CHAN(req)-1),
        S_CS   
    );

}

/*

    Transfer Complete
      - No Interrupt
      - Channel Remains Enabled
    
    TRANSFER STATUS CHECK FUNCTION
      - Returns In-Progress, No Error, or Error
      - Clears the Error bit if set
      - To check if there is an error
        1. If Error Register has bit set, unset it
        2. 

*/
