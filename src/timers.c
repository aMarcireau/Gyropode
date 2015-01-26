#include "timers.h"

/**
 * Initialize timer 1
 */
void initializeTimer1(void)
{
	CKCON |= 0x08; // Timer1 clock source = SYSCLK
	TMOD = 0x20;   // 8-bit auto-reload mode
    TH1 = 0x96;    // Overflow value (corresponds to a 230400Hz frequency)
    TL1 = TH1;     // Initialize timer
    TR1 = 1;       // Start Timer 1
}

/**
 * Initialize timer 2
 */
void initializeTimer2(int counts)
{
	TMR2CN = 0x00;     // Stop Timer 2 and clear TF2
	CKCON &= ~0x20;	   // Timer 2 clocked based on T2XCLK
	TMR2RL = -counts;  // Initialize reload value
	TMR2 = 0xffff;     // Set to reload immediately
	ET2 = 1;           // Enable Timer 2 interrupts
	TR2 = 1;           // Start Timer 2
}
