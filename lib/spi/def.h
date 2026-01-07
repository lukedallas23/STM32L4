#ifndef SPI_HEADER_H
#define SPI_HEADER_H

//
// SPI Module Base Addresses
//
#define     R_SPI1_BASE         0x40013000
#define     R_SPI2_BASE         0x40003800
#define     R_SPI3_BASE         0x40003C00


//
// SPI Register Offsets
//
#define     R_SPI_CR1_OFF       0x00
#define     R_SPI_CR2_OFF       0x04
#define     R_SPI_SR_OFF        0x08
#define     R_SPI_DR_OFF        0x0C
#define     R_SPI_CRCPR_OFF     0x10
#define     R_SPI_RXCRCR_OFF    0x14
#define     R_SPI_TXCRCR_OFF    0x18


//
// SPI Control Register 1 (SPIx_CR1) definitions
//
#define     N_BIDIMODE          15
#define     N_BIDIOE            14
#define     N_SPI_CRCEN         13
#define     N_CRCNEXT           12
#define     N_CRCL              11
#define     N_RXONLY            10
#define     N_SSM               9
#define     N_SSI               8
#define     N_LSBFIRST          7
#define     N_SPE               6
#define     N_SPI_BR            3
#define     N_MSTR              2
#define     N_CPOL              1
#define     N_CHPA              0

#define     S_BIDIMODE          1
#define     S_BIDIOE            1
#define     S_SPI_CRCEN         1
#define     S_CRCNEXT           1
#define     S_CRCL              1
#define     S_RXONLY            1
#define     S_SSM               1
#define     S_SSI               1
#define     S_LSBFIRST          1
#define     S_SPE               1
#define     S_SPI_BR            3
#define     S_MSTR              1
#define     S_CPOL              1
#define     S_CHPA              1

typedef enum {
    TWO_LINE_UNIDIR      = 0,
    ONE_LINE_BIDIR       = 1
} SPI_BIDIMODE_MODE;

typedef enum {
    BIDIOE_MODE_DIS     = 0,
    BIDIOE_MODE_EN      = 1
} SPI_BIDIOE_MODE;

typedef enum {
    SPI_CRC_DIS         = 0,
    SPI_CRC_EN          = 1
} SPI_CRC_MODE;

typedef enum {
    SPI_CRC_NEXT_TX     = 0,
    SPI_CRC_NEXT_CRC    = 1
} SPI_CRCNEXT_MODE;

typedef enum {
    SPI_CRC_LEN_8       = 0,
    SPI_CRC_LEN_16      = 1
} SPI_CRC_LEN_MODE;

typedef enum {
    SPI_TX_AND_RX       = 0,
    SPI_RX_ONLY         = 1
} SPI_RXONLY_MODE;

typedef enum {
    SPI_SSM_DIS         = 0,
    SPI_SSM_EN          = 1
} SPI_SSM_MODE;

typedef enum {
    SPI_LSBFIRST        = 0,
    SPI_MSBFIRST        = 1
} SPI_LSBFIRST_MODE;

typedef enum {
    SPI_MODULE_DIS      = 0,
    SPI_MODULE_EN       = 1
} SPI_EN_MODE;

typedef enum {
    SPI_FPCLK_1_2       = 0,
    SPI_FPCLK_1_4       = 1,
    SPI_FPCLK_1_8       = 2,
    SPI_FPCLK_1_16      = 3,
    SPI_FPCLK_1_32      = 4,
    SPI_FPCLK_1_64      = 5,
    SPI_FPCLK_1_128     = 6,
    SPI_FPCLK_1_256     = 7
} SPI_BR_MODE;

typedef enum {
    SPI_SLAVE_MODE      = 0,
    SPI_MASTER_MODE     = 1
} SPI_MSTR_MODE;

typedef enum {
    SPI_CK_0_IDLE       = 0,
    SPI_CK_1_IDLE       = 1
} SPI_CPOL_MODE;

typedef enum {
    SPI_FIRST_TRAN      = 0,
    SPI_SECOND_TRAN     = 1
} SPI_CPHA_MODE;


//
// SPI Control Register 2 (SPI_CR2) definitions
//
#define     N_LDMA_TX       14
#define     N_LDMA_RX       13
#define     N_FRXTH         12
#define     N_DS            8
#define     N_TXEIE         7
#define     N_RXNEIE        6
#define     N_ERRIE         5
#define     N_FRF           4
#define     N_NSSP          3
#define     N_SSOE          2
#define     N_TXDMAEN       1
#define     N_RXDMAEN       0

#define     S_LDMA_TX       1
#define     S_LDMA_RX       1
#define     S_FRXTH         1
#define     S_DS            4
#define     S_TXEIE         1
#define     S_RXNEIE        1
#define     S_ERROE         1
#define     S_FRF           1
#define     S_NSSP          1
#define     S_SSOE          1
#define     S_TXDMAEN       1
#define     S_RXDMAEN       1

