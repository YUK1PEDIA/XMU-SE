/*
 * @Author: your name
 * @Date: 2021-07-08 09:18:14
 * @LastEditTime: 2021-07-21 13:33:10
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\APP_StartShow.c
 */
#include "APP_StartShow.h"
#include "BSP_LCD.h"
#include "BSP_Can.h"
#include "BSP_LCDTouch.h"
#include "BSP_W25x16.h"
#include "BSP_24c02.h"
#include "BSP_WM8978.h"
#include "BSP_RS485.h"
#include "BSP_CAN.h"

#include "tim.h"
#include "can.h"
#include "usart.h"
#include "sdio.h"
#include "piclib.h"

#include "bmp.h"

#include "OS_Malloc.h"
#include "OS_LWIP_Ping.h"
#include "ff.h"
#include <lwip/sockets.h>
#include "cmsis_os.h"
#include "LCD_Show.h"
/******************SPI Flash �������*****************************/

__FILE_SYS_ mySDFileSystem;

///* �������Ӳ���ĳ�ʱʱ�� */
#define DEVICE_TIMEOUT (2000)

///**
// * @description: �������ں�����ping�ⲿ�豸
// * @param {const char} *IPAddr
// * @param {uint16_t} port
// * @param {uint32_t} Timeout
// * @return {*}
// */
// HAL_StatusTypeDef ETH_Ping_Test(const char *IPAddr, uint16_t port, uint32_t Timeout)
//{
//  uint32_t tickstart = HAL_GetTick();
//  icmp_pcb_init();

//  /* ��д�ⲿ�豸��·������IP��ַ */
//  ping_send(192, 168, 3, 1);
//  while (pingEchoReply != 1)
//  {
//    if (Timeout != HAL_MAX_DELAY)
//    {
//      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
//      {
//        return HAL_TIMEOUT;
//      }
//    }
//  }
//  return HAL_OK;
//}

typedef enum
{
  COOY_OFFSET = 30,       // ������ƫ����
  SPI_FLASH_COOYNUM = 50, // ��ʼ��ʾ���� ��ʾSPI W25x16����
  I2C_EEPROM_COOYNUM = SPI_FLASH_COOYNUM + COOY_OFFSET,
  SDIO_SDCARD_COOYNUM = I2C_EEPROM_COOYNUM + COOY_OFFSET,
  WM8978_COOYNUM = SDIO_SDCARD_COOYNUM + COOY_OFFSET,
  RS485_COOYNUM = WM8978_COOYNUM + COOY_OFFSET,
  CAN_COOYNUM = RS485_COOYNUM + COOY_OFFSET,
  ETH_COOYNUM = CAN_COOYNUM + COOY_OFFSET,
} __Display_Coordinate_Y; // ��ʾ����ʾ���� Y�� ������

/**
 * @description: ��ʼ�����Ӳ��
 * @param {*}
 * @return {*}
 */
void Board_Init(void)
{
  LCD_Init();          // LCD��ʾ����ʼ��
  TP_Init();           // LCD������������ʼ��
  OS_mem_init(SRAMIN); // ��ʼ���ڲ��ڴ��
  // OS_mem_init(SRAMCCM);
//  piclib_init(); // ����ͼƬ�ĳ�ʼ��
//	LCD_ShowString(50, 20, 700, 24, 24, (uint8_t *)"System is starting, please wait......");
//	HAL_Delay(2000);
	LCD_DrawPicture(0,0,800,480,(uint8_t *)gImage_hqyj);	
}
/**
 * @description: ����ϵͳ֮ǰ���Բ���
 * @param {*}
 * @return {*}
 */
