/*
 * @Author: your name
 * @Date: 2021-07-08 09:09:51
 * @LastEditTime: 2021-07-11 16:47:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_DC_motor.c
 */
#include "BSP_DC_motor.h"
#include "i2c.h"

#define DC_Motor_Addr 0x9A
#define I2C_Open_LONG_TIMEOUT ((uint32_t)0xffff)
__IO uint32_t I2CTimeout1 = I2C_Open_LONG_TIMEOUT;

/**
 * @description: 向寄存器中写一个字节的数据
 * @param {I2C_HandleTypeDef} *I2Cx
 * @param {uint8_t} I2C_Addr
 * @param {uint8_t} RegisterAddr
 * @param {uint8_t} value
 * @return {*}
 */
static void I2C_DC_Motor_WriteOneByte(I2C_HandleTypeDef *I2Cx, uint8_t I2C_Addr, uint8_t RegisterAddr, uint8_t value)
{
    HAL_I2C_Mem_Write(I2Cx, I2C_Addr, RegisterAddr, I2C_MEMADD_SIZE_8BIT, &value, 0x01, I2CTimeout1);
}
/**
 * @description: 向连续的寄存器中，连续写数据
 * @param {I2C_HandleTypeDef} *I2Cx
 * @param {uint8_t} I2C_Addr
 * @param {uint8_t} RegisterAddr
 * @param {uint8_t} *buf
 * @param {uint8_t} num
 * @return {*}
 */
static void I2C_DC_Motor_Write(I2C_HandleTypeDef *I2Cx, uint8_t I2C_Addr, uint8_t RegisterAddr, uint8_t *buf, uint8_t num)
{
    while (num--)
    {
        I2C_DC_Motor_WriteOneByte(I2Cx, I2C_Addr, RegisterAddr++, *buf++);
        HAL_Delay(5);
    }
}
/**
 * @description: 直流电机停转
 * @param {*}
 * @return {*}
 */
void Set_Dc_Motor_Stop(void)
{
    uint8_t Buffer_DC_Zero[1] = {0x00};
    HAL_GPIO_WritePin(DC_MOTOR_GPIO_Port, DC_MOTOR_Pin, GPIO_PIN_RESET);
    I2C_DC_Motor_Write(&hi2c1, DC_Motor_Addr, 0x00, Buffer_DC_Zero, 1);
}

/**
 * @description: 设置直流电机的电压值(实现将电压值传给DAC5517芯片，需要转换传送，电压不是一次传送的)
 * @param {uint8_t} V_Data 0~255
 * @return {*}
 */
static void Set_Dc_Motor_V(uint8_t V_Data)
{
    uint8_t Data_F;
    uint8_t Data_B[1] = {0};
    Data_F = V_Data & 0xf0;
    Data_F = Data_F >> 4;
    V_Data = V_Data & 0X0F;
    Data_B[0] = V_Data << 4;
    I2C_DC_Motor_Write(&hi2c1, DC_Motor_Addr, Data_F, Data_B, 1);
}
/**
 * @description: 电机正转
 * @param {uint8_t} v_data 直流电机的电压值
 * @return {*}
 */
void Set_DC_Motor_Z(uint8_t v_data)
{
    HAL_GPIO_WritePin(DC_MOTOR_GPIO_Port, DC_MOTOR_Pin, GPIO_PIN_RESET);
    Set_Dc_Motor_V(v_data);
}
/**
 * @description: 电机反转
 * @param {uint8_t} v_data 直流电机的电压值
 * @return {*}
 */
void Set_DC_Motor_B(uint8_t v_data) //反
{
    HAL_GPIO_WritePin(DC_MOTOR_GPIO_Port, DC_MOTOR_Pin, GPIO_PIN_SET);
    Set_Dc_Motor_V(v_data);
}
