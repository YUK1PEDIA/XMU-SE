/*
 * @Author: your name
 * @Date: 2021-07-12 09:41:12
 * @LastEditTime: 2021-07-12 10:01:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Can.h
 */
#ifndef __BSP_CAN_H_
#define __BSP_CAN_H_

#include "main.h"

void CAN1_Function_Init(void);
void CAN1_Send_Test(void);
HAL_StatusTypeDef CAN_Test(uint32_t Timeout);



#endif // !__BSP_CAN_H_



