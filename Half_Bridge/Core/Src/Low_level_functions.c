#include "Low_level_functions.h"
#include "GestionMvt.h"

/*
 * ,uint32_t speed_R1,uint32_t speed_R2
 */
void select_GPIO_out_stator(int stator_num){
int state = 0;
switch (stator_num){
	// Q1L_R1
	case 0 :
		if (state == 0){
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
		}

		break;

	// Q1H_R1
	case 1 :

		if (state == 0){
			TIM2 -> CCR1 = 0;
		}
		else{
			TIM2 -> CCR1 = settings_R1.speed;
		}

		break;

	// Q2L_R1
	case 2 :

		if (state == 0){
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
		}
		break;

	// Q2H_R1
	case 3 :
		if (state == 0){
			TIM2 -> CCR1 = 0;
		}
		else{
			TIM2 -> CCR2 = settings_R1.speed;
		}
		break;

	// Q3L_R1
	case 4 :
		if (state == 0){
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		}
		break;

	// Q3H_R1
	case 5 :
		if (state == 0){
			TIM2 -> CCR3 = 0;
		}
		else{
			TIM2 -> CCR3 = settings_R1.speed;
		}

		break;
	// Q1L_R2
	case 6 :
		if (state == 0){
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
		}
		break;

	// Q1H_R2
	case 7 :

		if (state == 0){
			TIM4 -> CCR1 = 0;
		}
		else{
			TIM4 -> CCR1 = settings_R2.speed;
		}
		break;

	// Q2L_R2
	case 8 :
		if (state == 0){
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		}
		break;

	// Q2H_R2
	case 9 :
		if (state == 0){
			TIM4 -> CCR2 = 0;
		}
		else{
			TIM4 -> CCR2 = settings_R2.speed;
		}
		break;

	// Q3L_R2
	case 10 :
		if (state == 0){
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
		}
		break;

	// Q3H_R2
	case 11 :
		if (state == 0){
			TIM4 -> CCR3 = 0;
		}
		else{
			TIM4 -> CCR3 = settings_R2.speed;
		}
		break;

	// Default
	default :
		
		break;
}

return;

};
