
#include "SequencerWheel.h"

#include "C:\Users\anico\Desktop\Ecole\5a\Projet Majeur\Software\Half_Bridge\Core\Inc\Low_level_functions.h"


/**
  * @brief  Clear the ouput to control the H bridge for the BLDC.
  * @param  None
  * @retval None
  */
void resetOutput_R1(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
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
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
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
*/
int8_t verityTableHoraire_R1(int8_t oldHallSensor,int8_t hallSensor,uint32_t speed_R1){
	resetOutput_R1();
	int success = 1;
	switch (hallSensor){
	// Phase 1
	case 5 :
		//if (oldHallSensor == 0 || oldHallSensor == 4) {
			select_GPIO_out_stator(1,speed_R1,0);
			select_GPIO_out_stator(2,speed_R1,0);
		/*}else{
			resetOutput_R1();
			success = 0;
		}*/
		break;

	// Phase 2
	case 1 :
		if (oldHallSensor == 0 || oldHallSensor == 5){
			select_GPIO_out_stator(1,speed_R1,0);
			select_GPIO_out_stator(4,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
		}
		break;

	// Phase 3
	case 3 :
		if (oldHallSensor == 0 ||oldHallSensor == 1){
			select_GPIO_out_stator(3,speed_R1,0);
			select_GPIO_out_stator(4,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
			}
		break;

	// Phase 4
	case 2 :
		if (oldHallSensor == 0 ||oldHallSensor == 3){
			select_GPIO_out_stator(0,speed_R1,0);
			select_GPIO_out_stator(3,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
			}
		break;

	// Phase 5
	case 6 :
		if (oldHallSensor == 0 ||oldHallSensor == 2){
			select_GPIO_out_stator(0,speed_R1,0);
			select_GPIO_out_stator(5,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
			}
		break;

	// Phase 6
	case 4 :
		if (oldHallSensor == 0 ||oldHallSensor == 6){
			select_GPIO_out_stator(2,speed_R1,0);
			select_GPIO_out_stator(5,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
			}
		break;
	//IDLE
	case 7 :
		resetOutput_R1();
		success = 0;
	// Default
	default :
		resetOutput_R1();
		success = 0;
		break;
	}
	if (success) {
		oldHallSensor = hallSensor;
	}else{
		stopAlert();
		oldHallSensor = 7;
	}
	return oldHallSensor;
}


/**
  * @brief  To run in anti-horaire sense the selected BLDC following the pahse order.
  * If the order is not followed, the BLDC is stop.
  * @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
  * @retval oldHallSensor with the new value of the Hall Sensor.
  */
int8_t verityTableHoraireAntiHoraire_R1(int8_t oldHallSensor,int8_t hallSensor,uint32_t speed_R1)
{
	resetOutput_R1();
	int success = 1;
	switch (hallSensor){
	// Phase 1
	case 5 :
		if (oldHallSensor == 0 || oldHallSensor == 4) {
			select_GPIO_out_stator(0,speed_R1,0);
			select_GPIO_out_stator(3,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
		}
		break;

	// Phase 2
	case 1 :
		if (oldHallSensor == 0 || oldHallSensor == 5){
			select_GPIO_out_stator(0,speed_R1,0);
			select_GPIO_out_stator(5,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
		}
		break;

	// Phase 3
	case 3 :
		if (oldHallSensor == 0 ||oldHallSensor == 1){
			select_GPIO_out_stator(2,speed_R1,0);
			select_GPIO_out_stator(5,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
		}
		break;

	// Phase 4
	case 2 :
		if (oldHallSensor == 0 ||oldHallSensor == 3){
			select_GPIO_out_stator(1,speed_R1,0);
			select_GPIO_out_stator(2,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
		}
		break;

	// Phase 5
	case 6 :
		if (oldHallSensor == 0 ||oldHallSensor == 3){
			select_GPIO_out_stator(1,speed_R1,0);
			select_GPIO_out_stator(4,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
		}
		break;

	// Phase 6
	case 4 :
		if (oldHallSensor == 0 ||oldHallSensor == 6){
			select_GPIO_out_stator(3,speed_R1,0);
			select_GPIO_out_stator(4,speed_R1,0);
		}else{
			resetOutput_R1();
			success = 0;
		}
		break;
	//IDLE
	case 7 :
		resetOutput_R1();
		success = 0;
	// Default
	default :
		resetOutput_R1();
		success = 0;
		break;
	}
	if (success) {
		oldHallSensor = hallSensor;
	}else{
		stopAlert();
		oldHallSensor = 7;
	}
	return oldHallSensor;
}

/**
* @brief  To run in horaire sense the selected BLDC following the pahse order.
* If the order is not followed, the BLDC is stop.
* @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
* @retval oldHallSensor with the new value of the Hall Sensor.
*/
int8_t verityTableHoraire_R2(int8_t oldHallSensor,int8_t hallSensor,uint32_t speed_R2){
	resetOutput_R2();
	int success = 1;
	switch (hallSensor){
	// Phase 1
	case 40 :
		if (oldHallSensor == 0 || oldHallSensor == 64) {
			select_GPIO_out_stator(9,0,speed_R2);
			select_GPIO_out_stator(10,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
		}
		break;

	// Phase 2
	case 8 :
		if (oldHallSensor == 0 || oldHallSensor == 40){
			select_GPIO_out_stator(7,0,speed_R2);
			select_GPIO_out_stator(10,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
		}
		break;

	// Phase 3
	case 24 :
		if (oldHallSensor == 0 ||oldHallSensor == 8){
			select_GPIO_out_stator(9,0,speed_R2);
			select_GPIO_out_stator(10,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
			}
		break;

	// Phase 4
	case 16 :
		if (oldHallSensor == 0 ||oldHallSensor == 24){
			select_GPIO_out_stator(6,0,speed_R2);
			select_GPIO_out_stator(9,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
			}
		break;

	// Phase 5
	case 48 :
		if (oldHallSensor == 0 ||oldHallSensor == 16){
			select_GPIO_out_stator(6,0,speed_R2);
			select_GPIO_out_stator(11,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
			}
		break;

	// Phase 6
	case 64 :
		if (oldHallSensor == 0 ||oldHallSensor == 48){
			select_GPIO_out_stator(8,0,speed_R2);
			select_GPIO_out_stator(11,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
			}
		break;
	//IDLE
	case 7 :
		resetOutput_R2();
		success = 0;
	// Default
	default :
		resetOutput_R2();
		success = 0;
		break;
	}
	if (success) {
		oldHallSensor = hallSensor;
	}else{
		stopAlert();
		oldHallSensor = 7;
	}
	return oldHallSensor;
}


/**
  * @brief  To run in anti-horaire sense the selected BLDC following the pahse order.
  * If the order is not followed, the BLDC is stop.
  * @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
  * @retval oldHallSensor with the new value of the Hall Sensor.
  */
int8_t verityTableHoraireAntiHoraire_R2(int8_t oldHallSensor,int8_t hallSensor,uint32_t speed_R2)
{
	resetOutput_R2();
	int success = 1;
	switch (hallSensor){
	// Phase 1
	case 40 :
			if (oldHallSensor == 0 || oldHallSensor == 64) {
			select_GPIO_out_stator(6,0,speed_R2);
			select_GPIO_out_stator(9,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
		}
		break;

	// Phase 2
	case 8 :
		if (oldHallSensor == 0 || oldHallSensor == 40){
			select_GPIO_out_stator(9,0,speed_R2);
			select_GPIO_out_stator(11,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
		}
		break;

	// Phase 3
	case 24 :
		if (oldHallSensor == 0 ||oldHallSensor == 8){
			select_GPIO_out_stator(8,0,speed_R2);
			select_GPIO_out_stator(11,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
		}
		break;

	// Phase 4
	case 16 :
		if (oldHallSensor == 0 ||oldHallSensor == 24){
			select_GPIO_out_stator(7,0,speed_R2);
			select_GPIO_out_stator(8,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
		}
		break;

	// Phase 5
	case 48 :
		if (oldHallSensor == 0 ||oldHallSensor == 16){
			select_GPIO_out_stator(7,0,speed_R2);
			select_GPIO_out_stator(10,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
		}
		break;

	// Phase 6
	case 64 :
		if (oldHallSensor == 0 ||oldHallSensor == 48){
			select_GPIO_out_stator(9,0,speed_R2);
			select_GPIO_out_stator(10,0,speed_R2);
		}else{
			resetOutput_R2();
			success = 0;
		}
		break;
	//IDLE
	case 7 :
		resetOutput_R2();
		success = 0;
	// Default
	default :
		resetOutput_R2();
		success = 0;
		break;
	}
	if (success) {
		oldHallSensor = hallSensor;
	}else{
		stopAlert();
		oldHallSensor = 7;
	}
	return oldHallSensor;
}
