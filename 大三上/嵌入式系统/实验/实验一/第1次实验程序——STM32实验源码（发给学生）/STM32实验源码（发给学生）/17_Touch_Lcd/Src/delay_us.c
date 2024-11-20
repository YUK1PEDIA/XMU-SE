#include "delay_us.h"


// us级延时函数
static uint32_t fac_us = 0; //us延时倍乘数

void delay_init(uint8_t SYSCLK)
{
  fac_us = SYSCLK;
}

void delay_us(uint32_t nus)
{
  uint32_t ticks;
  uint32_t told, tnow, tcnt = 0;
  uint32_t reload = SysTick->LOAD; //LOAD的值
  ticks = nus * fac_us;            //需要的节拍数
  told = SysTick->VAL;             //刚进入时的计数器值
  while (1)
  {
    tnow = SysTick->VAL;
    if (tnow != told)
    {
      if (tnow < told)
        tcnt += told - tnow; //这里注意一下SYSTICK是一个递减的计数器就可以了.
      else
        tcnt += reload - tnow + told;
      told = tnow;
      if (tcnt >= ticks)
        break; //时间超过/等于要延迟的时间,则退出.
    }
  };
}

void delay_ms(uint16_t nms)
{
  uint32_t i;
  for (i = 0; i < nms; i++)
    delay_us(1000);
}


