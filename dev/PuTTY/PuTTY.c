#include "PuTTY.h"

void putty_init(uartInfo *info) {
    uartInitModule(info);
}

/*
    Send an ASCII string to the terminal

*/
void putty_send(uartInfo *info ,char *buf, uint32_t len) {
    
    uartTx(info, buf, len);
}

void hexToAscii(uint8_t num, char *buf) {

    if ((num & 0xF) < 10) buf[1] = '0' + (num & 0xF);
    else buf[1] = 'a' + ((num & 0xF) - 10);

    num >>= 4;

    if ((num & 0xF) < 10) buf[0] = '0' + (num & 0xF);
    else buf[0] = 'a' + ((num & 0xF) - 10);

}

/*
    Prints a hexmap to the terminal. Up to 65536 bytes

*/
void putty_print_hex(uartInfo *info, uint8_t *buf, unsigned int len) {

    char line[47] = "000000 0000 0000 0000 0000 0000 0000 0000 0000\n";

    for (unsigned int i = 0; i < len; i += 16) {

        // Print header
        hexToAscii((uint8_t)(i >> 8), &line[2]);
        hexToAscii((uint8_t)i, &line[4]);

        // Print one row
        for (int j = 0; j < 8; j++) {
            hexToAscii(buf[i+2*j], &line[5*j+7]);
            hexToAscii(buf[i+2*j+1], &line[5*j+9]);
        }
        
        putty_send(info, buf, len);

    }
}