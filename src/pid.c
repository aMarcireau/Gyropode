#include "pid.h"

/**
 * Definitions
 */
int accelerometerSpeed;
int accelerometerPosition;
int gyroscopePosition;
int measuredGyroscopePosition;
int error;
int integratedError;
int speed;

/**
 * Reset zero
 */
void initializePid(void)
{
    accelerometerSpeed = 0;
    accelerometerPosition = 0;
    gyroscopePosition = 0;
    measuredGyroscopePosition = 0;
    error = 0;
    integratedError = 0;
}

/**
 * Get error (command - measured)
 */
int getError(int accelerometerAcceleration, int gyroscopeSpeed, int angleTarget) {
	int newMeasuredGyroscopePosition;

	accelerometerSpeed = integrate(accelerometerSpeed, accelerometerAcceleration);
	accelerometerPosition = lowPassFilter(accelerometerPosition, integrate(accelerometerPosition, accelerometerSpeed));

	newMeasuredGyroscopePosition = integrate(gyroscopePosition, gyroscopeSpeed);
	gyroscopePosition = highPassFilter(gyroscopePosition, difference(newMeasuredGyroscopePosition, measuredGyroscopePosition));
	measuredGyroscopePosition = newMeasuredGyroscopePosition;

	return difference(angleTarget, segment(
		checkOverflow(HEIGHT * accelerometerPosition), 
		gyroscopePosition, 
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
