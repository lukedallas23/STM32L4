/*
    Library which inits the protocol tables for the realitive
    protocols.
*/
#include "udp/udp.h"
#include "../dev/W5500/w5500.h"

void initProtocolTables() {

    UDPTable.open = w5500_open_socket;
    

}