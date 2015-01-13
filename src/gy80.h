#ifndef __SEGWAY__GY_80__
#define __SEGWAY__GY_80__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#include "smBus.h"

void initializeGy80(void);  // Initialize GY80
void getAccelerations(int accelerations[3]); // Get accelerations
void getRotations(int rotations[3]);         // Get rotations

#endif // __SEGWAY__GY_80__
