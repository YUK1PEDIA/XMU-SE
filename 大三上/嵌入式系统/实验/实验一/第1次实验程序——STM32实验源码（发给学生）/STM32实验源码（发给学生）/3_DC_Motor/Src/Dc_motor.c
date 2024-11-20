#include "Dc_motor.h"

#define I2C_Open_LONG_TIMEOUT         ((uint32_t)0xffff)

 __IO uint32_t  I2CTimeout1 = I2C_Open_LONG_TIMEOUT;

void I2C_DC_Motor_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value)
{   
	while( HAL_I2C_Mem_Write(I2Cx, I2C_Addr, addr, I2C_MEMADD_SIZE_8BIT, &value, 0x01, I2CTimeout1) != HAL_OK ){};
}

void I2C_DC_Motor_Write(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint8_t num)
{
	while(num--)
	{
    		I2C_DC_Motor_WriteOneByte(I2Cx, I2C_Addr,addr++,*buf++);
		HAL_Delay(5);
	}
}

uint8_t fs_flag = 0;

/***************************************************************************************************************
void DC_Task(uint8_t iKey)
{
	uint8_t Buffer_DC[1]={0Xff};
	uint8_t Buffer_DC_Zero[1]={0x00};

	switch(iKey)
	{
        			case 0xf7:		//按键“1”
					DC_Motor_Pin_Low();	
					I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x03,Buffer_DC_Zero,1);	//停转			
          					break;

        			case 0xfb:	//按键“2”
					DC_Motor_Pin_Low();	
				  	I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x05,Buffer_DC,1);		//逆时针转
          					break;

        			case 0xfd:	//按键“3”
					DC_Motor_Pin_Low();	
					I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x0f,Buffer_DC,1);		//逆时针转
          					break;	
		
        			case 0x14:	//按键“4”
				  	DC_MOtor_Pin_High();
					I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x0A,Buffer_DC,1);		//顺时针转				
          					break;   

			case 0x13:	//按键“5”		
				  	DC_MOtor_Pin_High();
				  	I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x05,Buffer_DC,1);		//顺时针转
					break;

        			case 0x12:	//按键“6”
					DC_MOtor_Pin_High();
				  	I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x03,Buffer_DC,1);		//停转
          					break;

        			default:		//按其它键
					DC_Motor_Pin_Low();	
				  	I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x00,Buffer_DC_Zero,1);
          					break;
			}
}
*************************************************************************************************/

//*************************************************************************************************
void DC_Task(uint8_t iKey)
{
	uint8_t Buffer_DC[1]={0Xff};
	uint8_t Buffer_DC_Zero[1]={0x00};

	switch(iKey)
	{
			case 0xf7:		//按键“1”		
				  	DC_MOtor_Pin_High();
				  	I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x05,Buffer_DC,1);		//顺时针转
					break;

        			case 0xfb:	//按键“2”
					DC_Motor_Pin_Low();	
				  	I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x05,Buffer_DC,1);		//逆时针转
          					break;

        			case 0xfd:	//按键“3”
					DC_Motor_Pin_Low();	
					I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x03,Buffer_DC_Zero,1);	//停转			
          					break;

        			default:		//按其它键
					DC_Motor_Pin_Low();	
				  	I2C_DC_Motor_Write(&hi2c1,DC_Motor_Addr,0x00,Buffer_DC_Zero,1);	//停转
          					break;
	}
}
//*******************************************************************************************/












