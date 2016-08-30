#include "Monitor.h"
/*
 * Monitor.c
 *
 *  Created on: Apr 20, 2016
 *      Author: Dean
 */

//////////////////////
// Function name: Monitor_Init
// input: None
// output: None
// Description: initialize the LCD on the board
// Steps:
// 1 - call API functions for LCD
// 2 - set general settings
//////////////////////
void Monitor_Init(void) {
	// Initializes display
	Crystalfontz128x128_Init();
	Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

	// Initialize context
	Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128);
	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
	Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
	GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
	Graphics_clearDisplay(&g_sContext);
	Graphics_drawString(&g_sContext,"Monitoring:",AUTO_STRING_LENGTH,30,10,OPAQUE_TEXT);
}

