#ifndef __SEGWAY__PID__
#define __SEGWAY__PID__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#include "filters.h"
#include "motors.h"

#define HEIGHT 0.1
#define KI 0
#define KD 0
#define KP 10
#define ACCELEROMETER_GYROSCOPE_RATIO 1

int pidTransferFunction(
    int currentAccelerometerAcceleration, 
    int currentGyroscopeSpeed, 
    int angleTarget
);                                        // PID transfer function
int getError(int newError)                // Get error (command - measured)
void initializePid(void);                 // Reset zero

#endif // __SEGWAY__PID__
