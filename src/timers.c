#include "timers.h"

/**
 * Initialize timer 2
 */
void initializeTimer2(int counts) {
	TMR2CN = 0x00;    // Stop Timer 2 and clear TF2
	CKCON &= ~0x60;	  // Timer 2 clocked based on T2XCLK
	TMR2RL = -counts; // Initialize reload value
	TMR2 = 0xffff;    // Set to reload immediately
	ET2 = 1;          // Enable Timer 2 interrupts
	TR2 = 1;          // Start Timer 2
}
