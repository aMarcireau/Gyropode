#include "ports.h"

/**
 * Initialize ports
 */
void initializePorts(void)
{
	XBR0 = 0x05;
	XBR1 = 0x42;
	P0SKIP = 0xcc;
					 //    Pin: 7|6|5|4|3|2|1|0
	P0MDOUT  = 0x00; // Port 0: 0 0 0 0 0 0 0 0
	P1MDOUT |= 0x03; // Port 1: - - - - - - 1 1
 	P1MDOUT |= 0x00; // Port 1: - - - - - - - -
	P3MDOUT |= 0x08; // Port 3: - - - - 1 - - -

	P0 = 0xff;
}
