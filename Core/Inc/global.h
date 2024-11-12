/*
 * global.h
 *
 *  Created on: Oct 28, 2024
 *      Author: Bach
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

#define RELEASE_STATE			GPIO_PIN_SET
#define PRESS_STATE				GPIO_PIN_RESET
#define BUTTON_NUM				3
#define BUTTON_MODE				0
#define BUTTON_MODIFY			1
#define BUTTON_SET				2

extern int redDuration;
extern int yellowDuration;
extern int greenDuration;

extern int modifyingDuration;
extern uint8_t buffer7SEG[4];
extern uint8_t ledOn;

enum color{INIT, AUTORUN, RED, YELLOW, GREEN};
extern enum color mode;
extern enum color trf_flag[2];

extern int blinking_prescaler;
extern int blinking_period;

#endif /* INC_GLOBAL_H_ */
