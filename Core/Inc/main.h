/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HTU21D.h"
#include "1602_LCD.h"
#include "peripherialFunctions.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void I2C_Scanner(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define out1_Pin GPIO_PIN_6
#define out1_GPIO_Port GPIOA
#define out2_Pin GPIO_PIN_7
#define out2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

//defing gpio pins used for d[0:3] pins going to the 4 data bits of the LCD screen
#define Lcd_D4_Pin GPIO_PIN_12 // all pin descriptions located on pg7 of chfah1602A datasheet
#define Lcd_D4_GPIO_Port GPIOA
#define Lcd_D5_Pin GPIO_PIN_11
#define Lcd_D5_GPIO_Port GPIOA
#define Lcd_D6_Pin GPIO_PIN_10
#define Lcd_D6_GPIO_Port GPIOA
#define Lcd_D7_Pin GPIO_PIN_9
#define Lcd_D7_GPIO_Port GPIOA

//defining gpio pins used for reading and writing intructions to the LCD
#define Lcd_RegSel_Pin GPIO_PIN_8
#define Lcd_RegSel_GPIO_Port GPIOA
#define Lcd_ReadWrite_Pin GPIO_PIN_7
#define Lcd_ReadWrite_GPIO_Port GPIOA
#define Lcd_Enable_Pin GPIO_PIN_6
#define Lcd_Enable_GPIO_Port GPIOA



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
