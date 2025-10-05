/*
 * update_traffic_light.c
 *
 *  Created on: Oct 3, 2025
 *      Author: khanh
 */

#include "update_traffic_light.h"



void updateTrafficLight(){
	displayLED7SEG_MODE(1);
	switch (traffic_state){
	case RED_GREEN:
		 displayLED_RED(1, 0);
		 displayLED_GREEN(1, 1);

		 displayLED_GREEN(0, 0);
		 displayLED_YELLOW(0, 0);
		 displayLED_YELLOW(0, 1);
		 displayLED_RED(0, 1);

		 displayLED7SEG_LEFT(time_counter_road1);
		 displayLED7SEG_TOP(time_counter_road2);

		 if(isTimerExpired(TIMER_TRAFFIC) == 1){
			 traffic_state = RED_AMBER;
			 time_counter_road2 = time_amber/1000;
			 setTimer(TIMER_TRAFFIC, time_amber);
		 }
		 break;

	case RED_AMBER:
		 displayLED_RED(1, 0);
		 displayLED_YELLOW(1, 1);

	     displayLED_GREEN(0, 0);
		 displayLED_YELLOW(0, 0);
		 displayLED_GREEN(0, 1);
		 displayLED_RED(0, 1);

		 displayLED7SEG_LEFT(time_counter_road1);
		 displayLED7SEG_TOP(time_counter_road2);

		 if(isTimerExpired(TIMER_TRAFFIC) == 1){
			 traffic_state = GREEN_RED;
			 time_counter_road1 = time_green / 1000;
			 time_counter_road2 = time_red / 1000;
			 setTimer(TIMER_TRAFFIC, time_green);
		 }
		 break;

	case GREEN_RED:
		  displayLED_RED(1, 1);
		  displayLED_GREEN(1, 0);

		  displayLED_GREEN(0, 1);
		  displayLED_YELLOW(0, 0);
		  displayLED_YELLOW(0, 1);
		  displayLED_RED(0, 0);


		  displayLED7SEG_LEFT(time_counter_road1);
		  displayLED7SEG_TOP(time_counter_road2);

		  if(isTimerExpired(TIMER_TRAFFIC) == 1){
			  traffic_state = AMBER_RED;
			  time_counter_road1 = time_amber / 1000;
			  setTimer(TIMER_TRAFFIC, time_amber);
		  }
		  break;

	case AMBER_RED:
		 displayLED_YELLOW(1, 0);
		 displayLED_RED(1, 1);

		 displayLED_GREEN(0, 1);
		 displayLED_GREEN(0, 0);
		 displayLED_YELLOW(0, 1);
		 displayLED_RED(0, 0);

		 displayLED7SEG_LEFT(time_counter_road1);
		 displayLED7SEG_TOP(time_counter_road2);

		 if (isTimerExpired(TIMER_TRAFFIC) == 1){
			 traffic_state = RED_GREEN;
			 time_counter_road1 = time_red / 1000;
			 time_counter_road2 = time_green / 1000;
			 setTimer(TIMER_TRAFFIC, time_green);
		 }
		 break;
	}
}
