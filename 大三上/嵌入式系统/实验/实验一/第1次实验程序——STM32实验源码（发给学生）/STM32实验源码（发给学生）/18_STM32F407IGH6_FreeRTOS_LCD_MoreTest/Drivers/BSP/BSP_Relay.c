/*
 * @Author: your name
 * @Date: 2021-07-08 09:02:15
 * @LastEditTime: 2021-07-11 17:31:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Relay.c
 */
#include "BSP_Relay.h"

/**
 * @description: 继电器的初始化
 * @param {*}
 * @return {*}
 */
void BSP_RELAY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = RELAY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RELAY_GPIO_Port, &GPIO_InitStruct);
}
