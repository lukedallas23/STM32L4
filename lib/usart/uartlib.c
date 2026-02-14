#include "usartlib.h"


void uartInitModule(uartInfo *info) {

    // Set pheripheral clock
    rccReset(RCC_RST_USART1);
    rccSetClock(RCC_CLK_USART1, RCC_CLOCK_EN);

    uint32_t baseAddr = usartGetBaseAddr(info->module);
    uint32_t clkFreq = rccGetPerphClkFreq(RCC_PCLK_USART1);
    clkFreq = 4000000;
    uint16_t UARTDIV = clkFreq / info->baudRate;

    // Init GPIO Pin
    gpioPinInit(info->tx, GPIO_MODE_ALT_FN);
    gpioPinInit(info->rx, GPIO_MODE_ALT_FN);
    gpioSetAltFn(info->tx, AF_USART1);
    gpioSetAltFn(info->rx, AF_USART1);

    // Set M1 and M0 to 0 for 8-bit transmission
    setRegVal(baseAddr + R_USART_CR1_OFF, USART_M0_7_8_BIT, N_M0, S_M0);
    setRegVal(baseAddr + R_USART_CR1_OFF, USART_M1_8_9_BIT, N_M1, S_M1);

    // Set Baud Rate - which is f_CK/USARTDIV
    setRegVal(baseAddr + R_USART_BRR_OFF, UARTDIV, N_USART_BRR, S_USART_BRR);
    info->baudRate = clkFreq / UARTDIV;

    // Enable module
    setRegVal(baseAddr + R_USART_CR1_OFF, USART_UE_ENABLED, N_UE, S_UE);
	return;
}

void uartTx(uartInfo *info, uint8_t *buf, uint32_t len) {

    uint32_t baseAddr = usartGetBaseAddr(info->module);

    setRegVal(baseAddr + R_USART_CR1_OFF, USART_TE_ENABLE, N_TE, S_TE);

    for (int byte = 0; byte < len; byte++) {
        setRegVal8(baseAddr + R_USART_TDR_OFF, buf[byte], N_TDR, S_TDR);
        while (getRegVal(baseAddr + R_USART_ISR_OFF, N_USART_TXE, S_USART_ISR) == USART_FLAG_CLEAR);
    }

    while (getRegVal(baseAddr + R_USART_ISR_OFF, N_TC, S_USART_ISR) == USART_FLAG_CLEAR);
    
    setRegVal(baseAddr + R_USART_CR1_OFF, USART_TE_DISABLED, N_TE, S_TE);
}


/*


1. There are 7, 8, and 9 bit modes. We will only be using the standard 8-bit mode
 - M[1:0] = 0b00

2. There are 0.5, 1, 1.5, and 2 bit stop bit options. We will only be using the standard 1 bit mode.
-

3. Transmitting charetchers
  a. Program M[1:0] to 0b00 in USART_CR1 (8-bit)
  b. Select the Baud Rate in USART_BRR (9600 baud?)
  c. Program the number of stop bits in USART_CR2 (1 stop bit)
  d. Enable the USART (UE=1) in USART_CR1
  e. No Multibuffer Communication, ignore for now???
  f. Set the TE bit in USART_CR1 to send an Idle Frame (All HIGH)
  g. Write the data to send in USART_TDR (thus clearing TXE bit). Continue writing to this register until
     the buffer is finished writing.
  h. After writing done, wait until TC=1.

Sending Procedure

void sendData(char *buf, int bufLen) {

  // Data transfers should start with an Idle Preamble
  sendIdleFrame();

  for (int i = 0; i < bufLen; i++) {
     
     USART_TDR = buf[i];     // With TXE being 1 again, the USART_TDR reg is empty, a new byte can be written now
     while (TXE_flag == 0);  // Wait until the TXE flag goes high, indicating that the data has been transferd
          // To the shift register and the next frame can be written to USART_TDR
  }
 
  // After the last transmission, the TC flag will go high, indicating that transmission is complete and there
  // is no new value in the USART_TDR to send.
  while (TC_flag == 0);
 
}



Bit 7 TXE: Transmit data register empty
This bit is set by hardware when the content of the USART_TDR register has been
transferred into the shift register. It is cleared by a write to the USART_TDR register.
The TXE flag can also be cleared by writing 1 to the TXFRQ in the USART_RQR register, in
order to discard the data (only in smartcard T=0 mode, in case of transmission failure).
An interrupt is generated if the TXEIE bit =1 in the USART_CR1 register.
0: data is not transferred to the shift register
1: data is transferred to the shift register)
Note: This bit is used during single buffer transmission.





*/