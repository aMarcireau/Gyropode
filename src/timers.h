#ifndef __SEGWAY__TIMERS__
#define __SEGWAY__TIMERS__

#include <compiler_defs.h>
#include <C8051f310_defs.h>

void initializeTimer1(unsigned int counts); // Initialize timer 1
void initializeTimer2(void);				// Initialize timer 2

#endif // __SEGWAY__TIMERS__
