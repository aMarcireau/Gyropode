#ifndef __SEGWAY__GY_80__
#define __SEGWAY__GY_80__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#include "smBus.h"
#include "timers.h"

#define GYROSCOPE_ADDRESS 0x69;
#define ACCELEROMETER_ADDRESS 0x53;

void initializeGY80(void); // Initialize GY80

#endif // __SEGWAY__GY_80__
