#include "gy80.h"

/**
 * Initialize gy80
 */
void initializeGY80(void)
{
	initializeSMBus(void);
	initializeTimer1(SYSTEM_CLOCK / SM_BUS_FREQUENCY / 3);
	initializeTimer3(SYSTEM_CLOCK / 12 / 40);

	writeOnSMBus(ACCELEROMETER_ADDRESS, {0x2D, 0x08}); // Switch on accelerometer
}

/**
 * Get X acceleration
 */
int getXAcceleration(void)
{
	unsigned char x0, x1;
	writeOnSMBus(ACCELEROMETER_ADDRESS, {0x2D});
	x0 = readFromSMBus();
	writeOnSMBus(ACCELEROMETER_ADDRESS, {0x2D});
	x1 = readFromSMBus();
}
