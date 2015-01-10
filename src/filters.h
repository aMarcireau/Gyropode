#ifndef __SEGWAY__FILTERS__
#define __SEGWAY__FILTERS__

#include <compiler_defs.h>
#include <C8051f310_defs.h>
#include <limits.h>

#define LOW_PASS_SMOOTH_FACTOR 0.02
#define HIGH_PASS_SMOOTH_FACTOR 0.02
#define TIME_CONSTANT 1

int difference(int previousState, int newState);             // Difference
int lowPassFilter(int previousState, int currentValue);	     // Low-pass filter
int highPassFilter(int previousState, int currentVariation); // High-pass filter
int differentiate(int previousState, int currentState);      // Discrete differentiate
int integrate(int previousState, int currentVariation);      // Discrete integrate
int checkOverflow(long value);								 // Prevent int overflow
int segment(int firstValue, int secondValue, float ratio);   // Segment

#endif // __SEGWAY__FILTERS__
