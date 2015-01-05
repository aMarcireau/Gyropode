#ifndef __SEGWAY__GY_80__
#define __SEGWAY__GY_80__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

#include "smBus.h"
#include "timers.h"

#define SYS_CLOCK 24500000
#define SMB_FREQUENCY 100000
#define ACCELEROMETER_ADDRESS 0x53; // ADXL345 
#define GYROSCOPE_ADDRESS 0x69;     // L3G4200D

void initializeGY80(void);  // Initialize GY80
int getXAcceleration(void); // Get X acceleration
int getYAcceleration(void); // Get Y acceleration
int getZAcceleration(void); // Get Z acceleration



#endif // __SEGWAY__GY_80__
