#include "gy80.h"

/**
 * Definitions
 */
const unsigned char accelerometerAddress = 0x53; // ADXL345
const unsigned char gyroscopeAddress = 0x69;     // L3G4200D

/**
 * Initialize gy80
 */
void initializeGy80(void)
{
	unsigned char test = 0;

	// Turn on accelerometer
	registerSmBus(accelerometerAddress, 0x2d);
	writeOnSmBus(0x08);
	stopSmBus();
}

/**
 * Get accelerations
 */
void getAccelerations(int accelerations[3])
{
	int x0 = 0;
	int x1 = 0;
	int y0 = 0;
	int y1 = 0;
	int z0 = 0;
	int z1 = 0;

	registerSmBus(accelerometerAddress, 0x32);
	addressSmBus(accelerometerAddress, 1);
	x0 = (int)readFromSmBus();
	acknowledgeSmBus();
	x1 = (int)readFromSmBus();
	acknowledgeSmBus();
	y0 = (int)readFromSmBus();
	acknowledgeSmBus();
	y1 = (int)readFromSmBus();
	acknowledgeSmBus();
	z0 = (int)readFromSmBus();
	acknowledgeSmBus();
	z1 = (int)readFromSmBus();
	notAcknowledgeSmBus();
	stopSmBus();

	accelerations[0] = (x1 << 8) | x0;
	accelerations[1] = (y1 << 8) | y0;
	accelerations[2] = (z1 << 8) | z0;
}
