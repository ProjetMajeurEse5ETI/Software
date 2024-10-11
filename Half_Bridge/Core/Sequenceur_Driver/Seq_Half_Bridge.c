
#include "Seq_Half_Bridge.h"
#include "../Inc/Low_level_function.h"

void resetOutput(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
	TIM2 -> CCR1 = 0;
	TIM2 -> CCR2 = 0;
	TIM2 -> CCR3 = 0;
}

void verityTableHoraire(void){
	int HallSensor = GPIOD->IDR & 0x0007; //lecture par bit (masque)
	resetOutput();
	switch (HallSensor){
	// Phase 1
	case 5 :
		select_GPIO_out_stator(1);
		select_GPIO_out_stator(3);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
		TIM2 -> CCR1 = 24;*/
		break;

	// Phase 2
	case 1 :
		select_GPIO_out_stator(2);
		select_GPIO_out_stator(3);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
		TIM2 -> CCR1 = 24;*/
		break;

	// Phase 3
	case 3 :
		select_GPIO_out_stator(2);
		select_GPIO_out_stator(4);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
		TIM2 -> CCR2 = 24;*/
		break;

	// Phase 4
	case 2 :
		select_GPIO_out_stator(0);
		select_GPIO_out_stator(4);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
		TIM2 -> CCR2 = 24;
		break;

	// Phase 5
	case 6 :
		select_GPIO_out_stator(0);
		select_GPIO_out_stator(5);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
		TIM2 -> CCR3 = 24;
		break;

	// Phase 6
	case 4 :
		select_GPIO_out_stator(1);
		select_GPIO_out_stator(5);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
		TIM2 -> CCR3 = 24;
		break;

	// Default
	default :
		resetOutput();
		break;
	}
}

void verityTableHoraireAntiHoraire(void)
{
	int HallSensor = GPIOD->IDR & 0x0007;//lecture par bit (masque)
	resetOutput();
	switch (HallSensor){
	// Phase 1
	case 4 :
		select_GPIO_out_stator(2);
		select_GPIO_out_stator(4);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
		TIM2 -> CCR2 = 24;*/
		break;

	// Phase 2
	case 6 :
		select_GPIO_out_stator(2);
		select_GPIO_out_stator(3);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
		TIM2 -> CCR1 = 24;*/
		break;

	// Phase 3
	case 2 :
		select_GPIO_out_stator(1);
		select_GPIO_out_stator(3);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
		TIM2 -> CCR1 = 24;*/
		break;

	// Phase 4
	case 3 :
		select_GPIO_out_stator(1);
		select_GPIO_out_stator(5);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
		TIM2 -> CCR3 = 24;*/
		break;

	// Phase 5
	case 1 :
		select_GPIO_out_stator(0);
		select_GPIO_out_stator(5);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
		TIM2 -> CCR3 = 24;*/
		break;

	// Phase 6
	case 5 :
		select_GPIO_out_stator(1);
		select_GPIO_out_stator(4);
		/*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
		TIM2 -> CCR2 = 24;*/
		break;

	// Default
	default :
		resetOutput();
		break;
	}
}
