/*
 * Accelerometer.h
 *
 *  Created on: Apr 21, 2016
 *      Author: Dean
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "Functions.h"

#define THRESHOLD 8100

volatile int avg;
volatile int resultsBuffer;
volatile int lastAvg = -1;
volatile int StickMovement[2];
extern volatile _Bool setting;
extern volatile _Bool PedometerStatus;
volatile int goal = 0;
volatile int steps = 0;
volatile int Accelcount = 1;
extern volatile int publishGoalReached;

#endif /* ACCELEROMETER_H_ */
