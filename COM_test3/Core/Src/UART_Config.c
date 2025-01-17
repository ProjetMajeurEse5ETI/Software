/*
 * UART_Config.c
 *
 *  Created on: Dec 10, 2024
 *      Author: augustinlaprais
 */
#include "stm32f4xx_hal.h"
#include "UART_Config.h"
#include "SPI_Config.h"
#include "movement_Control.h"
#include <stdio.h>

uint8_t UARX_Buffer_PC[3];
uint8_t UATX_Buffer_PC[3];

uint8_t UARX_Buffer_M0[2];
uint8_t UATX_Buffer_M0[2];

uint8_t commande;
int8_t angle;
uint8_t detect;

uint8_t Miahou;

/************************************************************************************************************
 * 																										    *
 * 																											*
 ************************************************************************************************************/
/*
void computerFiel(UART_HandleTypeDef *huart, SPI_HandleTypeDef *hspi, uint8_t data)
{
	UATX_Buffer_PC[0]=0x46;  //ASCII "F"
	UATX_Buffer_PC[1]=0x0D;
	UATX_Buffer_PC[2]=0x0A;

	if(data==0x7A){														//ASCII "z"
		ChangeDirection(hspi, 4, 4, 0x01, 0x01);
		UATX_Buffer_PC[0]=0x56;											//ASCII "V"
		HAL_UART_Transmit(huart, UATX_Buffer_PC, 3, HAL_MAX_DELAY);
	}else if(data==0x73){											    //ASCII "s"
		//ChangeDirection(hspi, 5, 5, 0x00, 0x00);
		ChangeDirection(hspi, 5, 5, 0x01, 0x01);
		UATX_Buffer_PC[0]=0x56;
		HAL_UART_Transmit(huart, UATX_Buffer_PC, 3, HAL_MAX_DELAY);
	}else if(data==0x71){												//ASCII "q"
		ChangeDirection(hspi, 6, 6, 0x01, 0x01);
		//ChangeDirection(hspi, 5, 0, 0x01, 0x01);
		UATX_Buffer_PC[0]=0x56;
		HAL_UART_Transmit(huart, UATX_Buffer_PC, 3, HAL_MAX_DELAY);
	}else if(data==0x64){												//ASCII "d"
		ChangeDirection(hspi, 4, 4, 0x01, 0x01);
		//ChangeDirection(hspi, 0, 5, 0x00, 0x00);
		UATX_Buffer_PC[0]=0x56;
	    HAL_UART_Transmit(huart, UATX_Buffer_PC, 3, HAL_MAX_DELAY);
	}else if(data==0x30){												//ASCII "0"
		send_SPI_message(hspi, Start_Stop, stop_Bot);
		UATX_Buffer_PC[0]=0x56;
	    HAL_UART_Transmit(huart, UATX_Buffer_PC, 3, HAL_MAX_DELAY);
	}else{
		HAL_UART_Transmit(huart, UATX_Buffer_PC, 3, HAL_MAX_DELAY);
	}
}*/

//reception des données IHM et chgmnt flag pour les roues
void computerFiel(UART_HandleTypeDef *huart, uint8_t data)
{
	UATX_Buffer_PC[0]=0x46;  //ASCII "F"
	UATX_Buffer_PC[1]=0x0D;  //ASCII "\n"
	UATX_Buffer_PC[2]=0x0A;  //ASCII "\r"

	if(data==0x7A){														//ASCII "z"
		//déplacement avant
		Miahou = 0x02;
		UATX_Buffer_PC[0]=0x56;											//ASCII "V"
	}else if(data==0x73){											    //ASCII "s"
		//déplacement arrière
		Miahou = 0x03;
		UATX_Buffer_PC[0]=0x56;
	}else if(data==0x71){												//ASCII "q"
		//déplacement gauche
		Miahou = 0x04;
		UATX_Buffer_PC[0]=0x56;
	}else if(data==0x64){												//ASCII "d"
		//déplacement droit
		Miahou = 0x05;
		UATX_Buffer_PC[0]=0x56;
	}else if(data==0x30){												//ASCII "0"
		//stop
		Miahou = 0x01;
		UATX_Buffer_PC[0]=0x56;
	}else if (data == 'A')
	{
		set_State(Automatic);
		UATX_Buffer_PC[0]=0x56;
	}
	else if (data == 'M')
	{
		set_State(Manual);
		UATX_Buffer_PC[0]=0x56;
	}
	else{
		//ne rien faire
		Miahou = 0x00;
		UATX_Buffer_PC[0]=0x56;
	}
	HAL_UART_Transmit(huart, UATX_Buffer_PC, 3, HAL_MAX_DELAY);
}

void Manual_Instruction(SPI_HandleTypeDef *hspi)
{
	if(Miahou==0x02){
		ChangeDirection(hspi, 2, 2, 0x01, 0x01);
		Miahou=0x00;
	}if(Miahou==0x03){
		ChangeDirection(hspi, 2, 2, 0x00, 0x00);
		Miahou=0x00;
	}if(Miahou==0x04){
		ChangeDirection(hspi, 2, 2, 0x01, 0x00);
		Miahou=0x00;
	}if(Miahou==0x05){
		ChangeDirection(hspi, 2, 2, 0x00, 0x01);
		Miahou=0x00;
	}if(Miahou==0x01){
		send_SPI_message(hspi, Start_Stop, stop_Bot);
		Miahou=0x00;
	}
}

void M0_Process(UART_HandleTypeDef *huart, uint8_t *data)
{
	if(commande != 0)
	{
		if(commande == '!')
		{
			detect = data[0];
			commande = 0;
			//printf("%i \n\r", detect);
		}
		if(commande == 'A')
		{
			angle = data[0];
			commande = 0;
			printf("%i \n\r", angle);
		}
	}
	else
	{
		if(data[0] == '!')
		{
			commande = data[0];
		}
		if(data[0] == 'A')
		{
			commande = data[0];
		}
	}
}

int getStatus(void)
{
	int res = 0;
	if(detect != 0)
	{
		res = 1;
	}
	return res;
}

int getAngle(void)
{
	return angle;
}

void sendStatus(UART_HandleTypeDef *huart)
{
	UATX_Buffer_PC[0]=0x21;  //ASCII "!"
	UATX_Buffer_PC[1] = detect;
	UATX_Buffer_PC[2] = 0x0A;
	HAL_UART_Transmit(huart, UATX_Buffer_PC, 2, HAL_MAX_DELAY);
}
