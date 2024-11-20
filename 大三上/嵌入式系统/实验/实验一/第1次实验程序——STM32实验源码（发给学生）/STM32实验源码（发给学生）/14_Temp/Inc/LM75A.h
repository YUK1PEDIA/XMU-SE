#ifndef __LM75A_H
#define __LM75A_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f4xx_hal.h"

#define DEBUG      0

#define TEMP_ADDR  0x00   //温度寄存器指针地址
#define CONF_ADDR  0x01   //配置寄存器指针地址
#define THYST_ADDR 0x02   //滞后寄存器指针地址
#define TOS_ADDR   0x03   //过热关断寄存器指针地址

/*器件工作模式*/
#define SHUTDOWN_MODE    0x01  //关断模式
#define NORMOR_MODE      0x00  //正常工作模式
/*OS工作模式*/
#define OSIRQ_MODE       0x02  //OS中断模式
#define OSCOMP_MODE      0x00  //OS比较器模式
/*OS极性选择*/
#define OS_HIGH          0x04  //OS高电平有效
#define OS_LOW           0x00  //OS低电平有效
/*OS故障队列*/
#define EQ_DEFAULT       0x00  //默认值    

#define EVL_OK           0     //成功返回值
#define EVL_ER           1     //失败返回值

uint8_t LM75SetMode(uint8_t ConfReg, uint8_t Mode);
uint16_t LM75GetTempReg(void);
double LM75GetTempValue(uint16_t tempreg);

#endif

