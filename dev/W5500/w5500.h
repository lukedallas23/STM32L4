#ifndef W5000_H
#define W5000_H

#include "../../lib/spi/spilib.h"
#include "../../lib/gpio/gpiolib.h"

typedef struct {

    uint8_t IPAddr3;
    uint8_t IPAddr2;
    uint8_t IPAddr1;
    uint8_t IPAddr0;

} IPv4_addr;

typedef struct {

    uint8_t MACAddr5;
    uint8_t MACAddr4;
    uint8_t MACAddr3;
    uint8_t MACAddr2;
    uint8_t MACAddr1;
    uint8_t MACAddr0;

} MAC_addr;

typedef enum {

    W5500_CLOSED        = 0,
    W5500_TCP_MODE      = 1,
    W5500_UDP_MODE      = 2,
    W5500_MACRAW_MODE   = 4

} w5500_protocol;

typedef struct {

    SPI_MODULE      spiModule;
    GPIO_PIN        mosi;
    GPIO_PIN        miso;
    GPIO_PIN        sclk;
    GPIO_PIN        nCS;
    uint32_t        bitRate;
    IPv4_addr       gatewayIp;
    IPv4_addr       subnetMask;
    MAC_addr        macAddr;
    IPv4_addr       sourceIp;       

} w5500_info;

typedef struct {

    uint8_t         socketNum; // 0-7
    w5500_protocol  protocol;
    uint16_t		port;
    IPv4_addr		destIp;
    uint16_t		destPort;
    uint16_t		RxBufSizeKb; // 1, 2, 4, 8, or 16k
    uint16_t		TxBufSizeKb; // 1, 2, 4, 8, or 16k
    uint16_t		RxPointer;
    uint16_t		TxPointer;

} w5500_socket;

// Default Info Block
#define     W5500_INFO_DEFAULT  {1, GPIO_A7, GPIO_A6, GPIO_A5, GPIO_A4, \
400000, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}}

// Default Socket Block
#define     W5500_SOCKET_DEFAULT  {0, W5500_TCP_MODE, 0, {0, 0, 0, 0}, 0, 2, 2}

#define		W5500_NUM_SOCKETS	8

#define     W5500_OM_VDM    0b00
#define     W5500_OM_1B     0b01
#define     W5500_OM_2B     0b10
#define     W5500_OM_4B     0b11

#define     W5500_OM_READ   0b000
#define     W5500_OM_WRITE  0b100

#define     W5500_BSB_MASK  0x1F0000

#define     W5500_CR        0x000000
#define     W5500_S0        0x010000
#define     W5500_S0_TX     0x020000
#define     W5500_S0_RX     0x030000

// Get socket addresses
#define     W5500_Sn_REG(S)     (S*0x40000+0x10000)
#define     W5500_Sn_TX(S)      (S*0x40000+0x20000)
#define     W5500_Sn_RX(S)      (S*0x40000+0x30000)

// Common Registers
#define     W5500_MR        		0x0000
#define     W5500_GAR       		0x0001
#define     W5500_SUBR      		0x0005
#define     W5500_SHAR      		0x0009
#define     W5500_SIPR      		0x000F
#define		W5500_INTLEVEL			0x0013
#define		W5500_IR				0x0015
#define		W5500_IRM				0x0016
#define		W5500_SIR				0x0017
#define		W5500_SIMR				0x0018
#define		W5500_RTR				0x0019
#define		W5500_RCR				0x001B
#define		W5500_PTIMER			0x001C
#define		W5500_PMAGIC			0x001D
#define		W5500_PHAR				0x001E
#define		W5500_PSID				0x0024
#define		W5500_PMRU				0x0026
#define		W5500_UIPR				0x0028
#define		W5500_UPORTR			0x002C
#define		W5500_PHYCFGR			0x002E
#define		W5500_VERSIONR			0x0039


