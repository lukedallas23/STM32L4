#ifndef USART_DEF_H
#define USART_DEF_H

//
// USART Module Base Addresses
//
#define     R_USART1_BASE       0x40013800
#define     R_USART2_BASE       0x40004400
#define     R_USART3_BASE       0x40004800


//
// SPI Register Offsets
//
#define     R_USART_CR1_OFF     0x00
#define     R_USART_CR2_OFF     0x04
#define     R_USART_CR3_OFF     0x08
#define     R_USART_BRR_OFF     0x0C
#define     R_USART_GTPR_OFF    0x10
#define     R_USART_RTOR_OFF    0x14
#define     R_USART_RQR_OFF     0x18
#define     R_USART_ISR_OFF     0x1C
#define     R_USART_ICR_OFF     0x20
#define     R_USART_RDR_OFF     0x24
#define     R_USART_TDR_OFF     0x28


//
// USART Control Register 1 (USART_CR1) definitions
//
#define     N_M1                28
#define     N_EOBIE             27
#define     N_RTOIE             26
#define     N_DEAT              21
#define     N_DEDT              16
#define     N_OVER8             15
#define     N_CMIE              14
#define     N_MME               13
#define     N_M0                12
#define     N_WAKE              11
#define     N_PCE               10
#define     N_PS                9
#define     N_PEIE              8
#define     N_TXEIE             7
#define     N_TCIE              6
#define     N_RXNEIE            5
#define     N_IDLEIE            4
#define     N_TE                3
#define     N_RE                2
#define     N_UESM              1
#define     N_UE                0

#define     S_M1                1
#define     S_EOBIE             1
#define     S_RTOIE             1
#define     S_DEAT              5
#define     S_DEDT              5
#define     S_OVER8             1
#define     S_CMIE              1
#define     S_MME               1
#define     S_M0                1
#define     S_WAKE              1
#define     S_PCE               1
#define     S_PS                1
#define     S_PEIE              1
#define     S_TXEIE             1
#define     S_TCIE              1
#define     S_RXNEIE            1
#define     S_IDLEIE            1
#define     S_TE                1
#define     S_RE                1
#define     S_UESM              1
#define     S_UE                1

typedef enum {
    USART_M1_8_9_BIT     = 0,
    USART_M1_7_BIT       = 1
} USART_M1_MODE;

typedef enum {
    USART_EOBIE_INHIBIT  = 0,
    USART_EOBIE_INT      = 1
} USART_EOBIE_MODE;

typedef enum {
    USART_RTOIE_INHIBIT = 0,
    USART_RTOIE_INT     = 1
} USART_RTOIE_MODE;

typedef enum {
    USART_OVER8_16      = 0,
    USART_OVER8_8       = 1
} USART_OVER8_MODE;

typedef enum {
    USART_CMIE_INHIBIT  = 0,
    USART_CMIE_INT      = 1
} USART_CMIE_MODE;

typedef enum {
    USART_MME_ONLY_ACT  = 0,
    USART_MME_SWITCH    = 1
} USART_MME_MODE;

typedef enum {
    USART_M0_7_9_BIT    = 0,
    USART_M0_8_BIT      = 1
} USART_M0_MODE;

typedef enum {
    USART_WAKE_IDLE     = 0,
    USART_WAKE_ADDR_MK  = 1
} USART_WAKE_MODE;

typedef enum {
    USART_PCE_DISABLED  = 0,
    USART_PCE_ENABLE    = 1
} USART_PCE_MODE;

typedef enum {
    USART_PS_EVEN       = 0,
    USART_PS_ODD        = 1
} USART_PS_MODE;

typedef enum {
    USART_PE_INHIBIT    = 0,
    USART_PE_INT        = 1
} USART_PEIE_MODE;

typedef enum {
    USART_TXEIE_INHIBIT = 0,
    USART_TXEIE_INT     = 1
} USART_TXEIE_MODE;

