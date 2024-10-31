/*
 * global.h
 *
 *  Created on: Oct 31, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

#define TIME_OUT 20
#define SEC 1000
#define MIN 60000

typedef enum ERROR_CODE{
	SENDED,
	SEND_FAILED,
	SEND_SUCCESS,
	RECEIVED,
	RECEIVE_FAILED,
	RECEIVE_SUCCESS
}ERROR_CODE;

//UART
uint8_t UART_error;

//I2C
uint8_t I2C_error;
uint8_t I2C_RECEIVE_buffer[20];
uint16_t raw_temperature;
uint16_t raw_humidity;
float TEMP, HUMID;

#endif /* INC_GLOBAL_H_ */
