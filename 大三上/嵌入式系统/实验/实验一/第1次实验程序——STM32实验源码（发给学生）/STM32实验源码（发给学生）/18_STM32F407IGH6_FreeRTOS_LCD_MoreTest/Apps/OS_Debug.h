/*
 * @Author: your name
 * @Date: 2021-07-07 15:34:48
 * @LastEditTime: 2021-07-14 09:39:49
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\OS_Debug.h
 */
#ifndef __OS_DEBUG_H__
#define __OS_DEBUG_H__

#include "main.h"
#include <stdio.h>



#ifndef USART_DEBUG_PORT
#define USART_DEBUG_PORT  huart1
#endif // !USART_DEBUG_PORT

#define	CONSOLE_ERROR(fmt, ...) do {printf("[ERROR][%s,%d]: " fmt "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);} while(0)
#define	CONSOLE_TRACE(fmt, ...) do {printf("[TRACE][%s,%d]: " fmt "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);} while(0)
#define	CONSOLE_DEBUG(fmt, ...) do {printf("[DEBUG][%s,%d]: " fmt "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);} while(0)
#define	CONSOLE_INFO(fmt, ...)  do {printf("[INFO][%s,%d]: " fmt "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);} while(0)
#define	CONSOLE_LINE()  do {printf("[LINE][%s,%d]\r\n", __FUNCTION__, __LINE__);} while(0)
void Printf_File_Error_Msg(uint8_t res);

#endif // !__OS_DEBUG_H__
