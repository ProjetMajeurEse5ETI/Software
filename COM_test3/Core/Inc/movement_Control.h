/*
 * movement_Control.h
 *
 *  Created on: Jan 13, 2025
 *      Author: augustin.laprais
 */

#ifndef INC_MOVEMENT_CONTROL_H_
#define INC_MOVEMENT_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

typedef enum
{
	Stand_By    = 0x0,
	Automatic   = 0x1,
	Manual		= 0x2
}State_Bot;


void Locklass(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart);
void set_State(State_Bot stat);
void detectionError(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart);
int get_State(void);
#ifdef __cplusplus
}
#endif

#endif /* INC_MOVEMENT_CONTROL_H_ */
