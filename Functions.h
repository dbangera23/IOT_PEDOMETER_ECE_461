/*
 * Functions.h
 *
 *  Created on: Apr 25, 2016
 *      Author: Dean
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "stdbool.h"
#include <grlib.h>
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>

Graphics_Context g_sContext;
void GoalSet(void);
void StepCount(void);
void Monitor_Init(void);
void Init_ADC(void);
void ButtonInit(void);
void writeGoals(void);
void writeSteps(void);
void writeRecordState(void);
int readSteps(void);
int readGoals(void);
_Bool readRecordState(void);
void initMemory(void);

#endif /* FUNCTIONS_H_ */