void App_StartShow(void)
{
//  uint8_t result = 0;

	if(KEY3 == 0)
	{
		LCD_ShowString(50, 20, 700, 24, 24, (uint8_t *)"                                      ");
		LCD_ShowString(50, 20, 700, 24, 24, (uint8_t *)"Backboard hardware test started.......");
		/* W25X16 SPI-FLASH  */
	 if (spi_flash_test())
	 {
	   CONSOLE_ERROR("W25X16 initialize failed!");
	   LCD_ShowString(50, SPI_FLASH_COOYNUM, 360, 24, 24, (uint8_t *)"SPI FLASH TEST     ERROR ");
	 }
	 else
	 {
	   CONSOLE_INFO("W25X16 initialize success!");
	   LCD_ShowString(50, SPI_FLASH_COOYNUM, 360, 24, 24, (uint8_t *)"SPI FLASH TEST     OK ");
	 }

	 /* 24c02 I2C-EEPROM  */
	 if (iic_24c02_test())
	 {
	   CONSOLE_ERROR("EEPROM initialize failed!");
	   LCD_ShowString(50, I2C_EEPROM_COOYNUM, 360, 24, 24, (uint8_t *)"I2C EEPROM TEST    ERROR ");
	 }
	 else
	 {
	   CONSOLE_INFO("EEPROM initialize success!");
	   LCD_ShowString(50, I2C_EEPROM_COOYNUM, 360, 24, 24, (uint8_t *)"I2C EEPROM TEST    OK ");
	 }

	 /* SD�����Գ���  */
	 if (SDIO_SD_Test())
	 {
	   CONSOLE_ERROR("SD card initialize failed!");
	   LCD_ShowString(50, SDIO_SDCARD_COOYNUM, 360, 24, 24, (uint8_t *)"SDIO_SDCARD TEST   ERROR ");
	 }
	 else
	 {
	   CONSOLE_INFO("SD card initialize success!");
	   LCD_ShowString(50, SDIO_SDCARD_COOYNUM, 360, 24, 24, (uint8_t *)"SDIO_SDCARD TEST   OK ");
	 }

	  /* �����ƵоƬ  */
	  if (BSP_WM8978_Init())
	  {
		CONSOLE_ERROR("wm8978 failed!");
		LCD_ShowString(50, WM8978_COOYNUM, 360, 24, 24, (uint8_t *)"WM8978 TEST        ERROR ");
	  }
	  else
	  {
		CONSOLE_INFO("wm8978 success!");
		LCD_ShowString(50, WM8978_COOYNUM, 360, 24, 24, (uint8_t *)"WM8978 TEST        OK ");
	  }

	 /* RS485����  */
	 if (RS485_Test(DEVICE_TIMEOUT) == HAL_TIMEOUT)
	 {
	   CONSOLE_ERROR("RS485_Test failed!");
	   LCD_ShowString(50, RS485_COOYNUM, 360, 24, 24, (uint8_t *)"RS485 TEST         ERROR ");
	 }
	 else
	 {
	   CONSOLE_INFO("RS485_Test success!");
	   LCD_ShowString(50, RS485_COOYNUM, 360, 24, 24, (uint8_t *)"RS485 TEST         OK ");
	 }

	 /* CAN����  */
	 if (CAN_Test(DEVICE_TIMEOUT) == HAL_TIMEOUT)
	 {
	   CONSOLE_ERROR("CAN_Test failed!");
	   LCD_ShowString(50, CAN_COOYNUM, 360, 24, 24, (uint8_t *)"CAN TEST           ERROR ");
	 }
	 else
	 {
	   CONSOLE_INFO("CAN_Test success!");
	   LCD_ShowString(50, CAN_COOYNUM, 360, 24, 24, (uint8_t *)"CAN TEST           OK ");
	 }

//	 /* ���ڵ�ping���� */
//	 if (ETH_Ping_Test(UDP_SERVER_IP, UDP_PORT, 5000) == HAL_TIMEOUT)
//	 {
//	   CONSOLE_ERROR("ETH_Ping_Test failed!");
//	   LCD_ShowString(50, ETH_COOYNUM, 360, 24, 24, (uint8_t *)"ETH TEST           ERROR ");
//	 }
//	 else
//	 {
//	   CONSOLE_INFO("ETH_Ping_Test success!");
//	   LCD_ShowString(50, ETH_COOYNUM, 360, 24, 24, (uint8_t *)"ETH TEST           OK ");
//	 }
 }
	while(!KEY3){
	
	}
//  /* ��ʼ��SD�� */
//  if (HAL_SD_Init(&hsd) != HAL_OK) // 1
//  {
//    CONSOLE_ERROR("HAL_SD_Init failed!");
//  }
//  else
//    CONSOLE_INFO("HAL_SD_Init success!");

//  HAL_Delay(2000); // ��ʱ�����ӣ���ֹһ������

//  LCD_Clear(BLACK); // �Լ����ɺ�����
//  result = f_mount(&mySDFileSystem.DiskFatFs, "0:", 1);
//  if(result != FR_OK)
//  {
//    CONSOLE_ERROR("f_mount->failed");
//    Printf_File_Error_Msg(result);
//  }
  
//  Load_Background_Bmp(); // ���ر���ͼƬ

  LCD_ShowString(53, 225, 90, 30, 24, (uint8_t *)"  OFF ");  // �������
  LCD_ShowString(155, 225, 90, 30, 24, (uint8_t *)"  OFF "); // ֱ�����
  LCD_ShowString(255, 225, 90, 30, 24, (uint8_t *)"  OFF "); // ���
  LCD_ShowString(357, 225, 90, 30, 24, (uint8_t *)"  OFF "); // �̵���
  LCD_ShowString(462, 225, 90, 30, 24, (uint8_t *)"  OFF "); // ������
  LCD_ShowString(560, 225, 90, 30, 24, (uint8_t *)"      "); // ��翪�ش�����
  LCD_ShowString(664, 225, 90, 30, 24, (uint8_t *)"      "); // ����ң����

  LCD_ShowString(53, 419, 90, 30, 24, (uint8_t *)"      ");  // �ƾ�
  LCD_ShowString(155, 419, 90, 30, 24, (uint8_t *)"      "); // ����
  LCD_ShowString(255, 419, 90, 30, 24, (uint8_t *)"      "); // ����
  LCD_ShowString(357, 419, 90, 30, 24, (uint8_t *)"      "); // ����
  LCD_ShowString(462, 419, 90, 30, 24, (uint8_t *)"      "); // �¶�
  LCD_ShowString(560, 419, 90, 30, 24, (uint8_t *)"  OFF "); // ����
  LCD_ShowString(664, 419, 90, 30, 24, (uint8_t *)"  OFF "); // LED
  /* ��������ж� */
  HAL_IT_Start();

  /* �ر�����ж� */
  HAL_UART_MspDeInit(&huart3); // �رմ���3(485)
  HAL_CAN_MspDeInit(&hcan1);   // �ر�CAN
}
/**
 * @description: �ر�����ж�
 * @param {*}
 * @return {*}
 */
