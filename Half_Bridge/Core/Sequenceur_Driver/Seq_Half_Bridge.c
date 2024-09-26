
#include "Seq_Half_Bridge.h"

void resetOutput(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
	TIM2 -> CCR1 = 0;
	TIM2 -> CCR2 = 0;
	TIM2 -> CCR3 = 0;
	/*HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);*/
}

void verityTable(void){
	int HallSensor = GPIOD->IDR & 0x0007;
	resetOutput();
	switch (HallSensor){
	// Phase 1
	case 5 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
		TIM2 -> CCR1 = 24;
		//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

		break;
	// Phase 2
	case 1 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
		TIM2 -> CCR1 = 24;
		//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

		break;
	// Phase 3
	case 3 :
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
		TIM2 -> CCR2 = 24;
		//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

		break;
	// Phase 4
		case 2 :
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
			TIM2 -> CCR2 = 24;
			//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

			break;
	// Phase 5
		case 6 :
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
			TIM2 -> CCR3 = 24;
			//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

			break;
	// Phase 6
		case 4 :
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
			TIM2 -> CCR3 = 24;
			//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
			break;
	// Default
		default :
			resetOutput();
			break;
	}

}
