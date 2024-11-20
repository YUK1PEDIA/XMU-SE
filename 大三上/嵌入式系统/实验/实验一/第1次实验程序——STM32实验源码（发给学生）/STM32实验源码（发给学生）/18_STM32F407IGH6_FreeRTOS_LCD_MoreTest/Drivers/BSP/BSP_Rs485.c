/*
 * @Author: your name
 * @Date: 2021-07-12 09:41:27
 * @LastEditTime: 2021-07-12 10:08:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Rs485.c
 */
#include "BSP_RS485.h"
#include "usart.h"
#include <string.h>


#define RS485_Port huart3
#define RS485_BUFF_SIZE 2
uint8_t RS485_BUFF[RS485_BUFF_SIZE] = {0};

uint8_t g_RS485_Recv_Flag = 0;

void DR_RS485_Init(void)
{

	__HAL_DMA_DISABLE(&hdma_usart3_rx); // 关闭DMA
	HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

	/* 开启DMA中断接收 */
	HAL_UART_Receive_DMA(&RS485_Port, RS485_BUFF, RS485_BUFF_SIZE);
}

void DR_RS485_SendData(uint8_t *data, uint16_t size)
{
	/* 发送数据 */
	HAL_UART_Transmit(&RS485_Port, data, size, 1000);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART3)
	{
		/* 如果接收到GET请求，返回OK */
		if (RS485_BUFF[0] == 'O' && RS485_BUFF[1] == 'K')
		{
			g_RS485_Recv_Flag = 1;
			CONSOLE_INFO("RS485 success Recv Data ：%s", RS485_BUFF);
		}
		else
			CONSOLE_ERROR("RS485 faile Recv Data");

		/* 开启DMA中断接收 */
		memset(RS485_BUFF, 0, RS485_BUFF_SIZE);
		HAL_UART_Receive_DMA(&RS485_Port, RS485_BUFF, RS485_BUFF_SIZE);
	}
}

/**
 * @description: RS485_Test
 * @param {uint32_t Timeout(ms)}
 * @return {0: 测试成功   其他: 失败}
 */
HAL_StatusTypeDef RS485_Test(uint32_t Timeout)
{
	uint32_t tickstart = HAL_GetTick();

	DR_RS485_Init();
	/* 发送测试数据 */
	DR_RS485_SendData("GET", 3);
	while (g_RS485_Recv_Flag != 1){
		if (Timeout != HAL_MAX_DELAY){
			if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout)){
				return HAL_TIMEOUT;
			}
		}
	}
	return HAL_OK;
}
