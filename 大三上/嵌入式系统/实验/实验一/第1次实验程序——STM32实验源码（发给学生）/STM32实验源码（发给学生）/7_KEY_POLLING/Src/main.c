#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"

#define KEY3  HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_9)	//获取GPIO状态（如果KEY3键按下，则KEY3=0）
#define KEY4  HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_11) 	//获取GPIO状态（如果KEY4键按下，则KEY4=0）

void SystemClock_Config(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();

  printf("-----查询方式按键程序-----\r\n");

  while (1)
  {
		if(KEY3==0)	//判断KEY3是否被按下
		{
		  	HAL_Delay(1);	//延时1ms
			printf("KEY3 is pressed\r\n");
			while(!KEY3);			//消抖，一直到松开按键
			printf("KEY3 is released\r\n\n\n");
		}

		if(KEY4==0)	//判断KEY4是否被按下
		{
		  	HAL_Delay(1);	//延时1ms
			printf("KEY4 is pressed\r\n");
			while(!KEY4);			//消抖，一直到松开按键
			printf("KEY4 is released\r\n\n\n");
		}
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0); 
	USART1->DR = (uint8_t) ch;      
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
