/*
 * TImer.c
 *
 *  Created on: Nov 1, 2024
 *      Author: TRONG DAT
 */
#include "timer.h"

void timer_init(uint32_t start_time){
	for(uint8_t i = 0; i < NUMBER_OF_TIMER; i++){
		set_timer(start_time, &Timer[i]);
	}
}

void set_timer(uint32_t duration, timer* Timer){
	Timer->tick_count = duration / INTERRUPT_CYCLE;
	Timer->timer_flag = 0;
}

void timer_run(){
	if(flag_timer_run == 1){
		timer_tick();
		flag_timer_run = 0;
	}
}

void timer_tick(){
	for(uint8_t i = 0; i < NUMBER_OF_TIMER; i++){
		Timer[i].tick_count--;
		if(Timer[i].tick_count == 0){
			Timer[i].timer_flag = 1;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM2){
    	flag_timer_run = 1;
    }
}

#define UNIT_TEST
#ifdef UNIT_TEST
void unit_test_timer(){
	if(Timer[0].timer_flag == 1){
		set_timer(500, &Timer[0]);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}
#endif
