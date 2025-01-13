// peripherialFunctions.h

#ifndef PERIPHERIAL_FUNCTIONS_H
#define PERIPHERIAL_FUNCTIONS_H

#include "stm32f4xx_hal.h"  // Include HAL header
#include <stdint.h>

extern TIM_HandleTypeDef htim2;  
extern TIM_HandleTypeDef htim5;


// Function prototype for DelayMicroseconds
void DelayMicroseconds(uint32_t microseconds);
void DelayNanoseconds(uint32_t nanoSecondsb11_9);
void I2C_Scanner(void);
void Toggle_Pin_Mode(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN);
void LCD_Print(const char *str);
void LCD_SendChar(char character);

#endif // PERIPHERIAL_FUNCTIONS_H