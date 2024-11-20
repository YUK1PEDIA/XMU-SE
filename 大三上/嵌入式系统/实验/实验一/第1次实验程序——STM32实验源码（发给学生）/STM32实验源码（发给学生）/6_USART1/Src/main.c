#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"

uint8_t Buff[5];
void SystemClock_Config(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();

  printf("\n\r FS-STM32�����崮���жϲ�������\r\n");							//�ڴ��ڵ�����������ʾ��ӡ������
  printf("\n\r ���ڴ��ڵ������ֵķ��Ϳ������롰12345�����������͡���ť���ۿ����ڵ������ֽ��տ��е�����\r\n");	//�ڴ��ڵ�����������ʾ��ӡ������

  while (1)
  {
	HAL_UART_Receive_IT(&huart1, Buff, 5);	//���ڽ��ա����жϷ�ʽ���գ��жϻص������﷢��Buff��ÿ�ν���5���ַ�
//	HAL_UART_Receive_IT(&huart1, Buff, 10);	//���ڽ��ա����жϷ�ʽ���գ��жϻص������﷢��Buff��ÿ�ν���10���ַ�
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Transmit(&huart1, Buff, 5,100);	//���ڷ��ͣ�ÿ�η���5���ַ�
//	HAL_UART_Transmit(&huart1, Buff, 10,100);	//���ڷ��ͣ�ÿ�η���10���ַ�
}

int fputc(int ch, FILE *f)
{ 
  	uint8_t tmp[1]={0};
	tmp[0] = (uint8_t)ch;
	HAL_UART_Transmit(&huart1,tmp,1,10);	//���ڷ���
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
