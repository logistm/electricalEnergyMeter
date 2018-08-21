/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define SS_SD_Pin GPIO_PIN_13
#define SS_SD_GPIO_Port GPIOC
#define SS_LCD_Pin GPIO_PIN_0
#define SS_LCD_GPIO_Port GPIOC
#define DC_LCD_Pin GPIO_PIN_1
#define DC_LCD_GPIO_Port GPIOC
#define CF2_OUT_Pin GPIO_PIN_0
#define CF2_OUT_GPIO_Port GPIOA
#define RST_ESP_Pin GPIO_PIN_1
#define RST_ESP_GPIO_Port GPIOA
#define ESP_TX_Pin GPIO_PIN_2
#define ESP_TX_GPIO_Port GPIOA
#define ESP_RX_Pin GPIO_PIN_3
#define ESP_RX_GPIO_Port GPIOA
#define ZX_OUT_Pin GPIO_PIN_4
#define ZX_OUT_GPIO_Port GPIOA
#define SS_ADE_Pin GPIO_PIN_4
#define SS_ADE_GPIO_Port GPIOC
#define RES_ADE_Pin GPIO_PIN_5
#define RES_ADE_GPIO_Port GPIOC
#define CF1_OUT_Pin GPIO_PIN_0
#define CF1_OUT_GPIO_Port GPIOB
#define IRQ_OUT_Pin GPIO_PIN_1
#define IRQ_OUT_GPIO_Port GPIOB
#define ZX1_OUT_Pin GPIO_PIN_12
#define ZX1_OUT_GPIO_Port GPIOB
#define REVP_OUT_Pin GPIO_PIN_15
#define REVP_OUT_GPIO_Port GPIOB
#define CP_TX_Pin GPIO_PIN_6
#define CP_TX_GPIO_Port GPIOC
#define CP_RX_Pin GPIO_PIN_7
#define CP_RX_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_8
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_9
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_8
#define LED3_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_11
#define LED4_GPIO_Port GPIOA
#define SW1_Pin GPIO_PIN_4
#define SW1_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_5
#define SW2_GPIO_Port GPIOB
#define SW3_Pin GPIO_PIN_6
#define SW3_GPIO_Port GPIOB
#define SW4_Pin GPIO_PIN_7
#define SW4_GPIO_Port GPIOB

#define CLK_ADE_Pin					GPIO_PIN_5
#define CLK_ADE_GPIO_Port		GPIOA

#define MISO_LCD_Pin				GPIO_PIN_2
#define MISO_LCD_GPIO_Port	GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
