#ifndef __SEGWAY__MOTORS__
#define __SEGWAY__MOTORS__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#define SPEED_MAX 6
#define SPEED_MIN -6

void initializeMotors(void); 						   // Initialize motors
void setMotorsSpeed(char speed);				       // Set motors speed
void setMotorSpeed(unsigned char motorId, char speed); // Set motor speed
char speedFilter(int);								   // Filter speed

#endif // __SEGWAY__MOTORS__
