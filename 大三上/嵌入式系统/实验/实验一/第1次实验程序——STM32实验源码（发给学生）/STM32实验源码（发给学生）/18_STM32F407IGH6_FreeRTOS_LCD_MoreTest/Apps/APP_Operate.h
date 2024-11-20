/*
 * @Author: your name
 * @Date: 2021-07-12 16:38:35
 * @LastEditTime: 2021-07-13 14:41:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\APP_Operate.h
 */
#ifndef __APP_OPERATE_H__
#define __APP_OPERATE_H__
#include "main.h"

/************** LCD��ʾ��������λ�� *****************/
typedef enum {
  ERROR_FLAG = -1,
  STEPPING_MOTOR_FLAG = 0,		// �������
  DC_MOTOR_FLAG,							// ֱ�����
  STEERING_GEATR_FLAG,				// ���
  RELAY_FLAG,									// �̵���
  BUZZER_FLAG,								// ������
  LED_FLAG,								// �������ֲ�����
  EXIT_MUSIC_FLAG,	//  �˳����ֲ�����
  START_STOP_MUSIC_FLAG,	    // ���ź���ͣ
  ON_SONG_MUSIC_FLAG,                // ��һ��
  NEXT_SONG_MUSIC_FLAG,                // ��һ��


  
} Coordinate_FLAG;


typedef struct {
  uint16_t CooX;		// ��ǰ�����Ļ������ֵ - ������
  uint16_t CooY;		// ��ǰ�����Ļ������ֵ - ������
  Coordinate_FLAG  TouchFlag;
} ts_globalVariable;
extern ts_globalVariable globalVariable;


uint8_t GT9147_Scan(uint8_t mode);


#endif // !__APP_OPERATE_H__
