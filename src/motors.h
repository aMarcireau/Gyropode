#ifndef __SEGWAY__MOTORS__
#define __SEGWAY__MOTORS__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#define SPEED_MAX 1500
#define SPEED_MIN -1500
#define SPEED_NULL 62464

void initializeMotors(void); 						   // Initialize motors
void setMotorsSpeed(int speed);				           // Set motors speed
void setMotorSpeed(unsigned char motorId, int speed);  // Set motor speed
int filterSpeed(int);								   // Filter speed

#endif // __SEGWAY__MOTORS__
