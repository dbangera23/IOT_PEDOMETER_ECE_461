#include "Buttons.h"
/*
 * Buttons.c
 *
 *  Created on: Apr 20, 2016
 *      Author: Dean
 */

//////////////////////
// Function name: ButtonInit
// input: None
// output: None
// Description: Set up buttons
// Steps:
// 1 - Set as button
// 2 - Enable interrupts
//////////////////////
void ButtonInit(void) {
	// Configuring P3.5 as an input for button press
	MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5);
	MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, GPIO_PIN5);
	MAP_GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);
	MAP_Interrupt_enableInterrupt(INT_PORT3);
}


void PORT3_IRQHandler(unsigned int index){
	MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, GPIO_PIN5);
	//Door button pressed. Handle debounce and turn on the buzzer
}
//////////////////////
// Function name: gpioButton0
// input: None
// output: None
// Description: button handler
// Steps:
//
//////////////////////
/*void PORT1_IRQHandler(unsigned int index) {
	uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
	MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

	// Toggling the output on the LED
	if(status & GPIO_PIN1){
		if(PedometerStatus){
			PedometerStatus = !PedometerStatus;
			ADC14_disableConversion();
			Graphics_drawString(&g_sContext,"OFF",AUTO_STRING_LENGTH,35,20,OPAQUE_TEXT);
			if(setting){
				setting = !setting;
				Graphics_drawString(&g_sContext,"Set     ",11,34,55,OPAQUE_TEXT);
			}
		}else{
			PedometerStatus = !PedometerStatus;
			ADC14_enableConversion();
			ADC14_toggleConversionTrigger();
			Graphics_drawString(&g_sContext,"ON ",AUTO_STRING_LENGTH,35,20,OPAQUE_TEXT);
		}
	}
	if(status & GPIO_PIN4){
		if(PedometerStatus){
			setting = !setting;
			if(setting)
				Graphics_drawString(&g_sContext,"Setting",8,34,55,OPAQUE_TEXT);
			else
				Graphics_drawString(&g_sContext,"Set     ",11,34,55,OPAQUE_TEXT);
		}
	}
}*/
