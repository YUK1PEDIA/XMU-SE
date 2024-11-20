/*
 * @Author: your name
 * @Date: 2021-07-07 15:47:16
 * @LastEditTime: 2021-07-15 10:53:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\OS_Malloc.c
 */
#include "OS_Malloc.h"
#include "cmsis_os.h"

/* 内存池(32字节对齐) */
static __align(32) uint8_t mem1base[MEM1_MAX_SIZE];                                 //内部SRAM内存池
static __align(32) uint8_t mem2base[MEM2_MAX_SIZE] __attribute__((at(0X68000000))); //外部SRAM内存池
static __align(32) uint8_t mem3base[MEM3_MAX_SIZE] __attribute__((at(0X10000000))); //内部CCM内存池

/* 内存管理表 */
static uint16_t mem1mapbase[MEM1_ALLOC_TABLE_SIZE];                                                 //内部SRAM内存池MAP
static uint16_t mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000 + MEM2_MAX_SIZE))); //外部SRAM内存池MAP
static uint16_t mem3mapbase[MEM3_ALLOC_TABLE_SIZE] __attribute__((at(0X10000000 + MEM3_MAX_SIZE))); //内部CCM内存池MAP

/* 内存管理参数 */
static const uint32_t memtblsize[SRAMBANK] = {MEM1_ALLOC_TABLE_SIZE, MEM2_ALLOC_TABLE_SIZE, MEM3_ALLOC_TABLE_SIZE}; //内存表大小
static const uint32_t memblksize[SRAMBANK] = {MEM1_BLOCK_SIZE, MEM2_BLOCK_SIZE, MEM3_BLOCK_SIZE};                   //内存分块大小
static const uint32_t memsize[SRAMBANK]    = {MEM1_MAX_SIZE, MEM2_MAX_SIZE, MEM3_MAX_SIZE};                            //内存总大小

/* 内存管理器 */
struct _m_mallco_dev
{
  void (*init)(uint8_t);					//初始化
  uint8_t (*perused)(uint8_t);		  	    	//内存使用率
  uint8_t 	*membase[SRAMBANK];				//内存池 管理SRAMBANK个区域的内存
  uint16_t *memmap[SRAMBANK]; 				//内存管理状态表
  uint8_t  memrdy[SRAMBANK]; 				//内存管理是否就绪
};

/* 内存管理器初始化 */
struct _m_mallco_dev mallco_dev =
{
  OS_mem_init,                           //内存初始化
  OS_mem_perused,                        //内存使用率
  mem1base, mem2base, mem3base,          //内存池
  mem1mapbase, mem2mapbase, mem3mapbase, //内存管理状态表
  0, 0, 0,                               //内存管理未就绪
};

/**
 * @description: 内存分配(内部调用)
 * @param {uint8_t} memx 所属内存块
 * @param {uint32_t} size 要分配的内存大小(字节)
 * @return {uint32_t} 0XFFFFFFFF,代表错误;其他,内存偏移地址
 */
static uint32_t my_mem_malloc(uint8_t memx, uint32_t size)
{
  signed long offset = 0;
  uint32_t nmemb;     //需要的内存块数
  uint32_t cmemb = 0; //连续空内存块数
  uint32_t i;
  if (!mallco_dev.memrdy[memx])
    mallco_dev.init(memx); //未初始化,先执行初始化
  if (size == 0)
    return 0XFFFFFFFF;             //不需要分配
  nmemb = size / memblksize[memx]; //获取需要分配的连续内存块数
  if (size % memblksize[memx])
    nmemb++;
  for (offset = memtblsize[memx] - 1; offset >= 0; offset--) //搜索整个内存控制区
  {
    if (!mallco_dev.memmap[memx][offset])
      cmemb++; //连续空内存块数增加
    else
      cmemb = 0;        //连续内存块清零
    if (cmemb == nmemb) //找到了连续nmemb个空内存块
    {
      for (i = 0; i < nmemb; i++) //标注内存块非空
      {
        mallco_dev.memmap[memx][offset + i] = nmemb;
      }
      return (offset * memblksize[memx]); //返回偏移地址
    }
  }
  return 0XFFFFFFFF; //未找到符合分配条件的内存块
}


/**
 * @description: 释放内存(内部调用)
 * @param {uint8_t} memx 所属内存块
 * @param {uint32_t} offset 内存地址偏移
 * @return {uint8_t} 0,释放成功;1,释放失败;
 */
