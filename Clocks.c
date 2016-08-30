#include "Clocks.h"
/*
 * Clocks.c
 *
 *  Created on: Apr 20, 2016
 *      Author: Dean
 */

//////////////////////
// Function name: Init_Clocks
// input: None
// output: None
// Description: Set up clocks for the system
// Steps:
// 1 - DCO Clock at 48Mhz
// 2 - Init MCLK, HSMCLK, SMCLK, ACLK
//////////////////////
void init_Clocks(void){
	/* Initializes Clock System */
	MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
	MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
	MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_128);
	MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
	MAP_CS_initClockSignal(CS_ACLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

}
