/*
 * @Author: your name
 * @Date: 2021-07-08 09:11:38
 * @LastEditTime: 2021-07-11 18:08:59
 * @LastEditors: Please set LastEditors
 * @Description: 矩阵键盘和数码管
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_zlg7290.c
 */
#include "BSP_zlg7290.h"
#include "i2c.h"
#include "stdio.h"
static __IO uint32_t I2C_ZLG7290_Timeout = ((uint32_t)0x1000);

/* 8段数码管的读取值 */
uint8_t Zlg7290_Rx2_Buffer[8] = {0};
uint8_t clear_7290[8] = {0};
/**
 * @description: 读寄存器
 * @param {uint8_t} RegisterAddr
 * @param {uint8_t} *buf
 * @param {uint8_t} num
 * @return {*}
 */
uint8_t I2C_ZLG7290_Read(uint8_t RegisterAddr, uint8_t *buf, uint8_t num)
{
   return HAL_I2C_Mem_Read(&hi2c1, ADDR_ZLG_R, RegisterAddr, I2C_MEMADD_SIZE_8BIT, buf, num, I2C_ZLG7290_Timeout);
}

//uint8_t I2C_ZLG7290_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num)
//{
//    while(HAL_I2C_Mem_Read (I2Cx ,I2C_Addr,addr,I2C_MEMADD_SIZE_8BIT,buf,num,I2C_ZLG7290_Timeout) != HAL_OK ){};
//}
/**
 * @description: 向寄存器写一个字节
 * @param {uint8_t} RegisterAddr
 * @param {uint8_t} value
 * @return {*}
 *///I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value
void I2C_ZLG7290_WriteOneByte(uint8_t RegisterAddr, uint8_t value)
{
    HAL_I2C_Mem_Write(&hi2c1, ADDR_ZLG_W, RegisterAddr, I2C_MEMADD_SIZE_8BIT, &value, 0x01, I2C_ZLG7290_Timeout);
}
/**
 * @description: 向寄存器写数据
 * @param {uint8_t} RegisterAddr
 * @param {uint8_t} *buf
 * @param {uint8_t} num
 * @return {*}
 */
void I2C_ZLG7290_Write(uint8_t RegisterAddr, uint8_t *buf, uint8_t num)
{
		uint8_t *p = (buf+7);
//		printf("RegisterAddr = 0x%x\n",RegisterAddr);
//		for(uint8_t i=0;i<8;i++)
//			printf("0x%x ",buf[i]);
//	printf("----------------\n");
		while(RegisterAddr != 0xf)	{
			I2C_ZLG7290_WriteOneByte(RegisterAddr, *p);
			HAL_Delay(5);
			p--;
			RegisterAddr--;			
		}

//    while (num--)
//    {
//        I2C_ZLG7290_WriteOneByte(RegisterAddr++, *buf++);
//        HAL_Delay(5);
//    }
}

//void I2C_ZLG7290_Write_buf(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t write_addr,uint8_t *buf,uint8_t num)
//{
//	uint8_t *p = (buf+7);
//	num--;
//	while(num--)
//	{
////		printf("%d-%x\n",num,*p);
//    I2C_ZLG7290_WriteOneByte(I2Cx, I2C_Addr,write_addr--,*p--);
//		HAL_Delay(5);

//	}
//}

//void I2C_ZLG7290_Write_char(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t write_addr,uint8_t *buf)
//{
//    I2C_ZLG7290_WriteOneByte(I2Cx, I2C_Addr,write_addr,*buf);
//		HAL_Delay(5);
//}
/**
 * @description: 读取矩阵键盘的值
 * @param {uint8_t} keyValue
 * @return {*}
 */
