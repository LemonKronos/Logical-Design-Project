/*
 * UART.h
 *
 *  Created on: Sep 24, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "global.h"

#define UART_ERROR_Port LD3_GPIO_Port
#define UART_ERROR_Pin LD3_Pin

uint8_t flagUART_sended;
uint8_t flagUART_received;
uint8_t flagUART_demand;
uint8_t UART_SEND_buffer[20];
uint8_t UART_RECEIVE_buffer[20];

void scheduleSendUART(UART_HandleTypeDef* gate);

void prepareSendData();

ERROR_CODE sendUART(uint8_t* UART_SEND_buffer, UART_HandleTypeDef* gate);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

void receiveUART(uint8_t* UART_RECEIVE_buffer, UART_HandleTypeDef* gate);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* INC_UART_H_ */
