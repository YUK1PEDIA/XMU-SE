/*
 * @Author: your name
 * @Date: 2021-07-08 09:01:58
 * @LastEditTime: 2021-07-11 11:46:03
 * @LastEditors: Please set LastEditors
 * @Description: ģ���źŵĲɼ�
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_ADCSensor.h
 */
#ifndef __BSP_ADCSENSOR_H
#define __BSP_ADCSENSOR_H
#include "main.h"

typedef enum {
    ADC_IN4_Alcohol = 0,     // �ƾ�
    ADC_IN5_Light,     		 // ����
    ADC_IN6_Flame,     		 // ����
	ADC_IN7_Gas,     		 // ��ȼ���崫����
    ADC_NUM  			     // ADCת���ĸ���
}ADC_INx;  

void Read_SensorValue(float *Alcohol, float *Light, float *Flame, float *Gas);

#endif // !__BSP_ADCSENSOR_H
