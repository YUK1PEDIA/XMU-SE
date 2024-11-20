#include "main.h"
#include "gpio.h"

uint16_t i = 0;
void SystemClock_Config(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1)
  {
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);	//实现 LED1 灯每隔 2000ms 闪烁一次
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_0);	//实现 LED2 灯每隔 2000ms 闪烁一次
//		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_15);	//实现 LED3 灯每隔 2000ms 闪烁一次
//		HAL_GPIO_TogglePin(GPIOH,GPIO_PIN_15);	//实现 LED4 灯每隔 2000ms 闪烁一次
		HAL_Delay(1000);				//延时1000ms	
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

void HAL_SYSTICK_Callback(void)
{
	i++;
	if(i == 500)
	{
		i = 0;
//		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);	//实现 LED1 灯每隔 1000ms 闪烁一次
//		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_0);	//实现 LED2 灯每隔 1000ms 闪烁一次
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_15);	//实现 LED3 灯每隔 1000ms 闪烁一次
		HAL_GPIO_TogglePin(GPIOH,GPIO_PIN_15);	//实现 LED4 灯每隔 1000ms 闪烁一次
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
