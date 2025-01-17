/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t  telemetre;
uint8_t telemetre_state;
// FLAG DE FINISH
#define FLAG_CONFIG 0b1011
uint8_t flag_tele = FLAG_CONFIG;
uint8_t flag_cmp[4] = {0xff, 0xff, 0xff, 0xff};

//STOCKAGE DELAY
int delay_tele[4] = {0, 0, 0, 0};

uint8_t FLAG = 0;
uint8_t FLAG_OLD = 0;
uint8_t ANGLE = 0;
uint8_t ANGLE_OLD = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

	/**********************************Servo moteur *************************************/

	void rotate(TIM_HandleTypeDef* tim, int channel, int angle){
	__HAL_TIM_SET_COMPARE(tim, channel, 10*angle+1500);
	}

	void ballayage(TIM_HandleTypeDef* tim, int channel, int min, int max, int inc){
	static int current_value = 0;
	static int direction = 1;

	static int measure_angle = 0;
	static int measure_val = 0;

	for(int k=0;k<12800*8*2 ;k++); //48ms * 2

	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, 1000);
	int val = HAL_ADC_GetValue(&hadc);
	if(val >= measure_val){
		 measure_val = val;
		 measure_angle = current_value;
	 }

	current_value += direction * inc;

	if (current_value > max-inc || current_value < min+inc) {
		direction *= -1;
		//printf("%d\r\n", measure_angle);
		ANGLE = measure_angle;
		measure_val = 0;
	}

	//printf("%d\n\r", current_value);
	 //printf("%d : %d | ",current_value, val);
	 // printf("%d | %d\r\n", val, current_value);

	 rotate(tim, channel, current_value);
	 display();
	}

	 /**********************************Telemetre *************************************/
	void trig_telemetre(void){
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10|GPIO_PIN_8, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9|GPIO_PIN_7, GPIO_PIN_SET);
		 for(int k=0;k<64;k++); //10us (mesurer 25us)
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10|GPIO_PIN_8, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9|GPIO_PIN_7, GPIO_PIN_RESET);
	}

	/********************************** Communication *************************************/
	void display(void){
		int verif_cmp = 1;
		for (int i=0; i<4; i++){
			if (flag_cmp[i]<2){
				verif_cmp = 0;
			}
		}
		if ((FLAG != FLAG_OLD) && (verif_cmp == 1)){
			FLAG_OLD = FLAG;
			//printf("!%c\n", FLAG_OLD);
			uint8_t ms[2] = {'!', FLAG_OLD};
			HAL_UART_Transmit(&hlpuart1, &ms, 2, 0xFFFF);
			//printf((uint8_t)FLAG_OLD);
			//printf("\r\n");
		}
		if ((ANGLE < ANGLE_OLD-10) || (ANGLE >  ANGLE_OLD+10)){
		//if (ANGLE != ANGLE_OLD){
			ANGLE_OLD = ANGLE;
			//printf("A%c\n", ANGLE_OLD);
			uint8_t ms[2] = {'A', ANGLE_OLD};
			HAL_UART_Transmit(&hlpuart1, &ms, 2, 0xFFFF);
			//printf((uint8_t)ANGLE_OLD);
			//printf("\r\n");
		}
	}

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
  MX_I2C1_Init();
  MX_LPUART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM21_Init();
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim21, TIM_CHANNEL_2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  ballayage(&htim21, TIM_CHANNEL_2, -70, 70, 10);
	  //printf("%ld\r\n", HAL_GetTick());

	  if (flag_tele == FLAG_CONFIG){
		 trig_telemetre();

		  //printf("%d\r\n", delay_tele[0]);
		  flag_tele = 0;
	  }
	  //display();
	  //HAL_Delay(400);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//test just pin a voir si on doit test la bank aussi
	switch (GPIO_Pin)
	{
	case GPIO_PIN_11:
		telemetre = 0;
		telemetre_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);
		break;
	case GPIO_PIN_9:
		telemetre = 1;
		telemetre_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
		break;
	case GPIO_PIN_8:
		telemetre = 2;
		telemetre_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);
		break;
	case GPIO_PIN_6:
		telemetre = 3;
		telemetre_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
		break;
	default:
		break;
	}

	//printf("telemetre : %d, state :%d\r\n", telemetre, telemetre_state);

	if (telemetre_state == 1)
	{
		delay_tele[telemetre] = HAL_GetTick();
		//printf("telemetre : %d, %d\r\n", telemetre, flag_tele);
	}
	else{
		delay_tele[telemetre] = HAL_GetTick() - delay_tele[telemetre];
		if (delay_tele[telemetre] <= 2){
			if (FLAG & (1<<telemetre)){
				flag_cmp[telemetre]++;
			}else{
				flag_cmp[telemetre] = 0;
			}
			FLAG |= (1<<telemetre);
			//printf("ATTENTION : %u\r\n", FLAG);
		}else{
			if (FLAG & (1<<telemetre)){
				flag_cmp[telemetre] = 0;
			}else{
				flag_cmp[telemetre]++;
			}
			FLAG &= ~(1<<telemetre);
			//printf("ATTENTION : %u\r\n", FLAG);
		}
		flag_tele |= (1<<telemetre);
		display();
	}
    /*if (GPIO_Pin == GPIO_PIN_0) {
        // Code à exécuter lorsque l'interruption est déclenchée sur PA0 ou PB0
        printf("Interruption externe détectée sur PA0 ou PB0!\n");
    }*/
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
