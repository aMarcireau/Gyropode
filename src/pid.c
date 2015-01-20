#include "pid.h"

/**
 * Definitions
 */
int accelerometerSpeed;
int accelerometerPosition;
int gyroscopeAngle;
int error;
int integratedError;
int resetCounter;

/**
 * Initialize PID
 */
void initializePid(void)
{
	resetMeasure();
    error = 0;
    integratedError = 0;

}

/**
 * Reset measure
 */
void resetMeasure(void)
{
    accelerometerSpeed = 0;
    accelerometerPosition = 0;
    gyroscopeAngle = 0;
    resetCounter = 0;
}


/**
 * Get error (command - measured)
 */
int getError(int accelerometerAcceleration, int gyroscopeSpeed, int angleTarget) {
	resetCounter++;
	if (resetCounter >= RESET_VALUE) {
		resetMeasure();
	}

	accelerometerSpeed = integrate(accelerometerSpeed, accelerometerAcceleration);
	accelerometerPosition = integrate(accelerometerPosition, accelerometerSpeed);
	gyroscopeAngle = integrate(gyroscopeAngle, gyroscopeSpeed);

	return difference(angleTarget, segment(
		(int)((float)POSITION_TO_ANGLE * (float)accelerometerPosition), 
		gyroscopeAngle,
		ACCELEROMETER_GYROSCOPE_RATIO
	));
}

/**
 * PID transfer function
 */
int pidTransferFunction(int newError) {
	int speed = filterSpeed(checkOverflow(
		(long)((float)KP * (float)newError) +
		(long)((float)KD * (float)differentiate(error, newError)) +
		(long)((float)KI * (float)integrate(integratedError, newError))
	));
	error = newError;

	return speed;
}
