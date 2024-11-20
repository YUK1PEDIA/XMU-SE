/*
 * @Author: your name
 * @Date: 2021-07-08 09:06:32
 * @LastEditTime: 2021-07-11 16:32:53
 * @LastEditors: Please set LastEditors
 * @Description: 光电开关
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Optoelectronic.h
 */
#ifndef __BSP_OPTOELECTRONIC_H
#define __BSP_OPTOELECTRONIC_H

#include "main.h"

void BSP_Optoelectronic_Init(void);

uint8_t BSP_Read_PhotoSwitch(void);

#endif // !__BSP_OPTOELECTRONIC_H


