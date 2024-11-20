#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"
#include "delay.h"  
#include "lcd.h" 
#include "pic.h" 
#include "stdio.h"

void SystemClock_Config(void);

int main(void)
{
  	HAL_Init();
  	SystemClock_Config();
  	MX_GPIO_Init();
  	MX_FSMC_Init();
  	MX_USART1_UART_Init();
	uint8_t lcd_id[12];				//存放LCD ID字符串
	delay_init(168);  				//初始化延时函数
 	LCD_Init();								//LCD初始化 
	POINT_COLOR=BLUE;	 
	sprintf((char*)lcd_id,"ID:%04X",lcddev.id);					//将LCD ID打印到lcd_id数组。		
  	LCD_ShowString(30,40,210,24,24,"STM32F407IGT6");
	LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
	LCD_ShowString(170,420,200,24,24,"FS_TFTLCD_V1.0");
 	LCD_ShowString(30,110,200,16,16,lcd_id);					//显示LCD ID	      					  
	HAL_Delay(2000);
 	LCD_Clear(WHITE);								//清屏    
	LCD_DrawPicture(0,300,480,500,(uint8_t *)gImage_hqyj);
  	while (1)
  	{
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
