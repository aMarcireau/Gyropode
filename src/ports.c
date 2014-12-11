#include "ports.h"

/**
 * Initialize ports
 */
void initializePorts(void) {
	XBR0 = 0x05;
	XBR1 = 0x41;
	P0MDOUT |= 0x10;
	P3MDOUT |= 0x08;
	P0SKIP = 0xcc;
	P1MDOUT |= 0x01;
}
