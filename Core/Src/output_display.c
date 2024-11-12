/*
 * output_display.c
 *
 *  Created on: Oct 28, 2024
 *      Author: Bach
 */

#include "output_display.h"

// phần led 7 đoạn
void display7SEG(uint8_t counter){
	switch (counter){
		case 0:
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin |
							  SEG4_Pin | SEG5_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG6_Pin , GPIO_PIN_SET);
			break;

		case 1:
			HAL_GPIO_WritePin(GPIOB , SEG1_Pin | SEG2_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin , GPIO_PIN_SET);
			break;

		case 2:
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG1_Pin | SEG3_Pin | SEG4_Pin | SEG6_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG2_Pin | SEG5_Pin , GPIO_PIN_SET);
			break;

		case 3:
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG6_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG4_Pin | SEG5_Pin , GPIO_PIN_SET);
			break;

		case 4:
			HAL_GPIO_WritePin(GPIOB , SEG1_Pin | SEG2_Pin | SEG5_Pin | SEG6_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG3_Pin | SEG4_Pin , GPIO_PIN_SET);
			break;

		case 5:
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG5_Pin | SEG6_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG1_Pin | SEG4_Pin , GPIO_PIN_SET);
			break;

		case 6:
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin |
							  SEG5_Pin | SEG6_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG1_Pin , GPIO_PIN_SET);
			break;

		case 7:
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG1_Pin | SEG2_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin , GPIO_PIN_SET);
			break;

		case 8:
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin |
							  SEG4_Pin | SEG5_Pin | SEG6_Pin , GPIO_PIN_RESET);
			break;

		case 9:
			HAL_GPIO_WritePin(GPIOB , SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin |
							  SEG5_Pin | SEG6_Pin , GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB , SEG4_Pin , GPIO_PIN_SET);
			break;

		default:
			break;
	}
}

void autorun_update_buffer7SEG(){
	buffer7SEG[0] = trfLight0_timer_counter / 1000;
	buffer7SEG[1] = (trfLight0_timer_counter / 100) % 10;
	buffer7SEG[2] = trfLight1_timer_counter / 1000;
	buffer7SEG[3] = (trfLight1_timer_counter / 100) % 10;
}

void update7SEG(uint8_t index){
	switch (index){
		case 0:
			display7SEG(buffer7SEG[0]);
			break;

		case 1:
			display7SEG(buffer7SEG[1]);
			break;

		case 2:
			display7SEG(buffer7SEG[2]);
			break;

		case 3:
			display7SEG(buffer7SEG[3]);
			break;

		default :
			break;
	}
}

void changing_LED_on(uint8_t ledOn){
	switch (ledOn){
	case 0:
		HAL_GPIO_WritePin(GPIOA , LED_MODE0_Pin , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA , LED_MODE1_Pin | LED_MODIFY0_Pin | LED_MODIFY1_Pin , GPIO_PIN_SET);
		update7SEG(0);
		break;

	case 1:
		HAL_GPIO_WritePin(GPIOA , LED_MODE1_Pin , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA , LED_MODE0_Pin | LED_MODIFY0_Pin | LED_MODIFY1_Pin , GPIO_PIN_SET);
		update7SEG(1);
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOA , LED_MODIFY0_Pin , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA , LED_MODE0_Pin | LED_MODE1_Pin | LED_MODIFY1_Pin , GPIO_PIN_SET);
		update7SEG(2);
		break;

	case 3:
		HAL_GPIO_WritePin(GPIOA , LED_MODIFY1_Pin , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA , LED_MODE0_Pin | LED_MODE1_Pin | LED_MODIFY0_Pin , GPIO_PIN_SET);
		update7SEG(3);
		break;

	default:
		break;
	}
}

// đèn giao thông
void blinking_trafficLight(enum color LED_blinking){				// chớp tắt của đèn đỏ khác hai đèn còn lại
	switch (LED_blinking){
		case RED:
			if (blinking_timer_flag == 1){
				HAL_GPIO_TogglePin(GPIOA, LED_RED0_Pin | LED_RED1_Pin);
				setTimerBlinking((4 * 1000000) / ((blinking_prescaler+1) * (blinking_period+1)));
			}

			break;

		case YELLOW:
			if (blinking_timer_flag == 1){
				HAL_GPIO_TogglePin(GPIOA, LED_YELLOW0_Pin | LED_YELLOW1_Pin);
				setTimerBlinking((4 * 1000000) / ((blinking_prescaler+1) * (blinking_period+1)));
			}

			break;

		case GREEN:
			if (blinking_timer_flag == 1){
				HAL_GPIO_TogglePin(GPIOA, LED_GREEN0_Pin | LED_GREEN1_Pin);
				setTimerBlinking((4 * 1000000) / ((blinking_prescaler+1) * (blinking_period+1)));
			}

			break;

		default:
			break;
	}
}

void onlyOn_RED0(){
	HAL_GPIO_WritePin(GPIOA, LED_RED0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_YELLOW0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_GREEN0_Pin, GPIO_PIN_SET);
}

void onlyOn_YELLOW0(){
	HAL_GPIO_WritePin(GPIOA, LED_RED0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_YELLOW0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_GREEN0_Pin, GPIO_PIN_SET);
}		// latest key gotten from button
		if (index == BUTTON_MODE) getButton[index] = HAL_GPIO_ReadPin(GPIOA, BUTTON_MODE_Pin);


void onlyOn_GREEN0(){
	HAL_GPIO_WritePin(GPIOA, LED_RED0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_YELLOW0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_GREEN0_Pin, GPIO_PIN_RESET);
}

void onlyOn_RED1(){
	HAL_GPIO_WritePin(GPIOA, LED_RED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_YELLOW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_GREEN1_Pin, GPIO_PIN_SET);
}

void onlyOn_YELLOW1(){
	HAL_GPIO_WritePin(GPIOA, LED_RED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_YELLOW1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_GREEN1_Pin, GPIO_PIN_SET);
}

void onlyOn_GREEN1(){
	HAL_GPIO_WritePin(GPIOA, LED_RED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_YELLOW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_GREEN1_Pin, GPIO_PIN_RESET);
}

void clear_trafficLight(){
	HAL_GPIO_WritePin(GPIOA, LED_RED0_Pin | LED_YELLOW0_Pin | LED_GREEN0_Pin |
							LED_RED1_Pin | LED_YELLOW1_Pin | LED_GREEN1_Pin, GPIO_PIN_SET);
}
