/*
 * GestionMvt.c
 *
 *  Created on: Nov 21, 2024
 *      Author: anico
 */

#include "stm32f3xx_hal.h"
#include "main.h"
#include "GestionMvt.h"
#include "SequencerWheel.h"

/*void stopRobot(bstop,){
	bstop = 1;
	resetOutput_R1();
	resetOutput_R2();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
}

 startRobot(){
	oldHallSensor_R1 = 0x0007;
	oldHallSensor_R2 = 0x0028;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	bstop = 0;
}

void variableModification (){

}*/
