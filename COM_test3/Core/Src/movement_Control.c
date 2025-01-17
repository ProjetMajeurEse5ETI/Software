/*
 * movement_Control.c
 *
 *  Created on: Jan 13, 2025
 *      Author: augustin.laprais
 */


#include "movement_Control.h"
#include "SPI_Config.h"
#include "UART_Config.h"
#include <stdio.h>

State_Bot state;
int flag;

void Locklass(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart)
{
	if(state == Manual) // detection obstacle + commande robot IHM
	{
		if(getStatus() == 1)
		{
			sendStatus(huart);
		}
		Manual_Instruction(hspi);
	}
	else if(state == Automatic) // déplacement selon reception capteur
	{
		int angle = getAngle();
		//printf("s%i \n\r", angle);
		detectionError(hspi, huart);
		if(angle <= -30)
		{
			ChangeDirection(hspi, 2, 2, 0, 1);
			while(angle <= -30){
				detectionError(hspi, huart);
				angle = getAngle();
			}
			ChangeDirection(hspi, 2, 2, 0, 0);
		}else if(angle >= 30)
		{
			ChangeDirection(hspi, 2, 2, 1, 0);
			while(angle >= 30){
				detectionError(hspi, huart);
				angle = getAngle();
			}
			ChangeDirection(hspi, 2, 2, 0, 0);
		}
	}
	else if(state == Stand_By) // arret robot
	{
		send_SPI_message(hspi, Start_Stop, stop_Bot);
		sendStatus(huart);
		while(state == Stand_By){}
	}

}

void detectionError(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart)
{
	if(getStatus() == 1)
	{
		send_SPI_message(hspi, Start_Stop, stop_Bot);
		//sendStatus(huart);
		while(getStatus() == 1){}
		send_SPI_message(hspi, Start_Stop, start_Bot);
	}
}

void set_State(State_Bot stat)
{
	state = stat;
}

int get_State(void)
{
	return state;
}
