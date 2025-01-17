
#include "SequencerWheel.h"
#include "GestionMvt.h"
#include "C:\Users\Julien\Desktop\Work or others Install\Projet Majeur 2024\Half_Bridge\Core\Inc\Low_level_functions.h"

int counterRamp_R1 = 0;
int counterRamp_R2 = 0;

void testFunction(int del){
	HAL_Delay(del);
	resetOutput_R1();
	select_GPIO_out_stator(1);
	select_GPIO_out_stator(2);
	HAL_Delay(del);
	resetOutput_R1();
	select_GPIO_out_stator(1);
	select_GPIO_out_stator(4);
	HAL_Delay(del);
	resetOutput_R1();
	select_GPIO_out_stator(3);
	select_GPIO_out_stator(4);
	HAL_Delay(del);
	resetOutput_R1();
	select_GPIO_out_stator(0);
	select_GPIO_out_stator(3);
	HAL_Delay(del);
	resetOutput_R1();
	select_GPIO_out_stator(0);
	select_GPIO_out_stator(5);
	HAL_Delay(del);
	resetOutput_R1();
	select_GPIO_out_stator(2);
	select_GPIO_out_stator(5);
}



/**
  * @brief  Clear the ouput to control the H bridge for the BLDC.
  * @param  None
  * @retval None
  */
void resetOutput_R1(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
	TIM2 -> CCR1 = 0;
	TIM2 -> CCR2 = 0;
	TIM2 -> CCR3 = 0;
}

/**
  * @brief  Clear the ouput to control the H bridge for the BLDC.
  * @param  None
  * @retval None
  */
void resetOutput_R2(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
	TIM4 -> CCR1 = 0;
	TIM4 -> CCR2 = 0;
	TIM4 -> CCR3 = 0;
}

