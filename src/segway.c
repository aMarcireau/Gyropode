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
#define SYS_CLOCK 24500000
#define SMB_FREQUENCY 100000
sbit SDA = P0 ^ 0;
sbit SCL = P0 ^ 1;
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
	initialize();

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
	initializeSystemClock();
	initializePorts();
	initializeUart();
	initializeMotors();
	initializeSMBus();
	initializeGY80();

	initializeTimer1(10000);
	initializeTimer2();
	initializeTimer3(SYSCLK / 12 / 40);
	EA = 1;
}

void timer2Interrupt(void) interrupt 5
{
	TF2H = 0;
	LED = ~LED;
	printf("%d", LED);
}