void HAL_IT_Stop(void)
{
  HAL_TIM_PWM_Stop_IT(&htim12, TIM_CHANNEL_1); // �ر� ��� PWM��ʱ��
  HAL_TIM_Base_Stop_IT(&htim4);                // �ر� ���� ��ʱ���ж�
  HAL_TIM_Base_Stop_IT(&htim5);                // �ر� ������� ��ʱ���ж�
  HAL_TIM_Base_Stop_IT(&htim9);                // �ر� ������ ��ʱ���ж�
}
/**
 * @description: ��������ж�
 * @param {*}
 * @return {*}
 */
void HAL_IT_Start(void)
{
  HAL_TIM_PWM_Start_IT(&htim12, TIM_CHANNEL_1); // ���� ��� PWM��ʱ��
  HAL_TIM_Base_Start_IT(&htim4);                // ���� ���� ��ʱ���ж�
}
/**
 * @description: ���ر���ͼƬ
 * @param {*}
 * @return {*}
 */
//void Load_Background_Bmp(void)
//{

//  uint8_t result;

//  if ((result = f_opendir(&mySDFileSystem.picdir, "0:/Picture")) != FR_OK) //��ͼƬ�ļ���
//  {
//    CONSOLE_ERROR("f_opendir() -> FAILE");
//    Printf_File_Error_Msg(result);
//  }
//  else
//  {
//    CONSOLE_INFO("f_opendir() -> OK");
////    ai_load_picfile("0:/Picture/background.bmp", 0, 0, g_lcddev.width, g_lcddev.height, 1); //��ʾͼƬ
//    // 5.�ر��ļ���
//    f_closedir(&mySDFileSystem.picdir);
//  }
//}
///**
// * @description: �������ֲ������ı���ͼƬ
// * @param {*}
// * @return {*}
// */
//void Load_MusicAudio_Bmp(void)
//{
//  /* ����SD�� ѡ����������ģʽ1 */
//  uint8_t result;

//  if ((result = f_opendir(&mySDFileSystem.picdir, "0:/Picture")) != FR_OK) //��ͼƬ�ļ���
//  {
//    CONSOLE_ERROR("f_opendir() -> FAILE");
//    Printf_File_Error_Msg(result);
//  }
//  else
//  {
//    CONSOLE_INFO("f_opendir() -> OK");

//    ai_load_picfile("0:/Picture/music_background.bmp", 0, 0, g_lcddev.width, g_lcddev.height, 1); //��ʾͼƬ

//    // 5.�ر��ļ�
//    f_closedir(&mySDFileSystem.picdir);
//  }
//}
///**
// * @description: �������ֲ��Ű�ť
// * @param {*}
// * @return {*}
// */
//void Load_Music_Start_Bmp(void)
//{
//  uint8_t result = 0;

//  if ((result = f_opendir(&mySDFileSystem.picdir, "0:/Picture")) != FR_OK) //��ͼƬ�ļ���
//  {
//    CONSOLE_ERROR("f_opendir() -> FAILE");
//    Printf_File_Error_Msg(result);
//  }
//  else
//  {
//    CONSOLE_INFO("f_opendir() -> OK");

//    ai_load_picfile("0:/Picture/music_start.bmp", 322, 164, 159, 158, 1); //��ʾͼƬ

//    // 5.�ر��ļ�
//    f_closedir(&mySDFileSystem.picdir);
//  }
//}
///**
// * @description: ��������ֹͣ��ť
// * @param {*}
// * @return {*}
// */
//void Load_Music_Stop_Bmp(void)
//{
//  uint8_t result = 0;

//  if ((result = f_opendir(&mySDFileSystem.picdir, "0:/Picture")) != FR_OK) //��ͼƬ�ļ���
//  {
//    CONSOLE_ERROR("f_opendir() -> FAILE");
//    Printf_File_Error_Msg(result);
//  }
//  else
//  {
//    CONSOLE_INFO("f_opendir() -> OK");

//    ai_load_picfile("0:/Picture/music_stop.bmp", 322, 164, 159, 158, 1); //��ʾͼƬ

//    // 5.�ر��ļ�
//    f_closedir(&mySDFileSystem.picdir);
//  }
//}