typedef enum {
    USART_TCIE_INHIBIT  = 0,
    USART_TCIE_INT      = 1
} USART_TCIE_MODE;

typedef enum {
    USART_RXNEIE_INHIBIT = 0,
    USART_RXNEIE_INT     = 1
} USART_RXNEIE_MODE;

typedef enum {
    USART_IDLEIE_INHIBIT = 0,
    USART_IDLEIE_INT     = 1
} USART_IDLEIE_MODE;

typedef enum {
    USART_TE_DISABLED   = 0,
    USART_TE_ENABLE     = 1
} USART_TE_MODE;

typedef enum {
    USART_RE_DISABLED   = 0,
    USART_RE_ENABLE     = 1
} USART_RE_MODE;

typedef enum {
    USART_UESM_NOT_ABLE = 0,
    USART_UESM_ABLE     = 1
} USART_UESM_MODE;

typedef enum {
    USART_UE_DISABLED   = 0,
    USART_UE_ENABLED    = 1
} USART_UE_MODE;


//
// USART Control Register 2 (USART_CR2) register definitions
//
#define     N_ADD               24
#define     N_RTOEN             23
#define     N_ABRMOD            21
#define     N_ABREN             20
#define     N_MSBFIRST          19
#define     N_DATAINV           18
#define     N_TXINV             17
#define     N_RXINV             16
#define     N_SWAP              15
#define     N_LINEN             14
#define     N_STOP              12
#define     N_CLKEN             11
#define     N_CPOL              10
#define     N_CHPA              9
#define     N_LBCL              8
#define     N_LBDIE             6
#define     N_LBDL              5
#define     N_ADDM7             4

#define     S_ADD               8
#define     S_RTOEN             1
#define     S_ABRMOD            2
#define     S_ABREN             1
#define     S_MSBFIRST          1
#define     S_DATAINV           1
#define     S_TXINV             1
#define     S_RXINV             1
#define     S_SWAP              1
#define     S_LINEN             1
#define     S_STOP              2
#define     S_CLKEN             1
#define     S_CPOL              1
#define     S_CHPA              1
#define     S_LBCL              1
#define     S_LBDIE             1
#define     S_LBDL              1
#define     S_ADDM7             1

typedef enum {
    USART_RTOEN_DIS         = 0,
    USART_RTOEN_EN          = 1
} USART_RTOEN_MODE;

typedef enum {
    USART_ABRMOD_ST_BIT     = 0,
    USART_ABRMOD_FALL_ED    = 1,
    USART_ABRMOD_7F_DET     = 2,
    USART_ABRMOD_55_DET     = 3
} USART_ABRMOD_MODE;

typedef enum {
    USART_ABREN_DIS         = 0,
    USART_ABREN_EN          = 1
} USART_ABREN_MODE;

typedef enum {
    USART_MSBFIRST_LSB      = 0,
    USART_MSBFIRST_MSB      = 1
} USART_MSBFIRST_MODE;

typedef enum {
    USART_DATAINV_POS_LOG   = 0,
    USART_DATAINV_NEG_LOG   = 1
} USART_DATAINV_MODE;

typedef enum {
    USART_TXINV_STD         = 0,
    USART_TXINV_INVERT      = 1
} USART_TXINV_MODE;

typedef enum {
    USART_RXINV_STD         = 0,
    USART_RXINV_INVERT      = 1
} USART_RXINV_MODE;

typedef enum {
    USART_SWAP_STD          = 0,
    USART_SWAP_SWAPPED      = 1
} USART_SWAP_MODE;

typedef enum {
    USART_LINEN_DIS         = 0,
    USART_LINEN_EN          = 1
} USART_LINEN_MODE;

typedef enum {
    USART_STOP_1_0_BIT      = 0,
    USART_STOP_0_5_BIT      = 1,
    USART_STOP_2_0_BIT      = 2,
    USART_STOP_1_5_BIT      = 3
} USART_STOP_MODE;

typedef enum {
    USART_CLKEN_DIS         = 0,
    USART_CLKEN_EN          = 1
} USART_CLKEN_MODE;

