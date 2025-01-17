/*
 * GestionMvt.c
 *
 *  Created on: Nov 21, 2024
 *      Author: anico
 */

#include "stm32f3xx_hal.h"
#include "GestionMvt.h"
#include "../Sequenceur_Driver/SequencerWheel.h"
#include "C:\Users\Julien\Desktop\Work or others Install\Projet Majeur 2024\Half_Bridge\Core\Inc\Low_level_functions.h"
#include "main.h"

uint16_t hallSensor_R1_Start = 0;
uint16_t hallSensor_R2_Start = 0;

Settings_RX settings_R1 = {
		.oldHallSensor = 0x0007,
		.rotation =1,
		.DC = 0,
		.speed = 2,
		.speedMax = 20,
		.tick = 0,
		.flagTick = 0
};
Settings_RX settings_R2 = {
		.oldHallSensor = 0x0038,
		.rotation =1,
		.DC = 0,
		.speed = 2,
		.speedMax = 20,
		.tick = 0,
		.flagTick = 0
};

GlobalSettings globalSettings = {
		.bstop = 1,
};

void stopRobot(){
	globalSettings.bstop = 1;
	resetOutput_R1();
	resetOutput_R2();
	// Minimum of 5 is required to enable the retriggering of the  interruption once the start is called again.
	settings_R1.speed = 5;
	settings_R2.speed = 5;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
}

 void startRobot(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	settings_R1.oldHallSensor = 0x0007;
	settings_R2.oldHallSensor = 0x0038;
	globalSettings.bstop = 0;
	hallSensor_R1_Start = GPIOD->IDR & 0x0007;
	hallSensor_R2_Start = GPIOB->IDR & 0x0038;
	//settings_R1.tick++;
	if (settings_R1.rotation == 1) {
		verityTableHoraire_R1(hallSensor_R1_Start);
	}
	else {
		verityTableHoraireAntiHoraire_R1(hallSensor_R1_Start);
	}
	//settings_R2.tick++;
	if (settings_R2.rotation == 1) {
		verityTableHoraire_R2(hallSensor_R2_Start);
	}
	else {
		verityTableHoraireAntiHoraire_R2(hallSensor_R2_Start);
	}
}

void variableModification(uint8_t rotation_R1,uint8_t rotation_R2,uint8_t DC_R1,uint8_t DC_R2){
	settings_R1.rotation = rotation_R1;
	settings_R2.rotation = rotation_R2;
	settings_R1.DC = DC_R1;
	settings_R2.DC = DC_R2;
	modif_DC();
}
