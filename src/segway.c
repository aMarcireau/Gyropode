/**
 * Includes
 */
#include <compiler_defs.h>
#include <C8051f310_defs.h>
#include <stdio.h>
#include "systemClock.h"
#include "ports.h"
#include "uart.h"
#include "motors.h"
#include "timers.h"


/**
 * Constants
 */
sbit LED = P3 ^ 3; // LED = '1' means ON
sbit SW2 = P0 ^ 7; // SW2 = '0' means switch pressed


/**
 * Function prototypes
 */
void initialize(void);


/**
 * Main
 */
void main(void)
{
	initialize();

	while (1) {
		setMotorsSpeed(6);
	}
}


/**
 * Function definitions
 */
void initialize(void)
{
	PCA0MD &= ~0x40;
	initializeSystemClock();
	initializePorts();
	initializeUart();
	initializeMotors();
	initializeTimer2(25000);
	EA = 1;
}

void timer2Interrupt(void) interrupt 5
{
	TF2H = 0;
	LED = ~LED;
	printf("%d", LED);
}
