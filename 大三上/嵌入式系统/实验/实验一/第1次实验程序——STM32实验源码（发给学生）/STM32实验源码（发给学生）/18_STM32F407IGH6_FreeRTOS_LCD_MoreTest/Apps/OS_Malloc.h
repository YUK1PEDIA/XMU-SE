/*
 * @Author: your name
 * @Date: 2021-07-07 15:47:23
 * @LastEditTime: 2021-07-21 11:43:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\OS_Malloc.h
 */
#ifndef __OS_MALLOC_H
#define __OS_MALLOC_H

#include "main.h"

#ifndef NULL
#define NULL 0
#endif

//定义三个内存池
#define SRAMIN	 0		//内部内存池
#define SRAMEX   1		//外部内存池
#define SRAMCCM  2		//CCM内存池(此部分SRAM仅仅CPU可以访问!!!)
#define SRAMBANK 	3	//定义支持的SRAM块数.	

//mem1内存参数设定.mem1完全处于内部SRAM里面.
#define MEM1_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM1_MAX_SIZE			60 *1024  						//最大管理内存 90K
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//内存表大小

//mem2内存参数设定.mem2的内存池处于外部SRAM里面
#define MEM2_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM2_MAX_SIZE			960 *1024  						//最大管理内存960K
#define MEM2_ALLOC_TABLE_SIZE	MEM2_MAX_SIZE/MEM2_BLOCK_SIZE 	//内存表大小

//mem3内存参数设定.mem3处于CCM,用于管理CCM(特别注意,这部分SRAM,仅CPU可以访问!!)
#define MEM3_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM3_MAX_SIZE			60 *1024  						//最大管理内存60K
#define MEM3_ALLOC_TABLE_SIZE	MEM3_MAX_SIZE/MEM3_BLOCK_SIZE 	//内存表大小

////////////////////////////////////////////////////////////////////////////////
//用户调用函数
void OS_mem_init(uint8_t memx);				//内存管理初始化函数(外/内部调用)
void OS_free(uint8_t memx,void *ptr);  			//内存释放(外部调用)
void *OS_malloc(uint8_t memx,uint32_t size);			//内存分配(外部调用)
void *OS_realloc(uint8_t memx,void *ptr,uint32_t size);//重新分配内存(外部调用)
void OS_memset(void *s,uint8_t c,uint32_t count);	//设置内存
void OS_memcpy(void *des,void *src,uint32_t n);//复制内存
uint8_t OS_mem_perused(uint8_t memx);				//获得内存使用率(外/内部调用)
#endif // !__OS_MALLOC_H


