/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************

  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "ade7953_reg.h"
#include "testFunc.h"
#include "espWiFi.h"
#include "math.h"

void SystemClock_Config(void);
void Error_Handler(void);
static void MX_NVIC_Init(void);

uint8_t signFlag;

#define euroConst		0.05

int main(void)
{
	uint8_t count = 0;
	uint32_t CurrentRaw = 0;
	float Voltage = 0, Current = 0;
	float ActiveP = 0, ApparentP = 0;
	float PowerF = 0;
	float Wh = 0, SumWh = 0, SumBill = 0;
	
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
	//HAL_SPI_Init(&hspi1);
	__HAL_SPI_ENABLE(&hspi1);
	
  //MX_SPI2_Init();
  //MX_USART1_UART_Init();	********	/*VRATITI ZA UART1!!*/***********
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();

  MX_NVIC_Init();		/* Initialize interrupts */		
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RST_ESP_GPIO_Port, RST_ESP_Pin, GPIO_PIN_SET);
	ADE7953_CS_HIGH();

	ADE7953_reset();								/*PO POTREBI RESETIRAJ ADE!!!*/
	ADE7953_RES_HIGH();
	ADE7953_init();									/*PO POTREBI INICIJALIZIRAJ ADE!!!*/

//	espCheckConnection();
 // ADE7953_SetGain(3);
	while (1)
  {
// reset ADE		
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 0)
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
			ADE7953_reset();
			HAL_Delay(10);
			ADE7953_init();
		}
		else HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

// reset ESP		
		if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) == 0)
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RST_ESP_GPIO_Port, RST_ESP_Pin, GPIO_PIN_RESET);
			HAL_Delay(1000);
			
		}
		else
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RST_ESP_GPIO_Port, RST_ESP_Pin, GPIO_PIN_SET);
		}
		
		if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == 0)
		{
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
			EspChechTime();
			HAL_Delay(1000);
		}
		else
		{
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
		}
		
		if(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == 0)
		{
			HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
			EspSendCSVToEmoncms(Voltage, Current, ActiveP, ApparentP, PowerF, Wh, SumWh, SumBill);
		}
		
		else
		{
			HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
		}
//		if((count % 2) == 0)
//		{
//			if(CurrentRaw <= 25000) ADE7953_SetGain(3);
//			else if(CurrentRaw > 25000 && CurrentRaw <= 50000) ADE7953_SetGain(2);
//			else if(CurrentRaw > 50000 && CurrentRaw <= 100000) ADE7953_SetGain(1);
//			else if(CurrentRaw > 300000) ADE7953_SetGain(0);
//			count = 0;	
//		}
//		
		ADE7953_RegisterValue32(VRMS_32, "VRMS: ", 1);
		CurrentRaw = ADE7953_RegisterValue32(IRMSA_32, "IRMS: ", 1);
		ADE7953_RegisterValue32_Signed(AWATT_32, "AWATT: ", 1);
		ADE7953_RegisterValue32_Signed(AVAR_32, "AVAR: ", 1);
		ADE7953_RegisterValue32_Signed(AVA_32, "AVA: ", 1);
		ADE7953_RegisterValue16_Signed(PFA, "PFA: ", 1);
		ADE7953_RegisterValue16_Signed(ANGLE_A, "ANGLE_A: ", 1);
		ADE7953_RegisterValue16(Period, "Period: ", 1);
		
//		ADE7953_RegisterValue32_Signed(AENERGYA_32, "\nAENERGYA: ", 1);
//		ADE7953_RegisterValue32_Signed(RENERGYA_32, "RENERGYA: ", 1);
//		ADE7953_RegisterValue32_Signed(APENERGYA_32, "APENERGYA: ", 1);
		
		Voltage = ADE7953_CalculateRegisterValue32(VRMS_32, "\nVoltage: ", " V", 1);
		Current = ADE7953_CalculateRegisterValue32(IRMSA_32, "Current: ", " A", 1);
		ActiveP = ADE7953_CalculateRegisterValue32_Signed(AWATT_32, "Active Power : ", " W", 1);
		ApparentP = ADE7953_CalculateRegisterValue32_Signed(AVA_32, "Apparent Power : ", " VA", 1);
		PowerF = ADE7953_CalculateRegisterValue16_Signed(PFA, "Power Factor: ", 1);
		
		Wh = ADE7953_CalculateRegisterValue32_Signed(AENERGYA_32, "\nActive Energy: ", " Wh", 1);		
		
		if(Wh == 0 && Current > 0,1) ADE7953_reset();
		
		
		SumWh = SumWh + Wh;				
		SumBill = (SumWh/1000.0)*euroConst;
		
		USART_Puts(USART6, "Energy: ");
		Usartfloat(USART6, SumWh);
		USART_Puts(USART6, " Wh\n");
		
		USART_Puts(USART6, "Price: ");
		Usartfloat(USART6, SumBill);
		USART_Puts(USART6, " €\n");

		EspSendCSVToEmoncms(Voltage, Current, ActiveP, ApparentP, PowerF, Wh, SumWh, SumBill);
		
		count++;	
		USART_Puts(USART6,"---------------------------------\n");
		HAL_Delay(1000);			
		
//		ADE7953_CalculateRegisterValue32_Signed(AVAR_32, "Reactive Power : ", " VAr", 1);
//		ADE7953_CalculateRegisterValue16_Signed(ANGLE_A, "Angle: ", 1);
  }

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** NVIC Configuration
*/
static void MX_NVIC_Init(void)
{
  /* RCC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(RCC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(RCC_IRQn);
  /* SPI1_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(SPI1_IRQn);
  /* SPI2_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(SPI2_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(SPI2_IRQn);
//  /* USART1_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(USART1_IRQn);
//  /* USART2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
//  /* USART6_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(USART6_IRQn);
}


/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
