/*
 * @Author: your name
 * @Date: 2021-07-08 09:24:04
 * @LastEditTime: 2021-07-11 17:54:26
 * @LastEditors: Please set LastEditors
 * @Description: SD¿¨
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_SDCard.h
 */
#ifndef __BSP_SDCARD_H
#define __BSP_SDCARD_H
#include "main.h"


#define SD_TRANSFER_OK     	(0x00)
#define SD_TRANSFER_BUSY   	(0x01)


uint8_t SD_Init(void);
uint8_t SD_GetCardInfo(HAL_SD_CardInfoTypeDef *cardinfo);
uint8_t SD_GetCardState(void);
uint8_t SD_ReadDisk(uint8_t* buf,uint32_t sector,uint32_t cnt);
uint8_t SD_WriteDisk(uint8_t *buf,uint32_t sector,uint32_t cnt);

#endif // !__BSP_SDCARD_H


