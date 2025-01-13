#include "1602_LCD.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "main.h"
#include "peripherialFunctions.h"

extern UART_HandleTypeDef huart2; // for debugging


void LCD_SendNibble(uint8_t LCD_NibbleData)
{
    LCD_NibbleClear();

    HAL_GPIO_WritePin(Lcd_D4_GPIO_Port, Lcd_D4_Pin, (LCD_NibbleData & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // lsb 
    HAL_GPIO_WritePin(Lcd_D5_GPIO_Port, Lcd_D5_Pin, (LCD_NibbleData & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Lcd_D6_GPIO_Port, Lcd_D6_Pin, (LCD_NibbleData & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Lcd_D7_GPIO_Port, Lcd_D7_Pin, (LCD_NibbleData & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(Lcd_ReadWrite_GPIO_Port, Lcd_ReadWrite_Pin, (LCD_NibbleData & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Lcd_RegSel_GPIO_Port, Lcd_RegSel_Pin, (LCD_NibbleData & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    
    DelayMicroseconds(100);
    LCD_Enable();
    DelayMicroseconds(100);

}

void LCD_NibbleClear(void)
{
    HAL_GPIO_WritePin(Lcd_D4_GPIO_Port, Lcd_D4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Lcd_D5_GPIO_Port, Lcd_D5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Lcd_D6_GPIO_Port, Lcd_D6_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Lcd_D7_GPIO_Port, Lcd_D7_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Lcd_D4_GPIO_Port,Lcd_ReadWrite_Pin , GPIO_PIN_RESET);
    HAL_GPIO_WritePin( Lcd_D4_GPIO_Port ,Lcd_RegSel_Pin , GPIO_PIN_RESET);
                      

}

void LCD_Enable(void)
{
    HAL_GPIO_WritePin(Lcd_Enable_GPIO_Port, Lcd_Enable_Pin, GPIO_PIN_SET);
    DelayMicroseconds(1);
    //HAL_Delay(1);
    HAL_GPIO_WritePin(Lcd_Enable_GPIO_Port, Lcd_Enable_Pin, GPIO_PIN_RESET);

}


void LCD_Check_BusyFlag(void)
{   
    LCD_SendNibble(0x10);
    DelayMicroseconds(80);
    LCD_NibbleClear();
    HAL_GPIO_WritePin(Lcd_Enable_GPIO_Port, Lcd_Enable_Pin, GPIO_PIN_SET);
    DelayMicroseconds(1);
    


    // sets D7 pin to input, so that we can read the lcd driver to see if the busy flag is high/low
    Toggle_Pin_Mode(Lcd_D7_GPIO_Port, Lcd_D7_Pin);

    HAL_GPIO_WritePin(Lcd_Enable_GPIO_Port, Lcd_Enable_Pin, GPIO_PIN_SET);
    DelayMicroseconds(1);
    uint8_t isBusy = HAL_GPIO_ReadPin(Lcd_Enable_GPIO_Port, Lcd_Enable_Pin);
    HAL_GPIO_WritePin(Lcd_Enable_GPIO_Port, Lcd_Enable_Pin, GPIO_PIN_RESET);

    while(1){

        if (isBusy == GPIO_PIN_RESET){
            break; // D7 is low, The Lcd is no longer busy
        }

        //adding small delay to avoid excessive polling
        DelayMicroseconds(1);
    }

    // toggling D7 pin to be an output
    Toggle_Pin_Mode(Lcd_D7_GPIO_Port,Lcd_D7_Pin);
    
}

void init1602Lcd()
{  
    HAL_Delay(1000);

    LCD_SendNibble(0x03);
    HAL_Delay(100);

    LCD_SendNibble(0x03);
    DelayMicroseconds(250);

    LCD_SendNibble(0x03);
    DelayMicroseconds(2);

    LCD_SendNibble(0x02);
    DelayMicroseconds(1);

    LCD_SendNibble(0x02);
    LCD_SendNibble(0x08); //2 row display

    LCD_SendNibble(0x00);
    LCD_SendNibble(0x08);

    LCD_SendNibble(0x00);
    LCD_SendNibble(0x01);

    LCD_SendNibble(0x00);
    LCD_SendNibble(0x06);
    
    // Clear display
    LCD_SendNibble(0x00);
    LCD_SendNibble(0x01);
    HAL_Delay(2); // Clear display needs >1.53ms

    //turning on display and cursor
    LCD_SendNibble(0x00);
    LCD_SendNibble(0x0E);

    //setting entrymode to increment addr by one and to shift
    //cursor to the right at the time of the write

    LCD_SendNibble(0x00);
    LCD_SendNibble(0x06);


}

void LCD_Print(const char *str)
{
    HAL_GPIO_WritePin(Lcd_RegSel_GPIO_Port, Lcd_RegSel_Pin, GPIO_PIN_SET);
    while (*str)
    {
        // Send the upper nibble of the character
        LCD_SendNibble(((*str >> 4) & 0x0F) | 0x20 );
        // Send the lower nibble of the character
        LCD_SendNibble((*str & 0x0F) | 0x20);
        // Small delay to ensure the LCD processes each character
        DelayMicroseconds(50);
        str++;
    }
    HAL_GPIO_WritePin(Lcd_RegSel_GPIO_Port, Lcd_RegSel_Pin, GPIO_PIN_RESET);
}
void Test_LCD_Initialization(void)
{
    

    
    // writes H to the ddram the cursor is incremented by one and shifts to the right
    LCD_SendNibble(0x23);
    LCD_SendNibble(0x20);
   
   
   
}

void LCD_SendChar(char character) {
    uint8_t upperNibble = (character >> 4) & 0x0F; // Extract upper nibble
    uint8_t lowerNibble = character & 0x0F;        // Extract lower nibble
    uint8_t regSelEn = 0x20;
    upperNibble = upperNibble | regSelEn;
    lowerNibble = lowerNibble | regSelEn;

    // Send upper nibble
    
    LCD_SendNibble(upperNibble);

    // Send lower nibble
    LCD_SendNibble(lowerNibble);

    // Small delay to allow the LCD to process the character
    DelayMicroseconds(50);

    
    char debugMessage[50];

   
    snprintf(debugMessage, sizeof(debugMessage), "Char: 0x%02x, upper: 0x%02X, Lower: 0x%02X\r\n", character, upperNibble, lowerNibble);

    
    HAL_UART_Transmit(&huart2, (uint8_t *)debugMessage, strlen(debugMessage), HAL_MAX_DELAY);
}




LCD_SendString(const char *str)
{
    // loop through the string unill the null terminator is reached
    while (*str){
        LCD_SendChar(*str);
        str++;
    }
}

void LCD_NextLine(void)
{
    LCD_SendNibble(0x0C);
    LCD_SendNibble(0x00);

}

void LCD_ClearScreen(void){
  // Clear display
  LCD_SendNibble(0x00);
  LCD_SendNibble(0x01);
  HAL_Delay(2); // Clear display needs >1.53ms
}