typedef enum {
    USART_CPOL_LOW          = 0,
    USART_CPOL_HIGH         = 1
} USART_CPOL_MODE;

typedef enum {
    USART_CPHA_FIRST_CLK    = 0,
    USART_CPHA_SECOND_CLK   = 1
} USART_CPHA_MODE;

typedef enum {
    USART_LBCL_NOT_OUTPUT   = 0,
    USART_LBCL_OUTPUT       = 1
} USART_LBCL_MODE;

typedef enum {
    USART_LBDIE_INHIBIT     = 0,
    USART_LBDIE_INT         = 1
} USART_LBDIE_MODE;

typedef enum {
    USART_LBDL_10_BREAK     = 0,
    USART_LBDL_11_BREAK     = 1
} USART_LBDL_MODE;

typedef enum {
    USART_ADDM7_4_BIT       = 0,
    USART_ADDM7_7_BIT       = 1
} USART_ADDM7_MODE;


//
// USART Control Register 3 (USART_CR3) register definitions
//
#define     N_TCBGTIE           24
#define     N_UCESM             23
#define     N_WUFIE             22
#define     N_WUS               20
#define     N_SCARCNT           17
#define     N_DEP               15
#define     N_DEM               14
#define     N_DDRE              13
#define     N_OVRDIS            12
#define     N_ONEBIT            11
#define     N_CTSIE             10
#define     N_CTSE              9
#define     N_RTSE              8
#define     N_DMAT              7
#define     N_DMAR              6
#define     N_SCEN              5
#define     N_NACK              4
#define     N_HDSEL             3
#define     N_IRLP              2
#define     N_IREN              1
#define     N_EIE               0

#define     N_TCBGTIE           1
#define     N_UCESM             1
#define     N_WUFIE             1
#define     N_WUS               2
#define     N_SCARCNT           3
#define     N_DEP               1
#define     N_DEM               1
#define     N_DDRE              1
#define     N_OVRDIS            1
#define     N_ONEBIT            1
#define     N_CTSIE             1
#define     N_CTSE              1
#define     N_RTSE              1
#define     N_DMAT              1
#define     N_DMAR              1
#define     N_SCEN              1
#define     N_NACK              1
#define     N_HDSEL             1
#define     N_IRLP              1
#define     N_IREN              1
#define     N_EIE               1

typedef enum {
    USART_TCBGTIE_INHIBIT   = 0,
    USART_TCBGTIE_INT       = 1
} USART_TCBGTIE_MODE;

typedef enum {
    USART_UCESM_CLK_DIS     = 0,
    USART_UCESM_CLK_EN      = 1
} USART_UCESM_MODE;

typedef enum {
    USART_WUFIE_INHIBIT     = 0,
    USART_WUFIE_INT         = 1
} USART_WUFIE_MODE;

typedef enum {
    USART_WUS_ADDR_MATCH    = 0,
    USART_WUS_START_BIT     = 2,
    USART_WUS_RXNE          = 3
} USART_WUS_MODE;

typedef enum {
    USART_DEP_ACT_HIGH      = 0,
    USART_DEP_ACT_LOW       = 1
} USART_DEP_MODE;

typedef enum {
    USART_DEM_DIS           = 0,
    USART_DEM_EN            = 1
} USART_DEM_MODE;

typedef enum {
    USART_DDRE_DIS          = 0,
    USART_DDRE_EN           = 1
} USART_DDRE_MODE;

typedef enum {
    USART_OVRDIS_ERR_FLG    = 0,
    USART_OVRDIS_DIS        = 1
} USART_OVRDIS_MODE;

typedef enum {
    USART_ONEBIT_3_BIT      = 0,
    USART_ONEBIT_1_BIT      = 1
} USART_ONEBIT_MODE;

typedef enum {
    USART_CTSIE_INHIBITED   = 0,
    USART_CTSIE_INT         = 1
} USART_CTSIE_MODE;

