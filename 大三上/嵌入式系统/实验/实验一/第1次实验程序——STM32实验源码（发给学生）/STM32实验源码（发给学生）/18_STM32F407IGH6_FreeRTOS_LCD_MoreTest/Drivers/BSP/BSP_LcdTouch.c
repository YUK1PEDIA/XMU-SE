#include "BSP_LcdTouch.h"
#include "BSP_LCD.h"


tp_dev_t tp_dev;


//��������ʼ��
//����ֵ:0,û�н���У׼
//       1,���й�У׼
uint8_t TP_Init(void)
{
  BSP_GT9147_Init();
	
  tp_dev.touchtype|=0X80;	//������
  tp_dev.touchtype|=g_lcddev.dir&0X01;//������������
  return 0;

}


