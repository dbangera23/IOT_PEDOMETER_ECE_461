#include "Accelerometer.h"
/*
 * Accelerometer.c
 *
 *  Created on: Apr 21, 2016
 *      Author: Dean
 */
void Init_ADC(void) {
	/* Configures Pin 6.0 and 4.4 as ADC input */
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
	// Configures Pin 4.0, 4.2, and 6.1 as ADC input
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
			GPIO_PIN0 | GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1,
			GPIO_TERTIARY_MODULE_FUNCTION);
	/* Initializing ADC (ADCOSC/64/8) */
	MAP_ADC14_enableModule();
	MAP_ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);

	/* Configuring ADC Memory (ADC_MEM0 - ADC_MEM1 (A15, A9)  with repeat)
	 * with internal 2.5v reference */
	MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM2, true);

	MAP_ADC14_configureConversionMemory(ADC_MEM0,
			ADC_VREFPOS_AVCC_VREFNEG_VSS,
			ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

	MAP_ADC14_configureConversionMemory(ADC_MEM1,
			ADC_VREFPOS_AVCC_VREFNEG_VSS,
			ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

	MAP_ADC14_configureConversionMemory(ADC_MEM2,
			ADC_VREFPOS_AVCC_VREFNEG_VSS,
			ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);
	/* Enabling the interrupt when a conversion on channel 1 (end of sequence)
	 *  is complete and enabling conversions */
	MAP_ADC14_enableInterrupt(ADC_INT1);
	MAP_ADC14_enableInterrupt(ADC_INT2);
	/* Enabling Interrupts */
	MAP_Interrupt_enableInterrupt(INT_ADC14);
	MAP_Interrupt_enableMaster();
	/* Setting up the sample timer to automatically step through the sequence
	 * convert.
	 */
	MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
	/* Triggering the start of the sample */
}

void ADC14_IRQHandler(void) {
	uint64_t status;
	status = MAP_ADC14_getEnabledInterruptStatus();

	// ADC_MEM2 conversion completed
	if ((status & ADC_INT2) && PedometerStatus) {
		// Store ADC14 conversion results
		resultsBuffer = ADC14_getResult(ADC_MEM2);
		StepCount();
	}
	/* ADC_MEM1 conversion completed */
	if(status & ADC_INT1){
		/* Store ADC14 conversion results */
		if(setting){
			StickMovement[0] = ADC14_getResult(ADC_MEM0);
			StickMovement[1] = ADC14_getResult(ADC_MEM1);
			if(StickMovement[1]>16000){
				goal++;
				GoalSet();
			}else{
				if(StickMovement[1]<1000){
					goal--;
					if(goal<0)
						goal = 0;
					GoalSet();
				}
			}
		}
	}
	MAP_ADC14_clearInterruptFlag(status);

}

void StepCount(void){
	if (lastAvg == -1) {
		lastAvg = resultsBuffer;
		avg = resultsBuffer;
	}else{
		avg = (avg * Accelcount + resultsBuffer)/(Accelcount + 1);
		Accelcount++;
	}
	if(Accelcount == 50){
//		char string[12];
//		sprintf(string, " %d ", avg);
//		Graphics_drawStringCentered(&g_sContext,(int8_t *)string,12,40,80,OPAQUE_TEXT);
		Accelcount = 1;
		if (avg < THRESHOLD && lastAvg > THRESHOLD) {
			// the board should be positioned in front of the user with the
			// screen oriented straight from their perspective
			steps++;
			writeSteps();
			char string[12];
			sprintf(string, "Steps: %5d", steps);
			Graphics_drawStringCentered(&g_sContext,(int8_t *)string,12,64,80,OPAQUE_TEXT);
			int percent = (100 * steps) / goal;
			sprintf(string, "Percent: %2d%%", percent);
			Graphics_drawStringCentered(&g_sContext,(int8_t *)string,12,64,90,OPAQUE_TEXT);
			if((steps>=goal) && (goal!=0)) {
				Graphics_drawString(&g_sContext,"Goal Completed!",15,15,40,OPAQUE_TEXT);
				publishGoalReached = 1;
			}
			else
				Graphics_drawString(&g_sContext,"               ",15,15,40,OPAQUE_TEXT);
		}
		lastAvg = avg;
		avg = resultsBuffer;
	}
}

void GoalSet(void){
	writeGoals();
	char string[12];
	sprintf(string, "Goal: %5d", goal);
	Graphics_drawStringCentered(&g_sContext,(int8_t *)string,11,64,70,OPAQUE_TEXT);
	int percent = (100 * steps) / goal;
	sprintf(string, "Percent: %2d%%", percent);
	Graphics_drawStringCentered(&g_sContext,(int8_t *)string,12,64,90,OPAQUE_TEXT);
	if((steps>=goal) && (goal!=0)) {
		Graphics_drawString(&g_sContext,"Goal Completed!",15,15,40,OPAQUE_TEXT);
		publishGoalReached = 1;
	} else
		Graphics_drawString(&g_sContext,"               ",15,15,40,OPAQUE_TEXT);
}
