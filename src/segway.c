/**
 * Includes
 */
#include <compiler_defs.h>
#include <C8051f310_defs.h>
#include <stdio.h>
#include "systemClock.h"
#include "ports.h"
#include "motors.h"
#include "smBus.h"
#include "gy80.h"
#include "timers.h"

/**
 * Constants
 */
sbit LED = P3 ^ 3;
sbit SW2 = P0 ^ 7;

/**
 * Function prototypes
 */
void initialize(void);

/**
 * Main
 */
void main(void)
{
	int accelerations[3];
	initialize();

	while (1) {
		getAccelerations(accelerations);

		setMotorsSpeed(-6);
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
	initializeMotors();
	initializeSmBus();
	initializeTimer2();

	EA = 1;

	initializeGy80();
}

void timer2InterruptServiceRoutine(void) interrupt INTERRUPT_TIMER2
{
	TF2H = 0;
	LED = ~LED;
}