static uint8_t my_mem_free(uint8_t memx, uint32_t offset)
{
  int i;
  if (!mallco_dev.memrdy[memx]) //未初始化,先执行初始化
  {
    mallco_dev.init(memx);
    return 1; //未初始化
  }
  if (offset < memsize[memx]) //偏移在内存池内.
  {
    int index = offset / memblksize[memx];      //偏移所在内存块号码
    int nmemb = mallco_dev.memmap[memx][index]; //内存块数量
    for (i = 0; i < nmemb; i++)                 //内存块清零
    {
      mallco_dev.memmap[memx][index + i] = 0;
    }
    return 0;
  }
  else
    return 2; //偏移超区了.
}
//复制内存
//*des:目的地址
//*src:源地址
//n:需要复制的内存长度(字节为单位)
void OS_memcpy(void *des, void *src, uint32_t n)
{
  uint8_t *xdes = des;
  uint8_t *xsrc = src;
  while (n--)
    *xdes++ = *xsrc++;
}
//设置内存
//*s:内存首地址
//c :要设置的值
//count:需要设置的内存大小(字节为单位)
void OS_memset(void *s, uint8_t c, uint32_t count)
{
  uint8_t *xs = s;
  while (count--)
    *xs++ = c;
}
//内存管理初始化
//memx:所属内存块
void OS_mem_init(uint8_t memx)
{
  OS_memset(mallco_dev.memmap[memx], 0, memtblsize[memx] * 2); //内存状态表数据清零
  OS_memset(mallco_dev.membase[memx], 0, memsize[memx]);       //内存池所有数据清零
  mallco_dev.memrdy[memx] = 1;                                //内存管理初始化OK
}
//获取内存使用率
//memx:所属内存块
//返回值:使用率(0~100)
uint8_t OS_mem_perused(uint8_t memx)
{
  uint32_t used = 0;
  uint32_t i;
  for (i = 0; i < memtblsize[memx]; i++)
  {
    if (mallco_dev.memmap[memx][i])
      used++;
  }
  return (used * 100) / (memtblsize[memx]);
}

//释放内存(外部调用)
//memx:所属内存块
//ptr:内存首地址
void OS_free(uint8_t memx, void *ptr)
{
  uint32_t offset;
  if (ptr == NULL)
    return;            //地址为0.
  //printf("free:%d,%x\r\n",memx,ptr);
//  taskENTER_CRITICAL(); //进入临界区(无法被中断打断)  // 进入临界区时间不宜过长
  offset = (uint32_t)ptr - (uint32_t)mallco_dev.membase[memx];
  my_mem_free(memx, offset); //释放内存
//  taskEXIT_CRITICAL();        //退出临界区(可以被中断打断)
}
//分配内存(外部调用)
//memx:所属内存块
//size:内存大小(字节)
//返回值:分配到的内存首地址.
void *OS_malloc(uint8_t memx, uint32_t size)
{

  uint32_t offset;
  //printf("m:%d,%d\r\n",memx,size);
//  taskENTER_CRITICAL(); //进入临界区(无法被中断打断)  // 进入临界区时间不宜过长
  offset = my_mem_malloc(memx, size);
//  taskEXIT_CRITICAL(); //退出临界区(可以被中断打断)
  if (offset == 0XFFFFFFFF)
    return NULL;
  else
    return (void *)((uint32_t)mallco_dev.membase[memx] + offset);
}
//重新分配内存(外部调用)
//memx:所属内存块
//*ptr:旧内存首地址
//size:要分配的内存大小(字节)
//返回值:新分配到的内存首地址.
void *OS_realloc(uint8_t memx, void *ptr, uint32_t size)
{
  uint32_t offset;

//  taskENTER_CRITICAL(); //进入临界区(无法被中断打断)  // 进入临界区时间不宜过长
  offset = my_mem_malloc(memx, size);
//  taskEXIT_CRITICAL(); //退出临界区(可以被中断打断)
  if (offset == 0XFFFFFFFF)
    return NULL;
  else
  {
    OS_memcpy((void *)((uint32_t)mallco_dev.membase[memx] + offset), ptr, size); //拷贝旧内存内容到新内存
    OS_free(memx, ptr);                                                          //释放旧内存
    return (void *)((uint32_t)mallco_dev.membase[memx] + offset);               //返回新内存首地址
  }
}


