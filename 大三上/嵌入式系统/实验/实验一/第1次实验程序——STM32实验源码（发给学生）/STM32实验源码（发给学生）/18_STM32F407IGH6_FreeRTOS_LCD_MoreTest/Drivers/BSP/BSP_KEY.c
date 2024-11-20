/*
 * @Author: your name
 * @Date: 2021-07-08 09:02:15
 * @LastEditTime: 2021-07-11 16:14:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_KEY.c
 */
#include "BSP_KEY.h"

/**
 * @description: 按键的初始化
 * @param {*}
 * @return {*}
 */
void BSP_KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStruct.Pin = KEY3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KEY3_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = KEY4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KEY4_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @description: 按键处理函数
 * @param {uint8_t} mode 0:不支持连按, 1: 支持连按
 * @return {*}
 */
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;

    if (mode == 1)
        key_up = 1;

    if (key_up && (KEY3 == 0 || KEY4 == 0 ))
    {
        HAL_Delay(10);
        key_up = 0;
        if (KEY3 == 0)
            return KEY3_PRES;
        else if (KEY4 == 0)
            return KEY4_PRES;
    }
    else if (KEY3 == 1 && KEY4 == 1)
        key_up = 1;
    return 0;
}
