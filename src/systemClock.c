#include "systemClock.h"

/**
 * Initialize system clock
 */
void initializeSystemClock(void) {
	OSCICN = 0xC3; // Configure internal oscillator for its lowest frequency
	RSTSRC = 0x04; // Enable missing clock detector
}
