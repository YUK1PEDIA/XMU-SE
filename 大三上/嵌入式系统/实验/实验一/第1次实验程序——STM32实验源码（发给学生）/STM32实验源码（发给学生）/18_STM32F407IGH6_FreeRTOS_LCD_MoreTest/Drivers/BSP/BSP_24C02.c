/*
 * @Author: your name
 * @Date: 2021-07-08 09:12:33
 * @LastEditTime: 2021-07-12 09:48:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_24C02.c
 */
#include "BSP_24C02.h"
#include "i2c.h"

#define ADDR_24C02_W    0xAE
#define ADDR_24C02_R  	0xAF

#define I2C_Open_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2C_Open_LONG_TIMEOUT         ((uint32_t)0xffff)
__IO uint32_t  I2CTimeout = I2C_Open_FLAG_TIMEOUT;

/**
 * @description: 读寄存器
 * @param {I2C_HandleTypeDef} *I2Cx I2C端口号
 * @param {uint8_t} I2C_DeviceAddr  从机端I2C地址
 * @param {uint16_t} RegisterAddr   
 * @param {uint8_t} *buf
 * @param {uint16_t} num
 * @return {*}
 */
void I2C_24C02_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_DeviceAddr,uint16_t RegisterAddr,uint8_t *buf,uint16_t num)
{
  while(HAL_I2C_Mem_Read (I2Cx,I2C_DeviceAddr,RegisterAddr,I2C_MEMADD_SIZE_8BIT,buf,num,I2CTimeout) != HAL_OK ) {};
}

/**
 * @description: 向寄存器中写一个字节
 * @param {I2C_HandleTypeDef} *I2Cx
 * @param {uint8_t} I2C_DeviceAddr
 * @param {uint16_t} RegisterAddr
 * @param {uint8_t} value
 * @return {*}
 */
void I2C_24C02_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_DeviceAddr,uint16_t RegisterAddr,uint8_t value)
{
  while( HAL_I2C_Mem_Write(I2Cx, I2C_DeviceAddr, RegisterAddr, I2C_MEMADD_SIZE_8BIT, &value, 0x01, I2CTimeout) != HAL_OK ) {};
}

/**
 * @description: 向某个地址写连续的数据
 * @param {I2C_HandleTypeDef} *I2Cx
 * @param {uint8_t} I2C_DeviceAddr
 * @param {uint16_t} RegisterAddr
 * @param {uint8_t} *buf
 * @param {uint16_t} num
 * @return {*}
 */
void I2C_24C02_Write(I2C_HandleTypeDef *I2Cx,uint8_t I2C_DeviceAddr,uint16_t RegisterAddr,uint8_t *buf,uint16_t num)
{
  while(num--)
  {
    I2C_24C02_WriteOneByte(I2Cx, I2C_DeviceAddr, RegisterAddr++, *buf++);
  }
}

/**
 * @description: iic_24c02_test （24c02 IIC EEPROM 测试程序）
 * @param {*}
 * @return {*}
 */
uint8_t iic_24c02_test(void)
{
  uint8_t WriteBuffer[6] = {0x01,0x02,0x03,0x04,0x05,0x06};
  uint8_t ReadBuffer[6] = {0};

  I2C_24C02_Write(&hi2c1,ADDR_24C02_W,0,(uint8_t *)WriteBuffer,6 );//向24C02的0地址写入数据

  I2C_24C02_Read(&hi2c1,ADDR_24C02_R,0,ReadBuffer,6 );					//从24C02的0地址读出数据
	
  if(ReadBuffer[0]==WriteBuffer[0]&&ReadBuffer[1]==WriteBuffer[1]&&ReadBuffer[2]==WriteBuffer[2]&&ReadBuffer[3]==WriteBuffer[3]&&ReadBuffer[4]==WriteBuffer[4]&&ReadBuffer[5]==WriteBuffer[5])
  {
		return 0;
  }
	else 
	{
		return 1;
  }
}
