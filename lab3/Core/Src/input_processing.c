/*
 * input_processing.c
 *
 *  Created on: Oct 2, 2025
 *      Author: khanh
 */

#include "input_processing.h"

#define NO 2
#define NO_BUTTONS 3
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

enum STATE { RELEASED, PRESSED, PRESSED_MORE_THAN_1_SECOND};

enum MODE {	MODE_1_NORMAL, MODE_2_RED_MODIFY, MODE_3_AMBER_MODIFY, MODE_4_GREEN_MODIFY};

static enum MODE currMode = MODE_1_NORMAL;
static enum STATE prevState[NO_BUTTONS] = {RELEASED, RELEASED, RELEASED};
static enum STATE currState[NO_BUTTONS] = {RELEASED, RELEASED, RELEASED};

void fsm_for_input_processing(void){
	for (int i = 0; i < NO_BUTTONS; i++)
	{
		if (is_buttons_pressed(i) == BUTTON_IS_PRESSED){
			prevState[i] = currState[i];
			currState[i] = PRESSED;
		}else
		{
			prevState[i] = currState[i];
			currState[i] = RELEASED;
		}
	}
	switch (currMode){
	case MODE_1_NORMAL:
		if (currState[0] == PRESSED && prevState[0] == RELEASED){
			currMode = MODE_2_RED_MODIFY;
		}
		 break;

	case MODE_2_RED_MODIFY:
		if (currState[0] == PRESSED && prevState[0] == RELEASED){

			currMode = MODE_3_AMBER_MODIFY;
		}
		break;

	case MODE_3_AMBER_MODIFY:
		if (currState[0] == PRESSED && prevState[0] == RELEASED){
			currMode = MODE_4_GREEN_MODIFY;
		}
		break;

	case MODE_4_GREEN_MODIFY:
		if (currState[0] == PRESSED && prevState[0] == RELEASED){
			currMode = MODE_1_NORMAL;
		}
		break;
	default:
		break;
	}
}
