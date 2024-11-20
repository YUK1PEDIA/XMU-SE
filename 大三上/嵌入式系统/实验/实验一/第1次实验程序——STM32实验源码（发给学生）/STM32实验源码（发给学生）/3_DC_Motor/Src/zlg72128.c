#include "zlg72128.h"
#include "stdio.h"

#define I2C_Open_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2C_Open_LONG_TIMEOUT         ((uint32_t)0xffff)
__IO uint32_t  I2CTimeout = I2C_Open_LONG_TIMEOUT;

void I2C_ZLG72128_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num)
{
    	while(HAL_I2C_Mem_Read (I2Cx ,I2C_Addr,addr,I2C_MEMADD_SIZE_8BIT,buf,num,I2CTimeout) != HAL_OK ){};
}

void I2C_ZLG72128_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value)
{   
	while( HAL_I2C_Mem_Write(I2Cx, I2C_Addr, addr, I2C_MEMADD_SIZE_8BIT, &value, 0x01, I2CTimeout) != HAL_OK ){};
}

void I2C_ZLG72128_Write_buf(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num)
{
	uint8_t *p = (buf+7);
	num--;
	while(num--)
	{
    		I2C_ZLG72128_WriteOneByte(I2Cx, I2C_Addr,addr--,*p--);
		HAL_Delay(5);
	}
}

void I2C_ZLG72128_Write_char(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf)
{
    	I2C_ZLG72128_WriteOneByte(I2Cx, I2C_Addr,addr,*buf);
	HAL_Delay(5);
}
