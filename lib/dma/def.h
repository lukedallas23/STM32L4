#ifndef DMA_HEADER_H
#define DMA_HEADER_H


//
// DMA Module Base Addresses
//
#define     R_DMA1_BASE         0x40020000
#define     R_DMA2_BASE         0x40020400

//
//  DMA Register Offsets
//
#define     R_DMA_ISR_OFF           0x00
#define     R_DMA_IFCR_OFF          0x04
#define     R_DMA_CCR_OFF           0x08
#define     R_DMA_CNDTR_OFF         0x0C
#define     R_DMA_CPAR_OFF          0x10
#define     R_DMA_CMAR_OFF          0x14
#define     R_DMA_CSELR_OFF         0xA8

//
// DMA Interrupt Status Register definitions
//
#define     N_TEIF7     27
#define     N_HTIF7     26
#define     N_TCIF7     25
#define     N_GIF7      24
#define     N_TEIF6     23
#define     N_HTIF6     22
#define     N_TCIF6     21
#define     N_GIF6      20
#define     N_TEIF5     19
#define     N_HTIF5     18
#define     N_TCIF5     17
#define     N_GIF5      16
#define     N_TEIF4     15
#define     N_HTIF4     14
#define     N_TCIF4     13
#define     N_GIF4      12
#define     N_TEIF3     11
#define     N_HTIF3     10
#define     N_TCIF3     9
#define     N_GIF3      8
#define     N_TEIF2     7
#define     N_HTIF2     6
#define     N_TCIF2     5
#define     N_GIF2      4
#define     N_TEIF1     3
#define     N_HTIF1     2
#define     N_TCIF1     1
#define     N_GIF1      0

#define     S_TEIF      1
#define     S_HTIF      1
#define     S_TCIF      1
#define     S_GIF       1

typedef enum {
    DMA_NO_TE_EVENT      = 0,
    DMA_TE_EVENT         = 1
} DMA_TEIF_FLAG;

typedef enum {
    DMA_NO_HT_EVENT      = 0,
    DMA_HT_EVENT         = 1
} DMA_HTIF_FLAG;

typedef enum {
    DMA_NO_TC_EVENT      = 0,
    DMA_TC_EVENT         = 1
} DMA_TCIF_FLAG;

typedef enum {
    DMA_NO_EVENT      = 0,
    DMA_EVENT         = 1
} DMA_GIF_FLAG;


//
// DMA Interrupt Flag Clear Register (DMA_IFCR) definitions
//
#define     N_CTEIF7    27
#define     N_CHTIF7    26
#define     N_CTCIF7    25
#define     N_CGIF7     24
#define     N_CTEIF6    23
#define     N_CHTIF6    22
#define     N_CTCIF6    21
#define     N_CGIF6     20
#define     N_CTEIF5    19
#define     N_CHTIF5    18
#define     N_CTCIF5    17
#define     N_CGIF5     16
#define     N_CTEIF4    15
#define     N_CHTIF4    14
#define     N_CTCIF4    13
#define     N_CGIF4     12
#define     N_CTEIF3    11
#define     N_CHTIF3    10
#define     N_CTCIF3    9
#define     N_CGIF3     8
#define     N_CTEIF2    7
#define     N_CHTIF2    6
#define     N_CTCIF2    5
#define     N_CGIF2     4
#define     N_CTEIF1    3
#define     N_CHTIF1    2
#define     N_CTCIF1    1
#define     N_CGIF1     0

#define     S_CTEIF     1
#define     S_CHTIF     1
#define     S_CTCIF     1
#define     S_CGIF      1


//
// DMA Channel Configuration Register (DMA_CCR) defintions.
//
#define     N_MEM2MEM   14
#define     N_PL        12
#define     N_MSIZE     10
#define     N_PSIZE     8
#define     N_MINC      7
#define     N_PINC      6
#define     N_CIRC      5
#define     N_DIR       4
#define     N_TEIE      3
#define     N_HTIE      2
#define     N_TCIE      1
#define     N_EN        0

#define     S_MEM2MEM   1
#define     S_PL        2
#define     S_MSIZE     2
#define     S_PSIZE     2
#define     S_MINC      1
#define     S_PINC      1
#define     S_CIRC      1
#define     S_DIR       1
#define     S_TEIE      1
#define     S_HTIE      1
#define     S_TCIE      1
#define     S_EN        1

typedef enum {
    DMA_MEM2MEM_DIS     = 0,
    DMA_MEM2MEM_EN      = 1
} DMA_MEM2MEM_MODE;

typedef enum {
    DMA_PRI_LOW         = 0,
    DMA_PRI_MEDIUM      = 1,
    DMA_PRI_HIGH        = 2,
    DMA_PRI_VERY_HIGH   = 3
} DMA_PRIORITY;

typedef enum {
    DMA_MSIZE_8_BIT     = 0,
    DMA_MSIZE_16_BIT    = 1,
    DMA_MSIZE_32_BIT    = 2
} DMA_MSIZE;

typedef enum {
    DMA_PSIZE_8_BIT     = 0,
    DMA_PSIZE_16_BIT    = 1,
    DMA_PSIZE_32_BIT    = 2
} DMA_PSIZE;

typedef enum {
    DMA_MINC_DIS        = 0,
    DMA_MINC_EN         = 1
} DMA_MINC_MODE;

typedef enum {
    DMA_PINC_DIS        = 0,
    DMA_PINC_EN         = 1
} DMA_PINC_MODE;

typedef enum {
    DMA_CIRC_DIS        = 0,
    DMA_CIRC_EN         = 1
} DMA_CIRC_MODE;

typedef enum {
    DMA_DIR_FROM_PER    = 0,
    DMA_DIR_FROM_MEM    = 1
} DMA_DIR_MODE;

typedef enum {
    DMA_TEIE_DIS        = 0,
    DMA_TEIE_EN         = 1
} DMA_TEIE_MODE;

typedef enum {
    DMA_HTIE_DIS        = 0,
    DMA_HTIE_EN         = 1
} DMA_HTIE_MODE;

typedef enum {
    DMA_TCIE_DIS        = 0,
    DMA_TCIE_EN         = 1
} DMA_TCIE_MODE;

typedef enum {
    DMA_CHAN_DIS        = 0,
    DMA_CHAN_EN         = 1
} DMA_EN_MODE;

//
// DMA Channel Number of Data to Transfer Register (DMA_CNDTR) definitions.
//
#define     N_NDT       0
#define     S_NDT       16


//
// DMA Channel Peripheral Address Register (DMA_CPAR) definitions
//
#define     N_PA        0
#define     S_PA        32


//
// DMA Channel Memory Address Register (DMA_CMAR) definitions
//
#define     N_MA        0
#define     S_MA        32


//
// DMA Channel Selection Register (DMA_CSELR) definitions
//
#define     N_C7S       24
#define     N_C6S       20
#define     N_C5S       16
#define     N_CS4       12
#define     N_CS3       8
#define     N_CS2       4
#define     N_CS1       0

#define     S_CS        4



#endif