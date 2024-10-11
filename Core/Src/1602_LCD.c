#include "1602_LCD.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>



void init1602Lcd(LCD_HandleTypeDef* lcd_handle)
{
    // WARNING: this init is for a 4bit interface. refer to pg 17 of datasheet
    HAL_Delay(20); // Step 1. lcd must be powered on for 15 seconds or more before init can begin
    
    // function set. first command for init
    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode
    //** this code below must be done 3 times to initilise the LCD screen. after third it command is sent, LCD can be configured *
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_SET);// d5 = 1
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_SET);// d4 = 1
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);

    // function set for second time
    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_SET);// d5 = 1
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_SET);// d4 = 1
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);
    
    // function set for third time
    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_SET);// d5 = 1
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_SET);// d4 = 1
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);


    //** the three first function sets are complete. the next set of commands will configure the lcd screen */

    //setting up functions to be in 4 bit mode
    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_SET);// d5 = 1
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_RESET);// d4 = 0
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);
  
   //setting up command for 2 lines and 5x11 characters 
    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_SET); // d7 = 1
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_SET);// d6 = 1
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_RESET);// d5 = 0
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_RESET);// d4 = 0
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);


    // turning the display off  calls for two commands to be sent all data bits low, then only data bit 7 high.
    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_RESET);// d5 = 0
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_RESET);// d4 = 0
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);

    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_SET); // d7 = 1
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_RESET);// d5 = 0
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_RESET);// d4 = 0
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);

    // now that display is turned off the next step is to clear the display which is commands [(0,0,0,0), (0,0,0,1)]
    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_RESET);// d5 = 0
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_RESET);// d4 = 0
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);

    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_RESET);// d5 = 0
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_SET);// d4 = 1
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);
    //**  the last step is to confgure the entry mode is sent as (0,0,0,0), (0,1,1,0) this will allow the cursor to shift to the right while disabling shifting of the screen */
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_RESET);// d6 = 0
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_RESET);// d5 = 0
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_RESET);// d4 = 0
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);

    HAL_GPIO_WritePin(lcd_handle->RS_Port,lcd_handle->RS_Pin,GPIO_PIN_RESET);// command mmode
    HAL_GPIO_WritePin(lcd_handle->RW_Port,lcd_handle->RW_Pin,GPIO_PIN_RESET);// write mode

    
    HAL_GPIO_WritePin(lcd_handle->D7_Port,lcd_handle->D7_Pin,GPIO_PIN_RESET); // d7 = 0
    HAL_GPIO_WritePin(lcd_handle->D6_Port,lcd_handle->D6_Pin,GPIO_PIN_SET);// d6 = 1
    HAL_GPIO_WritePin(lcd_handle->D5_Port,lcd_handle->D5_Pin,GPIO_PIN_SET);// d5 = 1
    HAL_GPIO_WritePin(lcd_handle->D4_Port,lcd_handle->D4_Pin,GPIO_PIN_RESET);// d4 = 0
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_SET); // enable high
    HAL_Delay(1); // let command process 
    
    HAL_GPIO_WritePin(lcd_handle->Enable_Port, lcd_handle->Enable_Pin, GPIO_PIN_RESET); // enable low, this completes the command.
    HAL_Delay(5);


  


    
}

