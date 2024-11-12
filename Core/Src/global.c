/*
 * global.c
 *
 *  Created on: Oct 28, 2024
 *      Author: Bach
 */

#include "global.h"

int modifyingDuration = 0;
uint8_t buffer7SEG[4] = {0, 0, 0, 0};
uint8_t ledOn = 0;

enum color mode = INIT;
enum color trf_flag[2] = {RED, GREEN};

//thời gian cho các đèn
int redDuration = 500;
int yellowDuration = 200;
int greenDuration = 300;

int blinking_prescaler;
int blinking_period;

//int blinking_prescaler = htim2.Init.Prescaler;
//int blinking_counter = htim2.Init.Period;
