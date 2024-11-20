#ifndef __Dc_motor_H
#define __Dc_motor_H
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "zlg72128.h"
#define DC_Motor_Addr 0x9A

#define DC_Motor_Port GPIOE
#define DC_Motor_Pin 	GPIO_PIN_2

#define DC_Motor_Pin_Low()  HAL_GPIO_WritePin(DC_Motor_Port, DC_Motor_Pin, GPIO_PIN_RESET) 
#define DC_MOtor_Pin_High() HAL_GPIO_WritePin(DC_Motor_Port, DC_Motor_Pin, GPIO_PIN_SET)

extern uint8_t fs_flag ;

void I2C_DC_Motor_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value);
void I2C_DC_Motor_Write(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num);

void DC_Task(uint8_t iKey);

#endif





















