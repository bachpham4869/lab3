/*
 * input_reading.c
 *
 *  Created on: Oct 28, 2024
 *      Author: Bach
 */
// only case press and release immediately

#include "input_reading.h"

/* [0] for button mode ; [1] for button modify ; [2] for button set */
static GPIO_PinState debounce0[BUTTON_NUM] = 		{RELEASE_STATE, RELEASE_STATE, RELEASE_STATE};
static GPIO_PinState debounce1[BUTTON_NUM] = 		{RELEASE_STATE, RELEASE_STATE, RELEASE_STATE};
static GPIO_PinState getButton[BUTTON_NUM] = 		{RELEASE_STATE, RELEASE_STATE, RELEASE_STATE};
static GPIO_PinState getPrevButton[BUTTON_NUM] = 	{RELEASE_STATE, RELEASE_STATE, RELEASE_STATE};
static GPIO_PinState Press_flag[BUTTON_NUM] = 		{RELEASE_STATE, RELEASE_STATE, RELEASE_STATE};
static uint16_t timerPress[BUTTON_NUM] = 			{200, 100, 200};

uint8_t isButtonPressed(uint8_t index){				// check có được nhấn hay chưa
	if (Press_flag[index] == PRESS_STATE){
		Press_flag[index] = RELEASE_STATE;
		return 1;
	}
	return 0;
}

void button_reading(){  // chống rung cho nút nhấn
	for (int index = 0; index < BUTTON_NUM; index++){
		debounce0[index] = debounce1[index];
		debounce1[index] = getButton[index];

		// latest key gotten from button
		if (index == BUTTON_MODE) getButton[index] = HAL_GPIO_ReadPin(GPIOA, BUTTON_MODE_Pin);
		else if (index == BUTTON_MODIFY) getButton[index] = HAL_GPIO_ReadPin(GPIOA, BUTTON_MODIFY_Pin);
		else getButton[index] = HAL_GPIO_ReadPin(GPIOA, BUTTON_SET_Pin);

		if (debounce0[index] == debounce1[index] && debounce1[index] == getButton[index]){
			if (getPrevButton[index] != getButton[index]){			// nhấn thả (trạng thái của nút nhấn lần trước và lần mới nhất khác nhau)
				getPrevButton[index] = getButton[index];			// lưu trạng thái mới nhất của nút nhấn cho lần sau

				if (getButton[index] == PRESS_STATE){				// nếu trạng thái mới là trạng thái nhấn thì bật cờ
					// TO DO
					timerPress[index] = 200;
					Press_flag[index] = PRESS_STATE;
				}
			}

			else{													// nhấn đè
				timerPress[index]--;
				if (timerPress[index] == 0){
					getPrevButton[index] = RELEASE_STATE;			// đưa trạng thái nhấn đè vào xử lí như nhấn thả
				}
			}
		}
	}
}
