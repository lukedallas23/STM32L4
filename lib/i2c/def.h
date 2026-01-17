#ifndef I2C_HEADER_H
#define I2C_HEADER_H

//
// I2C Module Base Addresses 
//
#define     R_I2C1_BASE         0x40005400
#define     R_I2C2_BASE         0x40005800
#define     R_I2C3_BASE         0x40005C00
#define     R_I2C4_BASE         0x40008400


//
// I2C Register Offsets
//
#define     R_I2C_CR1_OFF       0x00
#define     R_I2C_CR2_OFF       0x04
#define     R_I2C_OAR1_OFF      0x08
#define     R_I2C_OAR2_OFF      0x0C
#define     R_I2C_TIMINGR_OFF   0x10
#define     R_I2C_TIMEOUTR_OFF  0x14
#define     R_I2C_ISR_OFF       0x18
#define     R_I2C_ICR_OFF       0x1C
#define     R_I2C_PECR_OFF      0x20
#define     R_I2C_RXDR_OFF      0x24
#define     R_I2C_TXDR_OFF      0x28


//
// I2C Control Register 1 (I2Cx_CR1)
//
#define     N_PECEN             23
#define     N_ALERTEN           22
#define     N_SMBDEN            21
#define     N_SMBHEN            20
#define     N_GCEN              19
#define     N_WUPEN             18
#define     N_NOSTRETCH         17
#define     N_SBC               16
#define     N_I2C_RXDMAEN       15
#define     N_I2C_TXDAMEN       14
#define     N_ANFOFF            12
#define     N_DNF               8
#define     N_I2C_ERRIR         7
#define     N_TCIE              6
#define     N_STOPIE            5
#define     N_NACKIE            4
#define     N_ADDRIE            3
#define     N_SPI_RXIE          2
#define     N_SPI_TXIE          1
#define     N_PE                0

#define     S_PECEN             1
#define     S_ALERTEN           1
#define     S_SMBDEN            1
#define     S_SMBHEN            1
#define     S_GCEN              1
#define     S_WUPEN             1
#define     S_NOSTRETCH         1
#define     S_SBC               1
#define     S_I2C_RXDMAEN       1
#define     S_I2C_TXDAMEN       1
#define     S_ANFOFF            1
#define     S_DNF               4
#define     S_I2C_ERRIR         1
#define     S_TCIE              1
#define     S_STOPIE            1
#define     S_NACKIE            1
#define     S_ADDRIE            1
#define     S_SPI_RXIE          1
#define     S_SPI_TXIE          1
#define     S_PE                1

typedef enum {
    PEC_CALC_EN             = 0,
    PEC_CALC_DIS            = 1
} I2C_PECEN_MODE;

typedef enum {
    SMBA_NOT_SUPPORTED      = 0,
    SMBA_SUPPORTED          = 1
} I2C_ALERTEN_MODE;

typedef enum {
    SMBDEN_DIS              = 0,
    SMBDEN_EN               = 1
} I2C_SMBDEN_MODE;

typedef enum {
    SMBHEN_DIS              = 0,
    SMBHEN_EN               = 1
} I2C_SMBHEN_MODE;

typedef enum {
    GCEN_DIS                = 0,
    GCEN_EN                 = 1
} I2C_GCEN_MODE;

typedef enum {
    WAKE_FROM_STOP_DIS      = 0,
    WAKE_FROM_STOP_EN       = 1
} I2C_WAKE_UP_MODE;

typedef enum {
    CLK_STRECH_EN           = 0,
    CLK_STRECH_DIS          = 1
} I2C_CLK_STRETCH_MODE;

typedef enum {
    TARGET_BYTE_CON_DIS     = 0,
    TARGET_BYTE_CON_EN      = 1
} I2C_TARGET_BYTE_CON_MODE;

typedef enum {
    I2C_RXDMA_DIS           = 0,
    I2C_RXDMA_EN            = 1
} I2C_RXDMA_MODE;

typedef enum {
    I2C_TXDMA_DIS           = 0,
    I2C_TXDMA_EN            = 1
} I2C_TXDMA_MODE;

typedef enum {
    ANALOG_FILTER_EN        = 0,
    ANALOG_FILTER_DIS       = 1
} I2C_ANALOG_FILTER_MODE;

typedef enum {
    ERROR_INT_DIS           = 0,
    ERROR_INT_EN            = 1
} I2C_ERRIE_MODE;

typedef enum {
    TSFER_COMPLETE_INT_DIS  = 0,
    TSFER_COMPLETE_INT_EN   = 1
} I2C_TCIE_MODE;

typedef enum {
    STOP_DETEC_INT_DIS      = 0,
    STOP_DETEC_INT_EN       = 1
} I2C_STOPIE_MODE;

typedef enum {
    NOT_ACK_REC_INT_DIS     = 0,
    NOT_ACT_REC_INT_EN      = 1
} I2C_NACKIE_MODE;

