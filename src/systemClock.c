#include "systemClock.h"

/**
 * Initialize system clock
 */
void initializeSystemClock(void)
{
	OSCICN |= 0x03; // Configure internal oscillator
	RSTSRC = 0x04;  // Enable missing clock detector
}
