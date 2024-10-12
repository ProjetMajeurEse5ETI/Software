#include "Low_level_functions.h"



void select_GPIO_out_stator(int stator_num){

switch (stator_num){
	// Q1L
	case 0 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
		break;

	// Q1H
	case 1 :
		TIM2 -> CCR1 = 24;
		break;

	// Q2L
	case 2 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
		break;

	// Q2H
	case 3 :
		TIM2 -> CCR2 = 24;
		break;

	// Q3L
	case 4 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
		break;

	// Q3H
	case 5 :
		TIM2 -> CCR3 = 24;
		break;

	// Default
	default :
		
		break;
}

return;

};
