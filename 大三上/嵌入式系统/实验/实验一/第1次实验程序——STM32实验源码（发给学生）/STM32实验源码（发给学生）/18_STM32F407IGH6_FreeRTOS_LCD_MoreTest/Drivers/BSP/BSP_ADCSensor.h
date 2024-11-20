/*
 * @Author: your name
 * @Date: 2021-07-08 09:01:58
 * @LastEditTime: 2021-07-11 11:46:03
 * @LastEditors: Please set LastEditors
 * @Description: 模拟信号的采集
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_ADCSensor.h
 */
#ifndef __BSP_ADCSENSOR_H
#define __BSP_ADCSENSOR_H
#include "main.h"

typedef enum {
    ADC_IN4_Alcohol = 0,     // 酒精
    ADC_IN5_Light,     		 // 光敏
    ADC_IN6_Flame,     		 // 火焰
	ADC_IN7_Gas,     		 // 可燃气体传感器
    ADC_NUM  			     // ADC转化的个数
}ADC_INx;  

void Read_SensorValue(float *Alcohol, float *Light, float *Flame, float *Gas);

#endif // !__BSP_ADCSENSOR_H
