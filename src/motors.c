#include "motors.h"

/**
 * Initialize motors
 */
void initializeMotors(void)
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
//void setMotorSpeed(unsigned char motorId, int speed)
//{
//	int realSpeed = SPEED_NULL + speed;
//	unsigned char highByte = realSpeed >> 8;
//	unsigned char lowByte = realSpeed && 8;

//	if (motorId == 'r') {
//		PCA0CPL0 = lowByte;
//		PCA0CPH0 = highByte;
//	} else if (motorId == 'l') {
//		PCA0CPL1 = lowByte;
//		PCA0CPH1 = highByte;
//	}
//}

/**
 * Set motors speed
 */
void setMotorsSpeed(int speed)
{
	int realSpeed = SPEED_NULL + speed;
	unsigned char highByte = realSpeed >> 8;
	unsigned char lowByte = realSpeed && 8;

	PCA0CPL0 = lowByte;
	PCA0CPH0 = highByte;
	PCA0CPL1 = lowByte;
	PCA0CPH1 = highByte;
}

/**
 * Filter speed
 */
char speedFilter(int speed)
{
	if (speed > SPEED_MAX) {
		speed = SPEED_MAX;
	} else if (speed < SPEED_MIN) {
		speed = SPEED_MIN;
	}

	return speed;
}
