/*
 * @Author: your name
 * @Date: 2021-07-08 09:13:47
 * @LastEditTime: 2021-07-12 17:16:37
 * @LastEditors: Please set LastEditors
 * @Description: 红外遥控
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_Infrared.h
 */
#ifndef __BSP_INFRARED_H
#define __BSP_INFRARED_H
#include "main.h"


/* 定义红外线接收到的数据结构体类型 */
typedef struct _Remote_Infrared_data_struct 
{
	uint8_t bKeyCodeNot; //按键的的ASIIC码值
	uint8_t bKeyCode; //shift键按下标志
	uint8_t bIDNot; //断码标志位
	uint8_t bID; //新键标志位
}Remote_Infrared_data_struct;
typedef union _Remote_Infrared_data_union 
{
	Remote_Infrared_data_struct RemoteInfraredDataStruct; 
	uint32_t uiRemoteInfraredData; 
}Remote_Infrared_data_union;

/* 解析完成后的信息码 */
typedef enum{
    te_InFraredState_ERROR = 0,
    te_InFraredState_SWITCH = 0xEA,
    te_InFraredState_MUTE = 0xDA,
    te_InFraredState_WHITE = 0x68,
    te_InFraredState_I = 0x5A,
    te_InFraredState_PLAY = 0x4A,
    te_InFraredState_MOUSE = 0x0A,
    te_InFraredState_LIVE = 0xF0,
    te_InFraredState_SELECT = 0x32,
    te_InFraredState_VOLJIAN = 0x1A,
    te_InFraredState_VOLJIA = 0xD8,
    te_InFraredState_SET = 0xF2,
    te_InFraredState_MENU = 0x58,
    te_InFraredState_UP = 0xc2,
    te_InFraredState_LEFT = 0x60,
    te_InFraredState_RIGHT = 0x70,
    te_InFraredState_OK = 0x40,
    te_InFraredState_DOWN = 0x50,
    te_InFraredState_HOME = 0x72,
    te_InFraredState_RETURN = 0xB2,
    te_InFraredState_1 = 0x08,
    te_InFraredState_2 = 0x88,
    te_InFraredState_3 = 0x48,
    te_InFraredState_4 = 0xC8,
    te_InFraredState_5 = 0x28,
    te_InFraredState_6 = 0xA8,
    te_InFraredState_7 = 0xE8,
    te_InFraredState_8 = 0x18,
    te_InFraredState_9 = 0x98,
    te_InFraredState_0 = 0xB8,
    te_InFraredState_HTML5 = 0x38,
    te_InFraredState_DELETE = 0x78,
}Remote_Infrared_StateCode;


extern __IO uint32_t FlagGotKey;

void Remote_Infrared_KEY_ISR(void);
uint8_t Remote_Infrared_KeyDeCode(void);

#endif // !__BSP_INFRARED_H