void stopAlert(void){
	resetOutput_R1();
	resetOutput_R2();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

/**
* @brief  To run in horaire sense the selected BLDC following the pahse order.
* If the order is not followed, the BLDC is stop.
* @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
* @retval oldHallSensor with the new value of the Hall Sensor.
* int8_t oldHallSensor,int8_t hallSensor,uint32_t speed_R1
* int8_t
*/
void verityTableHoraire_R1(int8_t hallSensor){
	if (settings_R1.speed < settings_R1.speedMax) {
		if (counterRamp_R1 == 100) {
			settings_R1.speed++;
			counterRamp_R1 = 0;
		}
		else {
			counterRamp_R1++;
		}
	}
	// Added descending ramp
	else if(settings_R1.speed > settings_R1.speedMax){
		settings_R1.speed--;
	}
	switch (hallSensor){
	// Phase 1
	case 5 :
			TIM2 -> CCR1 = settings_R1.speed;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
			TIM2 -> CCR3 = 0;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
			TIM2 -> CCR2 = 0;
		break;

	// Phase 2
	case 1 :
		TIM2 -> CCR1 = settings_R1.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		TIM2 -> CCR2 = 0;
		TIM2 -> CCR3 = 0;
		break;

	// Phase 3
	case 3 :
		TIM2 -> CCR1 = 0;
		TIM2 -> CCR2 = settings_R1.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
		TIM2 -> CCR3 = 0;
		break;

	// Phase 4
	case 2 :
		TIM2 -> CCR2 = settings_R1.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
		TIM2 -> CCR3 = 0;
		TIM2 -> CCR1 = 0;
		break;

	// Phase 5
	case 6 :
		TIM2 -> CCR3 = settings_R1.speed;
		TIM2 -> CCR2 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		TIM2 -> CCR1 = 0;
		break;

	// Phase 6
	case 4 :
		TIM2 -> CCR3 = settings_R1.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		TIM2 -> CCR1 = 0;
		TIM2 -> CCR2 = 0;
		break;
	// Default
	default :
		//resetOutput_R1();
		break;
	}

	return;
}


/**
  * @brief  To run in anti-horaire sense the selected BLDC following the pahse order.
  * If the order is not followed, the BLDC is stop.
  * @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
  * @retval oldHallSensor with the new value of the Hall Sensor.
  */
void verityTableHoraireAntiHoraire_R1(int8_t hallSensor)
{
	if (settings_R1.speed < settings_R1.speedMax) {
		if (counterRamp_R1 == 100) {
			settings_R1.speed++;
			counterRamp_R1 = 0;
		}
		else {
			counterRamp_R1++;
		}
	}
	// Added descending ramp
	else if(settings_R1.speed > settings_R1.speedMax){
		settings_R1.speed--;
	}
	// Added descending ramp
	else if(settings_R1.speed > settings_R1.speedMax){
		settings_R1.speed--;
	}
	switch (hallSensor){
	// Phase 1
	case 5 :
			TIM2 -> CCR2 = settings_R1.speed;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
			TIM2 -> CCR3 = 0;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
			TIM2 -> CCR1 = 0;
		break;

	// Phase 2 - Q1L & Q3H
	case 1 :
		TIM2 -> CCR3 = settings_R1.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
		TIM2 -> CCR2 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
		TIM2 -> CCR1 = 0;

		break;

	// Phase 3 - Q2L & Q3H
	case 3 :
		TIM2 -> CCR3 = settings_R1.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
		TIM2 -> CCR1 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		TIM2 -> CCR3 = 0;
		break;

	// Phase 4 - Q1H & Q2L
	case 2 :
		TIM2 -> CCR1 = settings_R1.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		TIM2 -> CCR3 = 0;
		TIM2 -> CCR2 = 0;
		break;

	// Phase 5 - Q1H & Q3L
	case 6 :
		TIM2 -> CCR1 = settings_R1.speed;
		TIM2 -> CCR2 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		TIM2 -> CCR3 = 0;
		break;

	// Phase 6 - Q2H & Q3L
	case 4 :
		TIM2 -> CCR2 = settings_R1.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		TIM2 -> CCR3 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
		TIM2 -> CCR1 = 0;
		break;
	// Default
	default :
		//resetOutput_R1();
		break;
	}
	return;
}

/**
* @brief  To run in horaire sense the selected BLDC following the pahse order.
* If the order is not followed, the BLDC is stop.
* @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
* @retval oldHallSensor with the new value of the Hall Sensor.
*/
void verityTableHoraire_R2(int8_t hallSensor){
	if (settings_R2.speed < settings_R2.speedMax) {
		if (counterRamp_R2 == 100) {
			settings_R2.speed++;
			counterRamp_R2 = 0;
		}
		else {
			counterRamp_R2++;
		}
	}
	// Added descending ramp
	else if(settings_R2.speed > settings_R2.speedMax){
		settings_R2.speed--;
	}
	switch (hallSensor){
		// Phase 1 - Q1H & Q2L
		case 0x28 :
				TIM4 -> CCR1 = settings_R2.speed;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
				TIM4 -> CCR3 = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
				TIM4 -> CCR2 = 0;
			break;

		// Phase 2 - Q1H & Q3L
		case 0x08 :
			TIM4 -> CCR1 = settings_R2.speed;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
			TIM4 -> CCR2 = 0;
			TIM4 -> CCR3 = 0;
			break;

		// Phase 3 - Q2H & Q3L
		case 0x18 :
			TIM4 -> CCR1 = 0;
			TIM4 -> CCR2 = settings_R2.speed;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
			TIM4 -> CCR3 = 0;
			break;

		// Phase 4 - Q1L & Q2H
		case 0x10 :
			TIM4 -> CCR2 = settings_R2.speed;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
			TIM4 -> CCR3 = 0;
			TIM4 -> CCR1 = 0;
			break;

		// Phase 5 - Q1L & Q3H
		case 0x30 :
			TIM4 -> CCR3 = settings_R2.speed;
			TIM4 -> CCR2 = 0;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
			TIM4 -> CCR1 = 0;
			break;

		// Phase 6 - Q2L & Q3H
		case 0x20 :
			TIM4 -> CCR3 = settings_R2.speed;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
			TIM4 -> CCR1 = 0;
			TIM4 -> CCR2 = 0;
			break;
		// Default
		default :
			//resetOutput_R1();
			break;
		}
	settings_R2.oldHallSensor = hallSensor;
	return;
}


/**
  * @brief  To run in anti-horaire sense the selected BLDC following the pahse order.
  * If the order is not followed, the BLDC is stop.
  * @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
  * @retval oldHallSensor with the new value of the Hall Sensor.
  */
void verityTableHoraireAntiHoraire_R2(int8_t hallSensor)
{
	if (settings_R2.speed < settings_R2.speedMax) {
		if (counterRamp_R2 == 100) {
			settings_R2.speed++;
			counterRamp_R2 = 0;
		}
		else {
			counterRamp_R2++;
		}
	}
	// Added descending ramp
	else if(settings_R2.speed > settings_R2.speedMax){
		settings_R2.speed--;
	}
	switch (hallSensor){
	// Phase 1 - Q1L & Q2H
	case 0b101000 :
			TIM4 -> CCR2 = settings_R2.speed;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
			TIM4 -> CCR3 = 0;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
			TIM4 -> CCR1 = 0;
		break;

	// Phase 2 - Q1L & Q3H
	case 0b001000 :
		TIM4 -> CCR3 = settings_R2.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
		TIM4 -> CCR2 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		TIM4 -> CCR1 = 0;

		break;

	// Phase 3 - Q2L & Q3H
	case 0b011000 :
		TIM4 -> CCR3 = settings_R2.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		TIM4 -> CCR1 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		TIM4 -> CCR3 = 0;
		break;

	// Phase 4 - Q1H & Q2L
	case 0b010000 :
		TIM4 -> CCR1 = settings_R2.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		TIM4 -> CCR3 = 0;
		TIM4 -> CCR2 = 0;
		break;

	// Phase 5 - Q1H & Q3L
	case 0b110000 :
		TIM4 -> CCR1 = settings_R2.speed;
		TIM4 -> CCR2 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		TIM4 -> CCR3 = 0;
		break;

	// Phase 6 - Q2H & Q3L
	case 0b100000 :
		TIM4 -> CCR2 = settings_R2.speed;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		TIM4 -> CCR3 = 0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		TIM4 -> CCR1 = 0;
		break;
	// Default
	default :
		//resetOutput_R1();
		break;
	}
	return;
}
