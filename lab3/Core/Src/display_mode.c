/*
 * display_mode.c
 *
 *  Created on: Oct 2, 2025
 *      Author: khanh
 */

#include "display_mode.h"

void displayLED_YELLOW(int IS_ON, int index){
	switch (index){
	case 0:
		if (IS_ON == 1) HAL_GPIO_WritePin(PORTYPE_A, PIN_YELLOW_1, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(PORTYPE_A, PIN_YELLOW_1, GPIO_PIN_SET);
		break;

	case 1:
		if (IS_ON == 1) HAL_GPIO_WritePin(PORTYPE_A, PIN_YELLOW_2,GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(PORTYPE_A, PIN_YELLOW_2, GPIO_PIN_SET);
		break;
	}
}

void displayLED_RED(int IS_ON, int index){
	switch (index){
	case 0:
		if (IS_ON == 1) HAL_GPIO_WritePin(PORTYPE_A, PIN_RED_1, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(PORTYPE_A, PIN_RED_1, GPIO_PIN_SET);
		break;

	case 1:
		if (IS_ON == 1) HAL_GPIO_WritePin(PORTYPE_A, PIN_RED_2, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(PORTYPE_A, PIN_RED_2, GPIO_PIN_SET);
		break;
	}
}

void displayLED_GREEN(int IS_ON, int index){
	switch (index){
	case 0:
		if (IS_ON == 1) HAL_GPIO_WritePin(PORTYPE_A, PIN_GREEN_1, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(PORTYPE_A, PIN_GREEN_1, GPIO_PIN_SET);
		break;

	case 1:
		if (IS_ON == 1) HAL_GPIO_WritePin(PORTYPE_A, PIN_GREEN_2, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(PORTYPE_A, PIN_GREEN_2, GPIO_PIN_SET);
		break;
	}
}

void displayLED7SEG_LEFT(int number){
	int chuc = number /10;
	int don_vi = number %10;

	 // Xuất BCD cho chữ số HÀNG CHỤC (ra IC U4)
	    HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG1_0, (don_vi >> 0) & 1); // Lấy bit 0
	    HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG1_1, (don_vi >> 1) & 1); // Lấy bit 1
	    HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG1_2, (don_vi >> 2) & 1); // Lấy bit 2
	    HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG1_3, (don_vi >> 3) & 1); // Lấy bit 3

	    // Xuất BCD cho chữ số HÀNG ĐƠN VỊ (ra IC U3)
	    HAL_GPIO_WritePin(PORTYPE_A, PIN_INP_SEG0_0, (chuc >> 0) & 1);
	    HAL_GPIO_WritePin(PORTYPE_A, PIN_INP_SEG0_1, (chuc >> 1) & 1);
	    HAL_GPIO_WritePin(PORTYPE_A, PIN_INP_SEG0_2, (chuc >> 2) & 1);
	    HAL_GPIO_WritePin(PORTYPE_A, PIN_INP_SEG0_3, (chuc >> 3) & 1);
}

void displayLED7SEG_TOP(int number){
	int chuc = number/10;
	int don_vi = number % 10;



	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG2_0, (chuc >> 0) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG2_1, (chuc >> 1) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG2_2, (chuc >> 2) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG2_3, (chuc >> 3) & 1);


	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG3_0, (don_vi >> 0) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG3_1, (don_vi >> 1) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG3_2, (don_vi >> 2) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG3_3, (don_vi >> 3) & 1);

}

void displayLED7SEG_MODE(int number){

	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG_MODE_0, (number >> 0) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG_MODE_1, (number >> 1) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG_MODE_2, (number >> 2) & 1);
	HAL_GPIO_WritePin(PORTYPE_B, PIN_INP_SEG_MODE_3, (number >> 3) & 1);
}







