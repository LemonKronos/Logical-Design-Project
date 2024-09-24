/*
 * UART.h
 *
 *  Created on: Sep 24, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

#define TIME_OUT 20

enum ERROR_CODE{
	OK,
	NO_UART,
	huh
};

enum ERROR_CODE SEND_DATA(uint8_t* text_buff, UART_HandleTypeDef* gate);

#endif /* INC_UART_H_ */
