/*
 * @Author: your name
 * @Date: 2021-07-08 09:07:27
 * @LastEditTime: 2021-07-11 11:49:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_LM75A.c
 */
#include "BSP_LM75A.h"
#include "i2c.h"

#define		LM75A_ADDR		0X9F 

#define		REG_TEMP		0X00		
#define		REG_CONF		0X01		
#define		REG_THYST		0X02		
#define		REG_TOS			0X03

__IO uint32_t  I2C_LM75A_Timeout = 0x1000;

/**
 * @description: 获取芯片测量的温度
 * @param {*}
 * @return {float} 温度值 例如: 35.35
 */
float LM75GetTempValue(void)
{
	float TempValue;
	uint16_t temp;
	uint8_t dataBuf[2];
	
	if(HAL_I2C_Mem_Read(&hi2c1, LM75A_ADDR, REG_TEMP, 2, dataBuf, 2, I2C_LM75A_Timeout) == HAL_OK)
		temp = ((dataBuf[0] << 8) | dataBuf[1]) >> 5;
	
	if(temp & (0x01 << 16))
		TempValue = ((!temp)+1)*0.125;
	else
		TempValue = temp*0.125;
	
	return TempValue;
}

