#include "ports.h"

/**
 * Initialize ports
 */
void initializePorts(void) {
	XBR0 	 = 0x05;
	XBR1     = 0x42;    //XBARE=1,CEX0, CEX1 routed to Port pins. 
	P0MDOUT |= 0x10;
	P3MDOUT |= 0x08;
	P0SKIP 	 = 0xcc;
	P1MDOUT |= 0x03;   // P1.0=1; 1.1=1
}
