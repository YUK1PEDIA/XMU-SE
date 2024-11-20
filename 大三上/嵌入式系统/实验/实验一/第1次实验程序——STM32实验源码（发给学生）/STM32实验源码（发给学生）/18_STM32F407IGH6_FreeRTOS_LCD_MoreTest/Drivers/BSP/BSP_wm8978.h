/*
 * @Author: your name
 * @Date: 2021-07-01 18:32:46
 * @LastEditTime: 2021-07-07 16:56:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\F407_Multi_core_testing\UserFunctions\BSP\wm8978.h
 */
#ifndef __BSP_WM8978_H
#define __BSP_WM8978_H
#include "main.h"

#define WM8978_ADDR     0X1A	//WM8978的器件地址,固定为0X1A 

#define	WM8978_WIRTE_ADDRESS		(WM8978_ADDR << 1 | 0)

#define EQ1_80Hz		0X00
#define EQ1_105Hz		0X01
#define EQ1_135Hz		0X02
#define EQ1_175Hz		0X03

#define EQ2_230Hz		0X00
#define EQ2_300Hz		0X01
#define EQ2_385Hz		0X02
#define EQ2_500Hz		0X03

#define EQ3_650Hz		0X00
#define EQ3_850Hz		0X01
#define EQ3_1100Hz		0X02
#define EQ3_14000Hz		0X03

#define EQ4_1800Hz		0X00
#define EQ4_2400Hz		0X01
#define EQ4_3200Hz		0X02
#define EQ4_4100Hz		0X03

#define EQ5_5300Hz		0X00
#define EQ5_6900Hz		0X01
#define EQ5_9000Hz		0X02
#define EQ5_11700Hz		0X03

uint8_t BSP_WM8978_Init(void);
void BSP_WM8978_ADDA_Cfg(uint8_t dacen,uint8_t adcen);
void BSP_WM8978_Input_Cfg(uint8_t micen,uint8_t lineinen,uint8_t auxen);
void BSP_WM8978_Output_Cfg(uint8_t dacen,uint8_t bpsen);
void BSP_WM8978_MIC_Gain(uint8_t gain);
void BSP_WM8978_LINEIN_Gain(uint8_t gain);
void BSP_WM8978_AUX_Gain(uint8_t gain);
void BSP_WM8978_HPvol_Set(uint8_t voll,uint8_t volr);
void BSP_WM8978_SPKvol_Set(uint8_t volx);
void BSP_WM8978_I2S_Cfg(uint8_t fmt,uint8_t len);
void BSP_WM8978_3D_Set(uint8_t depth);
void BSP_WM8978_EQ_3D_Dir(uint8_t dir);
void BSP_WM8978_EQ1_Set(uint8_t cfreq,uint8_t gain);
void BSP_WM8978_EQ2_Set(uint8_t cfreq,uint8_t gain);
void BSP_WM8978_EQ3_Set(uint8_t cfreq,uint8_t gain);
void BSP_WM8978_EQ4_Set(uint8_t cfreq,uint8_t gain);
void BSP_WM8978_EQ5_Set(uint8_t cfreq,uint8_t gain);

#endif
