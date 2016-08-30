#include "memory.h"
/*
 * memory.c
 *
 *  Created on: Apr 26, 2016
 *      Author: Dean
 */

void initMemory(void){
	FlashCtl_setWaitState(FLASH_BANK1, 2);
	steps = readSteps();
	goal = readGoals();
	PedometerStatus = readRecordState();
	if(steps == 0xFFFFFFFF || steps<0){
		steps = 0;
		writeSteps();
	}
	if(goal == 0xFFFFFFFF || goal<0){
		goal = 0;
		writeGoals();
	}
	if(PedometerStatus == 0xFF){
		PedometerStatus = false;
		writeRecordState();
	}
	if(PedometerStatus){
		ADC14_enableConversion();
		ADC14_toggleConversionTrigger();
		Graphics_drawString(&g_sContext,"ON ",AUTO_STRING_LENGTH,35,20,OPAQUE_TEXT);
	}else{
		Graphics_drawString(&g_sContext,"OFF",AUTO_STRING_LENGTH,35,20,OPAQUE_TEXT);
	}
	char string[12];
	sprintf(string, "Goal: %5d", goal);
	Graphics_drawStringCentered(&g_sContext,(int8_t *)string,11,64,70,OPAQUE_TEXT);
	Graphics_drawString(&g_sContext,"Set     ",11,34,55,OPAQUE_TEXT);
	sprintf(string, "Steps: %5d", steps);
	Graphics_drawStringCentered(&g_sContext,(int8_t *)string,12,64,80,OPAQUE_TEXT);
	int percent = (100 * steps) / goal;
	sprintf(string, "Percent: %2d%%", percent);
	Graphics_drawStringCentered(&g_sContext,(int8_t *)string,12,64,90,OPAQUE_TEXT);
}

void writeSteps(void){
	uint8_t simulatedCalibrationData[4];
	memset(simulatedCalibrationData, steps, 4);
	MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR31);
	//int* addr_ptr = (int*)MEMORY_START;
	//*addr_ptr = steps;
	MAP_FlashCtl_programMemory((void*)simulatedCalibrationData,(void*) MEMORY_START, 4);
	MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR31);
}

int readSteps(void){
	int* addr_ptr = (int*)MEMORY_START;
	int data = *addr_ptr;
	return data;
}

void writeGoals(void){
	uint8_t simulatedCalibrationData[4];
	memset(simulatedCalibrationData, goal, 4);
	MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR30);
	MAP_FlashCtl_programMemory(simulatedCalibrationData,(void*) (MEMORY_START-0x1000), 4);
	MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR30);
}

int readGoals(void){
	int* addr_ptr = (int*)(MEMORY_START-0x1000);
	int data = *addr_ptr;
	return data;
}

void writeRecordState(void){
	uint8_t simulatedCalibrationData[1];
	memset(simulatedCalibrationData, PedometerStatus, 1);
	MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR29);
	MAP_FlashCtl_programMemory(simulatedCalibrationData,(void*) (MEMORY_START-0x1000*2), 1);
	MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR29);
}

_Bool readRecordState(void){
	_Bool* addr_ptr = (_Bool*)(MEMORY_START-0x1000*2);
	_Bool data = *addr_ptr;
	return data;
}
