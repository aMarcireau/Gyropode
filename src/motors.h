#ifndef __SEGWAY__PCA__
#define __SEGWAY__PCA__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

void initializeMotors(void); 						  // Initialize motors
void setMotorsSpeed(int speed);					      // Set motors speed
void setMotorSpeed(unsigned char motorId, int speed); // Set motor speed

#endif // __SEGWAY__PCA__
