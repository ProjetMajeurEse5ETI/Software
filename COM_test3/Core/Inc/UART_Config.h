/*
 * UART_Config.h
 *
 *  Created on: Dec 10, 2024
 *      Author: augustinlaprais
 */

#ifndef INC_UART_CONFIG_H_
#define INC_UART_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"


void computerFiel(UART_HandleTypeDef *huart, uint8_t data);
void Manual_Instruction(SPI_HandleTypeDef *hspi);
void M0_Process(UART_HandleTypeDef *huart, uint8_t *data);
int getStatus(void);
int getAngle(void);
void sendStatus(UART_HandleTypeDef *huart);
#ifdef __cplusplus
}
#endif

#endif /* INC_UART_CONFIG_H_ */
