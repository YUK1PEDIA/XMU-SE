/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "APP_StartShow.h"
#include "APP_Operate.h"
#include "APP_Audio.h"

#include "OS_Malloc.h"
#include "OS_LWIP_Ping.h"

#include "BSP_Lcd.h"
#include "BSP_LcdTouch.h"
#include "BSP_ADCSensor.h"
#include "BSP_LM75A.h"
#include "BSP_Infrared.h"
#include "BSP_Zlg7290.h"
#include "BSP_Wm8978.h"
#include "BSP_zlg72128.h"
#include "i2s.h"
#include "i2c.h"
#include "piclib.h"
#include <lwip/sockets.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern __FILE_SYS_ mySDFileSystem;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern uint8_t ZLGflag1;

uint8_t flag = 0xff;					//不同的按键有不同的标志位值
uint8_t flag_key = 0;					//中断标志位，每次按键产生一次中断，并开始读取8个数码管的值
uint8_t Rx2_Buffer[8]={0};
uint8_t Tx1_Buffer[8]={0};
uint8_t clear[9]={0};
uint8_t Rx1_Buffer[1]={0};


uint8_t Rx1_Buffer_P[1]={0};
uint8_t Rx1_Buffer_T[1]={0};
uint8_t reset[1]={0xff};
uint8_t Transmit_Buffer[2]={0x00,0x03};
/* USER CODE END Variables */
osThreadId StatMainTaskHandle;
osThreadId GetLCDTouchTaskHandle;
osThreadId lcdDisplayTaskHandle;
osThreadId getDataTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
osThreadId AudioPlayTaskHandle;
//void audioPlayTask(void const *argument);
//void Delete_audioPlayTask(void);   
/* USER CODE END FunctionPrototypes */

