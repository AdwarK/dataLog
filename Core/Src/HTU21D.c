#include "HTU21D.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>



void HTU21D_init(I2C_HandleTypeDef *hi2c)
{uint8_t  reset_command = soft_reset;
    HAL_I2C_Master_Transmit(hi2c, HTU21D_ADDR, &reset_command, 1, HAL_MAX_DELAY);
    HAL_Delay(15); // wait for reset to complete
}



  void read_humidity(I2C_HandleTypeDef *hi2c,UART_HandleTypeDef *huart)
  {
    uint8_t humidity_command = Humid_Measure_Hold;
    uint8_t humid_data[3]; // to store humidity data (2 bytes + checksum)
    uint16_t raw_humid;
    float humidity;

    //sending command to trigger humidity reading.
    if(HAL_I2C_Master_Transmit(hi2c, HTU21D_ADDR, &humidity_command, 1, HAL_MAX_DELAY) != HAL_OK)
    {
      char errMsg[] = "error sending humidity command!\r\n";
      HAL_UART_Transmit(huart,(uint8_t*)errMsg, strlen(errMsg), HAL_MAX_DELAY);
      return;
    }

    // receiving humidity data total size 3 2 bytes of data + 1 checksum
    if(HAL_I2C_Master_Receive(hi2c,HTU21D_ADDR,humid_data,3,HAL_MAX_DELAY) != HAL_OK)
    {
      char errMsg[] = "error receiving humidity data!\r\n";
      HAL_UART_Transmit(huart, (uint8_t*)errMsg, strlen(errMsg),HAL_MAX_DELAY);
      return;
    }

    // processing data from humidity packet

    raw_humid = ((uint16_t)humid_data[0] << 8) | (uint16_t)humid_data[1];
    raw_humid &= 0xFFFc;


    humidity =  -6.0 + (125.0 *(raw_humid/65536.0));
    char tempMsg[50];
    sprintf(tempMsg, "Humidity: %.2f %%\r\n", humidity);
    HAL_UART_Transmit(huart, (uint8_t*)tempMsg, strlen(tempMsg), HAL_MAX_DELAY);

    return;




  }

  void read_temperature(I2C_HandleTypeDef *hi2c,UART_HandleTypeDef *huart)
  {
    uint8_t temp_command = Temp_Measure_Hold;
    uint8_t temp_data[3]; // To store temperature data (2 bytes + checksum)
    uint16_t raw_temp;
    float temperature;

    
    
    // Send command to HTU21D to trigger temperature measurement
    if (HAL_I2C_Master_Transmit(hi2c,HTU21D_ADDR, &temp_command, 1, HAL_MAX_DELAY ) != HAL_OK)
    {
      // Error Handling
      char errMsg[] = "Error Sending Temperature command!\r\n";
      HAL_UART_Transmit(huart,(uint8_t*)errMsg, strlen(errMsg), HAL_MAX_DELAY);
      return;
    }

    if(HAL_I2C_Master_Receive(hi2c, HTU21D_ADDR  , temp_data, 3, HAL_MAX_DELAY) != HAL_OK)
    {
      char errMsg[] = "Error receiving temperature data!\r\n";
      HAL_UART_Transmit(huart, (uint8_t*)errMsg, strlen(errMsg), HAL_MAX_DELAY);
      return ;
    }

    // Combine the two temperatue bytes into a 16-bit value
    raw_temp = ((uint16_t)temp_data[0] << 8) | (uint16_t)temp_data[1];
    raw_temp &= 0xFFFc;

    // convert raw temp to Celsius using Formula from data sheet
    temperature = -46.85 +(175.72 *(raw_temp / 65536.0));

    // print temperature over UART
    
    char tempMsg[50];
    sprintf(tempMsg, "Temperature: %.2f°C\r\n", temperature);
    HAL_UART_Transmit(huart, (uint8_t*)tempMsg, strlen(tempMsg), HAL_MAX_DELAY);
  }


