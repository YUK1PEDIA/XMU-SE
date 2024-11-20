#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "zlg72128.h"
#include "stdio.h"

#define ZLG_READ_ADDRESS1         		0x01   		//��ֵ�Ĵ���
#define ZLG_READ_FUNCTION_ADDRESS 	0x03		//���ܼ��Ĵ���
#define ZLG_READ_ADDRESS2         		0x10

#define ZLG_WRITE_ADDRESS1        		0x17		//���ұߵ�����ܣ���ʾ�������׵�ַ��
#define ZLG_WRITE_ADDRESS2        		0x16		//������7�������
#define ZLG_WRITE_ADDRESS3        		0x15		//������6�������
#define ZLG_WRITE_ADDRESS4        		0x14		//������5�������
#define ZLG_WRITE_ADDRESS5        		0x13		//������4�������
#define ZLG_WRITE_ADDRESS6        		0x12		//������3�������
#define ZLG_WRITE_ADDRESS7        		0x11		//������2�������
#define ZLG_WRITE_ADDRESS8        		0x10		//����ߵ������

#define ZLG_WRITE_FLASH           		0x0B
#define ZLG_WRITE_SCANNUM         		0x0D
#define BUFFER_SIZE1              		(countof(Tx1_Buffer))
#define BUFFER_SIZE2              		(countof(Rx2_Buffer))
#define countof(a)		  		(sizeof(a) / sizeof(*(a)))

uint8_t flag = 0xff;			//��ͬ�İ����в�ͬ�ı�־λֵ
uint8_t flag_key = 0;		//�жϱ�־λ��ÿ�ΰ�������һ���жϣ�����ʼ��ȡ8������ܵ�ֵ
uint8_t Rx2_Buffer[8]={0};
uint8_t Tx1_Buffer[8]={0};
uint8_t clear[9]={0};
uint8_t Rx1_Buffer[1]={0};
uint8_t Rx1_Buffer_P[1]={0};
uint8_t Rx1_Buffer_T[1]={0};
uint8_t reset[1]={0xff};
uint8_t Transmit_Buffer[2]={0x00,0x03};

void SystemClock_Config(void);
void swtich_key(void);
void swtich_key_func(void);
void switch_flag(void);
void delay_my(uint8_t time);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();

  printf("======>ZLG72128<======\n");
  printf("======>���Գ���<======\n");

  while (1)
  {
   		if(flag_key == 1)
		{
			flag_key = 0;
			flag = 0xff;

			I2C_ZLG72128_Read(&hi2c1, 0x61, 0x01, Rx1_Buffer_P, 1);       	//����ͨ����ֵ
			I2C_ZLG72128_Read(&hi2c1, 0x61, 0x03, Rx1_Buffer_T, 1);		//�����ܰ���ֵ

			if (Rx1_Buffer_P[0] != 0x0)              //��ͨ����
			{
		//		printf("\n\r key value = %#x\r\n", Rx1_Buffer_P[0]);
				swtich_key();
				printf("flag = %d\n", flag);
			}

			if (Rx1_Buffer_T[0] != 0xff)             //���ܰ���
			{
		//		printf("\n\r function key value = %#x\r\n", Rx1_Buffer_T[0]);
				swtich_key_func();
				printf("flag = %d\n", flag);
			}

			I2C_ZLG72128_Read(&hi2c1,0x61,0x10,Rx2_Buffer,8);		//��8λ�����
			switch_flag();						//ɨ�赽��Ӧ�İ��������������д����ֵ	
		}					
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

void swtich_key(void)	//��ͨ�����ļ�ֵת����12������
{
	switch(Rx1_Buffer_P[0])
	{
		case 0x01:
			flag = 13;
			break;
		case 0x02:
			flag = 15;
			break;
		case 0x03:
			flag = 0;
			break;
		case 0x04:
			flag = 14;
			break;
		case 0x09:
			flag = 12;
			break;
		case 0x0a:
			flag = 9;
			break;
		case 0x0b:
			flag = 8;
			break;
		case 0x0c:
			flag = 7;
			break;
		case 0x11:
			flag = 11;
			break;
		case 0x12:
			flag = 6;
			break;
		case 0x13:
			flag = 5;
			break;
		case 0x14:
			flag = 4;
			break;
	}
}

void swtich_key_func(void)		//���ܰ����ļ�ֵת����4������
{
	switch (Rx1_Buffer_T[0])
	{
		case 0xfe:
			flag = 10;
			break;
		case 0xfd:
			flag = 3;
			break;
		case 0xfb:
			flag = 2;
			break;
		case 0xf7:
			flag = 1;
			break;
		default:
			break;
	}
}

void switch_flag(void)	//������ֵ�����������ʾ
{
	switch(flag){
			case 0:	//��ʾ��0��
					Tx1_Buffer[0] = 0x3f;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 1:	//��ʾ��1��
					Tx1_Buffer[0] = 0x06;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 2:	//��ʾ��2��
					Tx1_Buffer[0] = 0x5b;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 3:	//��ʾ��3��
					Tx1_Buffer[0] = 0x4f;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 4:	//��ʾ��4��
					Tx1_Buffer[0] = 0x66;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 5:	//��ʾ��5��
					Tx1_Buffer[0] = 0x6d;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 6:	//��ʾ��6��
					Tx1_Buffer[0] = 0x7d;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 7:	//��ʾ��7��
					Tx1_Buffer[0] = 0x07;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 8:	//��ʾ��8��
					Tx1_Buffer[0] = 0x7f;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 9:	//��ʾ��9��
					Tx1_Buffer[0] = 0x6f;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 10:	//��ʾ��A��
					Tx1_Buffer[0] = 0x77;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 11:	//��ʾ��b��
					Tx1_Buffer[0] = 0x7c;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 12:	//��ʾ��C��
				  	Tx1_Buffer[0] = 0x39;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 13:	//��ʾ��d��
					Tx1_Buffer[0] = 0x5e;                                   
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 14:	//��ʾ��.��
				 	Tx1_Buffer[0] = 0x80;
					if(Rx2_Buffer[7] == 0)
					{
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);
					}
					else
					{									
						I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
						I2C_ZLG72128_Write_char(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,Tx1_Buffer);					
					}
					break;

			case 15: 	//��ʾ��  ��                                    				
					I2C_ZLG72128_Write_buf(&hi2c1,0x60,ZLG_WRITE_ADDRESS1,clear,9);
					break;

			default:
					break;
		}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_13)
	{	
			delay_my(200);		
			if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13) == GPIO_PIN_RESET)	
			{
					flag_key = 1;
			}		
	}
}

void delay_my(uint8_t time)
{
	for(int i=0; i<time*10; i++)
	{
		for(int j=0; j<time; j++)
		{}
	}
}

int fputc(int ch, FILE *f)
{ 
  	uint8_t tmp[1]={0};
	tmp[0] = (uint8_t)ch;
	HAL_UART_Transmit(&huart1,tmp,1,10);	
	return ch;
}

void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{ 
}
#endif
