#include "timers.h"

/**
 * Initialize timer 1
 */
void initializeTimer1(unsigned int counts)
{
	CKCON |= 0x08  // Timer1 clock source = SYSCLK
	TMOD = 0x20;   // 8-bit auto-reload mode
    TH1 = -counts; // Overflow value
    TL1 = TH1;     // Initialize timer
    TR1 = 1;       // Start Timer 1
}

/**
 * Initialize timer 2
 */
void initializeTimer2(void)
{
	TMR2CN = 0x00;  // Stop Timer 2 and clear TF2
	CKCON &= ~0x60;	// Timer 2 clocked based on T2XCLK
	TMR2RL = 0;     // Initialize reload value
	TMR2 = 0xffff;  // Set to reload immediately
	ET2 = 1;        // Enable Timer 2 interrupts
	TR2 = 1;        // Start Timer 2
}

/**
 * Initialize timer 3
 */
void initializeTimer3(unsigned int counts)
{
	TMR3CN = 0x00;    // 16-bit auto-reload, low-byte interrupt disabled
	CKCON &= ~0x40;   // Timer3 clock source = SYSCLK / 12	
	TMR3RL = -counts; // Overflow value
    TMR3 = TMR3RL;    // Set to reload immediately 
    EIE1 |= 0x80;     // Timer3 interrupt enable   
    TMR3CN |= 0x04;   // Start Timer3            
}
