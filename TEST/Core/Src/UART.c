/*
 * UART.c
 *
 *  Created on: Sep 24, 2024
 *      Author: TRONG DAT
 */

#include "UART.h"

enum ERROR_CODE SEND_DATA(uint8_t* text_buff, UART_HandleTypeDef* gate){
	if(HAL_UART_Transmit(gate, text_buff, sizeof(text_buff), TIME_OUT) == HAL_OK) return OK;
	else return SEND_FAILED;
};
