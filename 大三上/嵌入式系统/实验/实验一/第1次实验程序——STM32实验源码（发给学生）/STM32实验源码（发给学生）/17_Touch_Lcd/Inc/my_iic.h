#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H

#include "main.h"

//IO��������	  
#define CT_IIC_SCL_1     HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET) //SCL
#define CT_IIC_SCL_0     HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET) //SCL
#define CT_IIC_SDA_1     HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_SET) //SCL
#define CT_IIC_SDA_0     HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_RESET) //SCL

#define CT_READ_SDA   		HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_3)   //����SDA 

//IIC���в�������
void CT_IIC_Init(void);                	//��ʼ��IIC��IO��				 
void CT_IIC_Start(void);				//����IIC��ʼ�ź�
void CT_IIC_Stop(void);	  				//����IICֹͣ�ź�
void CT_IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
uint8_t CT_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CT_IIC_Ack(void);					//IIC����ACK�ź�
void CT_IIC_NAck(void);					//IIC������ACK�ź�

#endif







