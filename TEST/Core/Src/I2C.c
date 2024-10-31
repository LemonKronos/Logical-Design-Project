/*
 * I2C.c
 *
 *  Created on: Oct 31, 2024
 *      Author: TRONG DAT
 */

#include "I2C.h"
#include "global.h"
#include "stm32f1xx_hal.h"

void readSensor(I2C_HandleTypeDef* gate){
	if(timer_flag[1] == 1 || flagI2C_demand == 1){
		if(flagI2C_received_DHT20 == 1 && readDHT20(gate) == RECEIVED){
			//run normally
			I2C_error = 0;
			HAL_GPIO_WritePin(I2C_ERROR_Port, I2C_ERROR_Pin, SET);
			flagI2C_demand = 0;
		}
		else{
			I2C_error++;
			if(I2C_error < 3){
			// set timer read again 1 second after
			set_timer(1 *SEC, &timer_flag[1]);
			}
			else{
			// failed 3 times, lit ERROR LED, hope and pray it work next time
			I2C_error = 0;
			HAL_GPIO_WritePin(I2C_ERROR_Port, I2C_ERROR_Pin, RESET);
			flagI2C_demand = 0;
			}
		}
	}
}

ERROR_CODE readDHT20(I2C_HandleTypeDef* gate){
	flagI2C_received_DHT20 = 0;
    if(HAL_I2C_Master_Receive_IT(gate, DHT20_ADDRESS, I2C_RECEIVE_buffer, sizeof(I2C_RECEIVE_buffer)) == HAL_OK)
    	return RECEIVED;
    else return RECEIVE_FAILED;
}

void extractDHT20Data(uint8_t *buffer, float *temperature, float *humidity){
    raw_humidity = (buffer[1] << 8) | buffer[2];
    raw_temperature = (buffer[3] << 8) | buffer[4];
    // Convert raw values to human-readable values
    *humidity = (raw_humidity * 100.0) / 65536.0;
    *temperature = ((raw_temperature * 200.0) / 65536.0) - 50.0;
}


void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c){
	if (hi2c->Instance == I2C1){
		flagI2C_received_DHT20 = 1;
	}
}

