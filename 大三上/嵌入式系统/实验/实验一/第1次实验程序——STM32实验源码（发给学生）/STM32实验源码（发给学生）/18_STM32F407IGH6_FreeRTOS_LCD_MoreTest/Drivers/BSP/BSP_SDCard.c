/*
 * @Author: your name
 * @Date: 2021-07-08 09:23:40
 * @LastEditTime: 2021-07-11 17:41:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_SDCard.c
 */
#include "BSP_SDCard.h"

//SD_ReadDisk/SD_WriteDisk函数专用buf,当这两个函数的数据缓存区地址不是4字节对齐的时候,
//需要用到该数组,确保数据缓存区地址是4字节对齐的.
__align(4) uint8_t SDIO_DATA_BUFFER[512];
#define  SD_TIMEOUT 			((uint32_t)100000000)  	//超时时间


SD_HandleTypeDef SDCARD_Handler;   //SD卡句柄

/**
 * @description: SD卡的初始化
 * @param {*}
 * @return {*} 0 初始化成功；other 初始化失败
 */
uint8_t SD_Init(void)
{
    HAL_SD_CardInfoTypeDef SDCardInfo; //SD卡信息结构体
    uint8_t SD_Error;

    //初始化时的时钟不能大于400KHZ
    SDCARD_Handler.Instance = SDIO;
    SDCARD_Handler.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;                       //上升沿
    SDCARD_Handler.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;                  //不使用bypass模式，直接用HCLK进行分频得到SDIO_CK
    SDCARD_Handler.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;           //空闲时不关闭时钟电源
    SDCARD_Handler.Init.BusWide = SDIO_BUS_WIDE_1B;                               //1位数据线
    SDCARD_Handler.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE; //关闭硬件流控
    SDCARD_Handler.Init.ClockDiv = 0;                                             //SD传输时钟频率最大25MHZ

    SD_Error = HAL_SD_Init(&SDCARD_Handler);
    if (SD_Error != HAL_OK)
        return 1;

    //获取SD卡信息
    HAL_SD_GetCardInfo(&SDCARD_Handler, &SDCardInfo);

    SD_Error = HAL_SD_ConfigWideBusOperation(&SDCARD_Handler, SDIO_BUS_WIDE_4B); //使能宽总线模式
    if (SD_Error != HAL_OK)
        return 2;
    return 0;
}

/**
 * @description: 得到卡的信息
 * @param {HAL_SD_CardInfoTypeDef} *cardinfo 卡信息存储区
 * @return {*} 错误状态
 */
uint8_t SD_GetCardInfo(HAL_SD_CardInfoTypeDef *cardinfo)
{
    uint8_t sta;
    sta=HAL_SD_GetCardInfo(&SDCARD_Handler,cardinfo);
    return sta;
}
	 
/**
 * @description: 判断SD卡是否可以传输(读写)数据
 * @param {*}
 * @return {*} SD_TRANSFER_OK 传输完成，可以继续下一次传输; SD_TRANSFER_BUSY SD卡正忙，不可以进行下一次传输
 */
uint8_t SD_GetCardState(void)
{
  return((HAL_SD_GetCardState(&SDCARD_Handler)==HAL_SD_CARD_TRANSFER )?SD_TRANSFER_OK:SD_TRANSFER_BUSY);
}

/**
 * @description: 读SD卡 
 * @param {uint8_t*} buf 读数据缓存区
 * @param {uint32_t} sector 扇区地址
 * @param {uint32_t} cnt 扇区个数
 * @return {*} 0,正常;其他,错误代码;
 */
uint8_t SD_ReadDisk(uint8_t* buf,uint32_t sector,uint32_t cnt)
{
  long long lsector=sector;
	if(HAL_SD_ReadBlocks(&SDCARD_Handler, (uint8_t*)buf,lsector,cnt,SD_TIMEOUT) != 0)
	{
		return HAL_ERROR;
	}else{
		return HAL_OK;
	}
}  

/**
 * @description: 写SD卡 
 * @param {uint8_t*} buf 读数据缓存区
 * @param {uint32_t} sector 扇区地址
 * @param {uint32_t} cnt 扇区个数
 * @return {*} 0,正常;其他,错误代码;
 */
uint8_t SD_WriteDisk(uint8_t *buf,uint32_t sector,uint32_t cnt)
{   
  long long lsector=sector;
	if(HAL_SD_WriteBlocks(&SDCARD_Handler, (uint8_t*)buf,lsector,cnt,SD_TIMEOUT) != 0)
	{
		return HAL_ERROR;
	}else{
		return HAL_OK;
	}
}




