#include "lcd_touch.h"
#include "lcd.h"
#include <stdio.h>


tp_dev_t tp_dev;


//��������ʼ��
//����ֵ:0,û�н���У׼
//       1,���й�У׼
uint8_t TP_Init(void)
{
	
  GT9147_Init();
	
  tp_dev.touchtype|=0X80;	//������
  tp_dev.touchtype|=lcddev.dir&0X01;//������������
  return 0;

}

