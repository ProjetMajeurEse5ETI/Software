/*
 * SPI_Config.h
 *
 *  Created on: Oct 29, 2024
 *      Author: gustook
 */

#ifndef INC_SPI_CONFIG_H_
#define INC_SPI_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define no_Data 0x00
#define SFD_Val 0x5
#define wheel_A 0x1
#define wheel_B 0x0
#define stop_Bot  0x1
#define start_Bot 0x0

typedef enum
{
	setting         	= 0x1,
	Start_Stop      	= 0x2,
	acknowledge_tick	= 0x3
}SPI_CMD_Byte;

typedef struct
{
	uint8_t         COMMAND:8;
	uint16_t        VALUE:16;
	uint8_t         reserved:8;
}SPI_Frame_B;

typedef struct
{
	uint8_t         SFD:4;
	uint8_t         CMD:3;
	uint8_t         reserved:1;
}SPI_CMD_B;

typedef union uint16_t
{
	uint32_t U;
	SPI_Frame_B B;
}SPI_Frame;

typedef union uint8_t
{
	uint8_t U;
	SPI_CMD_B B;
}CMD_Frame;

void getTickSlave(SPI_HandleTypeDef *hspi, uint8_t wheel);
void send_SPI_message(SPI_HandleTypeDef *hspi, SPI_CMD_Byte cmd, uint16_t data);
int VARgetTickSlave(SPI_HandleTypeDef *hspi, uint8_t wheel);
void ChangeDirection(SPI_HandleTypeDef *hspi, uint16_t speed_WA, uint16_t speed_WB, uint16_t rot_WA, uint16_t rot_WB);
#ifdef __cplusplus
}
#endif

#endif /* INC_SPI_CONFIG_H_ */
