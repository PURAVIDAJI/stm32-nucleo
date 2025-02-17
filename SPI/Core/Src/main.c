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
#include "gpio.h"

#include "M95.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

	uint8_t StatusRegisterValue =0;
	uint8_t ReadValue =0;
	uint8_t M95Type;
	uint8_t TxData1 ='A';
	uint8_t TxData2 ='B';
	uint8_t TxData3 ='C';


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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  //Disable chip selects.
  M95Type = M95040; DisableChipSelectM95(M95Type);
  M95Type = M95256; DisableChipSelectM95(M95Type);
  M95Type = M95M04; DisableChipSelectM95(M95Type);
   //those are distinct SPI memory device


  //Disable write-protect and hold
  DisableWriteProtectM95();
  DisableHoldM95();



 //Turn off the block protection for all devices
  M95Type = M95040;
  StatusRegisterValue = ReadStatusRegisterM95(M95Type);
  StatusRegisterValue = StatusRegisterValue & ~(0x0C);
  //Make BP1, BP2 as 0 - disable block protection
  WriteStatusRegisterM95(M95Type, StatusRegisterValue);
  //rewrite this value to EEPROM


  M95Type = M95256;
  StatusRegisterValue = ReadStatusRegisterM95(M95Type);
  StatusRegisterValue = StatusRegisterValue & ~(0x0C);
  WriteStatusRegisterM95(M95Type, StatusRegisterValue);


  M95Type = M95M04;
    StatusRegisterValue = ReadStatusRegisterM95(M95Type);
    StatusRegisterValue = StatusRegisterValue & ~(0x0C);
    WriteStatusRegisterM95(M95Type, StatusRegisterValue);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  M95Type = M95040;
	  WriteByteM95(M95Type, 0x00000001, TxData1);
	  StatusRegisterValue =0;
	  StatusRegisterValue = ReadStatusRegisterM95(M95Type);
	  while (StatusRegisterValue & 0x01) {
		  StatusRegisterValue =ReadStatusRegisterM95(M95Type);
	  }
	  //when wip bit is 1 which means it is being written, so in this case use "while" to read updated data
	  ReadValue=0;

	 ReadValue =ReadByteM95(M95Type, 0x00000001);
	 if(TxData1 == ReadValue){
		 HAL_Delay(1);
	 }



	  M95Type = M95256;
	  WriteByteM95(M95Type, 0x00000001, TxData2);
	  StatusRegisterValue =0;
	  StatusRegisterValue = ReadStatusRegisterM95(M95Type);
	  while (StatusRegisterValue & 0x01) {
		  StatusRegisterValue =ReadStatusRegisterM95(M95Type);

	  }
	  ReadValue=0;

	 ReadValue =ReadByteM95(M95Type, 0x00000001);
	 if(TxData2 == ReadValue){
		 HAL_Delay(1);
	 }



	  M95Type = M95M04;
	  WriteByteM95(M95Type, 0x00000001, TxData3);
	  StatusRegisterValue =0;
	  StatusRegisterValue = ReadStatusRegisterM95(M95Type);
	  while (StatusRegisterValue & 0x01) {
		  StatusRegisterValue =ReadStatusRegisterM95(M95Type);

	  }
	  ReadValue=0;

	 ReadValue =ReadByteM95(M95Type, 0x00000001);
	 if(TxData3 == ReadValue){
		 HAL_Delay(1);
	 }



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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
