/*
 * display_mode.h
 *
 *  Created on: Oct 2, 2025
 *      Author: khanh
 */

#ifndef INC_DISPLAY_MODE_H_
#define INC_DISPLAY_MODE_H_

#include "global.h"

void displayLED_YELLOW(int IS_ON, int index);
void displayLED_RED(int IS_ON, int index);
void displayLED_GREEN(int IS_ON, int index);
void displayLED7SEG_LEFT(int number);
void displayLED7SEG_TOP(int number);
void displayLED7SEG_MODE(int number);

#endif /* INC_DISPLAY_MODE_H_ */
