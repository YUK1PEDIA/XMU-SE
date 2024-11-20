#include "my_iic.h"
#include "delay_us.h"	 

//����I2C�ٶȵ���ʱ
void CT_Delay(void)
{
	delay_us(2);
} 
//���ݴ���оƬIIC�ӿڳ�ʼ��
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
    
    //PG0��ʼ������
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}	//PI3����ģʽ
void CT_SDA_OUT(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
    //PG0��ʼ������
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
} 	//PI3���ģʽ


//����IIC��ʼ�ź�
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda�����
	CT_IIC_SDA_1;	  	  
	CT_IIC_SCL_1;
	delay_us(5);
 	CT_IIC_SDA_0;//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	CT_IIC_SCL_0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda�����
	CT_IIC_SCL_1;
	//delay_us(5);
	CT_IIC_SDA_0;//STOP:when CLK is high DATA change form low to high
	delay_us(5);
	CT_IIC_SDA_1;//����I2C���߽����ź�  
	delay_us(5);
	CT_IIC_SCL_0;
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t CT_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	CT_SDA_IN();      //SDA����Ϊ����  
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
	CT_IIC_SCL_0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void CT_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL_0;//����ʱ�ӿ�ʼ���ݴ���
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
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t CT_IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
 	CT_SDA_IN();//SDA����Ϊ����
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
	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK   
 	return receive;
}





























