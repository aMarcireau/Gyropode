#ifndef __SEGWAY__PID__
#define __SEGWAY__PID__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#include "filters.h"
#include "motors.h"

#define KI 1
#define KD 1
#define KP 1
#define ACCELEROMETER_GYROSCOPE_RATIO 0.5

int pidTransferFunction(int currentAccelerometerAcceleration, int currentGyroscopeSpeed, int angleTarget); // PID transfer function
void initializePid(void);                                                                                  // Reset zero

#endif // __SEGWAY__PID__
