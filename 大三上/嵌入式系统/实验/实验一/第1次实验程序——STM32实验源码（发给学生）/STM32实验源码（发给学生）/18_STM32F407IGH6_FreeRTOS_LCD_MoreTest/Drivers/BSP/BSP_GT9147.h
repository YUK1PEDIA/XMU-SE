/*
 * @Author: your name
 * @Date: 2021-07-12 09:15:34
 * @LastEditTime: 2021-07-12 09:17:42
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_GT9147.h
 */

#ifndef __BSP_GT9147_H__
#define __BSP_GT9147_H__

#include "main.h"

//I2C��д����	
#define GT_CMD_WR 		0X28     	//д����
#define GT_CMD_RD 		0X29		//������
  
//GT9147 ���ּĴ������� 
#define GT_CTRL_REG 	0X8040   	//GT9147���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT9147������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT9147У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT9147��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT9147��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ  

uint8_t BSP_GT9147_Send_Cfg(uint8_t mode);
uint8_t BSP_GT9147_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
void    BSP_GT9147_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len); 
uint8_t BSP_GT9147_Init(void);


#endif /* __BSP_GT9147_H__ */


