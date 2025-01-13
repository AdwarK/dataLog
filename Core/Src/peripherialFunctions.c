// peripherialFunctions.c

#include "peripherialFunctions.h"
#include <stdint.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

// Assuming TIM2 is already initialized elsewhere
extern TIM_HandleTypeDef htim2;  // Declare htim2, which should be defined in  main file
extern TIM_HandleTypeDef htim5;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;
extern GPIO_InitTypeDef GPIO_InitStruct = {0};


void DelayMicroseconds(uint32_t microseconds) {
    __HAL_TIM_SET_COUNTER(&htim2, 0);  // Reset the counter
    HAL_TIM_Base_Start(&htim2);         // Start the timer

    while (__HAL_TIM_GET_COUNTER(&htim2) < microseconds); // Wait for the specified number of microseconds

    HAL_TIM_Base_Stop(&htim2);          // Stop the timer
}



void DelayNanoseconds(uint32_t nanoSecondsb11_9)
{
    __HAL_TIM_SET_COUNTER(&htim5, 0); //Reset Counter
    HAL_TIM_Base_Start(&htim5);

//HAL_UART_Transmit(&huart2, (uint8_t*)"step timer1\r\n", 15, HAL_MAX_DELAY);
    while (__HAL_TIM_GET_COUNTER(&htim5) < nanoSecondsb11_9);
    HAL_TIM_Base_Stop(&htim5);
    //HAL_UART_Transmit(&huart2, (uint8_t*)"step timwe3\r\n", 15, HAL_MAX_DELAY);

}




   void I2C_Scanner(void)
{
    char msg[64];
    for (uint16_t i = 0; i < 128; i++)
    {
        if (HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, 10) == HAL_OK)
        {
            sprintf(msg, "I2C device found at address 0x%02X\r\n", i);
            HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        }
    }
    HAL_UART_Transmit(&huart2, (uint8_t*)"Scan complete\r\n", 15, HAL_MAX_DELAY);
}


void Toggle_Pin_Mode(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN)
{
    uint32_t pin_position = 0;

    // finding the pin's position (0-15)
    while ((GPIO_PIN >> pin_position) != 1){
        pin_position++;
    }



    //check current mode in the MODER register
    /*
        MODER is the register that controls the mode ie. input/output
        each pin is controlled by 2 bits hence the pin position is multiplied
        by 2 to account for both registers.
        the 0x3 allows us to mask out everything except for the two bits that represent
        the mode of the selected pin.
    */
     
    uint32_t current_mode = (GPIOx->MODER >> (pin_position * 2)) & 0x3;


    //switching from output to input
    if (current_mode == GPIO_MODE_OUTPUT_PP)
    {
        HAL_GPIO_DeInit(GPIOx, GPIO_PIN);
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
    }


    // switching from input to output
    else if (current_mode == GPIO_MODE_INPUT)
    {
        HAL_GPIO_DeInit(GPIOx, GPIO_PIN);
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
    }
    
}