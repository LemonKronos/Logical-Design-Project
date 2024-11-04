/*
 * Timer.h
 *
 *  Created on: Nov 1, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
#include "global.h"

#define UNIT_TEST
#ifdef UNIT_TEST

#endif

// ALL AT GLOBAL.H
//#define INTERRUPT_CYCLE 10
//#define NUMBER_OF_TIMER 2
//
//typedef struct {
//	uint16_t tick_count;
//	uint8_t timer_flag;
//}timer;

extern uint8_t flag_timer_run;

extern timer Timer[NUMBER_OF_TIMER];

void timer_init(uint32_t start_time);

void timer_run();

void set_timer(uint32_t duration, timer* Timer);

void timer_tick();

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#ifdef UNIT_TEST
void unit_test_timer();
#endif

#endif /* INC_TIMER_H_ */

