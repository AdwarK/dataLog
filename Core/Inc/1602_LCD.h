/**
  ******************************************************************************
  * @file   1602_LCD.h
  * @author Adwar Kassa
  * @brief  
  * 
  * @todo   
  *                   
  ******************************************************************************
  */

#ifndef __1602_LCD_H
#define __1602_LCD_H




#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "main.h"
#include "peripherialFunctions.h"



typedef struct {
  GPIO_TypeDef* RS_Port; // Register select Port
  uint16_t RS_Pin; // Register select Pin
  GPIO_TypeDef* RW_Port;// Read/write port
  uint16_t RW_Pin; // read/write pin
  GPIO_TypeDef* Enable_Port; //enable port
  uint16_t Enable_Pin; // enable Pin
  GPIO_TypeDef* D4_Port;// D0 port
  uint16_t D4_Pin;// D0 Pin
  GPIO_TypeDef* D5_Port;// D1 port
  uint16_t D5_Pin;// D1 Pin
  GPIO_TypeDef* D6_Port;// D2 port
  uint16_t D6_Pin;// D2 Pin
  GPIO_TypeDef* D7_Port;// D3 port
  uint16_t D7_Pin;// D3 Pin

} LCD_HandleTypeDef;





void init1602Lcd();
void LCD_SendNibble(uint8_t LCD_NibbleData);
void LCD_NibbleClear(void);
void LCD_Enable(void);
void Test_LCD_Initialization(void);
void LCD_SendString(const char *str);
void LCD_NextLine(void);
void LCD_ClearScreen(void);



#endif /* __1602_LCD.h*/