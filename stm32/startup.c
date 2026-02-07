#include <stdint.h>
#include "interruptTable.h"

// The Interrupt Vector Table info is stored at page 326 of the refrence manual
int main();

//
// Interupt Handler Table
//
void reset_handler();
void default_handler();
void nmi_handler() __attribute__((weak, alias("default_handler")));
void hard_fault_handler() __attribute__((weak, alias("default_handler")));
void mem_manage_handler() __attribute__((weak, alias("default_handler")));
void bus_fault_handler() __attribute__((weak, alias("default_handler")));
void usage_fault_handler() __attribute__((weak, alias("default_handler")));
void sv_call_handler() __attribute__((weak, alias("default_handler")));
void debug_handler() __attribute__((weak, alias("default_handler")));
void pend_sv_handler() __attribute__((weak, alias("default_handler")));
void sys_tick_handler() __attribute__((weak, alias("default_handler")));
void wwdg_handler() __attribute__((weak, alias("default_handler")));
void pvd_pvm_handler() __attribute__((weak, alias("default_handler")));
void rtc_tamp_stamp_css_lse_handler() __attribute__((weak, alias("default_handler")));
void rtc_wkup_handler() __attribute__((weak, alias("default_handler")));
void flash_handler() __attribute__((weak, alias("default_handler")));
void rcc_handler() __attribute__((weak, alias("default_handler")));
void exti0_handler() __attribute__((weak, alias("default_handler")));
void exti1_handler() __attribute__((weak, alias("default_handler")));
void exti2_handler() __attribute__((weak, alias("default_handler")));
void exti3_handler() __attribute__((weak, alias("default_handler")));
void exti4_handler() __attribute__((weak, alias("default_handler")));
void dma1_ch1_handler() __attribute__((weak, alias("default_handler")));
void dma1_ch2_handler() __attribute__((weak, alias("default_handler")));
void dma1_ch3_handler() __attribute__((weak, alias("default_handler")));
void dma1_ch4_handler() __attribute__((weak, alias("default_handler")));
void dma1_ch5_handler() __attribute__((weak, alias("default_handler")));
void dma1_ch6_handler() __attribute__((weak, alias("default_handler")));
void dma1_ch7_handler() __attribute__((weak, alias("default_handler")));
void adc1_2_handler() __attribute__((weak, alias("default_handler")));
void can1_tx_handler() __attribute__((weak, alias("default_handler")));
void can1_rx0_handler() __attribute__((weak, alias("default_handler")));
void can1_rx1_handler() __attribute__((weak, alias("default_handler")));
void can1_sce_handler() __attribute__((weak, alias("default_handler")));
void exti9_5_handler() __attribute__((weak, alias("default_handler")));
void tim1_brk_tim15_handler() __attribute__((weak, alias("default_handler")));
void tim1_up_tim16_handler() __attribute__((weak, alias("default_handler")));
void tim1_trg_com_handler() __attribute__((weak, alias("default_handler")));
void tim1_cc_handler() __attribute__((weak, alias("default_handler")));
void tim2_handler() __attribute__((weak, alias("default_handler")));
void tim3_handler() __attribute__((weak, alias("default_handler")));
void i2c1_ev_handler() __attribute__((weak, alias("default_handler")));
void i2c1_er_handler() __attribute__((weak, alias("default_handler")));
void i2c2_ev_handler() __attribute__((weak, alias("default_handler")));
void i2c2_er_handler() __attribute__((weak, alias("default_handler")));
void spi_handler() __attribute__((weak, alias("default_handler")));
void usart1_handler() __attribute__((weak, alias("default_handler")));
void usart2_handler() __attribute__((weak, alias("default_handler")));
void usart3_handler() __attribute__((weak, alias("default_handler")));
void exti15_10_handler() __attribute__((weak, alias("default_handler")));
void rtc_alarm_handler() __attribute__((weak, alias("default_handler")));
void sdmmc1_handler() __attribute__((weak, alias("default_handler")));
void uart4_handler() __attribute__((weak, alias("default_handler")));
void tim6_dacunder_handler() __attribute__((weak, alias("default_handler")));
void tim7_handler() __attribute__((weak, alias("default_handler")));
void dma2_ch1_handler() __attribute__((weak, alias("default_handler")));
void dma2_ch2_handler() __attribute__((weak, alias("default_handler")));
void dma2_ch3_handler() __attribute__((weak, alias("default_handler")));
void dma2_ch4_handler() __attribute__((weak, alias("default_handler")));
void dma2_ch5_handler() __attribute__((weak, alias("default_handler")));
void dfsdm1_flt0_handler() __attribute__((weak, alias("default_handler")));
void dfsdm1_flt1_handler() __attribute__((weak, alias("default_handler")));
void comp_handler() __attribute__((weak, alias("default_handler")));
void lptim1_handler() __attribute__((weak, alias("default_handler")));
void lptim2_handler() __attribute__((weak, alias("default_handler")));
void usb_fs_handler() __attribute__((weak, alias("default_handler")));
void dma2_ch6_handler() __attribute__((weak, alias("default_handler")));
void dma2_ch7_handler() __attribute__((weak, alias("default_handler")));
void lpuart1_handler() __attribute__((weak, alias("default_handler")));
void quadspi_handler() __attribute__((weak, alias("default_handler")));
void i2c3_ev_handler() __attribute__((weak, alias("default_handler")));
void i2c3_er_handler() __attribute__((weak, alias("default_handler")));
void sai1_handler() __attribute__((weak, alias("default_handler")));
void swpmi1_handler() __attribute__((weak, alias("default_handler")));
void tsc_handler() __attribute__((weak, alias("default_handler")));
void lcd_handler() __attribute__((weak, alias("default_handler")));
void aes_handler() __attribute__((weak, alias("default_handler")));
void rng_handler() __attribute__((weak, alias("default_handler")));
void fpu_handler() __attribute__((weak, alias("default_handler")));
void crs_handler() __attribute__((weak, alias("default_handler")));
void i2c4_ev_handler() __attribute__((weak, alias("default_handler")));
void i2c4_er_handler() __attribute__((weak, alias("default_handler")));

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

