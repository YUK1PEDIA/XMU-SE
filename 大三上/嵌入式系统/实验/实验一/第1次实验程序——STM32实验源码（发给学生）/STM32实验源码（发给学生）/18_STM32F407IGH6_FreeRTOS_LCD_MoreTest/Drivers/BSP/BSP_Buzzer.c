/*
 * @Author: your name
 * @Date: 2021-07-08 09:02:15
 * @LastEditTime: 2021-07-12 08:52:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Buzzer.c
 */
#include "BSP_Buzzer.h"

/**
 * @description: 继电器的初始化
 * @param {*}
 * @return {*} 
 */
void BSP_BUZZER_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = BUZZER_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);
}
