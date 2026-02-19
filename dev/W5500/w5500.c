#include "w5500.h"

UDPTable UDP;

/*
    Initializes the W5500 device with the settings in the info provided.
    This is for the common registers, which apply to the entire device.
    Socket initialization is not done here.

    The device can be reinitialized if new settings are needed, but all
    socket settings are lost.

    @param  info    Pointer to W5500 device info

*/
void w5500_init_device() {

    /// THIS NEEDS TO BE CHANGED
    w5500_info w5500 = W5500_INFO_DEFAULT;
    w5500_info *info = &w5500;

    UDP.UDPInfoSize = W5500_SOCKET_SIZE;
    UDP.devInfo = malloc(sizeof(w5500_info));
    memcpy(UDP.devInfo, info, sizeof(w5500_info));
    // OTHER UDP TABLE DEFINITIONS, when complete
    UDP.open = w5500_udp_open;

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
	Open a socket in UDP mode.
	
	@param	info	 UDP Information for socket to open.



*/
void w5500_udp_open(UDPInfo *info) {
	
	uint8_t socket;
    w5500_info *devInfo = (w5500_info*)UDP.devInfo;
    w5500_socket *sockInfo = (w5500_socket*)malloc(sizeof(w5500_info));
	
	// Find first avaliable socket : RN ASSUMES THERE IS ALWAYS ONE AVALIABLE
	for (int i = 0; i < 8; i++) {
		if ((devInfo->socketUsed >> i) & 1) {
			socket = i;
			devInfo->socketUsed |= 1 << socket;
			break;
		}
	}
	
    info->reserved = sockInfo;
	sockInfo->socketNum = socket;
	sockInfo->protocol = W5500_UDP_MODE;
	
	// UDP mode
    w5500_write_reg(UDP.devInfo, W5500_Sn_REG(socket) | W5500_Sn_MR , W5500_UDP_MODE);
    
	// Destination IP address
	w5500_write(UDP.devInfo, W5500_Sn_REG(socket) | W5500_Sn_DIPR, &info->destIp, 4);
	
	// Destination Port number
	w5500_write_reg16(UDP.devInfo, W5500_Sn_REG(socket) | W5500_Sn_DPORT, info->destPort);
	
	// Maximum segment size for UDP
	w5500_write_reg16(UDP.devInfo, W5500_Sn_REG(socket) | W5500_Sn_MSSR, 1472);
	
	// RX and TX Buf Size : RN 2 KB for each : RN assumes there is always 2KB avlaible
	w5500_write_reg(UDP.devInfo, W5500_Sn_REG(socket) | W5500_Sn_RXBUF_SIZE, 2);
	w5500_write_reg(UDP.devInfo, W5500_Sn_REG(socket) | W5500_Sn_TXBUF_SIZE, 2);
	_W5500_SET_BUF_SIZE(socket, devInfo->TxBufSize, 2);
	_W5500_SET_BUF_SIZE(socket, devInfo->RxBufSize, 2);
	
	// Keep alive for 60 seconds
	w5500_write_reg(UDP.devInfo, W5500_Sn_REG(socket) | W5500_Sn_KPALVTR, 12);
}


/*
	Send data over a UDP socket.
	
	@param	info	UDP Info for socket to send
	@param	data	Data to send
	@param	len		Length of data to send


*/
void w5500_udp_send(UDPInfo *info, uint8_t *data, int len) {
	
	// RN Assumes data is valid and len is valid : Under 2kB
    w5500_info *devInfo = (w5500_info*)UDP.devInfo;
    w5500_socket *sockInfo = (w5500_socket*)info->reserved;

	int TxBufSize = _W5500_BUF_SIZE(sockInfo->socketNum, devInfo->TxBufSize) * 1024;
	
	// Save data to TX buffer - may require two write if there is an overflow
	if (sockInfo->TxPointer + len > TxBufSize) {
		uint16_t write1 = TxBufSize - sockInfo->TxPointer;
		w5500_write(UDP.devInfo, W5500_Sn_TX(sockInfo->socketNum) + sockInfo->TxPointer, data, write1);
		w5500_write(UDP.devInfo, W5500_Sn_TX(sockInfo->socketNum), &data[write1], len - write1);
	
	} else {
		w5500_write(UDP.devInfo, W5500_Sn_TX(sockInfo->socketNum), data, len);
	}
	
	sockInfo->TxPointer = (len + sockInfo->TxPointer) % (TxBufSize);

    // Increment pointer reg
    w5500_write_reg16(UDP.devInfo, W5500_Sn_REG(sockInfo->socketNum) | W5500_Sn_TX_WR, sockInfo->TxPointer);
    
    // Input a send command to send the data
    w5500_write_reg(UDP.devInfo, W5500_Sn_REG(sockInfo->socketNum) | W5500_Sn_CR, W5500_Sn_CR_SEND);
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
