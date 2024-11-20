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
/******************SPI Flash 测试相关*****************************/

__FILE_SYS_ mySDFileSystem;

///* 定义测试硬件的超时时间 */
#define DEVICE_TIMEOUT (2000)

///**
// * @description: 测试网口函数，ping外部设备
// * @param {const char} *IPAddr
// * @param {uint16_t} port
// * @param {uint32_t} Timeout
// * @return {*}
// */
// HAL_StatusTypeDef ETH_Ping_Test(const char *IPAddr, uint16_t port, uint32_t Timeout)
//{
//  uint32_t tickstart = HAL_GetTick();
//  icmp_pcb_init();

//  /* 填写外部设备或路由器的IP地址 */
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
  COOY_OFFSET = 30,       // 纵坐标偏移量
  SPI_FLASH_COOYNUM = 50, // 初始显示坐标 显示SPI W25x16测试
  I2C_EEPROM_COOYNUM = SPI_FLASH_COOYNUM + COOY_OFFSET,
  SDIO_SDCARD_COOYNUM = I2C_EEPROM_COOYNUM + COOY_OFFSET,
  WM8978_COOYNUM = SDIO_SDCARD_COOYNUM + COOY_OFFSET,
  RS485_COOYNUM = WM8978_COOYNUM + COOY_OFFSET,
  CAN_COOYNUM = RS485_COOYNUM + COOY_OFFSET,
  ETH_COOYNUM = CAN_COOYNUM + COOY_OFFSET,
} __Display_Coordinate_Y; // 显示屏显示坐标 Y轴 横坐标

/**
 * @description: 初始化相关硬件
 * @param {*}
 * @return {*}
 */
void Board_Init(void)
{
  LCD_Init();          // LCD显示屏初始化
  TP_Init();           // LCD触摸传感器初始化
  OS_mem_init(SRAMIN); // 初始化内部内存池
  // OS_mem_init(SRAMCCM);
//  piclib_init(); // 加载图片的初始化
//	LCD_ShowString(50, 20, 700, 24, 24, (uint8_t *)"System is starting, please wait......");
//	HAL_Delay(2000);
	LCD_DrawPicture(0,0,800,480,(uint8_t *)gImage_hqyj);	
}
/**
 * @description: 进入系统之前的自测试
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

	 /* SD卡测试程序  */
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

	  /* 检查音频芯片  */
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

	 /* RS485测试  */
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

	 /* CAN测试  */
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

//	 /* 网口的ping测试 */
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
//  /* 初始化SD卡 */
//  if (HAL_SD_Init(&hsd) != HAL_OK) // 1
//  {
//    CONSOLE_ERROR("HAL_SD_Init failed!");
//  }
//  else
//    CONSOLE_INFO("HAL_SD_Init success!");

//  HAL_Delay(2000); // 延时两秒钟，防止一闪而过

//  LCD_Clear(BLACK); // 自检查完成后，清屏
//  result = f_mount(&mySDFileSystem.DiskFatFs, "0:", 1);
//  if(result != FR_OK)
//  {
//    CONSOLE_ERROR("f_mount->failed");
//    Printf_File_Error_Msg(result);
//  }
  
//  Load_Background_Bmp(); // 加载背景图片

  LCD_ShowString(53, 225, 90, 30, 24, (uint8_t *)"  OFF ");  // 步进电机
  LCD_ShowString(155, 225, 90, 30, 24, (uint8_t *)"  OFF "); // 直流电机
  LCD_ShowString(255, 225, 90, 30, 24, (uint8_t *)"  OFF "); // 舵机
  LCD_ShowString(357, 225, 90, 30, 24, (uint8_t *)"  OFF "); // 继电器
  LCD_ShowString(462, 225, 90, 30, 24, (uint8_t *)"  OFF "); // 蜂鸣器
  LCD_ShowString(560, 225, 90, 30, 24, (uint8_t *)"      "); // 光电开关传感器
  LCD_ShowString(664, 225, 90, 30, 24, (uint8_t *)"      "); // 红外遥控器

  LCD_ShowString(53, 419, 90, 30, 24, (uint8_t *)"      ");  // 酒精
  LCD_ShowString(155, 419, 90, 30, 24, (uint8_t *)"      "); // 光敏
  LCD_ShowString(255, 419, 90, 30, 24, (uint8_t *)"      "); // 火焰
  LCD_ShowString(357, 419, 90, 30, 24, (uint8_t *)"      "); // 气体
  LCD_ShowString(462, 419, 90, 30, 24, (uint8_t *)"      "); // 温度
  LCD_ShowString(560, 419, 90, 30, 24, (uint8_t *)"  OFF "); // 按键
  LCD_ShowString(664, 419, 90, 30, 24, (uint8_t *)"  OFF "); // LED
  /* 开启相关中断 */
  HAL_IT_Start();

  /* 关闭相关中断 */
  HAL_UART_MspDeInit(&huart3); // 关闭串口3(485)
  HAL_CAN_MspDeInit(&hcan1);   // 关闭CAN
}
/**
 * @description: 关闭相关中断
 * @param {*}
 * @return {*}
 */
