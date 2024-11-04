/*
 * I2C.h
 *
 *  Created on: Oct 31, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"
#include "global.h"

#define I2C_ERROR_Port LD3_GPIO_Port
#define I2C_ERROR_Pin LD3_Pin
#define DHT20_ADDRESS 0x38

uint8_t flagI2C_demand;
uint8_t flagI2C_received_DHT20;
//uint8_t I2C_RECEIVE_buffer[20]; at global.h

void readSensor(I2C_HandleTypeDef* gate);

ERROR_CODE readDHT20(I2C_HandleTypeDef* gate);

void extractDHT20Data(uint8_t *buffer, float *temperature, float *humidity);

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c);

#endif /* INC_I2C_H_ */
