/*
 * Gestion.Mvt.h
 *
 *  Created on: 23 nov. 2024
 *      Author: anico
 */

#ifndef INC_GESTIONMVT_H_
#define INC_GESTIONMVT_H_


typedef struct{
	uint16_t oldHallSensor;
	uint8_t rotation;
	uint8_t DC;
	uint32_t speed;
	uint32_t speedMax;
	uint16_t tick;
	uint8_t flagTick;
}Settings_RX;

typedef struct {
	uint8_t  bstop;
}GlobalSettings;

extern Settings_RX settings_R1;
extern Settings_RX settings_R2;
extern GlobalSettings globalSettings;

void stopRobot();
void startRobot();
void variableModification (uint8_t rotation_R1,uint8_t rotation_R2,uint8_t DC_R1,uint8_t DC_R2);
void modif_DC(void);

#endif /* INC_GESTIONMVT_H_ */
