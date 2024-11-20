#include "my_iic.h"
#include "delay_us.h"	 

//控制I2C速度的延时
void CT_Delay(void)
{
	delay_us(2);
} 
//电容触摸芯片IIC接口初始化
void CT_IIC_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStruct;	
	
	__HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);  
	
	GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_SET); 
	
	
 // HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);  
}

void CT_SDA_IN(void)  
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
    //PG0初始化设置
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}	//PI3输入模式
void CT_SDA_OUT(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
    //PG0初始化设置
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
} 	//PI3输出模式


//产生IIC起始信号
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda线输出
	CT_IIC_SDA_1;	  	  
	CT_IIC_SCL_1;
	delay_us(5);
 	CT_IIC_SDA_0;//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	CT_IIC_SCL_0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda线输出
	CT_IIC_SCL_1;
	//delay_us(5);
	CT_IIC_SDA_0;//STOP:when CLK is high DATA change form low to high
	delay_us(5);
	CT_IIC_SDA_1;//发送I2C总线结束信号  
	delay_us(5);
	CT_IIC_SCL_0;
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t CT_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	CT_SDA_IN();      //SDA设置为输入  
	CT_IIC_SDA_1;	   delay_us(2);	
	CT_IIC_SCL_1;delay_us(2);	
	//CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
		CT_Delay();
	}
	CT_IIC_SCL_0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void CT_IIC_Ack(void)
{
	CT_IIC_SCL_0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA_0;
	CT_Delay();CT_Delay();
	CT_IIC_SCL_1;
	CT_Delay();CT_Delay();
	CT_IIC_SCL_0;
}
//不产生ACK应答		    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL_0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA_1;
	CT_Delay();
	CT_IIC_SCL_1;
	CT_Delay();
	CT_IIC_SCL_0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void CT_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL_0;//拉低时钟开始数据传输
	CT_Delay();
	for(t=0;t<8;t++)
    {              
     	if(((txd&0x80)>>7)==1)CT_IIC_SDA_1;
			else if(((txd&0x80)>>7)==0)CT_IIC_SDA_0;
        txd<<=1; 		
			delay_us(5);      
		CT_IIC_SCL_1; 
			delay_us(5);
		CT_IIC_SCL_0;	
			delay_us(5);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t CT_IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
 	CT_SDA_IN();//SDA设置为输入
	//delay_us(30);
	for(i=0;i<8;i++ )
	{ 
		CT_IIC_SCL_0; 	    	   
		delay_us(4);
		CT_IIC_SCL_1;	 
		receive<<=1;
		if(CT_READ_SDA)receive++;  
		delay_us(4);  
	}	  				 
	if (!ack)CT_IIC_NAck();//发送nACK
	else CT_IIC_Ack(); //发送ACK   
 	return receive;
}





























