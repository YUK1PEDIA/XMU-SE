#include "main.h"
#include "gpio.h"

void SystemClock_Config(void);
void Turn_On_LED(uint8_t LED_NUM);

int main(void)
{	
  uint8_t count=0;

  HAL_Init();	//该函数在\1_Led\Drivers\STM32F4xx_HAL_Driver\Src\stm32f4xx_hal.c文件中

  SystemClock_Config();	//系统时钟配置	

  MX_GPIO_Init();	//该函数在gpio.c文件中

  while (1)
  {
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET); 		//LED1 灭                            该函数在\1_Led\Drivers\STM32F4xx_HAL_Driver\Src\stm32f4xx_hal_gpio.c文件中
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);		//LED2 灭
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);		//LED3 灭
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_15,GPIO_PIN_SET);		//LED4 灭

	Turn_On_LED(count%4);	//点亮一个LED灯		
	count++;
	HAL_Delay(500);		//延时500ms
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

void Turn_On_LED(uint8_t LED_NUM)
{
	switch(LED_NUM)
	{
	        	case 3:
					HAL_GPIO_WritePin(GPIOH,GPIO_PIN_15,GPIO_PIN_RESET);	//LED4 亮
          					break;
        		case 2:
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);	//LED3 亮
          					break;
        		case 1:
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);		//LED2 亮 
          					break;
        		case 0:
					HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_RESET);	//LED1 亮
          					break;          
        		default:
          					break;
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
