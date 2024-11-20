#include "BSP_zlg72128.h"
#include "stdio.h"
#include "i2c.h"
/* Maximum Timeout values for flags and events waiting loops. These timeouts are
not based on accurate values, they just guarantee that the application will 
not remain stuck if the I2C communication is corrupted.
You may modify these timeout values depending on CPU frequency and application
conditions (interrupts routines ...). */   
#define I2C_Open_FLAG_TIMEOUT         ((uint32_t)0x1000)

#define I2C_Open_LONG_TIMEOUT         ((uint32_t)0xffff)

__IO uint32_t  I2CTimeout2 = I2C_Open_LONG_TIMEOUT;

#define ZLG_READ_ADDRESS1         0x01   	//键值寄存器
#define ZLG_READ_FUNCTION_ADDRESS 0x03		//功能键寄存器
#define ZLG_READ_ADDRESS2         0x10

#define ZLG_WRITE_ADDRESS1        0x17		//显示缓冲区首地址
#define ZLG_WRITE_ADDRESS2        0x16

#define ZLG_WRITE_FLASH           0x0B
#define ZLG_WRITE_SCANNUM         0x0D


#define BUFFER_SIZE1              (countof(Tx1_Buffer_1))
#define BUFFER_SIZE2              (countof(Rx2_Buffer_72128))
#define countof(a)							  (sizeof(a) / sizeof(*(a)))

uint8_t flag_72128 = 0xff;					//不同的按键有不同的标志位值
uint8_t flag_key_72128 = 0;					//中断标志位，每次按键产生一次中断，并开始读取8个数码管的值
uint8_t Rx2_Buffer_72128[8]={0};
uint8_t Tx1_Buffer_1[8]={0};
uint8_t clear_72128[9]={0};
uint8_t Rx1_Buffer_72128[1]={0};


uint8_t Rx1_Buffer_P_72128[1]={0};
uint8_t Rx1_Buffer_T_72128[1]={0};
uint8_t reset_72128[1]={0xff};
uint8_t Transmit_Buffer_72128[2]={0x00,0x03};
/*******************************************************************************
* Function Name  : I2C_24C64_Read
* Description    : 
* Input          : 
* Output         : 
* Return         : 
* Attention      : None
*******************************************************************************/

void I2C_ZLG72128_Read(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num)
{
    while(HAL_I2C_Mem_Read (I2Cx ,I2C_Addr,addr,I2C_MEMADD_SIZE_8BIT,buf,num,I2CTimeout2) != HAL_OK ){};
}

/*******************************************************************************
* Function Name  : I2C_24C64_WriteOneByte
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/

void I2C_ZLG72128_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value)
{   
	while( HAL_I2C_Mem_Write(I2Cx, I2C_Addr, addr, I2C_MEMADD_SIZE_8BIT, &value, 0x01, I2CTimeout2) != HAL_OK ){};
}

/*******************************************************************************
* Function Name  : I2C_24C64_Write
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/

void I2C_ZLG72128_Write_buf(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num)
{
	uint8_t *p = (buf+7);
	num--;
	while(num--)
	{
		printf("%d-%x\n",num,*p);
    I2C_ZLG72128_WriteOneByte(I2Cx, I2C_Addr,addr--,*p--);
		HAL_Delay(5);

	}
}

void I2C_ZLG72128_Write_char(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf)
{
    I2C_ZLG72128_WriteOneByte(I2Cx, I2C_Addr,addr,*buf);
		HAL_Delay(5);
}

void swtich_key(void)
{
	switch(Rx1_Buffer_P_72128[0])
	{
		case 0x01:
			flag_72128 = 13;
			break;
		case 0x02:
			flag_72128 = 15;
			break;
		case 0x03:
			flag_72128 = 0;
			break;
		case 0x04:
			flag_72128 = 14;
			break;
		case 0x09:
			flag_72128 = 12;
			break;
		case 0x0a:
			flag_72128 = 9;
			break;
		case 0x0b:
			flag_72128 = 8;
			break;
		case 0x0c:
			flag_72128 = 7;
			break;
		case 0x11:
			flag_72128 = 11;
			break;
		case 0x12:
			flag_72128 = 6;
			break;
		case 0x13:
			flag_72128 = 5;
			break;
		case 0x14:
			flag_72128 = 4;
			break;
	}
}
void swtich_key_func(void)
{
	switch (Rx1_Buffer_T_72128[0])
	{
		case 0xfe:
			flag_72128 = 10;
			break;
		case 0xfd:
			flag_72128 = 3;
			break;
		case 0xfb:
			flag_72128 = 2;
			break;
		case 0xf7:
			flag_72128 = 1;
			break;
		default:
			break;
	}
}

void switch_flag(void){
//	for(int i=0;i<8;i++)
//		printf("0x%x ",Rx2_Buffer_72128[i]);
//	printf("\n");
	switch(flag_72128){
			case 0:
					Tx1_Buffer_1[0] = 0x3f;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
				break;
			case 1:
					Tx1_Buffer_1[0] = 0x06;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 2:
					Tx1_Buffer_1[0] = 0x5b;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 3:
					Tx1_Buffer_1[0] = 0x4f;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 4:
					Tx1_Buffer_1[0] = 0x66;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 5:
					Tx1_Buffer_1[0] = 0x6d;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 6:
					Tx1_Buffer_1[0] = 0x7d;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 7:
					Tx1_Buffer_1[0] = 0x07;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 8:
					Tx1_Buffer_1[0] = 0x7f;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 9:
					Tx1_Buffer_1[0] = 0x6f;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 10:
					Tx1_Buffer_1[0] = 0x77;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 11:
					Tx1_Buffer_1[0] = 0x7c;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 12:
				  Tx1_Buffer_1[0] = 0x39;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 13:
					Tx1_Buffer_1[0] = 0x5e;                                      //0x7a;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 14:
				 Tx1_Buffer_1[0] = 0x80;
					if(Rx2_Buffer_72128[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer_72128,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer_1);					
					}
					break;
			case 15:                                     				
					I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,clear_72128,9);
					
					
					break;
			default:
				break;
		}
}

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
