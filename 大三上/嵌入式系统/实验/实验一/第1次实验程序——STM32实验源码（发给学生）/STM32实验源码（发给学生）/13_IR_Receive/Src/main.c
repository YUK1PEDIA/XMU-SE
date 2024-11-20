#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "RemoteInfrared.h"

__IO uint32_t GlobalTimingDelay100us;
void SystemClock_Config(void);

int main(void)
{
  	HAL_Init();
  	SystemClock_Config();
  	MX_GPIO_Init();
  	MX_USART1_UART_Init();

	printf("\n\r FS-STM32开发板 IR红外线接收实验程序\n\r");

  	while (1)
  	{
		Remote_Infrared_KeyDeCode();	//等待按红外遥控器的按键	
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/10000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);	//循环发送,直到发送完毕   
	USART1->DR = (uint8_t) ch;      
	return ch;
}

void HAL_SYSTICK_Callback(void)
{
    if(GlobalTimingDelay100us != 0)
    {
       GlobalTimingDelay100us--;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
       Remote_Infrared_KEY_ISR();
}

void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{ 
}
#endif