typedef enum {
    SPI_LDMA_TX_EVEN        = 0,
    SPI_LDMA_TX_ODD         = 1
} SPI_LDMA_TX_MODE;

typedef enum {
    SPI_LDMA_RX_EVEN        = 0,
    SPI_LDMA_RX_ODD         = 1
} SPI_LDMA_RX_MODE;

typedef enum {
    SPI_FRXTH_1_2           = 0,
    SPI_FRXTH_1_4           = 1
} SPI_FRXTH_MODE;

typedef enum {
    SPI_DS_4_BIT            = 3,
    SPI_DS_5_BIT            = 4,
    SPI_DS_6_BIT            = 5,
    SPI_DS_7_BIT            = 6,
    SPI_DS_8_BIT            = 7,
    SPI_DS_9_BIT            = 8,
    SPI_DS_10_BIT           = 9,
    SPI_DS_11_BIT           = 10,
    SPI_DS_12_BIT           = 11,
    SPI_DS_13_BIT           = 12,
    SPI_DS_14_BIT           = 13,
    SPI_DS_15_BIT           = 14,
    SPI_DS_16_BIT           = 15,
} SPI_DATA_LENGTH;

typedef enum {
    SPI_TXE_INT_MASKED      = 0,
    SPI_TXE_INT_EN          = 1
} SPI_TXEIE_MODE;

typedef enum {
    SPI_RXNE_INT_MASKED     = 0,
    SPI_RXNE_INT_EN         = 1
} SPI_RXNEIE_MODE;

typedef enum {
    SPI_ERRIE_INT_MASKED    = 0,
    SPI_ERRIE_INT_EN        = 1
} SPI_ERRIR_MODE;

typedef enum {
    SPI_FRF_MOTOROLA        = 0,
    SPI_FRF_TI              = 1
} SPI_FRF_MODE;

typedef enum {
    SPI_NO_NSS_PULSE        = 0,
    SPI_NSS_PULSE_GEN       = 1
} SPI_NSSP_MODE;

typedef enum {
    SPI_SS_OUTPUT_DIS       = 0,
    SPI_SS_OUTPUT_EN        = 1
} SPI_SSOE_MODE;

typedef enum {
    SPI_TX_BUF_DMA_DIS      = 0,
    SPI_TX_BUF_DMA_EN       = 1
} SPI_TXDMAEN_MODE;

typedef enum {
    SPI_RX_BUF_DMA_DIS      = 0,
    SPI_RX_BUF_DMA_EN       = 1
} SPI_RXDMAEN_MODE;


//
// SPI Status Register (SPIx_SR) definitions
//
#define     N_FTLVL         11
#define     N_FRLVL         9
#define     N_FRE           8
#define     N_BSY           7
#define     N_OVR           6
#define     N_MODF          5
#define     N_CRCERR        4
#define     N_TXE           1
#define     N_RXNE          0

#define     S_FTLVL         2
#define     S_FRLVL         2
#define     S_FRE           1
#define     S_BSY           1
#define     S_OVR           1
#define     S_MODF          1
#define     S_CRCERR        1
#define     S_TXE           1
#define     S_RXNE          1

typedef enum {
    SPI_FTLVL_EMPTY         = 0,
    SPI_FTLVL_1_4_FULL      = 1,
    SPI_FTLVL_1_2_FULL      = 2,
    SPI_FTLVL_FULL          = 3
} SPI_FTLVL_MODE;

typedef enum {
    SPI_FRLVL_EMPTY         = 0,
    SPI_FRLVL_1_4_FULL      = 1,
    SPI_FRLVL_1_2_FULL      = 2,
    SPI_FRLVL_FULL          = 3
} SPI_FRLVL_MODE;

typedef enum {
    SPI_NO_FF_ERROR         = 0,
    SPI_FF_ERROR            = 1
} SPI_FRE_MODE;

typedef enum {
    SPI_NOT_BUSY            = 0,
    SPI_BUSY                = 1
} SPI_BSY_FLAG;

typedef enum {
    SPI_NO_OVERRUN          = 0,
    SPI_OVERRUN             = 1
} SPI_OVR_FLAG;

typedef enum {
    SPI_NO_MODE_FAULT       = 0,
    SPI_MODE_FAULT          = 1
} SPI_MODF_FLAG;

typedef enum {
    SPI_NO_CRC_ERROR        = 0,
    SPI_CRC_ERROR           = 1
} SPI_CRCERR_FLAG;

typedef enum {
    SPI_TXE_NOT_EMPTY       = 0,
    SPI_TXE_EMPTY           = 1
} SPI_TXE_FLAG;

typedef enum {
    SPI_RXNE_EMPTY          = 0,
    SPI_RXNE_NOT_EMPTY      = 1
} SPI_RXNE_FLAG;

#endif













/*
  3. Email about schlorship
  4. Change resume
  5. Change cover letter
  6. Work on SPI driver.

*/