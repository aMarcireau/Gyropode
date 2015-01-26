#ifndef __SEGWAY__PID__
#define __SEGWAY__PID__

#include <compiler_defs.h>
#include <C8051f310_defs.h>
#include <stdio.h>

#include "filters.h"
#include "motors.h"

#define KI 10
#define KP 10
#define KD 10

int pidTransferFunction(int newError);    // PID transfer function
void initializePid(void);                 // Reset zero

#endif // __SEGWAY__PID__
