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
	initialize(void);

	while (1) {
		setMotorsSpeed(-6);
	}
}

/**
 * Function definitions
 */
void initialize(void)
{
	PCA0MD &= ~0x40;
	initializeSystemClock(void);
	initializePorts(void);
	initializeUart(void);
	initializeMotors(void);
	initializeGY80(void);

	initializeTimer2(void);
	EA = 1;
}

void timer2Interrupt(void) interrupt 5
{
	TF2H = 0;
	LED = ~LED;
	printf("%d", LED);
}