typedef enum {
    USART_CTSE_DIS          = 0,
    USART_CTSE_EN           = 1
} USART_CTSE_MODE;

typedef enum {
    USART_RTSE_DIS          = 0,
    USART_RTSE_EN           = 1
} USART_RTSE_MODE;

typedef enum {
    USART_DMAT_DIS          = 0,
    USART_DMAT_EN           = 1
} USART_DMAT_MODE;

typedef enum {
    USART_DMAR_DIS          = 0,
    USART_DMAR_EN           = 1
} USART_DMAR_MODE;

typedef enum {
    USART_SCEN_DIS          = 0,
    USART_SCEN_EN           = 1
} USART_SCEN_MODE;

typedef enum {
    USART_NACK_DIS          = 0,
    USART_NACK_EN           = 1
} USART_NACK_MODE;

typedef enum {
    USART_HDSEL_NOT_SEL     = 0,
    USART_HDSEL_SELECT      = 1
} USART_HDSEL_MODE;

typedef enum {
    USART_IRLP_NORMAL       = 0,
    USART_IRLP_LOW_POW      = 1
} USART_IRLP_MODE;

typedef enum {
    USART_IREN_DIS          = 0,
    USART_IREN_EN           = 1
} USART_IREN_MODE;

typedef enum {
    USART_EIE_INHIBIT       = 0,
    USART_EIE_INT           = 1
} USART_EIE_MODE;


//
// USART Baud Rate (USART_BRR) register definitions
//
#define     N_BRR               0

#define     S_BRR               16


//
// USART Gaurd Time and Prescaler (USART_GTPR) register definitions
//
#define     N_GT                8
#define     N_PSC               0

#define     S_GT                8
#define     S_PSC               8


//
// USART Receiver Timeout (USART_RTOR) register definitions
//
#define     N_BLEN              24
#define     N_RTO               0

#define     S_BLEN              8
#define     S_RTO               24


//
// USART Request (USART_RQR) register definitions
//
#define     N_TXFRQ             4
#define     N_RXFRQ             3
#define     N_MMIRQ             2
#define     N_SBKRQ             1
#define     N_ABRRQ             0

#define     S_TXFRQ             1
#define     S_RXFRQ             1
#define     S_MMIRQ             1
#define     S_SBKRQ             1
#define     S_ABRRQ             1


//
// USART Interrupt and Status (USART_ISR) register difinitions
//
#define     N_TCBGT             25
#define     N_REACK             22
#define     N_TEACK             21
#define     N_WUF               20
#define     N_RWU               19
#define     N_SBKF              18
#define     N_CMF               17
#define     N_BUSY              16
#define     N_ABRF              15
#define     N_ABRE              14
#define     N_EOBF              12
#define     N_RTOF              11
#define     N_CTS               10
#define     N_CTSIF             9
#define     N_LBDF              8
#define     N_TXE               7
#define     N_TC                6
#define     N_RXNE              5
#define     N_IDLE              4
#define     N_ORE               3
#define     N_NF                2
#define     N_FE                1
#define     N_PE                0

#define     S_USART_ISR         1

#define     USART_FLAG_SET      1
#define     USART_FLAG_CLEAR    0


//
// USART Interrupt Flag Clear (USART_ICR) register definitions
//
#define     N_WUCF              20
#define     N_CMCF              17
#define     N_EOBCF             12
#define     N_RTOCF             11
#define     N_CTSCF             9
#define     N_LBDCF             8
#define     N_TCBGTCF           7
#define     N_TCCF              6
#define     N_IDLECL            4
#define     N_ORECF             3
#define     N_NCF               2
#define     N_FECF              1
#define     N_PECF              0

#define     USART_CLEAR_FLAG    1


//
// USART Receive Data (USART_RDR) register definitions
//
#define     N_RDR               0

#define     S_RDR               8


//
// USART Transmit Data (USART_TDR) register definitions
//
#define     N_TDR               0

#define     S_TDR               8

#endif