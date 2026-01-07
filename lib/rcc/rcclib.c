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