void statMainTask(void const * argument);
void getLCDTouchTask(void const * argument);
void LcdDisplayTask(void const * argument);
void GetDataTask(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of SrarMainTask */
  osThreadDef(StatMainTask, statMainTask, osPriorityNormal, 0, 512);
  StatMainTaskHandle = osThreadCreate(osThread(StatMainTask), NULL);

//  /* definition and creation of GetLCDTouchTask */
//  osThreadDef(GetLCDTouchTask, getLCDTouchTask, osPriorityIdle, 0, 256);
//  GetLCDTouchTaskHandle = osThreadCreate(osThread(GetLCDTouchTask), NULL);

//  /* definition and creation of lcdDisplayTask */
//  osThreadDef(lcdDisplayTask, LcdDisplayTask, osPriorityIdle, 0, 512);
//  lcdDisplayTaskHandle = osThreadCreate(osThread(lcdDisplayTask), NULL);

//  /* definition and creation of getDataTask */
//  osThreadDef(getDataTask, GetDataTask, osPriorityIdle, 0, 256);
//  getDataTaskHandle = osThreadCreate(osThread(getDataTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_statMainTask */
/**
  * @brief  Function implementing the SrarMainTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_statMainTask */
void statMainTask(void const * argument)
{
  /* init code for LWIP */
//  MX_LWIP_Init();
  /* USER CODE BEGIN statMainTask */
  /* Infinite loop */
  App_StartShow();

  taskENTER_CRITICAL(); // 进入临界区
                        /* definition and creation of GetLCDTouchTask */
  osThreadDef(GetLCDTouchTask, getLCDTouchTask, osPriorityHigh, 0, 512);
  GetLCDTouchTaskHandle = osThreadCreate(osThread(GetLCDTouchTask), NULL);

  /* definition and creation of lcdDisplayTask */
  osThreadDef(lcdDisplayTask, LcdDisplayTask, osPriorityNormal, 0, 512);
  lcdDisplayTaskHandle = osThreadCreate(osThread(lcdDisplayTask), NULL);

  /* definition and creation of getDataTask */
  osThreadDef(getDataTask, GetDataTask, osPriorityNormal, 0, 256);
  getDataTaskHandle = osThreadCreate(osThread(getDataTask), NULL);

  /* 初始化检查完成之后，将本任务挂起 */
  vTaskSuspend(StatMainTaskHandle);

  taskEXIT_CRITICAL(); // 退出临界区
  /* USER CODE END statMainTask */
}

/* USER CODE BEGIN Header_getLCDTouchTask */
/**
* @brief Function implementing the GetLCDTouchTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_getLCDTouchTask */
void getLCDTouchTask(void const * argument)
{
  /* USER CODE BEGIN getLCDTouchTask */
  /* Infinite loop */
  for(;;)
  {
		GT9147_Scan(0); // 触摸屏检测 获取触摸位置

    vTaskDelay(10);
//    osDelay(1);
  }
  /* USER CODE END getLCDTouchTask */
}

/* USER CODE BEGIN Header_LcdDisplayTask */
/**
* @brief Function implementing the lcdDisplayTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LcdDisplayTask */
void LcdDisplayTask(void const * argument)
{
  /* USER CODE BEGIN LcdDisplayTask */
  float Alcohol = 0, Light = 0, Flame = 0, Gas = 0;
  char DisPlayBuff[10] = {0};
  uint8_t Infrared_KeyDeCode = 0;
  /* Infinite loop */
  for(;;)
  {
    Read_SensorValue(&Alcohol, &Light, &Flame, &Gas);

    snprintf(DisPlayBuff, sizeof(DisPlayBuff), " %.2fV", Alcohol);
    LCD_ShowString(54, 419, 90, 30, 24, (uint8_t *)DisPlayBuff); // 酒精
    memset(DisPlayBuff, 0, sizeof(DisPlayBuff));

    snprintf(DisPlayBuff, sizeof(DisPlayBuff), " %.2fV", Light);
    LCD_ShowString(155, 419, 90, 30, 24, (uint8_t *)DisPlayBuff); // 光照
    memset(DisPlayBuff, 0, sizeof(DisPlayBuff));

    snprintf(DisPlayBuff, sizeof(DisPlayBuff), " %.2fV", Flame);
    LCD_ShowString(255, 419, 90, 30, 24, (uint8_t *)DisPlayBuff); // 火焰
    memset(DisPlayBuff, 0, sizeof(DisPlayBuff));

    snprintf(DisPlayBuff, sizeof(DisPlayBuff), " %.2fV", Gas);
    LCD_ShowString(357, 419, 90, 30, 24, (uint8_t *)DisPlayBuff); // 可燃气体传感器
    memset(DisPlayBuff, 0, sizeof(DisPlayBuff));

    if (PHOTO_SWITCH) // 光电开关
      LCD_ShowString(560, 225, 90, 30, 24, (uint8_t *)"  ON  ");
    else
      LCD_ShowString(560, 225, 90, 30, 24, (uint8_t *)"  OFF ");

    snprintf(DisPlayBuff, sizeof(DisPlayBuff), " %.2fC", LM75GetTempValue());
    LCD_ShowString(462, 419, 90, 30, 24, (uint8_t *)DisPlayBuff); // 温度传感器
    memset(DisPlayBuff, 0, sizeof(DisPlayBuff));

    if (FlagGotKey == 1) //通码
    {
      FlagGotKey = 0;
      Infrared_KeyDeCode = Remote_Infrared_KeyDeCode();
      switch (Infrared_KeyDeCode)
      {
      case te_InFraredState_ERROR:
        CONSOLE_INFO("ERROR ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" ERROR ");
        break;
      case te_InFraredState_SWITCH:
        CONSOLE_INFO("开关 ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Switch");
        break;
      case te_InFraredState_MUTE:
        CONSOLE_INFO("静音   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  Mute ");
        break;
      case te_InFraredState_WHITE:
        CONSOLE_INFO("白键     ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" WHITE ");
        break;
      case te_InFraredState_I:
        CONSOLE_INFO("i    ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"   i   ");
        break;
      case te_InFraredState_PLAY:
        CONSOLE_INFO("播放   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Play  ");
        break;
      case te_InFraredState_MOUSE:
        CONSOLE_INFO("鼠标    ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Mouse ");
        break;
      case te_InFraredState_LIVE:
        CONSOLE_INFO("直播  ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Live  ");
        break;
      case te_InFraredState_SELECT:
        CONSOLE_INFO("点播   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Select");
        break;
      case te_InFraredState_VOLJIAN:
        CONSOLE_INFO("VOL-   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" VOL-  ");
        break;
      case te_InFraredState_VOLJIA:
        CONSOLE_INFO("VOL+   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" VOL+  ");
        break;
      case te_InFraredState_SET:
        CONSOLE_INFO("设置     ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"Setting");
        break;
      case te_InFraredState_MENU:
        CONSOLE_INFO("菜单   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Menu  ");
        break;
      case te_InFraredState_UP:
        CONSOLE_INFO("↑   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  Up   ");
        break;
      case te_InFraredState_LEFT:
        CONSOLE_INFO("←   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Left  ");
        break;
      case te_InFraredState_RIGHT:
        CONSOLE_INFO("→   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Right ");
        break;
      case te_InFraredState_OK:
        CONSOLE_INFO("OK   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  OK   ");
        break;
      case te_InFraredState_DOWN:
        CONSOLE_INFO("↓   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Down  ");
        break;
      case te_InFraredState_HOME:
        CONSOLE_INFO("主页   ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Home  ");
        break;
      case te_InFraredState_RETURN:
        CONSOLE_INFO("返回  ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"Return ");
        break;
      case te_InFraredState_1:
        CONSOLE_INFO("1      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  1    ");
        break;
      case te_InFraredState_2:
        CONSOLE_INFO("2      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  2    ");
        break;
      case te_InFraredState_3:
        CONSOLE_INFO("3      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  3    ");
        break;
      case te_InFraredState_4:
        CONSOLE_INFO("4      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  4    ");
        break;
      case te_InFraredState_5:
        CONSOLE_INFO("5      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  5    ");
        break;
      case te_InFraredState_6:
        CONSOLE_INFO("6      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  6    ");
        break;
      case te_InFraredState_7:
        CONSOLE_INFO("7      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  7    ");
        break;
      case te_InFraredState_8:
        CONSOLE_INFO("8      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  8    ");
        break;
      case te_InFraredState_9:
        CONSOLE_INFO("9      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  9    ");
        break;
      case te_InFraredState_0:
        CONSOLE_INFO("0      ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"  0    ");
        break;
      case te_InFraredState_HTML5:
        CONSOLE_INFO("HTML5/FLASH");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" HTML5 ");
        break;
      case te_InFraredState_DELETE:
        CONSOLE_INFO("删除     ");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)" Delete");
        break;
      default:
        CONSOLE_INFO("Unknown key!");
        LCD_ShowString(663, 225, 90, 30, 24, (uint8_t *)"Unknown");
      }
    }
    osDelay(200);
  }
  /* USER CODE END LcdDisplayTask */
}

/* USER CODE BEGIN Header_GetDataTask */
/**
* @brief Function implementing the getDataTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GetDataTask */
void GetDataTask(void const * argument)
{
  /* USER CODE BEGIN GetDataTask */
  uint8_t KEY_ValueBuffer[1] = {0};
  uint8_t key_Flag = 0;

  char tmp[1] = {0};
  char *LCD_String = NULL;
  /* Infinite loop */
  for(;;)
  {
    if (ZLGflag1 == 1)
    {
      ZLGflag1 = 0;
      if(!I2C_ZLG7290_Read(0x01, KEY_ValueBuffer, 1))  {        //读键值
				CONSOLE_INFO("按键键值 = 0x%x", KEY_ValueBuffer[0]); //想串口发送键值
				sprintf(tmp, "%#x ", KEY_ValueBuffer[0]);
				LCD_String = LCD_ZLG_ToString(KEY_ValueBuffer[0]);
				LCD_ShowString(565, 419, 90, 30, 24, (uint8_t *)LCD_String); // 矩阵按键

				key_Flag = BSP_read_MatrixKeyToFlag(KEY_ValueBuffer[0]); //扫描键值，写标志位
				I2C_ZLG7290_Read(0x10, Zlg7290_Rx2_Buffer, 8);           //读8位数码管
//				I2C_ZLG7290_Read(&hi2c1,0x71,0x10,Zlg7290_Rx2_Buffer,8);//读8位数码管
//				for(int i=0;i<8;i++)
//					printf("0x%x ",Zlg7290_Rx2_Buffer[i]);
//				printf("===================\n");
				write_LcdDisplay(key_Flag);                              //扫描到相应的按键并且向数码管写进数值
			}
			else {
				ZLGflag1 = 0;
				flag = 0xff;
				I2C_ZLG72128_Read(&hi2c1, 0x61, 0x01, Rx1_Buffer_P, 1);       //读键值
				I2C_ZLG72128_Read(&hi2c1, 0x61, 0x03, Rx1_Buffer_T, 1);				//读键值

				if (Rx1_Buffer_T[0] != 0xff)             //功能按键
					swtich_key_func();
				if (Rx1_Buffer_P[0] != 0x0)              //普通按键
					swtich_key();	
				I2C_ZLG72128_Read(&hi2c1,0x61,0x10,Rx2_Buffer,8);//读8位数码管
				switch_flag();//扫描到相应的按键并且向数码管写进数值	
			}					
		}
		osDelay(1);
	}
    
  /* USER CODE END GetDataTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
//void audioPlayTask(void const *argument)
//{
//  /* USER CODE BEGIN getLCDTouchTask */
//  CONSOLE_INFO("Enter AudioTask is OK!!!");
//  uint8_t i = 0;
//  uint8_t res = 0;
//  // FATFS tempDiskFatFs;
//  // 加载音乐播放器的图片
//  Load_MusicAudio_Bmp();

//  //申请空间
//  audiodev.path = OS_malloc(SRAMIN, MM_BUFF_PATH_SIZE);
//  audiodev.name = OS_malloc(SRAMIN, MM_BUFF_NAME_SIZE);
//  if (audiodev.path == NULL && audiodev.name == NULL)
//  {
//    CONSOLE_ERROR("audiodev.path和audiodev.name申请内存失败");
//    goto ERR_EXIT1;
//  }
//  memset(audiodev.path, 0, MM_BUFF_PATH_SIZE);
//  memset(audiodev.name, 0, MM_BUFF_NAME_SIZE);
//	
//  strcpy((char *)audiodev.path, "0:/MUSIC"); //默认播放路径
//  CONSOLE_INFO("默认播放路径： %s", audiodev.path);

//  audiodev.mfilenum = audio_get_tnum((uint8_t *)audiodev.path, NULL); //得到总有效文件数
//  if (audiodev.mfilenum == 0)
//  {
//    CONSOLE_INFO("获取到总有效文件数： %d", audiodev.mfilenum);
//    goto ERR_EXIT1;
//  }
//  CONSOLE_INFO("获取到总有效文件数： %d", audiodev.mfilenum);

//  for (i = 0; i < audiodev.mfilenum; i++)
//  {
//    music_name_array[i] = OS_malloc(SRAMIN, MM_BUFF_NAME_SIZE);
//    if (music_name_array[i] == NULL)
//    {
//      CONSOLE_ERROR("music_name_array[%d]申请内存失败", i);
//      goto ERR_EXIT2;
//    }
//  }

//  audio_get_tnum((uint8_t *)audiodev.path, music_name_array); //获取文件名

//  BSP_WM8978_ADDA_Cfg(1, 0);     //开启DAC
//  BSP_WM8978_Input_Cfg(0, 0, 0); //关闭输入通道
//  BSP_WM8978_Output_Cfg(1, 0);   //开启DAC输出
//  BSP_WM8978_HPvol_Set(30, 30);   // 设置音量
//  audiodev.mode = 0; //初始化播放模式
//  /* Infinite loop */
//  for (;;)
//  {
//    res = audio_play();
//    if(res == AP_OVER)
//      break;
//  }

//	CONSOLE_INFO("释放内存");

//ERR_EXIT2:
//  OS_free(SRAMIN, audiodev.path);
//  OS_free(SRAMIN, audiodev.name);
//  do
//  {
//    OS_free(SRAMIN, music_name_array[i]);
//  } while (--i);
//  CONSOLE_INFO("释放完成，开始删除任务");
//ERR_EXIT1:

//  // 删除任务
//  Delete_audioPlayTask();
//  /* USER CODE END getLCDTouchTask */
//}
///**
// * @description: 创建音乐播放器任务
// * @param {*}
// * @return {*}
// */
//uint8_t Create_audioPlayTask(void) // 创建任务
//{
//  /* 挂起其他任务 */
//  vTaskSuspend(lcdDisplayTaskHandle);
//  vTaskSuspend(getDataTaskHandle);
//   
//  /* 停止中断(蜂鸣器、舵机、红外、步进的定时器中断) */
//  HAL_IT_Stop();

////  osThreadDef(AudioPlayTask, audioPlayTask, osPriorityBelowNormal, 0, 1024);
//  taskENTER_CRITICAL();
////  AudioPlayTaskHandle = osThreadCreate(osThread(AudioPlayTask), NULL);
//  taskEXIT_CRITICAL();

//  if (AudioPlayTaskHandle == NULL){
//    CONSOLE_ERROR("创建音乐播放器任务失败");
//    return 1;
//  }
//  else
//    return 0;
//}
///**
// * @description: 删除音乐播放器任务
// * @param {*}
// * @return {*}
// */
//void Delete_audioPlayTask(void) // 删除任务
//{
//  /* 删除任务 */
//  audiodev.status = 0;    // 需要清零，防止再次进入主界面之后，控制按键不能使用
//	CONSOLE_INFO("删除任务成功, 开始关闭硬件WM8978");

//  BSP_WM8978_ADDA_Cfg(0, 0);      //关闭DAC&ADC
//  BSP_WM8978_Input_Cfg(0, 0, 0); //关闭输入通道
//  BSP_WM8978_Output_Cfg(0, 0);   //关闭DAC输出
//  BSP_WM8978_HPvol_Set(0, 0);   // 设置音量0

//  /* 开启中断(舵机、红外的定时器中断) */
//  HAL_IT_Start();
//  // 关闭I2S DMA
//  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn,5,0);                    		//DMA中断优先级
//  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
//  HAL_I2S_MspDeInit(&hi2s2);    // 关闭DMA传输中断
//	CONSOLE_INFO("开启中断，恢复其他任务，开始加载主界面图片");
//  
//  // 加载首页图片
//	// taskENTER_CRITICAL();
//  Load_Background_Bmp();
//  LCD_ShowString(53, 225, 90, 30, 24,  (uint8_t *)"  OFF ");  // 步进电机
//  LCD_ShowString(155, 225, 90, 30, 24, (uint8_t *)"  OFF "); // 直流电机
//  LCD_ShowString(255, 225, 90, 30, 24, (uint8_t *)"  OFF "); // 舵机
//  LCD_ShowString(357, 225, 90, 30, 24, (uint8_t *)"  OFF "); // 继电器
//  LCD_ShowString(462, 225, 90, 30, 24, (uint8_t *)"  OFF "); // 蜂鸣器
//  
//	osDelay(5);
//	/* 恢复其他任务 */
//  vTaskResume(lcdDisplayTaskHandle);
//  vTaskResume(getDataTaskHandle);

//  vTaskDelete(AudioPlayTaskHandle);
//	// taskEXIT_CRITICAL();


//}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
