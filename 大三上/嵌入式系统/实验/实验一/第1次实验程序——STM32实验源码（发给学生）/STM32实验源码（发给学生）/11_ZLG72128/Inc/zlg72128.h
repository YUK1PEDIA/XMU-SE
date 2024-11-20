#ifndef __ZLG72128_H
#define __ZLG72128_H

#include "stm32f4xx_hal.h"
#define ADDR_24LC64     0x70
#define I2C_PAGESIZE    8

void I2C_ZLG72128_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num);
void I2C_ZLG72128_Write_char(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf);
void I2C_ZLG72128_Write_buf(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num);

#endif
