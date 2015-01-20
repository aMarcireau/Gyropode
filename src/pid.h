#ifndef __SEGWAY__PID__
#define __SEGWAY__PID__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#include "filters.h"
#include "motors.h"

#define HEIGHT 0.1
#define KI 50
#define KP 50
#define KD 0
#define ACCELEROMETER_GYROSCOPE_RATIO 0.8
#define POSITION_TO_ANGLE 0.16
#define RESET_VALUE 20


int getError(
    int currentAccelerometerAcceleration, 
    int currentGyroscopeSpeed,
    int angleTarget
);                 		                  // Get error (command - measured)
int pidTransferFunction(int newError);    // PID transfer function
void initializePid(void);                 // Reset zero
void resetMeasure(void);				  // Reset measure

#endif // __SEGWAY__PID__
