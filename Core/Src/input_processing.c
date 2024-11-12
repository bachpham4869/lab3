/*
 * input_processing.c
 *
 *  Created on: Oct 28, 2024
 *      Author: Bach
 */

#include "input_processing.h"

void update_modifyDuration_and_buffer(){
	if (isButtonPressed(BUTTON_MODIFY)){	// press button modify, only affect mode234
		modifyingDuration += 100;

	buffer7SEG[0] = 0;
	buffer7SEG[2] = modifyingDuration / 1000;
	buffer7SEG[3] = (modifyingDuration / 100) % 10;

	switch (mode){
		case RED:
			buffer7SEG[1] = 2;
			break;

		case YELLOW:
			buffer7SEG[1] = 3;
			break;

		case GREEN:
			buffer7SEG[1] = 4;
			break;

		default:
			break;
		}
	}
}

void fsm_manual_traffic_light(){
	switch (mode){
		case RED:
			blinking_trafficLight(RED);

			if (isButtonPressed(BUTTON_MODE)){		// nhấn nút thứ 1
				mode = YELLOW;
				modifyingDuration = 0;
				buffer7SEG[0] = 0;
				buffer7SEG[1] = 3;
				buffer7SEG[2] = 0;
				buffer7SEG[3] = 0;
				clear_trafficLight();
			}

			update_modifyDuration_and_buffer();		// nhấn nút thứ 2

			if (isButtonPressed(BUTTON_SET)){		// nhấn nút thứ 3
				redDuration = modifyingDuration;
				modifyingDuration = 0;
				buffer7SEG[1] = 3;
				buffer7SEG[2] = 0;
				buffer7SEG[3] = 0;
				clear_trafficLight();
				mode = YELLOW;
			}

			break;

		case YELLOW:
			blinking_trafficLight(YELLOW);

			if (isButtonPressed(BUTTON_MODE)){		// nhấn nút thứ 1
				mode = GREEN;
				modifyingDuration = 0;
				buffer7SEG[0] = 0;
				buffer7SEG[1] = 4;
				buffer7SEG[2] = 0;
				buffer7SEG[3] = 0;
				clear_trafficLight();
			}

			update_modifyDuration_and_buffer();		// nhấn nút thứ 2

			if (isButtonPressed(BUTTON_SET)){		// nhấn nút thứ 3
				yellowDuration = modifyingDuration;
				clear_trafficLight();
				modifyingDuration = 0;
				buffer7SEG[1] = 4;
				buffer7SEG[2] = 0;
				buffer7SEG[3] = 0;
				mode = GREEN;
			}

			break;

		case GREEN:
			blinking_trafficLight(GREEN);

			if (isButtonPressed(BUTTON_MODE)){		// nhấn nút thứ 1
				trf_flag[0] = RED;
				trf_flag[1] = GREEN;
				mode = INIT;
			}

			update_modifyDuration_and_buffer();		// nhấn nút thứ 2

			if (isButtonPressed(BUTTON_SET)){		// nhấn nút thứ 3
				greenDuration = modifyingDuration;
				trf_flag[0] = RED;
				trf_flag[1] = GREEN;
				clear_trafficLight();
				mode = AUTORUN;
			}

			break;

		default:
			break;
	}
}


void fsm_autorun_traffic_light0(){
	switch (trf_flag[0]){
		case RED:
			onlyOn_RED0();

			if (trfLight0_timer_flag == 1){
				trf_flag[0] = GREEN;
				auto_setTimer_trfLight(0);
			}
			break;

		case YELLOW:
			onlyOn_YELLOW0();

			HAL_GPIO_WritePin(GPIOA, LED_RED0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, LED_YELLOW0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_GREEN0_Pin, GPIO_PIN_SET);

			if (trfLight0_timer_flag == 1){
				trf_flag[0] = RED;
				auto_setTimer_trfLight(0);
			}
			break;

		case GREEN:
			onlyOn_GREEN0();

			HAL_GPIO_WritePin(GPIOA, LED_RED0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, LED_YELLOW0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, LED_GREEN0_Pin, GPIO_PIN_RESET);

			if (trfLight0_timer_flag == 1){
				trf_flag[0] = YELLOW;
				auto_setTimer_trfLight(0);
			}
			break;

		default:
			break;

	}
}

void fsm_autorun_traffic_light1(){
	switch (trf_flag[1]){
		case RED:
			onlyOn_RED1();

			if (trfLight1_timer_flag == 1){
				trf_flag[1] = GREEN;
				auto_setTimer_trfLight(1);
			}
			break;

		case YELLOW:
			onlyOn_YELLOW1();

			if (trfLight1_timer_flag == 1){
				trf_flag[1] = RED;
				auto_setTimer_trfLight(1);
			}
			break;

		case GREEN:
			onlyOn_GREEN1();

			if (trfLight1_timer_flag == 1){
				trf_flag[1] = YELLOW;
				auto_setTimer_trfLight(1);
			}
			break;

		default:
			break;

	}
}