uint32_t isr_vector[ISR_VECTOR_SIZE] __attribute__((section(".isr_vector"))) = {

    STACK_POINTER_INIT_ADDRESS,
    (uint32_t)&reset_handler,
    (uint32_t)&nmi_handler,
    (uint32_t)&hard_fault_handler,
    (uint32_t)&mem_manage_handler,
    (uint32_t)&bus_fault_handler,
    (uint32_t)&usage_fault_handler,
    0,
    0,
    0,
    0,
    (uint32_t)&sv_call_handler,
    (uint32_t)&debug_handler,
    0,
    (uint32_t)&pend_sv_handler,
    (uint32_t)&sys_tick_handler,
    (uint32_t)&wwdg_handler,
    (uint32_t)&pvd_pvm_handler,
    (uint32_t)&rtc_tamp_stamp_css_lse_handler,
    (uint32_t)&rtc_wkup_handler,
    (uint32_t)&flash_handler,
    (uint32_t)&rcc_handler,
    (uint32_t)&exti0_handler,
    (uint32_t)&exti1_handler,
    (uint32_t)&exti2_handler,
    (uint32_t)&exti3_handler,
    (uint32_t)&exti4_handler,
    (uint32_t)&dma1_ch1_handler,
    (uint32_t)&dma1_ch2_handler,
    (uint32_t)&dma1_ch3_handler,
    (uint32_t)&dma1_ch4_handler,
    (uint32_t)&dma1_ch5_handler,
    (uint32_t)&dma1_ch6_handler,
    (uint32_t)&dma1_ch7_handler,
    (uint32_t)&adc1_2_handler,
    (uint32_t)&can1_tx_handler,
    (uint32_t)&can1_rx0_handler,
    (uint32_t)&can1_rx1_handler,
    (uint32_t)&can1_sce_handler,
    (uint32_t)&exti9_5_handler,
    (uint32_t)&tim1_brk_tim15_handler,
    (uint32_t)&tim1_up_tim16_handler,
    (uint32_t)&tim1_trg_com_handler,
    (uint32_t)&tim1_cc_handler,
    (uint32_t)&tim2_handler,
    (uint32_t)&tim3_handler,
    0,
    (uint32_t)&i2c1_ev_handler,
    (uint32_t)&i2c1_er_handler,
    (uint32_t)&i2c2_ev_handler,
    (uint32_t)&i2c2_er_handler,
    (uint32_t)&spi_handler,
    (uint32_t)&spi_handler,
    (uint32_t)&usart1_handler,
    (uint32_t)&usart2_handler,
    (uint32_t)&usart3_handler,
    (uint32_t)&exti15_10_handler,
    (uint32_t)&rtc_alarm_handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&sdmmc1_handler,
    0,
    (uint32_t)&spi_handler,
    (uint32_t)&uart4_handler,
    0,
    (uint32_t)&tim6_dacunder_handler,
    (uint32_t)&tim7_handler,
    (uint32_t)&dma2_ch1_handler,
    (uint32_t)&dma2_ch2_handler,
    (uint32_t)&dma2_ch3_handler,
    (uint32_t)&dma2_ch4_handler,
    (uint32_t)&dma2_ch5_handler,
    (uint32_t)&dfsdm1_flt0_handler,
    (uint32_t)&dfsdm1_flt1_handler,
    0,
    (uint32_t)&comp_handler,
    (uint32_t)&lptim1_handler,
    (uint32_t)&lptim2_handler,
    (uint32_t)&usb_fs_handler,
    (uint32_t)&dma2_ch6_handler,
    (uint32_t)&dma2_ch7_handler,
    (uint32_t)&lpuart1_handler,
    (uint32_t)&quadspi_handler,
    (uint32_t)&i2c3_ev_handler,
    (uint32_t)&i2c3_er_handler,
    (uint32_t)&sai1_handler,
    0,
    (uint32_t)&swpmi1_handler,
    (uint32_t)&tsc_handler,
    (uint32_t)&lcd_handler,
    (uint32_t)&aes_handler,
    (uint32_t)&rng_handler,
    (uint32_t)&fpu_handler,
    (uint32_t)&crs_handler,
    (uint32_t)&i2c4_ev_handler,
    (uint32_t)&i2c4_er_handler
};



void default_handler() {
    while(1);
}


void reset_handler(void)
{
  // Copy .data from FLASH to SRAM
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *flash_data = (uint8_t*) &_etext;
  uint8_t *sram_data = (uint8_t*) &_sdata;
  
  for (uint32_t i = 0; i < data_size; i++)
  {
    sram_data[i] = flash_data[i];
  }

  // Zero-fill .bss section in SRAM
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t*) &_sbss;

  for (uint32_t i = 0; i < bss_size; i++)
  {
    bss[i] = 0;
  }

  int retStatus = main();
}
