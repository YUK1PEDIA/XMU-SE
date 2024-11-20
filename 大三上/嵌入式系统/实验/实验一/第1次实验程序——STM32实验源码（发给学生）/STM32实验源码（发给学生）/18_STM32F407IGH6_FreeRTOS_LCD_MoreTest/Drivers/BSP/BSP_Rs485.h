/*
 * @Author: your name
 * @Date: 2021-07-12 09:41:38
 * @LastEditTime: 2021-07-12 10:03:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Rs485.h
 */
#ifndef __BSP_RS485_H
#define __BSP_RS485_H

#include "main.h"

void DR_RS485_Init(void);
void DR_RS485_SendData(uint8_t *data, uint16_t size);
HAL_StatusTypeDef RS485_Test(uint32_t Timeout);


#endif // !__BSP_RS485_H
