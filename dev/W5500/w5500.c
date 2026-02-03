#include "w5500.h"


/*
    Initializes the W5500 device with the settings in the info provided.
    This is for the common registers, which apply to the entire device.
    Socket initialization is not done here.

    The device can be reinitialized if new settings are needed, but all
    socket settings are lost.

    @param  info    Pointer to W5500 device info

*/
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


/*
    Initializes a W5500 socket with the settings provided. This includes port,
    layer 4 protocol, destination IP address, and memory allocation. To change a setting,
    call the function again with updated socket info.

    Socket information is reset on a device reset.

    @param  info    Pointer to W5500 device info
    @param  socket  Pointer to socket info

*/
void w5500_init_socket(w5500_info *info, w5500_socket *socket) {

	// TCP or UDP mode
    w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_MR , socket->protocol);
	
	// Port number
	w5500_write_reg16(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_PORT, socket->port);
	
	// Destination IP address
	w5500_write(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_DIPR, &socket->destIp, 4);
	
	// Destination Port number
	w5500_write_reg16(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_DPORT, socket->destPort);
	
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

	w5500_write_reg16(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_MSSR, mssr);
	
	// RX and TX Buf Size
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_RXBUF_SIZE, socket->RxBufSizeKb);
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_TXBUF_SIZE, socket->TxBufSizeKb);
	socket->TxPointer = 0;
	socket->RxPointer = 0;

	// Keep alive for 60 seconds
	w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_KPALVTR, 12);

}


/*
    Send data over a UDP socket by writing to the TX buffer and initializing a transfer.

    @param  info    W5500 info
    @param  socket  Socket info
    @param  buf     Pointer to data to send
    @param  len     Length of data to send

*/
void w5500_tx_data(w5500_info *info, w5500_socket *socket, uint8_t *buf, uint32_t len) {

    // Save data to TX buffer - may require two write if there is an overflow
    if (socket->TxPointer + len > (1024 * socket->TxBufSizeKb)) {
        uint16_t write1 = (1024 * socket->TxBufSizeKb) - socket->TxPointer;
        w5500_write(info, W5500_Sn_TX(socket->socketNum) + socket->TxPointer , buf, write1);
        w5500_write(info, W5500_Sn_TX(socket->socketNum), &buf[write1], len - write1);
    } else {
        w5500_write(info, W5500_Sn_TX(socket->socketNum) + socket->TxPointer , buf, len);
    }
    socket->TxPointer = (len + socket->TxPointer) % (1024 * socket->TxBufSizeKb);

    // Increment pointer reg
    w5500_write_reg16(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_TX_WR, socket->TxPointer);

    // Input a send command to send the data
    w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_CR, W5500_Sn_CR_SEND);
}


/*
    Receive data from a UDP socket and place it in a buffer.

    @param  info    W5500 Info
    @param  socket  Socket Info
    @param  buf     Buffer for received data
    @param  len     Maximum amount of data to read

    @retval Amount of bytes read


*/
uint16_t w5500_rx_data(w5500_info *info, w5500_socket *socket, uint8_t *buf, uint16_t len) {

    uint16_t rxBytesToRead = w5500_read_reg16(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_RX_RSR);
    rxBytesToRead = (len > rxBytesToRead) ? rxBytesToRead : len;
    

    // Save data to buffer - may require two reads if there is an overflow
    if (socket->RxPointer + rxBytesToRead > (1024 * socket->RxBufSizeKb)) {
        uint16_t read1 = (1024 * socket->RxBufSizeKb) - socket->RxPointer;
        w5500_read(info, W5500_Sn_RX(socket->socketNum) + socket->RxPointer , buf, read1);
        w5500_read(info, W5500_Sn_RX(socket->socketNum), &buf[read1], rxBytesToRead - read1);
    } else {
        w5500_read(info, W5500_Sn_RX(socket->socketNum) + socket->RxPointer , buf, rxBytesToRead);
    }
    socket->RxPointer = (rxBytesToRead + socket->RxPointer) % (1024 * socket->RxBufSizeKb);

    // Increment pointer reg
    w5500_write_reg16(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_RX_RD, socket->RxPointer);

    // Input a recv command
    w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_CR, W5500_Sn_CR_SEND);

    return rxBytesToRead;
}

/*
    Open a socket on the W5500 according to the info provided on an open socket.
    
    @param  info    W5500 info
    @param  socket  Socket info


*/
void w5500_open_socket(w5500_info *info, w5500_socket *socket) {

    w5500_init_socket(info, socket);
    w5500_write_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_CR, W5500_Sn_CR_OPEN);

    // Wait until the UDP port is open
    while (w5500_read_reg(info, W5500_Sn_REG(socket->socketNum) | W5500_Sn_SR) != W5500_Sn_SR_UDP);
}



