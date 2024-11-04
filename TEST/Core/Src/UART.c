/*
 * UART.c
 *
 *  Created on: Sep 24, 2024
 *      Author: TRONG DAT
 */

#include "UART.h"
#include "global.h"
#include "string.h"
#include "timer.h"

void scheduleSendUART(UART_HandleTypeDef* gate){
	if(Timer[0].timer_flag == 1 || flagUART_demand == 1){
		prepareSendData();
		if(flagUART_sended == 1 && sendUART(UART_SEND_buffer, gate) == SENDED){
			// set timer run normally
			set_timer(5 *MIN, &Timer[0]);
			UART_error = 0;
			HAL_GPIO_WritePin(UART_ERROR_Port, UART_ERROR_Pin, SET);
			flagUART_demand = 0;
		}
		else{
			UART_error++;
			if(UART_error < 3){
				// set timer send again 1 second after
				set_timer(1 *SEC, &Timer[0]);
			}
			else{
				// failed 3 times, lit ERROR LED, hope and pray it work next time
				set_timer(5 *MIN, &Timer[0]);
				UART_error = 0;
				HAL_GPIO_WritePin(UART_ERROR_Port, UART_ERROR_Pin, RESET);
				flagUART_demand = 0;
			}
		}
	}
}

void prepareSendData(){//specifically for this case
	for(int i = 0; i < 4; i++){// prepare 2 bytes of raw humidity then 2 bytes of raw temperature
		UART_SEND_buffer[i] = I2C_RECEIVE_buffer[i];
	}
}

ERROR_CODE sendUART(uint8_t* UART_SEND_buffer, UART_HandleTypeDef* gate){
	flagUART_sended = 0;
	if(HAL_UART_Transmit_IT(gate, UART_SEND_buffer, sizeof(UART_SEND_buffer)) == HAL_OK) return SENDED;
	else return SEND_FAILED;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    if (huart->Instance == USART2){
        flagUART_sended = 1;
    }
}

void receiveUART(uint8_t* UART_RECEIVE_buffer, UART_HandleTypeDef* gate){
	HAL_UART_Receive_IT(gate, UART_RECEIVE_buffer, sizeof(*UART_RECEIVE_buffer));
	//if receive success, deal with data, else ignore
	if(flagUART_received == 1){
		if(strcmp((char*)UART_RECEIVE_buffer, "SEND DATA NOW\0")){
			flagUART_demand = 1;
		}
		else{
			// more case here
		}
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if (huart->Instance == USART2){
		flagUART_demand = 1;
	}
}

