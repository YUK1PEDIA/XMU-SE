/*
 * @Author: your name
 * @Date: 2021-07-08 09:18:36
 * @LastEditTime: 2021-07-21 13:10:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\APP_StartShow.h
 */
#ifndef __APP_STARTSHOW_H
#define __APP_STARTSHOW_H

#include "main.h"
#include "ff.h"
typedef struct
{
  char DiskPath[4]; // ´ÅÅÌÂ·¾¶
  DIR picdir;       //Í¼Æ¬Ä¿Â¼
  FATFS DiskFatFs;  // ´ÅÅÌ FatFs
} __FILE_SYS_;

void App_StartShow(void);
void Board_Init(void);
void HAL_IT_Start(void);
void HAL_IT_Stop(void);

void Load_Background_Bmp(void);
void Load_MusicAudio_Bmp(void);
void Load_Music_Stop_Bmp(void);
void Load_Music_Start_Bmp(void);
#endif // !__APP_STARTSHOW_H
