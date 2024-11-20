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

/************** LCD显示屏触摸点位置 *****************/
typedef enum {
  ERROR_FLAG = -1,
  STEPPING_MOTOR_FLAG = 0,		// 步进电机
  DC_MOTOR_FLAG,							// 直流电机
  STEERING_GEATR_FLAG,				// 舵机
  RELAY_FLAG,									// 继电器
  BUZZER_FLAG,								// 蜂鸣器
  LED_FLAG,								// 进入音乐播放器
  EXIT_MUSIC_FLAG,	//  退出音乐播放器
  START_STOP_MUSIC_FLAG,	    // 播放和暂停
  ON_SONG_MUSIC_FLAG,                // 上一曲
  NEXT_SONG_MUSIC_FLAG,                // 下一曲


  
} Coordinate_FLAG;


typedef struct {
  uint16_t CooX;		// 当前点击屏幕的坐标值 - 横坐标
  uint16_t CooY;		// 当前点击屏幕的坐标值 - 纵坐标
  Coordinate_FLAG  TouchFlag;
} ts_globalVariable;
extern ts_globalVariable globalVariable;


uint8_t GT9147_Scan(uint8_t mode);


#endif // !__APP_OPERATE_H__
