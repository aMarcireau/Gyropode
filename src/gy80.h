#ifndef __SEGWAY__GY_80__
#define __SEGWAY__GY_80__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#include "smBus.h"
#include "timers.h"

#define SYSTEM_CLOCK 24500000
#define SM_BUS_FREQUENCY 100000

void initializeGy80(void);  // Initialize GY80
int getXAcceleration(void); // Get X acceleration
int getYAcceleration(void); // Get Y acceleration
int getZAcceleration(void); // Get Z acceleration



#endif // __SEGWAY__GY_80__
