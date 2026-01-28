#include "w5500.h"


void w5500_init_device(w5500_info *info) {
    
    spiMasterModuleInit(
        info->spiModule,
        info->mosi,
        info->miso,
        info->sclk,
        0,
        info->bitRate
    );

    gpioPinInit(info->nCS, GPIO_MODE_OUTPUT); // Chip select
    gpioSetPinLevel(info->nCS, GPIO_VAL_HIGH);

    // The bitrate may not be different than the selected one
    info->bitRate = spiGetBitRate(info->spiModule);

    // Reset the device and wait until the reset is complete.
    w5500_write_reg(info, W5500_CR | W5500_MR, W5500_MR_RST);
    //while (!(w5500_read_reg(info, W5500_CR | W5500_MR) & W5500_MR_RST));

    // Default gateway
    w5500_write(info, W5500_CR | W5500_GAR, &info->gatewayIp, 4);

    // Subnet mask
    w5500_write(info, W5500_CR | W5500_SUBR, &info->subnetMask, 4);

    // MAC address
    w5500_write(info, W5500_CR | W5500_SHAR, &info->macAddr, 6);

    // Source IP Address
    w5500_write(info, W5500_CR | W5500_SIPR, &info->sourceIp, 4);
    
    // Need to reduce all socket TX and RX buffers to 0kB so that they can be allocated
    for (int socket = 0; socket < W5500_NUM_SOCKETS; socket++) {
		
		w5500_write_reg(info, W5500_Sn_REG(socket) | W5500_Sn_RXBUF_SIZE, 0);
		w5500_write_reg(info, W5500_Sn_REG(socket) | W5500_Sn_TXBUF_SIZE, 0);
	}
	
}


void w5500_init_socket(w5500_info *info, w5500_socket *socket) {

	// TCP or UDP mode
    w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_MR , socket->protocol);
	
	// Port number
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | (W5500_Sn_PORT+1), (uint8_t)(socket->port >> 8));
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_PORT, (uint8_t)socket->port);
	
	// Destination IP address
	w5500_write(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_DIPR, &socket->destIp, 4);
	
	// Destination Port number
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | (W5500_Sn_DPORT+1), (uint8_t)(socket->destPort >> 8));
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_DPORT, (uint8_t)socket->destPort);
	
	// Maximum segment size
	uint16_t mssr;
	switch (socket->protocol) {
		case W5500_TCP_MODE:
			mssr = 1460; break;
		case W5500_UDP_MODE:
			mssr = 1472; break;
		case W5500_MACRAW_MODE:
			mssr = 1514; break;
		default:
			mssr = 0;
	}

	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | (W5500_Sn_MSSR+1), (uint8_t)(mssr >> 8));
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_MSSR, (uint8_t)mssr);
	
	// RX and TX Buf Size
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_RXBUF_SIZE, socket->RxBufSizeKb);
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_TXBUF_SIZE, socket->TxBufSizeKb);

	// Keep alive for 60 seconds
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_KPALVTR, 12);

}
















// Write to the W5000 in VDM
// Address format is 0bAAAAA BBBBBBBB BBBBBBBB
// A is control block, B is address within the block
void w5500_write(w5500_info *info, uint32_t addr, void *data, uint32_t len) {

    uint8_t control = ((addr & W5500_BSB_MASK) >> 13) | W5500_OM_WRITE | W5500_OM_VDM;

    gpioSetPinLevel(info->nCS, GPIO_VAL_LOW);

    spiSendData(info->spiModule, 1, ((uint8_t*)&addr)+1, NULL);
    spiSendData(info->spiModule, 1, (uint8_t*)&addr, NULL);
    spiSendData(info->spiModule, 1, &control, NULL);
    spiSendData(info->spiModule, len, data, NULL);

    gpioSetPinLevel(info->nCS, GPIO_VAL_HIGH);
}

// Write to a register
void w5500_write_reg(w5500_info *info, uint32_t addr, uint8_t data) {

    uint8_t control = ((addr & W5500_BSB_MASK) >> 13) | W5500_OM_WRITE | W5500_OM_VDM;

    gpioSetPinLevel(info->nCS, GPIO_VAL_LOW);

    spiSendData(info->spiModule, 1, ((uint8_t*)&addr)+1, NULL);
    spiSendData(info->spiModule, 1, (uint8_t*)&addr, NULL);
    spiSendData(info->spiModule, 1, &control, NULL);
    spiSendData(info->spiModule, 1, &data, NULL);

    gpioSetPinLevel(info->nCS, GPIO_VAL_HIGH);
}


void w5500_read(w5500_info *info, uint32_t addr, void *data, uint32_t len) {

    uint8_t control = ((addr & W5500_BSB_MASK) >> 13) | W5500_OM_READ | W5500_OM_VDM;

    gpioSetPinLevel(info->nCS, GPIO_VAL_LOW);

    spiSendData(info->spiModule, 1, ((uint8_t*)&addr)+1, NULL);
    spiSendData(info->spiModule, 1, (uint8_t*)&addr, NULL);
    spiSendData(info->spiModule, 1, &control, NULL);
    spiSendData(info->spiModule, len, NULL, (uint8_t*)data);

    gpioSetPinLevel(info->nCS, GPIO_VAL_HIGH);
}


// Write to a register
uint8_t w5500_read_reg(w5500_info *info, uint32_t addr) {

    uint8_t data;

    uint8_t control = ((addr & W5500_BSB_MASK) >> 13) | W5500_OM_READ | W5500_OM_VDM;

    gpioSetPinLevel(info->nCS, GPIO_VAL_LOW);

    spiSendData(info->spiModule, 1, ((uint8_t*)&addr)+1, NULL);
    spiSendData(info->spiModule, 1, (uint8_t*)&addr, NULL);
    spiSendData(info->spiModule, 1, &control, NULL);
    spiSendData(info->spiModule, 1, NULL, &data);

    gpioSetPinLevel(info->nCS, GPIO_VAL_HIGH);

    return data;
}
