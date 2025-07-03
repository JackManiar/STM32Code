/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

//function that takes in the handle type, port type, pin number, potentiometer select, and value and sets the potentiometer to that value
//function example:
//MP41050_Write_Bit(&hspi1, GPIOA, GPIO_PIN_6, 128)
void MP41050_Write_Bit(SPI_HandleTypeDef *hspi,GPIO_TypeDef* csPort, uint16_t csPin, uint8_t value) {
	if(value < 0 || value > 255){ //error checking
			printf("Error(Write_Bit): Value out of range\n");
					return; // Indicate failure
		}
	//format: [XXC1C0 XXXP0] [DDDD DDDD]
	//XX = don't care bits
	//C1C0(command bits): 00, 11 = no command executed, 01 = write data, 10 = put pots in shutdown mode
	//P0(pot select bits): 0 = nothing, 1 = pot 0
	//D...D = new register data,

	//setting the resistance, calculating D_n, implement this with a function later
	//R_WA = (R_AB)(256-D_n)/256 + R_w, R_WB = (R_AB)(D_n)/256 + R_w
	//R_WA = (50k)(256-D_n)/256 + wiper resistance, R_WB = (50k)(D_n)/256 + wiper resistance

	//shutdown mode: disconnects the "A" terminal from the resistor stack and simultaneously connects the wiper to the "B" terminal. During shutdown mode, the content of the wiper register can be changed and the pot return from shutdown to the new value. The wiper is reset to the mid-scale position upon power-up. The reset pin implements a hardware reset and also returns the wiper to mid-scale.
	//The shutdown command allows the user to put the application circuit into power-saving mode. In this mode, the a terminal A is open-circuited and the B and W terminals are shorted together. The command select bits C1C0 are set to 10. The pot selection bits P1P0 allow each pot to be shut down independently. If either P1P0 are high, the respective pot will enter shutdown mode. The data bits following the command byte still need to be transmitted for the shutdown command, but they are don't care bits.

	uint8_t command = 0b00010001;
	uint8_t data[2] = {command, value}; //concatenating bit strings

	//executing any command is accomplished by setting CS low
	//then clocking-in a command byte followed by a data byte into
	//the 16-bit shift reg, the command is executed when CS is raised

	//resets cs low to begin data transfer
	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

	//sends the 16 bit command
	HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

	//sets cs high to end the data transfer
	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}

//same as above function but takes in resistance value instead of 0-255
void MP41050_Write_Resistance(SPI_HandleTypeDef *hspi,GPIO_TypeDef* csPort, uint16_t csPin, int res) {
	if(res < 0 || res > 50000){ //error checking
			printf("Error(Write_Resistance): Resistance out of range\n");
					return; // Indicate failure
		}

	uint8_t command = 0b00010001;
	uint8_t data[2] = {command, resistanceToBit(res)};

	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}

//function that takes in desired potentiometer value and returns the 0-255 value that corresponds for use with the MP41510 function
uint8_t resistanceToBit(int res){
	if(res < 0 || res > 50000){ //error checking
		printf("Error(resToBit): Resistance out of range\n");
				return 0xFF; // Indicate failure
	}

	return (uint8_t)((res * 255 + 25000) / 50000); //the 25000 is added so that the truncation actually rounds

}

//function that puts the pots in shutdown mode when not being used
//in shutdown mode, the wiper gets shorted to ground, this saves power for when they are not being used
//to wake up, just call the write functions
void MP41050_Shutdown(SPI_HandleTypeDef *hspi, GPIO_TypeDef* csPort, uint16_t csPin){
	uint8_t command = 0b00100001; //command says enter shutdown mode
	uint8_t data[2] = {command, 0b00000000}; //still need to send don't care bits

	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}


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
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* Example code to light up the led on board
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);//LED On
	  HAL_Delay(1000); //delay 1 sec
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);//LED On
	  HAL_Delay(1000); //delay 1 sec
	  */

	  //beginning MCP41050 resistor control code


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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
