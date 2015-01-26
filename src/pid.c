#include "pid.h"

/**
 * Definitions
 */
int error;
int integratedError;
int resetCounter;

/**
 * Initialize PID
 */
void initializePid(void)
{
    error = 0;
    integratedError = 0;
}

/**
 * PID transfer function
 */
int pidTransferFunction(int newError) {
	int speed;

	integratedError = integrate(integratedError, newError);

	speed = filterSpeed(checkOverflow(
		(long)((float)KP * (float)newError) +
		(long)((float)KD * (float)differentiate(newError, error)) +
		(long)((float)KI * (float)integrate(integratedError, newError))
	));

	printf("new speed: %d, old speed: %d\r", newError, error);
	error = newError;

	return speed;
}
