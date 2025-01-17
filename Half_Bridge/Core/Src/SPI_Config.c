/*
 * SPI_Config.c
 *
 *  Created on: Oct 29, 2024
 *      Author: gustook
 */

#include "SPI_Config.h"
#include "GestionMvt.h"
#include <stdio.h>
#include "main.h"

SPI_Frame TXmessage;
SPI_Frame RXmessage;
CMD_Frame cmd_Message;
int tick_A;
int tick_B;
uint8_t rotation_R1;
uint8_t rotation_R2;
uint8_t DC_R1;
uint8_t DC_R2;
uint8_t RX_Buffer[3];

void send_SPI_message(SPI_HandleTypeDef *hspi, SPI_CMD_Byte cmd, uint16_t data)
{
	TXmessage.U = 0X00000000;
	cmd_Message.U = 0x00;
	cmd_Message.B.SFD = SFD_Val;
	cmd_Message.B.CMD = cmd;
	TXmessage.B.COMMAND = cmd_Message.U;
	TXmessage.B.VALUE = data;

	//ajout sécurité type crc ou bit de parité

	uint8_t dataFrame[3];
	dataFrame[0] = cmd_Message.U;
	dataFrame[1] = (data>>8)& 0xFF;
	dataFrame[2] = data & 0xFF;
	//printf("%i %i", dataFrame[0], dataFrame[1]);

	HAL_SPI_Transmit(hspi,dataFrame, 3, 1000);
}


void SPI_data_processing(uint8_t *RXdata)
{
	RXmessage.U = 0X00000000;
	cmd_Message.U = RXdata[0];

	RXmessage.B.COMMAND = RXdata[0];
	RXmessage.B.VALUE |= RXdata[1] & 0x00FF;
	RXmessage.B.VALUE = (RXmessage.B.VALUE << 8) & 0xFF00;
	RXmessage.B.VALUE |= RXdata[2] & 0x00FF;

	if(cmd_Message.B.SFD == SFD_Val)
	{
		//Reception des settings
		if (cmd_Message.B.CMD == 1) {
			rotation_R1 = RXmessage.B.VALUE& 0x0001;
			rotation_R2 = ((RXmessage.B.VALUE& 0x0002) >> 1);
			DC_R1 = ((RXmessage.B.VALUE& 0x003C) >> 2);
			DC_R2 = ((RXmessage.B.VALUE& 0x03C0)>>6);
			variableModification(rotation_R1,rotation_R2,DC_R1,DC_R2);
		}
		if (cmd_Message.B.CMD == 2){
			if ((RXmessage.B.VALUE& 0x0001) == 1){//stop
				stopRobot();
			}
			else{//start
				startRobot();
			}
		}
		if (cmd_Message.B.CMD == 3){
			if ((RXmessage.B.VALUE) == 1){//send tick R1
				settings_R1.tick = 15786;
				settings_R1.flagTick = 1;
				//send_SPI_message(hspi,3,settings_R1.tick);
			}
			else if ((RXmessage.B.VALUE) == 0){
				settings_R2.tick = 18754;
				settings_R2.flagTick = 1;
				//send_SPI_message(hspi,3,settings_R2.tick);
			}
		}

	}
	else{
		int i = 0;
		i++;
	}

}

