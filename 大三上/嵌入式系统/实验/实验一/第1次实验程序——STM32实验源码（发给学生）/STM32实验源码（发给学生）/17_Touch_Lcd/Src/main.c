#include <stdio.h>
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"
#include "lcd.h"
#include "pic.h"
#include "lcd_touch.h"
#include "delay_us.h"
#include "gt9147.h"

void SystemClock_Config(void);

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
  return ch;
}

int main(void)
{
  	HAL_Init();
  	SystemClock_Config();
  	MX_GPIO_Init();
  	MX_USART1_UART_Init();
  	MX_FSMC_Init();
	delay_init(168); // us延时初始化
	LCD_Init();  // LCD初始化
	TP_Init();   // LCD触摸传感器初始化
	LCD_Clear(BLUE); // 全屏为蓝色
	LCD_ShowString(30, 40, 210, 24, 24, "STM32F407IGH6");
  	LCD_ShowString(30, 70, 200, 16, 16, "TFTLCD TEST");
	LCD_DrawPicture(0, 300, 480, 500, (uint8_t *)gImage_hqyj);
  	while (1)
  	{
		GT9147_Scan(0);
		HAL_Delay(50);
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

void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{ 
}
#endif
