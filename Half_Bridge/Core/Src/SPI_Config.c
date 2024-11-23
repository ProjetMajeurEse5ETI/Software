/*
 * SPI_Config.c
 *
 *  Created on: Oct 29, 2024
 *      Author: gustook
 */

#include "SPI_Config.h"
#include <stdio.h>

SPI_Frame TXmessage;
SPI_Frame RXmessage;
CMD_Frame cmd_Message;
int tick_A;
int tick_B;
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

	uint8_t dataFrame[3] = {RXmessage.U};
	printf("%i %i", dataFrame[0], dataFrame[1]);

	HAL_SPI_Transmit(hspi, dataFrame, 3, 1000);
}


void getTickSlave(SPI_HandleTypeDef *hspi, uint8_t wheel)
{
	TXmessage.U = 0X00000000;
	cmd_Message.U = 0x00;
	uint16_t data = 0x0000;

	cmd_Message.B.SFD = SFD_Val;
	if(wheel == wheel_A){
		cmd_Message.B.CMD = acknowledge_A;
	}else{
		cmd_Message.B.CMD = acknowledge_B;
	}
	TXmessage.B.COMMAND = cmd_Message.U;
	TXmessage.B.VALUE = data;

	//ajout sécurité type crc ou bit de parité

	uint8_t dataFrame[3] = {TXmessage.U};
	HAL_SPI_TransmitReceive(hspi, dataFrame, RX_Buffer, 3, 100);

	data |= RX_Buffer[1] & 0x00FF;
	data = (data << 8);
	data |= RX_Buffer[2] & 0x00FF;
	if(wheel == wheel_A){
		tick_A = (int) data;
	}else{
		tick_B = (int) data;
	}
}

void SPI_data_processing(uint8_t *RXdata)
{
	RXmessage.U = 0X00000000;
	cmd_Message.U = RXdata[0];

	RXmessage.B.COMMAND = RXdata[0];
	RXmessage.B.VALUE |= RXdata[1] & 0x00FF;
	RXmessage.B.VALUE = (RXmessage.B.VALUE << 8);
	RXmessage.B.VALUE |= RXdata[2] & 0x00FF;

	if(cmd_Message.B.SFD == SFD_Val)
	{
		printf("command: %X \r\n", cmd_Message.B.CMD);

	}

}

