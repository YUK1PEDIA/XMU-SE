/*
 * @Author: your name
 * @Date: 2021-07-12 09:41:04
 * @LastEditTime: 2021-07-12 10:08:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Can.c
 */
#include "BSP_Can.h"
#include "can.h"

static CAN_TxHeaderTypeDef TxMessage; //CAN发送的消息的消息头
static CAN_RxHeaderTypeDef RxMessage; //CAN接收的消息的消息头
uint8_t g_CAN_Recv_Flag = 0;

/* CAN过滤器配置函数 */
static void CANFilter_Config(void)
{
    CAN_FilterTypeDef sFilterConfig;

    sFilterConfig.FilterBank = 0;                      //CAN过滤器编号，范围0-27
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;  //CAN过滤器模式，掩码模式或列表模式
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; //CAN过滤器尺度，16位或32位
    sFilterConfig.FilterIdHigh = 0x0000;               //32位下，存储要过滤ID的高16位
    sFilterConfig.FilterIdLow = 0x0000;                //32位下，存储要过滤ID的低16位
    sFilterConfig.FilterMaskIdHigh = 0x0000;           //掩码模式下，存储的是掩码
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = 0;  //报文通过过滤器的匹配后，存储到哪个FIFO
    sFilterConfig.FilterActivation = ENABLE; //激活过滤器
    sFilterConfig.SlaveStartFilterBank = 0;

    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
    {
        CONSOLE_ERROR("CAN Filter Config Fail!");
        Error_Handler();
    }
    CONSOLE_INFO("CAN Filter Config Success!");
}
/* CAN中断函数 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t data[8];
    HAL_StatusTypeDef status;
    CONSOLE_INFO("-->HAL_CAN_RxFifo0MsgPendingCallback()");
    if (hcan == &hcan1)
    {
        status = HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxMessage, data);
        if (HAL_OK == status)
        {
            CONSOLE_INFO("--->Data Receieve!");
            CONSOLE_INFO("RxMessage.StdId is %#x", RxMessage.StdId);
            CONSOLE_INFO("data[0] is 0x%02x", data[0]);
            CONSOLE_INFO("data[1] is 0x%02x", data[1]);
            CONSOLE_INFO("data[2] is 0x%02x", data[2]);
            CONSOLE_INFO("data[3] is 0x%02x", data[3]);
            g_CAN_Recv_Flag = 1;
        }
    }
}
/* CAN 发送数据测试函数 */
void CAN1_Send_Test(void)
{
    uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};

    TxMessage.IDE = CAN_ID_STD;   //设置ID类型
    TxMessage.StdId = 0x222;      //设置ID号
    TxMessage.RTR = CAN_RTR_DATA; //设置传送数据帧
    TxMessage.DLC = 4;            //设置数据长度

    if (HAL_CAN_AddTxMessage(&hcan1, &TxMessage, data, (uint32_t *)CAN_TX_MAILBOX0) != HAL_OK)
    {
        CONSOLE_ERROR("CAN send test data fail!");
        Error_Handler();
    }
}
void CAN1_Function_Init(void)
{
    /* 1. CAN Filter Config */
    CANFilter_Config();

    /* 2. CAN Start */
    if (HAL_CAN_Start(&hcan1) != HAL_OK)
    {
        CONSOLE_ERROR("CAN Start Fail");
        Error_Handler();
    }

    /* 3. Enable CAN RX Interrupt */
    if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        CONSOLE_ERROR("CAN_IT_RX_FIFO0_MSG_PENDING Enable Fail");
        Error_Handler();
    }
}
/**
 * @description: CAN_Test
 * @param {uint32_t Timeout(ms)}
 * @return {0: 测试成功   其他: 失败}
 */
HAL_StatusTypeDef CAN_Test(uint32_t Timeout)
{
	uint32_t tickstart = HAL_GetTick();
	
	CAN1_Function_Init();
	/* 发送测试数据 */
	CAN1_Send_Test();
	while (g_CAN_Recv_Flag != 1){
		if (Timeout != HAL_MAX_DELAY){
			if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout)){
				return HAL_TIMEOUT;
			}
		}
	}
	return HAL_OK;
}


