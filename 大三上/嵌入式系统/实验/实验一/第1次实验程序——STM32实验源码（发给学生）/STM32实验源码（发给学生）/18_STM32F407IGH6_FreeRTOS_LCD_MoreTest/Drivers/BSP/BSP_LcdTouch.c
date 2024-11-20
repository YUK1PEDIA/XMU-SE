#include "BSP_LcdTouch.h"
#include "BSP_LCD.h"


tp_dev_t tp_dev;


//触摸屏初始化
//返回值:0,没有进行校准
//       1,进行过校准
uint8_t TP_Init(void)
{
  BSP_GT9147_Init();
	
  tp_dev.touchtype|=0X80;	//电容屏
  tp_dev.touchtype|=g_lcddev.dir&0X01;//横屏还是竖屏
  return 0;

}


