/*
 * input_processing.c
 *
 *  Created on: Oct 2, 2025
 *      Author: khanh
 */

#include "input_processing.h"

#define NO_BUTTONS 3
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

enum STATE { RELEASED, PRESSED, PRESSED_MORE_THAN_1_SECOND};

enum TRAFFIC_STATE traffic_state = RED_GREEN;
enum MODE currMode = MODE_1_NORMAL;

static enum STATE prevState[NO_BUTTONS] = {RELEASED, RELEASED, RELEASED};
static enum STATE currState[NO_BUTTONS] = {RELEASED, RELEASED, RELEASED};

int time_red = 5000;
int time_amber = 2000;
int time_green = 3000;
int temp_value= 0;

int time_counter_road1 = 0;
int time_counter_road2 = 0;

void startNormalMode(){
	currMode = MODE_1_NORMAL;
	traffic_state = RED_GREEN;
	time_counter_road1 = time_red / 1000;
	time_counter_road2 = time_green / 1000;

	setTimer(TIMER_TRAFFIC, time_green);
	setTimer(TIMER_1S_COUNTDOWN, 1000);
}

void fsm_for_input_processing(void){
	for (int i = 0; i < NO_BUTTONS; i++)
	{

		if (is_button_pressed(i) == BUTTON_IS_PRESSED){
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
			if (isTimerExpired(TIMER_1S_COUNTDOWN) == 1){
				time_counter_road1--;
				time_counter_road2--;
				setTimer(TIMER_1S_COUNTDOWN, 1000);
			}
			updateTrafficLight();

		if (currState[0] == PRESSED && prevState[0] == RELEASED){
			displayLED_GREEN(0, 0);
			displayLED_GREEN(0, 1);
			displayLED_RED(0, 0);
			displayLED_RED(0, 1);
			displayLED_YELLOW(0, 0);
			displayLED_YELLOW(0, 1);
			temp_value = time_red/1000;
			setTimer(TIMER_MODE_LED, 250);
			currMode = MODE_2_RED_MODIFY;
		}
		 break;

	case MODE_2_RED_MODIFY:

		if (isTimerExpired(TIMER_MODE_LED) == 1){
			HAL_GPIO_TogglePin(PORTYPE_A, PIN_RED_1);
			HAL_GPIO_TogglePin(PORTYPE_A,PIN_RED_2);
			setTimer(TIMER_MODE_LED, 250);
			}
			displayLED7SEG_MODE(2);
			displayLED7SEG_LEFT(temp_value);
			if (currState[1] == PRESSED && prevState[1] == RELEASED){
				temp_value++;
				if (temp_value > 99){
					temp_value = 1;
				}
			}
			if(currState[2] == PRESSED && prevState[2] == RELEASED){
				time_red = temp_value * 1000;
				time_green += ((temp_value * 1000) - 5000);
				displayLED_RED(0, 0);
				displayLED_RED(0, 1);
				startNormalMode();
			}


		if (currState[0] == PRESSED && prevState[0] == RELEASED){
			temp_value = time_amber/1000;
			displayLED_RED(0, 0);
			displayLED_RED(0, 1);
			setTimer(TIMER_MODE_LED, 250);
			currMode = MODE_3_AMBER_MODIFY;
		}
		break;

	case MODE_3_AMBER_MODIFY:

		if (isTimerExpired(TIMER_MODE_LED) == 1){
			HAL_GPIO_TogglePin(PORTYPE_A, PIN_YELLOW_1);
			HAL_GPIO_TogglePin(PORTYPE_A, PIN_YELLOW_2);
			setTimer(TIMER_MODE_LED, 250);
		}

		displayLED7SEG_MODE(3);
		displayLED7SEG_LEFT(temp_value);

		if (currState[1] == PRESSED && prevState[1] == RELEASED){
				temp_value++;
				if (temp_value > 99){
					temp_value = 1;
				}
			}

		if(currState[2] == PRESSED && prevState[2] == RELEASED){
			time_amber = temp_value*1000;
			time_red += ((temp_value *1000) - 2000);
			displayLED_YELLOW(0, 0);
			displayLED_YELLOW(0, 1);
			startNormalMode();
		}

		if (currState[0] == PRESSED && prevState[0] == RELEASED){
			temp_value = time_green /1000;
			displayLED_YELLOW(0, 0);
				displayLED_YELLOW(0, 1);
			setTimer(TIMER_MODE_LED, 250);
			currMode = MODE_4_GREEN_MODIFY;
		}
		break;

	case MODE_4_GREEN_MODIFY:

		if(isTimerExpired(TIMER_MODE_LED) == 1){
			HAL_GPIO_TogglePin(PORTYPE_A, PIN_GREEN_1);
			HAL_GPIO_TogglePin(PORTYPE_A, PIN_GREEN_2);
			setTimer(TIMER_MODE_LED, 250);
		}

		displayLED7SEG_MODE(4);
		displayLED7SEG_LEFT(temp_value);

		if (currState[1] == PRESSED && prevState[1] == RELEASED){
				temp_value++;
				if (temp_value > 99){
					temp_value = 1;
				}
			}

		if (currState[2] == PRESSED && prevState[2] == RELEASED){
			time_green = temp_value * 1000;
			time_red += ((temp_value * 1000) - 3000);
			currMode = MODE_1_NORMAL;
			displayLED_GREEN(0, 0);
			displayLED_GREEN(0, 1);
		    startNormalMode();
		}


		if (currState[0] == PRESSED && prevState[0] == RELEASED){
			currMode = MODE_1_NORMAL;
			displayLED_GREEN(0, 0);
			displayLED_GREEN(0, 1);
		}
		break;
	default:
		break;
	}
}
