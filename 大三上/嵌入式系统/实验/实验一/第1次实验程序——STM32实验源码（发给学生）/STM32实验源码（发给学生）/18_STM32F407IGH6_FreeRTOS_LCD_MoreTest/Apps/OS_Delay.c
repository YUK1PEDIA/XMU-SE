/*
 * @Author: your name
 * @Date: 2021-07-08 09:16:47
 * @LastEditTime: 2021-07-08 09:29:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\OS_Delay.c
 */
#include "OS_Delay.h"
#include "tim.h"

/**
 * @description: TIM定时器us延时
 * @param {uint16_t} nus
 * @return {*}
 */
void delay_us(uint16_t nus)
{
  uint16_t differ = 0xffff-nus-1;

  /* 设置定时器2的计数初始值 */
  __HAL_TIM_SetCounter(&htim2,differ);
  /* 开启定时器 */
  HAL_TIM_Base_Start(&htim2);

  while( differ<0xffff-1)
  {
    differ = __HAL_TIM_GetCounter(&htim2);
  };

  /* 关闭定时器 */
  HAL_TIM_Base_Stop(&htim2);
}
