/*
 * @Author: your name
 * @Date: 2021-07-08 09:02:15
 * @LastEditTime: 2021-07-11 16:31:25
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_KEY.h
 */
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "main.h"

typedef enum{
    KEY3_PRES = 1,
    KEY4_PRES,
}KEY_Status;

void BSP_KEY_Init(void);
uint8_t KEY_Scan(uint8_t mode);



#endif // !__BSP_KEY_H