void HAL_IT_Stop(void)
{
  HAL_TIM_PWM_Stop_IT(&htim12, TIM_CHANNEL_1); // 关闭 舵机 PWM定时器
  HAL_TIM_Base_Stop_IT(&htim4);                // 关闭 红外 定时器中断
  HAL_TIM_Base_Stop_IT(&htim5);                // 关闭 步进电机 定时器中断
  HAL_TIM_Base_Stop_IT(&htim9);                // 关闭 蜂鸣器 定时器中断
}
/**
 * @description: 开启相关中断
 * @param {*}
 * @return {*}
 */
void HAL_IT_Start(void)
{
  HAL_TIM_PWM_Start_IT(&htim12, TIM_CHANNEL_1); // 开启 舵机 PWM定时器
  HAL_TIM_Base_Start_IT(&htim4);                // 开启 红外 定时器中断
}
/**
 * @description: 加载背景图片
 * @param {*}
 * @return {*}
 */
//void Load_Background_Bmp(void)
//{

//  uint8_t result;

//  if ((result = f_opendir(&mySDFileSystem.picdir, "0:/Picture")) != FR_OK) //打开图片文件夹
//  {
//    CONSOLE_ERROR("f_opendir() -> FAILE");
//    Printf_File_Error_Msg(result);
//  }
//  else
//  {
//    CONSOLE_INFO("f_opendir() -> OK");
////    ai_load_picfile("0:/Picture/background.bmp", 0, 0, g_lcddev.width, g_lcddev.height, 1); //显示图片
//    // 5.关闭文件夹
//    f_closedir(&mySDFileSystem.picdir);
//  }
//}
///**
// * @description: 加载音乐播放器的背景图片
// * @param {*}
// * @return {*}
// */
//void Load_MusicAudio_Bmp(void)
//{
//  /* 挂载SD卡 选择立即挂载模式1 */
//  uint8_t result;

//  if ((result = f_opendir(&mySDFileSystem.picdir, "0:/Picture")) != FR_OK) //打开图片文件夹
//  {
//    CONSOLE_ERROR("f_opendir() -> FAILE");
//    Printf_File_Error_Msg(result);
//  }
//  else
//  {
//    CONSOLE_INFO("f_opendir() -> OK");

//    ai_load_picfile("0:/Picture/music_background.bmp", 0, 0, g_lcddev.width, g_lcddev.height, 1); //显示图片

//    // 5.关闭文件
//    f_closedir(&mySDFileSystem.picdir);
//  }
//}
///**
// * @description: 加载音乐播放按钮
// * @param {*}
// * @return {*}
// */
//void Load_Music_Start_Bmp(void)
//{
//  uint8_t result = 0;

//  if ((result = f_opendir(&mySDFileSystem.picdir, "0:/Picture")) != FR_OK) //打开图片文件夹
//  {
//    CONSOLE_ERROR("f_opendir() -> FAILE");
//    Printf_File_Error_Msg(result);
//  }
//  else
//  {
//    CONSOLE_INFO("f_opendir() -> OK");

//    ai_load_picfile("0:/Picture/music_start.bmp", 322, 164, 159, 158, 1); //显示图片

//    // 5.关闭文件
//    f_closedir(&mySDFileSystem.picdir);
//  }
//}
///**
// * @description: 加载音乐停止按钮
// * @param {*}
// * @return {*}
// */
//void Load_Music_Stop_Bmp(void)
//{
//  uint8_t result = 0;

//  if ((result = f_opendir(&mySDFileSystem.picdir, "0:/Picture")) != FR_OK) //打开图片文件夹
//  {
//    CONSOLE_ERROR("f_opendir() -> FAILE");
//    Printf_File_Error_Msg(result);
//  }
//  else
//  {
//    CONSOLE_INFO("f_opendir() -> OK");

//    ai_load_picfile("0:/Picture/music_stop.bmp", 322, 164, 159, 158, 1); //显示图片

//    // 5.关闭文件
//    f_closedir(&mySDFileSystem.picdir);
//  }
//}



