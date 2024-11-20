#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "zlg72128.h"
#include "stdio.h"
#include "Dc_motor.h"
#include "i2c.h"

#define ZLG_READ_ADDRESS1         		0x01  	//��ֵ�Ĵ���
#define ZLG_READ_FUNCTION_ADDRESS 	0x03	//���ܼ��Ĵ���
#define ZLG_READ_ADDRESS2         		0x10
#define ZLG_WRITE_ADDRESS1        		0x17	//�������ʾĩβ��ַ
#define ZLG_WRITE_ADDRESS2        		0x16  
#define BUFFER_SIZE1              		(countof(Tx1_Buffer))
#define BUFFER_SIZE2              		(countof(Rx2_Buffer))
#define countof(a) 				(sizeof(a) / sizeof(*(a)))

uint8_t flag;				//��ͬ�İ����в�ͬ�ı�־λֵ
uint8_t Rx2_Buffer[8]={0};
uint8_t Tx1_Buffer[8]={0};
uint8_t Rx1_Buffer[1]={0};
uint8_t Rx1_Buffer_P[1]={0};
uint8_t Rx1_Buffer_T[1]={0};
uint8_t reset[1]={0xff};
uint8_t Transmit_Buffer[2]={0x00,0x03};
unsigned char seg7code[10]={ 0xFC,0x0C,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xE6}; 	//������ָ�
void SystemClock_Config(void);
void swtich_key(void);
void swtich_key_func(void);
void switch_flag(void);

int main(void)
{
  	HAL_Init();		//HAL��ʼ��
  	SystemClock_Config();	//ϵͳʱ������
  	MX_GPIO_Init();		//GPIO��ʼ��
  	MX_I2C1_Init();		//I2C��ʼ��
  	MX_TIM3_Init();		//TIM3��ʼ��
  	MX_USART1_UART_Init();	//���ڳ�ʼ��

	printf("\n\r FS-STM32������ֱ���������ʵ��\r\n");		//�ڴ��ڵ�����������ʾ��ӡ������

	DC_Motor_Pin_Low();
	HAL_TIM_Base_Start_IT(&htim3);   	//������ʱ��3	
 
  	while (1)
  	{
		if(flag1 == 1)	//����а���
		{
			flag1 = 0;		//������ע��0

			I2C_ZLG72128_Read(&hi2c1,0x61,0x01,Rx1_Buffer_P,1);	//����ͨ����ֵ	
			I2C_ZLG72128_Read(&hi2c1,0x61,0x03,Rx1_Buffer_T,1);	//�����ܰ���ֵ	

			if (Rx1_Buffer_P[0] != 0x0)              //��ͨ������12����
			{
//				printf("\n\r key value = %#x\r\n", Rx1_Buffer_P[0]);		//�ڴ��ڵ�����������ʾ��ֵ
				swtich_key();		//��ֵת��
				printf("flag = %d\n", flag);
				DC_Task(Rx1_Buffer_P[0]);	//���ݼ�ֵ����Ӧ�Ķ���
			}	
	
			if (Rx1_Buffer_T[0] != 0xff)             //���ܰ�����4����
			{
//				printf("\n\r function key value = %#x\r\n", Rx1_Buffer_T[0]);	//�ڴ��ڵ�����������ʾ��ֵ
				swtich_key_func();		//��ֵת��
				printf("flag = %d\n", flag);
				DC_Task(Rx1_Buffer_T[0]);	//���ݼ�ֵ����Ӧ�Ķ���
			}
		}
	
	  	HAL_Delay(100);	//��ʱ100ms
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

void swtich_key(void)		//��ͨ����ֵת����12��������������0��4��5��6��7��8��9��11��12��13��14��15
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
		default:
			break;
	}
}

void swtich_key_func(void)		//���ܰ���ֵת����4������������1��2��3��10
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

int fputc(int ch, FILE *f)		//�����ڴ��ڵ�����������ʾ�ַ�
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
