/*
 * input_processing.h
 *
 *  Created on: Oct 28, 2024
 *      Author: Bach
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "input_reading.h"
#include "output_display.h"

// "color" type defines traffic light status as well as mode1234, which leads to element "autorun"
void fsm_manual_traffic_light(void);
void fsm_autorun_traffic_light0(void);
void fsm_autorun_traffic_light1(void);

#endif /* INC_INPUT_PROCESSING_H_ */
