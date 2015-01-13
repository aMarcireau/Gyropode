#include "filters.h"

/*
 * Difference
 */
int difference(int previousState, int newState)
{
	return checkOverflow((long)newState - (long)previousState);
}

/*
 * Low-pass filter
 */
int lowPassFilter(int previousState, int currentValue)
{
	return segment(currentValue, previousState, LOW_PASS_SMOOTH_FACTOR);
}

/*
 * High-pass filter
 */
int highPassFilter(int previousState, int currentVariation)
{
	return segment(previousState, currentVariation, HIGH_PASS_SMOOTH_FACTOR);
}

/**
 * Discrete differentiate
 */
int differentiate(int previousState, int currentState)
{
	return (currentState - previousState) / TIME_CONSTANT;
}

/**
 * Discrete integrate
 */
int integrate(int previousState, int currentVariation)
{
	return checkOverflow((long)previousState + (long)currentVariation * TIME_CONSTANT);
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
