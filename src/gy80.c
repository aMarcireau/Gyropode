#include "gy80.h"

/**
 * Initialize gy80
 */
void initializeGY80(void)
{
	initializeSMBus(void);
	initializeTimer1(SYSTEM_CLOCK / SM_BUS_FREQUENCY / 3);
	initializeTimer3(SYSTEM_CLOCK / 12 / 40);

	writeOnSMBus(ACCELEROMETER_ADDRESS, 0x2D, 0x08); // Switch on accelerometer
}

/**
 * Get X acceleration
 */
int getXAcceleration(void)
{
	int x0, x1;
	x0 = (int)readFromSMBus(ACCELEROMETER_ADDRESS, 0x32);
	x1 = (int)readFromSMBus(ACCELEROMETER_ADDRESS, 0x33)<<8;

	return x0 + x1;
}

/**
 * Get Y acceleration
 */
int getYAcceleration(void)
{
	int y0, y1;
	y0 = (int)readFromSMBus(ACCELEROMETER_ADDRESS, 0x34);
	y1 = (int)readFromSMBus(ACCELEROMETER_ADDRESS, 0x35) << 8;

	return y0 + y1;
}

/**
 * Get Z acceleration
 */
int getZAcceleration(void)
{
	int z0, z1;
	z0 = (int)readFromSMBus(ACCELEROMETER_ADDRESS, 0x36);
	z1 = (int)readFromSMBus(ACCELEROMETER_ADDRESS, 0x37) << 8;

	return z0 + z1;
}
