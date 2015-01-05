#include "gy80.h"

/**
 * Definitions
 */
const unsigned char accelerometerAddress = 0x53;
const unsigned char gyroscopeAddress = 0x69;

/**
 * Initialize gy80
 */
void initializeGy80(void)
{
	initializeSmBus();
	initializeTimer1(SYSTEM_CLOCK / SM_BUS_FREQUENCY / 3);
	initializeTimer3(SYSTEM_CLOCK / 12 / 40);

	writeOnSmBus(accelerometerAddress, 0x2D, 0x08, 1); // Switch on accelerometer
}

/**
 * Get X acceleration
 */
int getXAcceleration(void)
{
	int x0 = (int)readFromSmBus(accelerometerAddress, 0x32, 1);
	int x1 = (int)readFromSmBus(accelerometerAddress, 0x33, 1) << 8;

	return x0 + x1;
}

/**
 * Get Y acceleration
 */
int getYAcceleration(void)
{
	int y0 = (int)readFromSmBus(accelerometerAddress, 0x34, 1);
	int y1 = (int)readFromSmBus(accelerometerAddress, 0x35, 1) << 8;

	return y0 + y1;
}

/**
 * Get Z acceleration
 */
int getZAcceleration(void)
{
	int z0 = (int)readFromSmBus(accelerometerAddress, 0x36, 1);
	int z1 = (int)readFromSmBus(accelerometerAddress, 0x37, 1) << 8;

	return z0 + z1;
}
