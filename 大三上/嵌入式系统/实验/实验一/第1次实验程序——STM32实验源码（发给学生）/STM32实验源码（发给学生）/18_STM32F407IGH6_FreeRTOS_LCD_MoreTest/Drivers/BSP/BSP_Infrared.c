/*
 * @Author: your name
 * @Date: 2021-07-08 09:13:47
 * @LastEditTime: 2021-07-11 17:17:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Infrared.c
 */
#include "BSP_Infrared.h"

__IO uint32_t GlobalTimingDelay100us;
__IO uint32_t FlagGotKey = 0;
__IO Remote_Infrared_data_union RemoteInfrareddata;

const uint32_t TIME_DELAY_6MS = 60;
const uint32_t TIME_DELAY_10MS = 100;

/**
 * @description: 红外遥控器 接收信号函数
 * @param {*}
 * @return {*}
 */
void Remote_Infrared_KEY_ISR(void)
{
    static __IO uint8_t bBitCounter = 0; //键盘帧位计数
    static __IO uint32_t bKeyCode = 0;
    bBitCounter++;

    if (bBitCounter == 1) // 开始拉低9ms
    {
        if (REMOTE_INFRARED_INPUT) // 高电平无效
            bBitCounter = 0;
        else
            GlobalTimingDelay100us = TIME_DELAY_10MS;
    }
    else if (bBitCounter == 2) // 4.5ms的高脉冲
    {
        if (REMOTE_INFRARED_INPUT)
        {
            if ((GlobalTimingDelay100us > 2) && (GlobalTimingDelay100us < 18))
                GlobalTimingDelay100us = TIME_DELAY_6MS;
            else
                bBitCounter = 0;
        }
        else
            bBitCounter = 0;
    }
    else if (bBitCounter == 3) // 4.5ms的高脉冲
    {
        if (REMOTE_INFRARED_INPUT)
            bBitCounter = 0;
        else
        {
            if ((GlobalTimingDelay100us > 5) && (GlobalTimingDelay100us < 20))
                GlobalTimingDelay100us = TIME_DELAY_6MS;
            else if ((GlobalTimingDelay100us > 32) && (GlobalTimingDelay100us < 46))
            {
                bBitCounter = 0;
                RemoteInfrareddata.uiRemoteInfraredData = bKeyCode;
                bBitCounter = 0;
                FlagGotKey = 1;
            }
            else
                bBitCounter = 0;
        }
    }
    else if (bBitCounter > 3 && bBitCounter < 68) //接收8位数据
    {
        if (REMOTE_INFRARED_INPUT)
        {
            if ((GlobalTimingDelay100us > 50) && (GlobalTimingDelay100us < 58))
                GlobalTimingDelay100us = TIME_DELAY_6MS;
            else
                bBitCounter = 0;
        }
        else
        {
            if ((GlobalTimingDelay100us > 50) && (GlobalTimingDelay100us < 58)) // '0'
            {
                GlobalTimingDelay100us = TIME_DELAY_6MS;
                bKeyCode <<= 1; // MSB First
                bKeyCode += 0x00;
            }
            else if ((GlobalTimingDelay100us > 40) && (GlobalTimingDelay100us < 48)) //'1'
            {
                GlobalTimingDelay100us = TIME_DELAY_6MS;
                bKeyCode <<= 1; // MSB First
                bKeyCode += 0x01;
            }
            else
                bBitCounter = 0;
        }

        if (bBitCounter == 67)
        {
            RemoteInfrareddata.uiRemoteInfraredData = bKeyCode;
            bBitCounter = 0;
            FlagGotKey = 1;
        }
    }
    else
        bBitCounter = 0;
}

/**
 * @description: 红外遥控器 解码函数
 * @param {*}
 * @return {*}
 */
uint8_t Remote_Infrared_KeyDeCode(void)
{

        if ((RemoteInfrareddata.RemoteInfraredDataStruct.bID == (uint8_t)~RemoteInfrareddata.RemoteInfraredDataStruct.bIDNot) && (RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCode == (uint8_t)~RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCodeNot))
        {
            //   DEBUG_INFO("IR Receive KeyCode = 0x%02X, ", RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCode);
            return RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCode;
        }

    
    return 0;
}

/**
 *  switch(RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCode)
      {
      case 0:
        DEBUG_INFO("ERROR ");
        LCD_ShowString(663, 225, 90,30, 24,(uint8_t *)" ERROR ");
        break;
      case 0xEA:
        DEBUG_INFO("开关 ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Switch");
        break;
      case 0xDA:
        DEBUG_INFO("静音   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  Mute ");
        break;
      case  0x68:
        DEBUG_INFO("白键     ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" WHITE ");
        break;
      case 0x5A:
        DEBUG_INFO("i    ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"   i   ");
        break;
      case 0x4A:
        DEBUG_INFO("播放   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Play  ");
        break;
      case 0x0A:
        DEBUG_INFO("鼠标    ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Mouse ");
        break;
      case 0xF0:
        DEBUG_INFO("直播  ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Live  ");
        break;
      case  0x32:
        DEBUG_INFO("点播   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Select");
        break;
      case 0x1A:
        DEBUG_INFO("VOL-   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" VOL-  ");
        break;
      case 0xD8:
        DEBUG_INFO("VOL+   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" VOL+  ");
        break;
      case 0xF2:
        DEBUG_INFO("设置     ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"Setting");
        break;
      case 0x58:
        DEBUG_INFO("菜单   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Menu  ");
        break;
      case 0xC2:
        DEBUG_INFO("↑   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  Up   ");
        break;
      case  0x60:
        DEBUG_INFO("←   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Left  ");
        break;
      case 0x70:
        DEBUG_INFO("→   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Right ");
        break;
      case 0x40:
        DEBUG_INFO("OK   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  OK   ");
        break;
      case 0x50:
        DEBUG_INFO("↓   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Down  ");
        break;
      case 0x72:
        DEBUG_INFO("主页   ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Home  ");
        break;
      case 0xB2:
        DEBUG_INFO("返回  ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"Return ");
        break;
      case 0x08:
        DEBUG_INFO("1      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  1    ");
        break;
      case 0x88:
        DEBUG_INFO("2      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  2    ");
        break;
      case 0x48:
        DEBUG_INFO("3      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  3    ");
        break;
      case 0xC8:
        DEBUG_INFO("4      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  4    ");
        break;
      case 0x28:
        DEBUG_INFO("5      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  5    ");
        break;
      case 0xA8:
        DEBUG_INFO("6      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  6    ");
        break;
      case 0xE8:
        DEBUG_INFO("7      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  7    ");
        break;
      case 0x18:
        DEBUG_INFO("8      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  8    ");
        break;
      case 0x98:
        DEBUG_INFO("9      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  9    ");
        break;
      case 0xB8:
        DEBUG_INFO("0      ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"  0    ");
        break;
      case 0x38:
        DEBUG_INFO("HTML5/FLASH");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" HTML5 ");
        break;
      case 0x78:
        DEBUG_INFO("删除     ");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)" Delete");
        break;
      default:
        DEBUG_INFO("Unknown key!");
        LCD_ShowString(663,225,90,30,24,(uint8_t *)"Unknown");
*/
