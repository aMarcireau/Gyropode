/**
 * Includes
 */
#include <compiler_defs.h>
#include <C8051f310_defs.h>
#include <stdio.h>
#include "systemClock.h"
#include "ports.h"
#include "uart.h"
#include "timers.h"
#include "PCA.h"


/**
 * Constants
 */
sbit LED = P3 ^ 3; // LED = '1' means ON
sbit SW2 = P0 ^ 7; // SW2 = '0' means switch pressed


/**
 * Function prototypes
 */
void initialize(void);      // Initialize
void timer2Interrupt(void); // Timer 2 interrupt


/**
 * Main
 */
void main(void) {
	initialize();

	while (1) 
	{
		PCA0CPH0 = 250;
	  	PCA0CPH1 = 238;
	}
}


/**
 * Function definitions
 */

// Initialize
void initialize(void) {
	initializeSystemClock();
	initializePorts();
	initializeUart();
	initializeTimer2(0);
	initializePCA();
	EA = 1;
}

// Timer 2 interrupt
void timer2Interrupt(void) interrupt 5
{
	TF2H = 0;
	LED = ~LED;
}
