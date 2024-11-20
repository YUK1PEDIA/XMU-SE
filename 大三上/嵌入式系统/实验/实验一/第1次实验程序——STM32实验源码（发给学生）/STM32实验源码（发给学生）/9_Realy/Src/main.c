#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"

uint8_t Buff[2] = {0};
void SystemClock_Config(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();

  printf("\n\r FS-STM32开发板 继电器控制实验程序");
  printf("\n\r 请在串口软件输入框里输入“开”或者“关”, 然后按“发送”按钮");
  printf("\n\r 在发送完控制命令后可以听到继电器开启或者关闭的声音\n\r");

  while (1)
  {
		HAL_UART_Receive_IT(&huart1,Buff,2);		//等待接收输入的“开”或“关”字符
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

int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);	//循环发送, 直到发送完毕   
	USART1->DR = (uint8_t) ch;      
	return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		if(Buff[0]==0xBF&&Buff[1]==0xAA)		//检测接收到的数据是不是“开”
		{
			HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_SET);		//开启继电器
			printf("\n\r继电器 ：开\r\n");
		}
		else if(Buff[0]==0xB9&&Buff[1]==0xD8)	//检测接收到的数据是不是“关”
		{
			HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);	//关闭继电器
			printf("\n\r继电器 ：关\r\n");
		}
}

void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{ 
}
#endif