/*
    Write to W5500 device memory.

    @param  info    W5500 device info
    @param  addr    Address to write to
    @param  data    Buffer containing data to write
    @param  len     Length of data to write

*/
void w5500_write(w5500_info *info, uint32_t addr, void *data, uint32_t len) {

    uint8_t control = ((addr & W5500_BSB_MASK) >> 13) | W5500_OM_WRITE | W5500_OM_VDM;

    gpioSetPinLevel(info->nCS, GPIO_VAL_LOW);

    spiSendData(info->spiModule, 1, ((uint8_t*)&addr)+1, NULL);
    spiSendData(info->spiModule, 1, (uint8_t*)&addr, NULL);
    spiSendData(info->spiModule, 1, &control, NULL);
    spiSendData(info->spiModule, len, data, NULL);

    gpioSetPinLevel(info->nCS, GPIO_VAL_HIGH);
}


/*
    Write to a 8-bit register on the W5500 device.

    @param  info    W5500 device info
    @param  addr    Address to write to
    @param  data    Byte of data to write

*/
void w5500_write_reg(w5500_info *info, uint32_t addr, uint8_t data) {

    w5500_write(info, addr, &data, 1);
}


/*
    Read from W5500 device memory.

    @param  info    W5500 device info
    @param  addr    Address to read from
    @param  data    Buffer to place read data
    @param  len     Length of data to read

*/
void w5500_read(w5500_info *info, uint32_t addr, void *data, uint32_t len) {

    uint8_t control = ((addr & W5500_BSB_MASK) >> 13) | W5500_OM_READ | W5500_OM_VDM;

    gpioSetPinLevel(info->nCS, GPIO_VAL_LOW);

    spiSendData(info->spiModule, 1, ((uint8_t*)&addr)+1, NULL);
    spiSendData(info->spiModule, 1, (uint8_t*)&addr, NULL);
    spiSendData(info->spiModule, 1, &control, NULL);
    spiSendData(info->spiModule, len, NULL, (uint8_t*)data);

    gpioSetPinLevel(info->nCS, GPIO_VAL_HIGH);
}


/*
    Read a 8-bit register on the W5500 device.

    @param  info    W5500 device info
    @param  addr    Address to read from

    @retval Received byte

*/
uint8_t w5500_read_reg(w5500_info *info, uint32_t addr) {

    uint8_t data;

    w5500_read(info, addr, &data, 1);

    return data;
}

/*
    Read a 16-bit register on the W5500 device.

    @param  info    W5500 device info
    @param  addr    Address to read from

    @retval Received byte

*/
uint16_t w5500_read_reg16(w5500_info *info, uint32_t addr) {

    uint16_t data;

    data = w5500_read_reg(info, addr) << 8;
    data |= w5500_read_reg(info, addr+1);

    return data;
}


/*
    Write to a 16-bit register on the W5500 device.

    @param  info    W5500 device info
    @param  addr    Address to write to
    @param  data    Byte of data to write

*/
void w5500_write_reg16(w5500_info *info, uint32_t addr, uint16_t data) {

    w5500_write_reg(info, addr, (uint8_t)(data >> 8));
    w5500_write_reg(info, addr+1, (uint8_t)data);
}


/*
 * Process - 
 * 1. Socket is opened - TX_FSR = 0x800, TX_RD = 0, TX_WR = 0
 * 2. Data to transmit is written to the TX buffer (Example 500 Bytes)
 * 3. TX_WR should be written by this program to the end of the write (TX_WR = 500).
 * 	  TX_RD is not incremented. TX_FSR is decreased by the size of the write (TX_FSR = 0x800-500)
 * 4. The data is sent using the SEND command
 * 5. TX_RD is automatically updated to 500, and TX_FSR is increased back up to 0x800.
 * 
 * The TXPointer value in the struct is the value of the write register, where the next write should occour
 * The BufSize value in the struct is the free size remaining
 * 
 * 
 * 
 * RX
 * Sn_RX_RSR    Received size register
 * --- Difference between Sn_RX_RD and Sn_RX_WR
 * Sn_RX_WR     Write Data Pointer
 * --- This is incremented when data is received and placed in the
 *     buffer.
 * Sn_RX_RD     Read Data Pointer
 * --- This is the register that is written to by this code
 * --- When reading from the RX buffer, this should be incremented to indicate the
 *     data is received.
 * --- If RD and WR are the same, then the buffer is empty (probably)
 * 
 * To receive
 * 1. Read data from the buffer starting at the RD pointer
 * 2. Increment the RD pointer by the amount read
 * 3. Send the RECV command to update everything
 */