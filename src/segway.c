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
#include "pid.h"

/**
 * Constants
 */
#define TARGET_ANGLE 0
sbit LED = P3 ^ 3;
sbit SW2 = P0 ^ 7;

/**
 * Definitions
 */
bit timer2Flag;
int accelerations[3];
int rotations[3];

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
		if (!SW2) {
			LED = 1;
			initializePid();
		} else if (timer2Flag) {
			timer2Flag = 0;
			LED = ~LED;
			getAccelerations(accelerations);
			getRotations(rotations);
			setMotorsSpeed(pidTransferFunction(
				accelerations[1], 
				rotations[2], 
				TARGET_ANGLE
			));
		}
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
	timer2Flag = 0;
	EA = 1;
	initializeGy80();
	initializePid();
}

void timer2InterruptServiceRoutine(void) interrupt INTERRUPT_TIMER2
{
	TF2H = 0;
	timer2Flag = 1;
}
