/*
 * @Author: your name
 * @Date: 2021-07-08 09:15:02
 * @LastEditTime: 2021-07-11 17:22:19
 * @LastEditors: Please set LastEditors
 * @Description: ģ��IICͨ��Э��
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_MyI2C.h
 */
#ifndef __BSP_MYIIC_H
#define __BSP_MYIIC_H

#include "main.h"
//���¶���IO��
#define MY_I2C_SDA_GPIO_PORT         TOUCH_SDA_GPIO_Port
#define MY_I2C_SDA_GPIO_PIN          TOUCH_SDA_Pin

#define MY_I2C_SCL_GPIO_PORT         TOUCH_SCL_GPIO_Port
#define MY_I2C_SCL_GPIO_PIN          TOUCH_SCL_Pin

//IO��������	  
#define MY_IIC_SCL_1     HAL_GPIO_WritePin(MY_I2C_SCL_GPIO_PORT, MY_I2C_SCL_GPIO_PIN, GPIO_PIN_SET) 
#define MY_IIC_SCL_0     HAL_GPIO_WritePin(MY_I2C_SCL_GPIO_PORT, MY_I2C_SCL_GPIO_PIN, GPIO_PIN_RESET)
#define MY_IIC_SDA_1     HAL_GPIO_WritePin(MY_I2C_SDA_GPIO_PORT, MY_I2C_SDA_GPIO_PIN, GPIO_PIN_SET) 
#define MY_IIC_SDA_0     HAL_GPIO_WritePin(MY_I2C_SDA_GPIO_PORT, MY_I2C_SDA_GPIO_PIN, GPIO_PIN_RESET) 
#define CT_READ_SDA   	 HAL_GPIO_ReadPin(MY_I2C_SDA_GPIO_PORT,MY_I2C_SDA_GPIO_PIN)   

//IIC���в�������
void MY_IIC_Init(void);                	//��ʼ��IIC��IO��				 
void MY_IIC_Start(void);				//����IIC��ʼ�ź�
void MY_IIC_Stop(void);	  				//����IICֹͣ�ź�
void MY_IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t MY_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
uint8_t MY_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MY_IIC_Ack(void);					//IIC����ACK�ź�
void MY_IIC_NAck(void);					//IIC������ACK�ź�

#endif // !__BSP_MYIIC_H


