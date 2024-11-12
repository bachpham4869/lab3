/*
 * output_display.h
 *
 *  Created on: Oct 28, 2024
 *      Author: Bach
 */

#ifndef INC_OUTPUT_DISPLAY_H_
#define INC_OUTPUT_DISPLAY_H_

#include "software_timer.h"

void display7SEG(uint8_t);
void autorun_update_buffer7SEG(void);
void update7SEG(uint8_t);
void changing_LED_on(uint8_t);
void blinking_trafficLight(enum color);

void onlyOn_RED0(void);
void onlyOn_YELLOW0(void);
void onlyOn_GREEN0(void);
void onlyOn_RED1(void);
void onlyOn_YELLOW1(void);
void onlyOn_GREEN1(void);
void clear_trafficLight(void);

#endif /* INC_OUTPUT_DISPLAY_H_ */
