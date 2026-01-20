#include "rcclib.h"

/*
    Enables or disables a peripheral clock.

    @param  clk         Peripheral clock
    @param  clkState    On/off state

*/
void rccSetClock(RCC_CLK clk, RCC_CLK_STATE clkState) {

    setRegVal(
        R_RCC_BASE+_RCC_REG_OFF(clk), 
        clkState, 
        _RCC_BIT_POS(clk),
        S_RCC_CLK_ST
    );
    
}


/*
    Resets a peripheral, reseting all register values to defaults.

    @param  rst         Peripheral to Reset

*/
void rccReset(RCC_RST rst) {

    setRegVal(
        R_RCC_BASE+_RCC_REG_OFF(rst), 
        RCC_RESET, 
        _RCC_BIT_POS(rst),
        S_RCC_RST_ST
    );

    setRegVal(
        R_RCC_BASE+_RCC_REG_OFF(rst), 
        RCC_CLEAR_RST, 
        _RCC_BIT_POS(rst),
        S_RCC_RST_ST
    );

}

uint32_t rccGetClockFreq(RCC_CLOCK_TYPE clk) {

    if (clk == RCC_SYSCLK_CLK) {
        RCC_SW_MODE swMode = getRegVal(
            R_RCC_BASE + R_RCC_CFGR_OFF,
            N_SWS,
            S_SWS
        );
        switch (swMode) {
            case RCC_SW_MSI:
                clk = RCC_MSI_CLK; break;
            case RCC_SW_HSI16:
                clk = RCC_HSI16_CLK; break;
            case RCC_SW_HSE:
                clk = RCC_HSE_CLK; break;
            case RCC_SW_PLL:
                clk = RCC_PLL_CLK; break;
        }
    }

    if (clk == RCC_HSE_CLK) {
        return 0; // TODO
    } else if (clk == RCC_HSI16_CLK) {
        return 16000000;
    } else if (clk == RCC_MSI_CLK) {

        RCC_MSIRANGE_MODE freq = getRegVal(
            R_RCC_BASE + R_RCC_CR_OFF,
            N_MSIRANGE,
            S_MSIRANGE
        );

        switch (freq) {
            case RCC_MSIRNG_100K: return 100000;
            case RCC_MSIRNG_200K: return 200000;
            case RCC_MSIRNG_400K: return 400000;
            case RCC_MSIRNG_800K: return 800000;
            case RCC_MSIRNG_1M: return 1000000;
            case RCC_MSIRNG_2M: return 2000000;
            case RCC_MSIRNG_4M: return 4000000;
            case RCC_MSIRNG_8M: return 8000000;
            case RCC_MSIRNG_16M: return 16000000;
            case RCC_MSIRNG_24M: return 24000000;
            case RCC_MSIRNG_32M: return 32000000;
            case RCC_MSIRNG_48M: return 48000000; 
            default: return 100000;
        }

    } else if (clk == RCC_HSI48_CLK) {
        return 48000000;
    } else if (clk == RCC_PLL_CLK) {
        return 0; // TODO
    } else if (clk == RCC_LSE_CLK) {
        return 32768; // TODO for external bypass
    } else if (clk == RCC_LSI_CLK) {
        return 32000;
    }

    // ADC, RTC Clock TODO
    return 0;
}


/*
    Get the clock speed of a peripheral in Hz

    @param  Peripheral clock to measure  

    @retval The clock speed of the peripheral in Hz

*/
uint32_t rccGetPerphClkFreq(RCC_PCLK pclk) {

    if (pclk & RCC_CLK_48MHZ) {
        return 48000000;
    }

    uint32_t clkSpeed = rccGetClockFreq(RCC_SYSCLK_CLK);

    if (pclk & RCC_CLK_SYSCLK) {
        return clkSpeed;
    }

    // Check if AHB prescaled
    if (pclk & RCC_CLK_AHB_PRESC) {

        RCC_HPRE_MODE pre = getRegVal(R_RCC_BASE + R_RCC_CFGR_OFF, N_HPRE, S_HPRE);
        switch (pre) {
            case RCC_SYSCLK_FULL: break;
            case RCC_SYSCLK_1_2: clkSpeed /= 2; break;
            case RCC_SYSCLK_1_4: clkSpeed /= 4; break;
            case RCC_SYSCLK_1_8: clkSpeed /= 8; break;
            case RCC_SYSCLK_1_16: clkSpeed /= 16; break;
            case RCC_SYSCLK_1_64: clkSpeed /= 64; break;
            case RCC_SYSCLK_1_128: clkSpeed /= 128; break;
            case RCC_SYSCLK_1_256: clkSpeed /= 256; break;
            case RCC_SYSCLK_1_512: clkSpeed /= 512; break;
            default: break;
        }
    }

    if (pclk & RCC_CLK_APB1_PRESC) {
        RCC_PPRE_MODE pre = getRegVal(R_RCC_BASE + R_RCC_CFGR_OFF, N_PPRE1, S_PPRE1);
        switch (pre) {
            case RCC_PPRE_FULL: break;
            case RCC_PPRE_1_2: clkSpeed /= 2; break;
            case RCC_PPRE_1_4: clkSpeed /= 4; break;
            case RCC_PPRE_1_8: clkSpeed /= 8; break;
            case RCC_PPRE_1_16: clkSpeed /= 16; break;
            default: break;
        }
    } 
    
    if (pclk & RCC_CLK_APB2_PRESC) {
        RCC_PPRE_MODE pre = getRegVal(R_RCC_BASE + R_RCC_CFGR_OFF, N_PPRE2, S_PPRE2);
        switch (pre) {
            case RCC_PPRE_FULL: break;
            case RCC_PPRE_1_2: clkSpeed /= 2; break;
            case RCC_PPRE_1_4: clkSpeed /= 4; break;
            case RCC_PPRE_1_8: clkSpeed /= 8; break;
            case RCC_PPRE_1_16: clkSpeed /= 16; break;
            default: break;
        }
    }

    if (!(pclk & RCC_CLK_MUX_USED)) {
        return clkSpeed;
    }

    // Get the pclk that the perphrial is set to
    uint32_t regOff = (pclk & RCC_CLK_CCIPR2) ? R_RCC_CCIPR2_OFF : R_RCC_CCIPR_OFF;
    uint32_t mux = getRegVal(
        R_RCC_BASE + regOff,
        _RCC_BIT_POS(pclk),
        2
    );

    uint32_t clk;

    switch (mux) {
        case 0:
            clk = _PCLK_MUX0(pclk);
        case 1:
            clk = _PCLK_MUX1(pclk);
        case 2:
            clk = _PCLK_MUX2(pclk);
        case 3:
            clk = _PCLK_MUX3(pclk);
    }

    if (clk == RCC_PCLK_CLK) return clkSpeed;
    return rccGetClockFreq(clk);
}