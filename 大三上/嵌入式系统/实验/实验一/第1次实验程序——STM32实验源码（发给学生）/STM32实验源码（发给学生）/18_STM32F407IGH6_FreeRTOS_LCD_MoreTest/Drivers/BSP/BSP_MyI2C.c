/*
 * @Author: your name
 * @Date: 2021-07-08 09:15:02
 * @LastEditTime: 2021-07-11 17:29:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_MyI2C.c
 */
#include "BSP_MyI2C.h"
#include "OS_Delay.h"

/**
 * @description: 控制IIC传输的传输速度
 * @param {*}
 * @return {*}
 */
static void MY_Delay(void)
{
    delay_us(2);
}
/**
 * @description: 改变SDA引脚的工作模式为输入模式
 * @param {*}
 * @return {*}
 */
static void MY_SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = MY_I2C_SDA_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    ;
    HAL_GPIO_Init(MY_I2C_SDA_GPIO_PORT, &GPIO_InitStruct);
}
/**
 * @description: 改变SDA引脚的工作模式为输出模式
 * @param {*}
 * @return {*}
 */
static void MY_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = MY_I2C_SDA_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MY_I2C_SDA_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * @description: 产生起始信号
 * @param {*}
 * @return {*}
 */
void MY_IIC_Start(void)
{
    MY_SDA_OUT(); //sda线输出
    MY_IIC_SDA_1;
    MY_IIC_SCL_1;
    delay_us(5);
    MY_IIC_SDA_0; //START:when CLK is high,DATA change form high to low
    delay_us(5);
    MY_IIC_SCL_0; //钳住I2C总线，准备发送或接收数据
}
/**
 * @description: 产生停止信号
 * @param {*}
 * @return {*}
 */
void MY_IIC_Stop(void)
{
    MY_SDA_OUT(); //sda线输出
    MY_IIC_SCL_1;
    //delay_us(5);
    MY_IIC_SDA_0; //STOP:when CLK is high DATA change form low to high
    delay_us(5);
    MY_IIC_SDA_1; //发送I2C总线结束信号
    delay_us(5);
    MY_IIC_SCL_0;
}
/**
 * @description: 等待应该信号
 * @param {*}
 * @return {*} 返回值：1，接收应答失败
 *                    0，接收应答成功
 */
uint8_t MY_IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    MY_SDA_IN(); //SDA设置为输入
    MY_IIC_SDA_1;
    delay_us(2);
    MY_IIC_SCL_1;
    delay_us(2);
    //MY_Delay();
    while (CT_READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            MY_IIC_Stop();
            return 1;
        }
        MY_Delay();
    }
    MY_IIC_SCL_0; //时钟输出0
    return 0;
}
/**
 * @description: 产生应答信号
 * @param {*}
 * @return {*}
 */
void MY_IIC_Ack(void)
{
    MY_IIC_SCL_0;
    MY_SDA_OUT();
    MY_Delay();
    MY_IIC_SDA_0;
    MY_Delay();
    MY_Delay();
    MY_IIC_SCL_1;
    MY_Delay();
    MY_Delay();
    MY_IIC_SCL_0;
}
/**
 * @description: 不产生应答信号
 * @param {*}
 * @return {*}
 */
void MY_IIC_NAck(void)
{
    MY_IIC_SCL_0;
    MY_SDA_OUT();
    MY_Delay();
    MY_IIC_SDA_1;
    MY_Delay();
    MY_IIC_SCL_1;
    MY_Delay();
    MY_IIC_SCL_0;
}

/**
 * @description: IIC发送一个字节
 * @param {uint8_t} txd
 * @return {*}
 */
void MY_IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    MY_SDA_OUT();
    MY_IIC_SCL_0; //拉低时钟开始数据传输
    MY_Delay();
    for (t = 0; t < 8; t++)
    {
        if (((txd & 0x80) >> 7) == 1)
            MY_IIC_SDA_1;
        else if (((txd & 0x80) >> 7) == 0)
            MY_IIC_SDA_0;
        txd <<= 1;
        delay_us(5);
        MY_IIC_SCL_1;
        delay_us(5);
        MY_IIC_SCL_0;
        delay_us(5);
    }
}

/**
 * @description: 读取一个字节(ack=1时，发送ACK，ack=0，发送nACK)
 * @param {unsigned char} ack
 * @return {*}
 */
uint8_t MY_IIC_Read_Byte(unsigned char ack)
{
    uint8_t i, receive = 0;
    MY_SDA_IN(); //SDA设置为输入
    //delay_us(30);
    for (i = 0; i < 8; i++)
    {
        MY_IIC_SCL_0;
        delay_us(4);
        MY_IIC_SCL_1;
        receive <<= 1;
        if (CT_READ_SDA)
            receive++;
        delay_us(4);
    }
    if (!ack)
        MY_IIC_NAck(); //发送nACK
    else
        MY_IIC_Ack(); //发送ACK
    return receive;
}
