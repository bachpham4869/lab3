/*
 * software_timer.c
 *
 *  Created on: Oct 28, 2024
 *      Author: Bach
 */

#include "software_timer.h"

int trfLight0_timer_counter = 0;
int trfLight1_timer_counter = 0;
int blinking_timer_counter = 0;
int changeLED_timer_counter = 0;

uint8_t trfLight0_timer_flag = 0;
uint8_t trfLight1_timer_flag = 0;
uint8_t blinking_timer_flag = 0;
uint8_t changeLED_timer_flag = 0;

void setTimer_trfLight0(int duration){
	trfLight0_timer_counter = duration;
	trfLight0_timer_flag = 0;
}

void setTimer_trfLight1(int duration){
	trfLight1_timer_counter = duration;
	trfLight1_timer_flag = 0;
}

void setTimer_changing_LED_on(int duration){
	changeLED_timer_counter = duration;
	changeLED_timer_flag = 0;
}

void setTimerBlinking(int duration){
	blinking_timer_counter = duration;
	blinking_timer_flag = 0;
}

void timerRun(){
	if (trfLight0_timer_counter > 0){
		trfLight0_timer_counter--;
		if (trfLight0_timer_counter <= 0){
			trfLight0_timer_flag = 1;
		}
	}

	if (trfLight1_timer_counter > 0){
		trfLight1_timer_counter--;
		if (trfLight1_timer_counter <= 0){
			trfLight1_timer_flag = 1;
		}
	}

	if (blinking_timer_counter > 0){
		blinking_timer_counter--;
		if (blinking_timer_counter <= 0){
			blinking_timer_flag = 1;
		}
	}

	if (changeLED_timer_counter > 0){
		changeLED_timer_counter--;
		if (changeLED_timer_counter <= 0){
			changeLED_timer_flag = 1;
		}
	}
}

void auto_setTimer_trfLight(uint8_t index){
	if (index == 0){
		switch (trf_flag[0]){
		case RED:
			setTimer_trfLight0(redDuration);
			break;

		case YELLOW:
			setTimer_trfLight0(yellowDuration);
			break;

		case GREEN:
			setTimer_trfLight0(greenDuration);
			break;

		default:
			break;
		}
	}

	if (index == 1){
		switch (trf_flag[1]){
		case RED:
			setTimer_trfLight1(redDuration);
			break;

		case YELLOW:
			setTimer_trfLight1(yellowDuration);
			break;

		case GREEN:
			setTimer_trfLight1(greenDuration);
			break;

		default:
			break;
		}
	}
}
