/*
 * @Author: your name
 * @Date: 2021-07-08 09:23:40
 * @LastEditTime: 2021-07-11 17:41:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_SDCard.c
 */
#include "BSP_SDCard.h"

//SD_ReadDisk/SD_WriteDisk����ר��buf,�����������������ݻ�������ַ����4�ֽڶ����ʱ��,
//��Ҫ�õ�������,ȷ�����ݻ�������ַ��4�ֽڶ����.
__align(4) uint8_t SDIO_DATA_BUFFER[512];
#define  SD_TIMEOUT 			((uint32_t)100000000)  	//��ʱʱ��


SD_HandleTypeDef SDCARD_Handler;   //SD�����

/**
 * @description: SD���ĳ�ʼ��
 * @param {*}
 * @return {*} 0 ��ʼ���ɹ���other ��ʼ��ʧ��
 */
uint8_t SD_Init(void)
{
    HAL_SD_CardInfoTypeDef SDCardInfo; //SD����Ϣ�ṹ��
    uint8_t SD_Error;

    //��ʼ��ʱ��ʱ�Ӳ��ܴ���400KHZ
    SDCARD_Handler.Instance = SDIO;
    SDCARD_Handler.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;                       //������
    SDCARD_Handler.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;                  //��ʹ��bypassģʽ��ֱ����HCLK���з�Ƶ�õ�SDIO_CK
    SDCARD_Handler.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;           //����ʱ���ر�ʱ�ӵ�Դ
    SDCARD_Handler.Init.BusWide = SDIO_BUS_WIDE_1B;                               //1λ������
    SDCARD_Handler.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE; //�ر�Ӳ������
    SDCARD_Handler.Init.ClockDiv = 0;                                             //SD����ʱ��Ƶ�����25MHZ

    SD_Error = HAL_SD_Init(&SDCARD_Handler);
    if (SD_Error != HAL_OK)
        return 1;

    //��ȡSD����Ϣ
    HAL_SD_GetCardInfo(&SDCARD_Handler, &SDCardInfo);

    SD_Error = HAL_SD_ConfigWideBusOperation(&SDCARD_Handler, SDIO_BUS_WIDE_4B); //ʹ�ܿ�����ģʽ
    if (SD_Error != HAL_OK)
        return 2;
    return 0;
}

/**
 * @description: �õ�������Ϣ
 * @param {HAL_SD_CardInfoTypeDef} *cardinfo ����Ϣ�洢��
 * @return {*} ����״̬
 */
uint8_t SD_GetCardInfo(HAL_SD_CardInfoTypeDef *cardinfo)
{
    uint8_t sta;
    sta=HAL_SD_GetCardInfo(&SDCARD_Handler,cardinfo);
    return sta;
}
	 
/**
 * @description: �ж�SD���Ƿ���Դ���(��д)����
 * @param {*}
 * @return {*} SD_TRANSFER_OK ������ɣ����Լ�����һ�δ���; SD_TRANSFER_BUSY SD����æ�������Խ�����һ�δ���
 */
uint8_t SD_GetCardState(void)
{
  return((HAL_SD_GetCardState(&SDCARD_Handler)==HAL_SD_CARD_TRANSFER )?SD_TRANSFER_OK:SD_TRANSFER_BUSY);
}

/**
 * @description: ��SD�� 
 * @param {uint8_t*} buf �����ݻ�����
 * @param {uint32_t} sector ������ַ
 * @param {uint32_t} cnt ��������
 * @return {*} 0,����;����,�������;
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
 * @description: дSD�� 
 * @param {uint8_t*} buf �����ݻ�����
 * @param {uint32_t} sector ������ַ
 * @param {uint32_t} cnt ��������
 * @return {*} 0,����;����,�������;
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




