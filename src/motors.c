#include "motors.h"

/**
 * Initialize motors
 */
void initializeMotors()
{
	CR = 1;
	PCA0CPM0 = 0xc2;
	PCA0CP0 = -3062; // 1.5 ms
	PCA0CPH0 = 244;
	PCA0CPM1 = 0xc2;
	PCA0CP1 = -3062; // 1.5 ms
	PCA0CPH1 = 244;
}

/**
 * Set motor speed
 */
void setMotorSpeed(unsigned char motorId, char speed)
{
	if (motorId == 'r') {
		PCA0CPH0 = 244 + speed;
	} else if (motorId == 'l') {
		PCA0CPH1 = 244 + speed;
	}
}

/**
 * Set motors speed
 */
void setMotorsSpeed(char speed)
{
	setMotorSpeed('r', speed);
	setMotorSpeed('l', -speed);
}
