/*

    This library contains definitions for the UDP table, which
    defines function pointers to standard UDP access functions.

*/
#ifndef UDP_LIB_H
#define UDP_LIB_H

#include <stdint.h>

#define		UDP_CLOSED		0
#define		UDP_DEFAULT		0
#define		UDP_OPEN		1



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

typedef struct {
	
	uint16_t 	sourcePort;		// Source UDP port
	uint16_t	destPort;		// Destination UDP port
	IPv4_addr	destIp;			// Destination IPv4 Address
	int			status;			// Status of socket
	void 		*otherInfo;		// Pointer to device specific socket information
	
} UDPInfo;

/*
 * This is going to have a defined structure which has function pointers
 * to the UDP functions that the system is going to use.
 * 
 * I think this this will be initilized in the startup library of maybe
 * in main.
 */
typedef struct {
	
	void *devInfo;				// Device Info
    int  UDPInfoSize;           // Size of UDP Info
	void (*open)(UDPInfo*);		// Open Socket
	void (*send)(UDPInfo*);		// Send Data
	void (*recv)(UDPInfo*);		// Receive Data
	void (*close)(UDPInfo*);	// Close Scoekt
	
} UDPTable;

// This will hold the systems UDP table
extern UDPTable UDP;

#endif