typedef enum {
    ADDR_MATCH_INT_DIS      = 0,
    ADDR_MATCH_INT_EN       = 1
} I2C_ADDRIE_MODE;

typedef enum {
    I2C_RX_INT_DIS          = 0,
    I2C_RX_INT_EN           = 1
} I2C_RX_INT_MODE;

typedef enum {
    I2C_TX_INT_DIS          = 0,
    I2C_TX_INT_EN           = 1
} I2C_TX_INT_MODE;

typedef enum {
    I2C_MODULE_DIS          = 0,
    I2C_MODULE_EN           = 1
} I2C_PE_MODE;


//
// I2C Control Register 2 (I2Cx_CR2) definitions
//
#define     N_PECBYTE           26
#define     N_AUTOEND           25
#define     N_RELOAD            24
#define     N_NBYTES            16
#define     N_NACK              15
#define     N_STOP              14
#define     N_START             13
#define     N_HEAD10R           12
#define     N_ADD10             11
#define     N_RD_WRN            10
#define     N_SADD              0

#define     S_PECBYTE           1
#define     S_AUTOEND           1
#define     S_RELOAD            1
#define     S_NBYTES            8
#define     S_NACK              1
#define     S_STOP              1
#define     S_START             1
#define     S_HEAD10R           1
#define     S_ADD10             1
#define     S_RD_WRN            1
#define     S_SADD              10

typedef enum {
    NO_PEC_TSFER         = 0,
    PEC_TSM_REQ          = 1
} I2C_PECBYTE_TSFR;

typedef enum {
    SW_END_MODE         = 0,
    AUTO_END_MODE       = 1
} I2C_AUTOEND_MODE;

typedef enum {
    RELOAD_COMPLETE     = 0,
    RELOAD_NOT_COMPLETE = 1
} I2C_RELOAD_MODE;

typedef enum {
    SEND_ACK            = 0,
    SEND_NACK           = 1
} I2C_NACK_MODE;

typedef enum {
    NO_STOP_GEN         = 0,
    STOP_GENERATION     = 1
} I2C_STOP_MODE;

typedef enum {
    NO_START_GEN        = 0,
    START_GENERATION    = 1
} I2C_START_MODE;

typedef enum {
    SEND_10BIT           = 0,
    SEND_7BIT            = 1
} I2C_HEAD10R_MODE;

typedef enum {
    I2C_7BIT_ADDR       = 0,
    I2C_10BIT_ADDR      = 1
} I2C_ADD10_MODE;

typedef enum {
    REQ_WRITE_TSFR      = 0,
    REQ_READ_TSFR       = 1
} I2C_RD_WRN_MODE;


//
// I2C Own Address 1 Register (I2Cx_OAR1) register definitions
//
#define     N_OA1EN             15
#define     N_OA1MODE           10
#define     N_OA1               0

#define     S_OA1EN             1
#define     S_OA1MODE           1
#define     S_OA1               10

typedef enum {
    OWN_ADDR_DIS        = 0,
    OWN_ADDR_EN         = 1
} I2C_OWN_ADDR_EN;

typedef enum {
    OWN_ADDR_7BIT       = 0,
    OWN_ADDR_10BIT      = 1
} I2C_OWN_ADDR_LEN;


//
// I2C Own Address 2 Register (I2Cx_OAR2) register definitions
//
#define     N_OA2EN             15
#define     N_OA2MSK            8
#define     N_OA2               1

#define     S_OA1EN             1
#define     S_OA1MODE           3
#define     S_OA1               7


//
// I2C Timing Register (I2Cx_TIMINGR) register definitions
//
#define     N_PRESEC            28
#define     N_SCLDEL            20
#define     N_SDADEL            16
#define     N_SCLH              8
#define     N_SCLL              0

#define     S_PRESEC            4
#define     S_SCLDEL            4
#define     S_SDADEL            4
#define     S_SCLH              8
#define     S_SCLL              8


//
// I2C Timeout Register (I2Cx_TIMEOUTR) register definitions
//
#define     N_TEXTEN            31
#define     N_TIMEOUTB          16
#define     N_TIMEOUTEN         15
#define     N_TIDLE             12
#define     N_TIMEOUTA          0

#define     S_TEXTEN            1
#define     S_TIMEOUTB          12
#define     S_TIMEOUTEN         1
#define     S_TIDLE             1
#define     S_TIMEOUTA          12

typedef enum {
    EX_TIMEOUT_DETEC_DIS    = 0,
    EX_TIMEOUT_DETEC_EN     = 1
} I2C_TEXTEN_MODE;

typedef enum {
    CLK_TIMEOUT_DIS         = 0,
    CLK_TIMEOUT_EN          = 1
} I2C_TIMEOUT_MODE;

