#include "LM75A.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "usart.h"

uint8_t LM75SetMode(uint8_t ConfReg, uint8_t Mode)
{
	uint8_t Config;
	if(HAL_I2C_Mem_Write(&hi2c1,0x9F,ConfReg,1,&Mode,1,100) == HAL_OK)
	{
		if((HAL_I2C_Mem_Read(&hi2c1,0x9F,ConfReg,1,&Config,1,100) == HAL_OK) && ((Config && Mode) == Mode))
		{
#if DEBUG
			printf("current conf_reg: %02x\n",Config);
#endif
			return EVL_OK;
		}
	}
	return EVL_ER;
}

uint16_t LM75GetTempReg(void)
{
	uint8_t tempreg[2];
	uint16_t temp;
	if(HAL_I2C_Mem_Read(&hi2c1,0x9F,TEMP_ADDR,2,tempreg,2,100) == HAL_OK)
	{
		temp = ((tempreg[0] << 8) | tempreg[1]) >> 5;
#if DEBUG
		printf("current Temp: %04x\n",temp);
#endif
		return temp;
	}
	return EVL_ER;
}

double LM75GetTempValue(uint16_t tempreg)
{
	double TempValue;
	if(tempreg & (0x01 << 16))
	{
		TempValue = ((!tempreg)+1)*0.125;
		printf("TempValue: %lf`C\n",TempValue);
	}
	else
	{
		TempValue = tempreg*0.125;
		printf("TempValue: %lf`C\n",TempValue);
	}
	return TempValue;
}




