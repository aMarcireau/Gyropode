#include "ports.h"

/**
 * Initialize ports
 */
void initializePorts(void) {
	XBR0 = 0x05;
	XBR1 = 0x42;
	P0SKIP = 0xcc;
	P0MDOUT |= 0x10;
	P1MDOUT |= 0x03;
	P3MDOUT |= 0x08;
}
