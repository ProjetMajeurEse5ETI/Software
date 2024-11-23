#include "Low_level_functions.h"



void select_GPIO_out_stator(int stator_num,uint32_t speed_R1,uint32_t speed_R2){

switch (stator_num){
	// Q1L_R1
	case 0 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
		break;

	// Q1H_R1
	case 1 :
		TIM2 -> CCR1 = speed_R1;
		break;

	// Q2L_R1
	case 2 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
		break;

	// Q2H_R1
	case 3 :
		TIM2 -> CCR2 = speed_R1;
		break;

	// Q3L_R1
	case 4 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		break;

	// Q3H_R1
	case 5 :
		TIM2 -> CCR3 = speed_R1;
		break;
	// Q1L_R2
	case 6 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
		break;

	// Q1H_R2
	case 7 :
		TIM4 -> CCR1 = speed_R2;
		break;

	// Q2L_R2
	case 8 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		break;

	// Q2H_R2
	case 9 :
		TIM4 -> CCR2 = speed_R2;
		break;

	// Q3L_R2
	case 10 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
		break;

	// Q3H_R2
	case 11 :
		TIM4 -> CCR3 = speed_R2;
		break;

	// Default
	default :
		
		break;
}

return;

};