uint8_t BSP_read_MatrixKeyToFlag(uint8_t keyValue)
{
    uint8_t ret = 0;
    switch (keyValue)
    {
    case 0x1C:
        ret = 1;
        break;
    case 0x1B:
        ret = 2;
        break;
    case 0x1A:
        ret = 3;
        break;
    case 0x14:
        ret = 4;
        break;
    case 0x13:
        ret = 5;
        break;
    case 0x12:
        ret = 6;
        break;
    case 0x0C:
        ret = 7;
        break;
    case 0x0B:
        ret = 8;
        break;
    case 0x0A:
        ret = 9;
        break;
    case 0x03:
        ret = 15;
        break;
    case 0x19:
        ret = 10;
        break;
    case 0x11:
        ret = 11;
        break;
    case 0x09:
        ret = 12;
        break;
    case 0x01:
        ret = 13;
        break;
    case 0x02:
        ret = 14;
        break;
    case 0x04:
        ret = 16;
        break;
    default:
        break;
    }
    return ret;
}
/**
 * @description: 显示在数码管中
 * @param {uint8_t} flag
 * @return {*}
 */
void write_LcdDisplay(uint8_t flag)
{
    uint8_t Tx1_Buffer[2] = {0};
    switch (flag)
    {
			
    case 1:
        Tx1_Buffer[0] = 0x0c;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
//						printf("char - 0x%x ",Tx1_Buffer[0]);						
//            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS1, Tx1_Buffer, 1);
						I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {		
//						printf("buf - 0x%x ",Tx1_Buffer[0]);	
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 2:
        Tx1_Buffer[0] = 0xDA;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 3:
        Tx1_Buffer[0] = 0xF2;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 4:
        Tx1_Buffer[0] = 0x66;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 5:
        Tx1_Buffer[0] = 0xB6;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 6:
        Tx1_Buffer[0] = 0xBE;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
           I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 7:
        Tx1_Buffer[0] = 0xE0;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
						I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 8:
        Tx1_Buffer[0] = 0xFE;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 9:
        Tx1_Buffer[0] = 0xF6;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
           I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 10:
        Tx1_Buffer[0] = 0xEE;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
           I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 11:
        Tx1_Buffer[0] = 0x3E;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 12:
        Tx1_Buffer[0] = 0x9C;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 13:
        Tx1_Buffer[0] = 0x7A;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    case 14:
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, clear_7290, BUFFER_SIZE2);
            I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, clear_7290[0]);
        break;
    case 15:
        Tx1_Buffer[0] = 0xFC;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
           I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
           I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
    case 16:
        Tx1_Buffer[0] = 0x1;
        if (Zlg7290_Rx2_Buffer[7] == 0)
        {
           I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        else
        {
            I2C_ZLG7290_Write(ZLG_WRITE_ADDRESS2, Zlg7290_Rx2_Buffer, BUFFER_SIZE2);
           I2C_ZLG7290_WriteOneByte(ZLG_WRITE_ADDRESS1, Tx1_Buffer[0]);
        }
        break;
    default:
        break;
    }
}
/**
 * @description: 在TFT-LCD显示屏中显示
 * @param {uint8_t} keyValue
 * @return {*}
 */
char *LCD_ZLG_ToString(uint8_t keyValue)
{
    char *LCD_Data;
    switch (keyValue)
    {
    case 0x1C:
        LCD_Data = "   1   ";
        break;
    case 0x1B:
        LCD_Data = "   2   ";
        break;
    case 0x1A:
        LCD_Data = "   3   ";
        break;
    case 0x14:
        LCD_Data = "   4   ";
        break;
    case 0x13:
        LCD_Data = "   5   ";
        break;
    case 0x12:
        LCD_Data = "   6   ";
        break;
    case 0x0C:
        LCD_Data = "   7   ";
        break;
    case 0x0B:
        LCD_Data = "   8   ";
        break;
    case 0x0A:
        LCD_Data = "   9   ";
        break;
    case 0x03:
        LCD_Data = "   0   ";
        break;
    case 0x19:
        LCD_Data = "   A   ";
        break;
    case 0x11:
        LCD_Data = "   B   ";
        break;
    case 0x09:
        LCD_Data = "   C   ";
        break;
    case 0x01:
        LCD_Data = "   D   ";
        break;
    case 0x02:
        LCD_Data = "   #   ";
        break;
    case 0x04:
        LCD_Data = "   *   ";
        break;
    default:
        LCD_Data = "      ";
        break;
    }
    return LCD_Data;
}
