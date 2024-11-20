/*
 * @Author: your name
 * @Date: 2021-07-08 09:12:45
 * @LastEditTime: 2021-07-12 09:47:54
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_24C02.h
 */
#ifndef __BSP_24C02_H
#define __BSP_24C02_H

#include "main.h"


void I2C_24C02_Write(I2C_HandleTypeDef *I2Cx,uint8_t I2C_DeviceAddr,uint16_t RegisterAddr,uint8_t *buf,uint16_t num);
void I2C_24C02_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_DeviceAddr,uint16_t RegisterAddr,uint8_t value);
void I2C_24C02_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_DeviceAddr,uint16_t RegisterAddr,uint8_t *buf,uint16_t num);


uint8_t iic_24c02_test(void);


#endif // !__BSP_24C02_H
