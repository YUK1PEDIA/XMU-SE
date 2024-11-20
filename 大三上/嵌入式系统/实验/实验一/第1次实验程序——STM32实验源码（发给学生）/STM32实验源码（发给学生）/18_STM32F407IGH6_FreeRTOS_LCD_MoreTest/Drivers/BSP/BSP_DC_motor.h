/*
 * @Author: your name
 * @Date: 2021-07-08 09:09:51
 * @LastEditTime: 2021-07-11 16:43:57
 * @LastEditors: Please set LastEditors
 * @Description: 直流电机
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_DC_motor.h
 */
#ifndef __BSP_DC_MOTOR_H
#define __BSP_DC_MOTOR_H

#include "main.h"

void Set_Dc_Motor_Stop(void);
void Set_DC_Motor_B(uint8_t v_data);
void Set_DC_Motor_Z(uint8_t v_data);

#endif // !__BSP_DC_MOTOR_H
