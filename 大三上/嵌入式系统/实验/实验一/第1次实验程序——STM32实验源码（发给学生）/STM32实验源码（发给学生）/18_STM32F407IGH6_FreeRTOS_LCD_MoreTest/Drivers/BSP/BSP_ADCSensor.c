/*
 * @Author: your name
 * @Date: 2021-07-08 09:02:14
 * @LastEditTime: 2021-07-11 11:47:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_ADCSensor.c
 */
#include "BSP_ADCSensor.h"
#include "adc.h"

__IO uint16_t ADC_DMA_Value[ADC_NUM] = {0};    //AD采集的

void Read_SensorValue(float *Alcohol, float *Light, float *Flame, float *Gas)
{
  HAL_ADC_Start_DMA(&hadc3,(uint32_t*)ADC_DMA_Value,ADC_NUM);

  *Alcohol = (float)ADC_DMA_Value[ADC_IN4_Alcohol]*(3.3/4096);
  *Light   = (float)(4096 - ADC_DMA_Value[ADC_IN5_Light])*(3.3/4096);
  *Flame   = (float)ADC_DMA_Value[ADC_IN6_Flame]*(3.3/4096);
  *Gas     = (float)ADC_DMA_Value[ADC_IN7_Gas]*(3.3/4096);

  HAL_ADC_Stop_DMA(&hadc3);
//   snprintf(Buff, sizeof(Buff), " %.2fV", Alcohol);
//   LCD_ShowString(54, 419, 90, 30, 24, (uint8_t *)Buff);		// 酒精
//   memset(Buff, 0, sizeof(Buff));

//   snprintf(Buff, sizeof(Buff), " %.2fV", Light);
//   LCD_ShowString(155, 419, 90, 30, 24, (uint8_t *)Buff);		// 光照
//   memset(Buff, 0, sizeof(Buff));

//   snprintf(Buff, sizeof(Buff), " %.2fV", Flame);
//   LCD_ShowString(255, 419, 90, 30, 24, (uint8_t *)Buff);		// 火焰
//   memset(Buff, 0, sizeof(Buff));

//   snprintf(Buff, sizeof(Buff), " %.2fV", Gas);
//   LCD_ShowString(357, 419, 90, 30, 24, (uint8_t *)Buff);		// 可燃气体传感器
//   memset(Buff, 0, sizeof(Buff));

  
  // taskEXIT_CRITICAL();        //退出临界区(可以被中断打断)   


//   if(PHOTO_SWITCH)   // 光电开关
//     LCD_ShowString(560, 225, 90, 30, 24, (uint8_t *)"  ON  ");
//   else
//     LCD_ShowString(560, 225, 90, 30, 24, (uint8_t *)"  OFF ");
		
// 	snprintf(Buff, sizeof(Buff), " %.2fC", LM75GetTempValue());
//   LCD_ShowString(462, 419, 90, 30, 24, (uint8_t *)Buff);		// 温度传感器
//   memset(Buff, 0, sizeof(Buff));
}