// Socket Registers
#define     W5500_Sn_MR     		0x0000
#define     W5500_Sn_CR             0x0001
#define     W5500_Sn_IR             0x0002
#define     W5500_Sn_SR             0x0003
#define		W5500_Sn_PORT			0x0004
#define		W5500_Sn_DHAR0			0x0006
#define		W5500_Sn_DIPR			0x000C
#define		W5500_Sn_DPORT			0x0010
#define		W5500_Sn_MSSR			0x0012
#define		W5500_Sn_TOS			0x0015
#define		W5500_Sn_TTL			0x0016
#define		W5500_Sn_RXBUF_SIZE		0x001E
#define		W5500_Sn_TXBUF_SIZE		0x001F
#define		W5500_Sn_TX_FSR			0x0020
#define		W5500_Sn_TX_RD			0x0022
#define		W5500_Sn_TX_WR			0x0024
#define		W5500_Sn_RX_RSR			0x0026
#define		W5500_Sn_RX_RD			0x0028
#define		W5500_Sn_RX_WR			0x002A
#define		W5500_Sn_IMR			0x002C
#define		W5500_Sn_FRAG			0x002D
#define		W5500_Sn_KPALVTR		0x002F


// W5500 Commands
#define     W5500_Sn_CR_OPEN        0x01    // Init and open a socket
#define     W5500_Sn_CR_LISTEN      0x02    // (TCP ONLY) Wait for connection request from client
#define     W5500_Sn_CR_CONNECT     0x04    // (TCP ONLY) Connect to a TCP server
#define     W5500_Sn_CR_DISCON      0x08    // (TCP ONLY) Disconnect from peer
#define     W5500_Sn_CR_CLOSE       0x10    // Close socket
#define     W5500_Sn_CR_SEND        0x20    // Transmit all data in the TX buffer
#define     W5500_Sn_CR_SEND_MAC    0x21    // (UDP ONLY) Send without automatic ARP (this is generally a DO NOT USE)
#define     W5500_Sn_CR_SEND_KEEP   0x22    // (TCP ONLY) Sends a keep-alive packet
#define     W5500_Sn_CR_RECV        0x40    // Complete the processing of the received data in RX buffer

// W5500 Statuses
#define     W5500_Sn_SR_CLOSED          0x00    // Socket is released
#define     W5500_Sn_SR_INIT            0x13    // Socket is opened with TCP mode 
#define     W5500_Sn_SR_LISTEN          0x14    // Socket os operating as a TCP server
#define     W5500_Sn_SR_ESTABLISHED     0x17    // Socket has processed a SYN packet from a TCP client
#define     W5500_Sn_SR_CLOSE_WAIT      0x1C    // Socket received a FIN packet from connected peer
#define     W5500_Sn_SR_UDP             0x22    // Socket is open in UDP mode
#define     W5500_Sn_SR_MACRAW          0x42    // Socket 0 is opened in MACRAW mode
#define     W5500_Sn_SR_SYNSENT         0x15    // Socket sent the SYN packet to a peer
#define     W5500_Sn_SR_SYNRECV         0x16    // Socket has received the SYN packet from a peer
#define     W5500_Sn_SR_FIN_WAIT        0x18    // Socket is closing
#define     W5500_Sn_SR_CLOSING         0x1A    // Socket is closing
#define     W5500_Sn_SR_TIME_WAIT       0x1B    // Socket is closing
#define     W5500_Sn_SR_SOCK_LAST_ACK   0x1D    // Socket is waiting for the response FIN/ACK to the FIN packet


#define     W5500_MR_RST    0x80

void w5500_init_device(w5500_info *info);
void w5500_init_socket(w5500_info *info, w5500_socket *socket);
void w5500_tx_data(w5500_info *info, w5500_socket *socket, uint8_t *buf, uint32_t len);
uint16_t w5500_rx_data(w5500_info *info, w5500_socket *socket, uint8_t *buf, uint16_t len);
void w5500_open_socket(w5500_info *info, w5500_socket *socket);
void w5500_write(w5500_info *info, uint32_t addr, void *data, uint32_t len);
void w5500_write_reg(w5500_info *info, uint32_t addr, uint8_t data);
void w5500_read(w5500_info *info, uint32_t addr, void *data, uint32_t len);
uint8_t w5500_read_reg(w5500_info *info, uint32_t addr);
uint16_t w5500_read_reg16(w5500_info *info, uint32_t addr);
void w5500_write_reg16(w5500_info *info, uint32_t addr, uint16_t data);

#endif