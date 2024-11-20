/*
 * @Author: your name
 * @Date: 2021-07-08 09:06:32
 * @LastEditTime: 2021-07-11 16:33:38
 * @LastEditors: Please set LastEditors
 * @Description: 光电开关的输入检测
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Optoelectronic.c
 */
#include "BSP_Optoelectronic.h"

/**
 * @description: 光电开关传感器的初始化
 * @param {*}
 * @return {*}
 */
void BSP_Optoelectronic_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = PHOTO_SWITCH_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PHOTO_SWITCH_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @description: 读取光电开关的状态
 * @param {*}
 * @return {uint8_t} 0: 没有物体挡住，1: 有物体挡住
 */
uint8_t BSP_Read_PhotoSwitch(void)
{
    return (PHOTO_SWITCH ? 1: 0);
}


