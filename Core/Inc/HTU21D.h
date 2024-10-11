/**
  ******************************************************************************
  * @file   HTU21D.h
  * @author Adwar Kassa
  * @brief  HTU21D temperature and humidity sensor driver. this file currently 
  *         is able to receive both temperature and humidity data from the
  *         sensor using i2c, and then is printed via UART to the console 
  * 
  * @todo   instead of the temperature and humidity being sent to usart. It will
  *         be written to the DMA and connected to a timestamp attained from the
  *         RTC
  *         add in CRC for reliablity and accururacy [page 14 of datasheet]
  *                   
  ******************************************************************************
  */

#ifndef HTU21D_H
#define HTU21D_H

#include "stm32f4xx_hal.h"
#include <string.h>



/*****************  defining HTU21D address (page 10 of datasheet) ******************/

#define HTU21D_ADDR  (0x40 << 1) // I2C address of HTU21D [7 bit address so it must be 
                                 //shifted to the left by 1 to be read by the stm32HAl]

/*********************  defining all HTU21D I2C commands (page 10 of datasheet)  ***********/

#define soft_reset  0xFE;        // triggers soft reset, must be used during sensor init
#define Temp_Measure_Hold  0xE3  // Command to trigger temperature measurement
#define Humid_Measure_Hold 0xE5  // Command to trigger humidity measurement

/******************************  defining all HTU21D functions   ****************************************/

/**
 * @brief initializes the HTU21D temp/humidity sensor
 * @note  HTU21D requires a soft reset command (0xFE) being sent to it before being able to conduct
 *        any measurements.
 * @param hi2c Pointer to the I2C_HandleTypedef structure that contains the config info for the I2c
 *        peripherial. Used to communicate with the sensor.
 * 
 */
void HTU21D_init(I2C_HandleTypeDef *hi2c);

/**
 * @brief reads humidity from HTU21D sensor
 * @note  this function sends the command (0xE5) to the HTU21D sensor to return a relative humidity and is sent over usart
 * @param hi2c Pointer to the I2C_HandleTypedef structure that contains the config info for the I2C
 *        peripherial. Used to communicate with the sensor.
 * @param huart Pointer to the UART_HandleTypedef structure that contains the config info for the UART
 *        peripherial. used to send humidity data to serial monitor
 * @todo  this functionality will be changed overtime and will instead be stored to the DMA and stored with a timestamp attained from the RTC
 */
void read_humidity(I2C_HandleTypeDef *hi2c,UART_HandleTypeDef *huart);


/**
 * @brief reads temperature in celcius from the HTU21D sensor
 * @note  this function sends the command (0xE3) to the HTU21D sensor to return the temperature in Celcius and is sent over usart
 * @param hi2c Pointer to the I2C_HandleTypedef structure that contains the config info for the I2C
 *        peripherial. Used to communicate with the sensor.
 * @param huart Pointer to the UART_HandleTypedef structure that contains the config info for the UART
 *        peripherial. used to send humidity data to serial monitor 
 * @todo  this functionality will be changed overtime and will instead be stored to the DMA and stored with a timestamp attained from the RTC
 *        this function will have a parameter that will determine if the user wants the temperature in celcius or farenheight
 * 
 */
void read_temperature(I2C_HandleTypeDef *hi2c,UART_HandleTypeDef *huart);


#endif //HTU21D_H

