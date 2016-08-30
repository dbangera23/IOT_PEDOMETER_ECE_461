/*
 * memory.h
 *
 *  Created on: Apr 26, 2016
 *      Author: Dean
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "Functions.h"
#include "string.h"
extern volatile int goal;
extern volatile int steps;
extern volatile _Bool PedometerStatus;
#define MEMORY_START 0x0003F000
#endif /* MEMORY_H_ */
