/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../Sequenceur_Driver/SequencerWheel.h"
#include "..\Inc\GestionMvt.h"
#include "..\Inc\SPI_Config.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//Initalize Hall sensor for verityTable
/*uint16_t oldHallSensor_R1 = 0x0007;
uint16_t oldHallSensor_R2 = 0x0028;*/
uint16_t hallSensor_R1 = 0;
uint16_t hallSensor_R2 = 0;
/*uint8_t rotation_R1 = 1;
uint8_t rotation_R2 = 1;
uint8_t DC_R1 = 0;
uint8_t DC_R2 = 0;
uint32_t speed_R1 = 24;
uint32_t speed_R2 = 24;
uint16_t tick_R1 = 0;
uint16_t tick_R2 = 0;
uint8_t bstop = 0;*/
uint8_t counter = 0;
uint8_t pData[3];
uint16_t size = 3;
uint8_t res0 = 0;
uint8_t res1 = 0;
uint8_t res2 = 0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  resetOutput_R1();
  resetOutput_R2();
  HAL_SPI_Receive_IT(&hspi2, pData,size);
  //globalSettings.bstop = 1;
  /*hallSensor_R1 = GPIOD->IDR & 0x0007;
  hallSensor_R2 = GPIOD->IDR & 0x0028;
  verityTableHoraire_R1(hallSensor_R1);
  verityTableHoraire_R2(hallSensor_R2);*/
  //startRobot();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {		/*HAL_Delay(5000);
	    startRobot();
  	  	HAL_Delay(5000);
  	    stopRobot();
  	    settings_R2.rotation = 0;
		HAL_Delay(5000);
		startRobot();
		HAL_Delay(5000);
		stopRobot();*/
  	    //variableModification(1,1,4,4);*/
	/*if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET){
		globalSettings.bstop = 1;
	}*/
	/*if (settings_R1.tick >= 63000 || settings_R2.tick  >= 63000){
		globalSettings.bstop = 1;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	}
	if (settings_R1.flagTick == 1){
		settings_R1.flagTick = 0;
		send_SPI_message(&hspi2,3,settings_R1.tick);
		HAL_SPI_Receive_IT(&hspi2, pData,size);
	}
	if (settings_R2.flagTick == 1){
		settings_R2.flagTick = 0;
		send_SPI_message(&hspi2,3,settings_R2.tick);
		HAL_SPI_Receive_IT(&hspi2, pData,size);
	}*/

	  /*HAL_Delay(100);
	  int stater = GPIOD->IDR & 0x0007;

	  switch (stater){
	  	// Phase 1 in to 2
	  	case 5 :
	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	  		break;
	  	// Phase 2
	  	case 1 :
	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	  		break;
	  	// Phase 3
	  	case 3 :
	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	  		break;
	  	// Phase 4
	  	case 2 :
	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	  		break;
	  	// Phase 5
	  	case 6 :
	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	  		break;
	  	// Phase 6
	  	case 4 :
	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	  		break;

	  	default :
	  		break;
	  }
	   */
	  //testFunction(50);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* Fonction mise en mvt robot
 *
 *
 *
*/

void modif_DC(void)
{
  //The duty cycle value is a percentage of the reload register value (ARR). Rounding is used.*/
	settings_R1.speedMax = (uint32_t)(htim4.Instance->ARR) * (settings_R1.DC *0.1);
	settings_R2.speedMax = (uint32_t)(htim4.Instance->ARR) * (settings_R2.DC *0.1);
 /*In case of the DC being calculated as higher than the reload register, cap it to the reload register*/
 if(settings_R1.speedMax > htim2.Instance->ARR)
 {
	 settings_R1.speedMax = htim2.Instance->ARR;
 }
 if(settings_R2.speedMax> htim4.Instance->ARR)
 {
	 settings_R2.speedMax= htim4.Instance->ARR;
 }

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (globalSettings.bstop == 0) {
		hallSensor_R1 = GPIOD->IDR & 0x0007;
		hallSensor_R2 = GPIOB->IDR & 0x0038;
		/*if (settings_R1.oldHallSensor != hallSensor_R1) {
			settings_R1.tick++;

		}
		if (settings_R2.oldHallSensor != hallSensor_R2){
			settings_R2.tick++;
		}*/

		if (settings_R1.rotation == 1) {
			verityTableHoraire_R1(hallSensor_R1);
		}
		else{
			verityTableHoraireAntiHoraire_R1(hallSensor_R1);
		}
		if (settings_R2.rotation == 0) {
			verityTableHoraire_R2(hallSensor_R2);
		}
		else{
			verityTableHoraireAntiHoraire_R2(hallSensor_R2);
		}
	}
}


/* Fonction réception/envoi SPI
 *
 *
 *
*/

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi){
	if (hspi ->Instance == SPI2){
		SPI_data_processing(pData);
		/*if ((settings_R1.flagTick == 0) &(settings_R2.flagTick == 0)){
			HAL_SPI_Receive_IT(&hspi2, pData,size);
		}*/
		HAL_SPI_Receive_IT(hspi, pData,size);
	}

}


void HAL_SPI_ErrorCallback(SPI_HandleTypeDef * hspi)
{
	HAL_SPI_Receive_IT(hspi, pData,size);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
