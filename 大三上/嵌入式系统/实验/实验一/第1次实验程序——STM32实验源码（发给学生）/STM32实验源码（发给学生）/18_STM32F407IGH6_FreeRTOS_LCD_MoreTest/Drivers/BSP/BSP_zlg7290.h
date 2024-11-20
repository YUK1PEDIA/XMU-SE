/*
 * @Author: your name
 * @Date: 2021-07-08 09:11:38
 * @LastEditTime: 2021-07-11 18:09:47
 * @LastEditors: Please set LastEditors
 * @Description: æÿ’Ûº¸≈Ã∫Õ ˝¬Îπ‹
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_zlg7290.h
 */
#ifndef __BSP_ZLG7290_H
#define __BSP_ZLG7290_H

#include "main.h"

#define ADDR_ZLG_W     0x70
#define ADDR_ZLG_R     0x71

#define ZLG_READ_ADDRESS1         0x01
#define ZLG_READ_ADDRESS2         0x10
#define ZLG_WRITE_ADDRESS1        0x17
#define ZLG_WRITE_ADDRESS2        0x16

#define countof(a) (sizeof(a) / sizeof(*(a)))
#define BUFFER_SIZE2              (countof(Zlg7290_Rx2_Buffer))
#define I2C_PAGESIZE    8

extern uint8_t Zlg7290_Rx2_Buffer[8];

uint8_t I2C_ZLG7290_Read(uint8_t addr,uint8_t *buf,uint8_t num);
void I2C_ZLG7290_Write(uint8_t addr,uint8_t *buf,uint8_t num);
//uint8_t I2C_ZLG7290_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num);
//void I2C_ZLG7290_Write(uint8_t addr,uint8_t *buf,uint8_t num);


uint8_t BSP_read_MatrixKeyToFlag(uint8_t keyValue);
void write_LcdDisplay(uint8_t flag);

char* LCD_ZLG_ToString(uint8_t keyValue);

//void I2C_ZLG7290_Write_buf(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t write_addr,uint8_t *buf,uint8_t num);
//void I2C_ZLG7290_Write_char(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t write_addr,uint8_t *buf);
#endif // !__BSP_ZLG7290_H


