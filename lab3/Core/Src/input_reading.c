/*
 * input_processing.c
 *
 *  Created on: Sep 30, 2025
 *      Author: khanh
 */
#include <input_reading.h>
#include "main.h"

//we aim to work with more than one buttons
#define NO_OF_BUTTONS 3
#define BUTTON_PIN_0	GPIO_PIN_9
#define BUTTON_PIN_1	GPIO_PIN_10
#define BUTTON_PIN_2	GPIO_PIN_11
//timer interrupt duration is 10ms, so to pass 1 second,
//we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_AUTO_INCREASING 100
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET
//the buffer that the final result is stored after
//debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
//we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] =
		{BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] =
		{BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
uint16_t arrayPIN[NO_OF_BUTTONS] = {
		BUTTON_PIN_0, BUTTON_PIN_1, BUTTON_PIN_2};
//we define a flag for a button pressed more than 1 second.
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
//we define counter for automatically increasing the value
//after the button is pressed more than 1 second.
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
void button_reading(void){
	for(uint8_t i = 0; i < NO_OF_BUTTONS; i ++){
	debounceButtonBuffer2 [i] =debounceButtonBuffer1 [i];
	debounceButtonBuffer1 [i] = HAL_GPIO_ReadPin(GPIOA, arrayPIN[i]);
	if(debounceButtonBuffer1 [i] == debounceButtonBuffer2 [i])
		buttonBuffer [i] = debounceButtonBuffer1 [i];
	if(buttonBuffer [i] == BUTTON_IS_PRESSED){
		//if a button is pressed, we start counting
		if(counterForButtonPress1s [i] < DURATION_FOR_AUTO_INCREASING){
			counterForButtonPress1s [i]++;
		} else {
			//the flag is turned on when 1 second has passed
			//since the button is pressed.
			flagForButtonPress1s [i] = 1;
		}
	} else {
		counterForButtonPress1s [i] = 0;
		flagForButtonPress1s [i] = 0;
	}
  }
}

unsigned char 	is_button_pressed(uint8_t index){
	if (index >= NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s (unsigned char index){
	if (index >= NO_OF_BUTTONS)	return 0xff;
	return (flagForButtonPress1s[index] == 1);
}











