#include "filters.h"

/*
 * Difference
 */
int difference(int newState, int previousState)
{
	return checkOverflow((long)newState - (long)previousState);
}

/**
 * Discrete differentiate
 */
int differentiate(int previousState, int currentState)
{
	return checkOverflow((long)((float)difference(currentState, previousState) / (float)TIME_CONSTANT));
}

/**
 * Discrete integrate
 */
int integrate(int previousState, int currentVariation)
{
	return checkOverflow((long)previousState + (long)((float)currentVariation * (float)TIME_CONSTANT));
}

/**
 * Prevent int overflow
 */
int checkOverflow(long value)
{
	if (value > (long)INT_MAX) {
		value = (long)INT_MAX;
	} else if (value < (long)INT_MIN) {
		value = (long)INT_MIN;
	}	

	return (int)value;
}

/**
 * Segment
 */
int segment(int firstValue, int secondValue, float ratio)
{
	return (int)((float)firstValue * ratio + (float)secondValue * (1.0 - ratio));
}