typedef enum {
    TIMEOUTA_SCL_LOW        = 0,
    TIMEOUTA_SCL_SDA_HIGH   = 1
} I2C_TIMEOUTA_MODE;


//
// I2C Interrupt and Status Register (I2Cx_ISR) register definitions
//
#define     N_ADDCODE           17
#define     N_DIR               16
#define     N_BUSY              15
#define     N_ALERT             13
#define     N_TIMOUT            12
#define     N_PECERR            11
#define     N_OVR               10
#define     N_ARLO              9
#define     N_BERR              8
#define     N_TCR               7
#define     N_TC                6
#define     N_STOPF             5
#define     N_NACKF             4
#define     N_ADDR              3
#define     N_RXNE              2
#define     N_TXIS              1
#define     N_TXE               0

#define     S_ADDCODE           7
#define     S_DIR               1
#define     S_BUSY              1
#define     S_ALERT             1
#define     S_TIMEOUT           1
#define     S_PECERR            1
#define     S_OVR               1
#define     S_ARLO              1
#define     S_BERR              1
#define     S_TCR               1
#define     S_TC                1
#define     S_STOPF             1
#define     S_NACKF             1
#define     S_ADDR              1
#define     S_RXNE              1
#define     S_TXIS              1
#define     S_TXE               1

typedef enum {
    WRITE_TSFR              = 0,
    READ_TSFR               = 1
} I2C_DIR_STATUS;

typedef enum {
    I2C_NOT_BSY             = 0,
    I2C_BSY                 = 1
} I2C_BSY_STATUS;

typedef enum {
    SMBUS_NO_ALERT          = 0,
    SMBUS_ALERT             = 1
} I2C_ALERT_STATUS;

typedef enum {
    I2C_TIMEOUT             = 0,
    I2C_NO_TIMEOUT          = 1
} I2C_TIMEOUT_STATUS;

typedef enum {
    I2C_NO_PEC_ERR          = 0,
    I2C_PEC_ERR             = 1
} I2C_PEC_STATUS;

typedef enum {
    I2C_NO_OVR_ERR          = 0,
    I2C_OVR_ERR             = 1
} I2C_OVR_STATUS;

typedef enum {
    I2C_ARB_NOT_LOST        = 0,
    I2C_ARB_LOST            = 1
} I2C_ARB_STATUS;

typedef enum {
    I2C_NO_BUS_ERR          = 0,
    I2C_BUS_ERR             = 1
} I2C_BUS_STATUS;

typedef enum {
    I2C_TSFR_NOT_COM_RLOAD  = 0,
    I2C_TSFR_COM_RLOAD      = 1
} I2C_TCR_STATUS;

typedef enum {
    I2C_TSFR_NOT_COMPLETE   = 0,
    I2C_TSFT_COMPETE        = 1    
} I2C_TC_STATUS;

typedef enum {
    I2C_NOT_STOPF           = 0,
    I2C_STOPF               = 1
} I2C_STOPF_STATUS;

typedef enum {
    I2C_NO_NAC_REC          = 0,
    I2C_NAC_REC             = 1
} I2C_NACKF_STATUS;

typedef enum {
    I2C_NO_ADDR_MATCH       = 0,
    I2C_ADDR_MATCH          = 1
} I2C_ADDR_STATUS;

typedef enum {
    I2C_TXIS_NOT_SET        = 0,
    I2C_TXIS_SET            = 1
} I2C_TXIS_STATUS;

typedef enum {
    I2C_TXE_NOT_EMPTY       = 0,
    I2C_TXE_EMPTY           = 1
} I2C_TXE_STATUS;


//
// I2C Interrupt Clear Register (I2Cx_ICR) register definitions
//
#define     N_ALERTCF           13
#define     N_TIMOUTCF          12
#define     N_PECCF             11
#define     N_OVRCF             10
#define     N_ARLOCF            9
#define     N_BERRCF            8
#define     N_STOPCF            5
#define     N_NACKCF            4
#define     N_ADDRCF            3

#define     S_ALERTCF           1
#define     S_TIMOUTCF          1
#define     S_PECCF             1
#define     S_OVRCF             1
#define     S_ARLOCF            1
#define     S_BERRCF            1
#define     S_STOPCF            1
#define     S_NACKCF            1
#define     S_ADDRCF            1

typedef enum {
    I2C_INT_NO_CLEAR        = 0,
    I2C_INT_CLEAR           = 1
} I2C_INT_CLEAR;


//
// I2C PEC (I2Cx_PECR) register definitions
//
#define     N_PEC               0
#define     S_PEC               8


//
// I2C Receive Data Register (I2Cx_RXDR) register definitions
//
#define     N_RXDATA            0
#define     S_RXDATA            8


//
// I2C Transmit Data Register (I2Cx_TXDR) register definitions
//
#define     N_TXDATA            0
#define     S_TXDATA            8


#endif
