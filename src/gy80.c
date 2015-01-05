#include "gy80.h"

/**
 * Initialize gy80
 */
void initializeGY80(void)
{
	initializeSMBus();
	initializeTimer1(SYSTEM_CLOCK / SM_BUS_FREQUENCY / 3);
	initializeTimer3(SYSTEM_CLOCK / 12 / 40);
}
