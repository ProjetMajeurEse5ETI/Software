/*
 * SPI_Config.c
 *
 *  Created on: Oct 29, 2024
 *      Author: gustook
 */
#include "stm32f4xx_hal.h"
#include "SPI_Config.h"
#include <stdio.h>

//SPI_HandleTypeDef hspi2;
SPI_Frame TXmessage;
CMD_Frame cmd_Message;
int tick_A;
int tick_B;
uint8_t RX_Buffer[3];

/************************************************************************************************************
 * 																										    *
 * 																											*
 ************************************************************************************************************/

//hspi: SPI utilisé;
//cmd: type commande a effectué sur le sequenceur;
//data: valeur du message
//Cette fonction envoie un message SPI à la carte esclave en fct de la commande, elle génère 3 paquets de 8 bits envoyé successivement

void send_SPI_message(SPI_HandleTypeDef *hspi, SPI_CMD_Byte cmd, uint16_t data)
{
	uint8_t dataFrame[3];
	cmd_Message.U = 0x00;

	/*	création du message	*/
	cmd_Message.B.SFD = SFD_Val;	   // frame d'initialisation
	cmd_Message.B.CMD = cmd;
	dataFrame[0] = cmd_Message.U;
	dataFrame[1] = (data >> 8) & 0xFF; // decalage 8bts et mask
	dataFrame[2] = data & 0xFF;

	//printf("On a envoyé %X %X %X \n\r", dataFrame[0], dataFrame[1], dataFrame[2]);

	/*	envoie du message	*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET);
	HAL_SPI_Transmit(hspi, dataFrame, 3, 10000);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
}

//hspi: SPI utilisé;
//wheel: numéro de la roue
//Cette fonction envoie une demande à la carte esclave pour connaitre le nombre de tick (dans la roue) qu'elle à parcourue puis attends une réponse

void getTickSlave(SPI_HandleTypeDef *hspi, uint8_t wheel)
{
	TXmessage.U = 0X00000000;
	cmd_Message.U = 0x00;
	uint16_t data = wheel;
	uint16_t ticks = 0X0;

	/*	création du message	*/
	cmd_Message.B.SFD = SFD_Val;
	cmd_Message.B.CMD = acknowledge_tick;
	TXmessage.B.COMMAND = cmd_Message.U;
	TXmessage.B.VALUE = data;

	//ToDo: ajout sécurité type crc ou bit de parité

	uint8_t dataFrame[3];
	dataFrame[0] = cmd_Message.U;
	dataFrame[1] = (data >> 8) & 0xFF;// decalage 8bts et mask
	dataFrame[2] = data & 0xFF;

	//printf("dataFrame= %d.\n\r",(int)dataFrame);
	HAL_SPI_Transmit(hspi, dataFrame, 3, HAL_MAX_DELAY);	//envoie du message
	HAL_Delay(5);
	HAL_SPI_Receive(hspi, RX_Buffer, 3, HAL_MAX_DELAY);		//reception du message

	ticks |= RX_Buffer[1] & 0x00FF;
	ticks = (ticks << 8);
	ticks |= RX_Buffer[2] & 0x00FF;

	if(wheel == wheel_A){
		tick_A = (int) ticks;
		printf("tick_A = %d\n\r ",tick_A);
	}else{
		tick_B = (int) ticks;
		printf("tick_B = %d \n\r",tick_B);
	}
}

int VARgetTickSlave(SPI_HandleTypeDef *hspi, uint8_t wheel)
{
	TXmessage.U = 0X00000000;
	cmd_Message.U = 0x00;
	uint16_t data = wheel;
	uint16_t ticks = 0X0;

	/*	création du message	*/
	cmd_Message.B.SFD = SFD_Val;
	cmd_Message.B.CMD = acknowledge_tick;
	TXmessage.B.COMMAND = cmd_Message.U;
	TXmessage.B.VALUE = data;


	uint8_t dataFrame[3];
	dataFrame[0] = cmd_Message.U;
	dataFrame[1] = (data >> 8) & 0xFF;// decalage 8bts et mask
	dataFrame[2] = data & 0xFF;

	HAL_SPI_Transmit(hspi, dataFrame, 3, HAL_MAX_DELAY);	//envoie du message
	HAL_Delay(5);
	HAL_SPI_Receive(hspi, RX_Buffer, 3, HAL_MAX_DELAY);		//reception du message

	ticks |= RX_Buffer[1] & 0x00FF;
	ticks = (ticks << 8);
	ticks |= RX_Buffer[2] & 0x00FF;
	return ticks;
}

void ChangeDirection(SPI_HandleTypeDef *hspi, uint16_t speed_WA, uint16_t speed_WB, uint16_t rot_WA, uint16_t rot_WB)
{
	uint16_t data = 0X00;
	data |= rot_WA & 0x01;
	data |= (rot_WB<<1) & 0x0002;
	data |= (speed_WA<<2) & 0x003C;
	data |= (speed_WB<<6) & 0x03C0;
	send_SPI_message(hspi, Start_Stop, stop_Bot);
	HAL_Delay(500);
	send_SPI_message(hspi, setting, data);
	HAL_Delay(500);
	send_SPI_message(hspi, Start_Stop, start_Bot);
}
