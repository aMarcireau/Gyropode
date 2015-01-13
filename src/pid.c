#include "pid.h"

/**
 * Definitions
 */
int accelerometerSpeed;
int accelerometerPosition;
int gyroscopePosition;
int measuredGyroscopePosition;
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
    speed = 0;    
}

/**
 * PID transfer function
 */
char pidTransferFunction(int accelerometerAcceleration, int gyroscopeSpeed, int angleTarget) {
	int newMeasuredGyroscopePosition;
	
	accelerometerSpeed = integrate(accelerometerSpeed, accelerometerAcceleration);
	accelerometerPosition = lowPassFilter(accelerometerPosition, integrate(accelerometerPosition, accelerometerSpeed));

	newMeasuredGyroscopePosition = integrate(gyroscopePosition, gyroscopeSpeed);
	gyroscopePosition = highPassFilter(gyroscopePosition, difference(measuredGyroscopePosition, newMeasuredGyroscopePosition));
	measuredGyroscopePosition = newMeasuredGyroscopePosition;

	speed = (int)((float)integrate(
		speed,
		checkOverflow(
			(int)((float)segment(accelerometerPosition, gyroscopePosition, ACCELEROMETER_GYROSCOPE_RATIO) * (float)KP) + 
			(int)((float)segment(accelerometerSpeed, gyroscopeSpeed, ACCELEROMETER_GYROSCOPE_RATIO) * (float)KD)
		)
	) * (float)KI);
	
	return speedFilter(speed);
}
