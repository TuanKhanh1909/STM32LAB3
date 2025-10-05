/*
 * global.h
 *
 *  Created on: Oct 1, 2025
 *      Author: khanh
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <input_reading.h>
#include "main.h"
#include "software_timer.h"
#include "define.h"
#include "display_mode.h"
#include "input_processing.h"
#include "update_traffic_light.h"

enum MODE {	MODE_1_NORMAL, MODE_2_RED_MODIFY, MODE_3_AMBER_MODIFY, MODE_4_GREEN_MODIFY};
enum TRAFFIC_STATE   {RED_GREEN, RED_AMBER, GREEN_RED, AMBER_RED};

extern enum MODE currMode;
extern enum TRAFFIC_STATE traffic_state;

extern int time_red;
extern int time_amber;
extern int time_green;

extern int time_counter_road1;
extern int time_counter_road2;

void fsm_for_input_processing(void);
void updateTrafficLight(void);
void startNormalMode(void);

#endif /* INC_GLOBAL_H_ */
