/*
 * @Author: your name
 * @Date: 2021-07-12 18:02:08
 * @LastEditTime: 2021-07-14 16:54:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\APP_Audio.h
 */
#ifndef __APP_AUDIO_H__
#define __APP_AUDIO_H__

#include "main.h"
#include "ff.h"
 
//���ֲ��Ų����������
typedef enum {
	AP_OK=0X00,				//�����������
	AP_NEXT,				//������һ��
	AP_PREV,				//������һ��
	AP_OVER,				//���Ž���
	AP_ERR=0X80,			//�����д���(û����������,������ʾ����) 
}APRESULT;

#define MM_BUFF_PATH_SIZE   40
#define MM_BUFF_NAME_SIZE   20

//���ֲ��ſ�����
typedef __packed struct
{  
	//2��I2S�����BUF
	uint8_t *i2sbuf1;
	uint8_t *i2sbuf2; 
	uint8_t *tbuf;			//��ʱ����
	FIL *file;			//��Ƶ�ļ�ָ�� 	
  	FILINFO *wavfileinfo; //�ļ���Ϣ
	uint32_t(*file_seek)(uint32_t);//�ļ�������˺��� 

	vu8 status;			//bit0:0,��ͣ����;1,��������
						//bit1:0,��������;1,��������  
						//bit2~3:����
						//bit4:0,�����ֲ���;1,���ֲ����� (������)		
						//bit5:0,�޶���;1,ִ����һ���и����(������)
						//bit6:0,�޶���;1,������ֹ����(���ǲ�ɾ����Ƶ��������),������ɺ�,���������Զ������λ
 						//bit7:0,��Ƶ����������ɾ��/����ɾ��;1,��Ƶ����������������(�������ִ��)
	
	uint8_t mode;			//����ģʽ
								//0,ȫ��ѭ��;1,����ѭ��;2,�������;
	
	uint8_t *path;			//��ǰ�ļ���·��
	uint8_t *name;			//��ǰ���ŵ�MP3��������
  	uint8_t *pname;
	uint16_t namelen;		//name��ռ�ĵ���.
	uint16_t curnamepos;		//��ǰ��ƫ��

	uint32_t totsec ;		//���׸�ʱ��,��λ:��
	uint32_t cursec ;		//��ǰ����ʱ�� 
	uint32_t bitrate;	   	//������(λ��)
	uint32_t samplerate;		//������ 
	uint16_t bps;			//λ��,����16bit,24bit,32bit
	
	uint16_t curindex;		//��ǰ���ŵ���Ƶ�ļ�
	uint16_t mfilenum;		//�����ļ���Ŀ	    
	uint16_t *mfindextbl;	//��Ƶ�ļ�������
	
}__audiodev; 
__packed typedef struct 
{							  
	uint8_t mvol;		//����(����������һ���),��Χ:0~63
	uint8_t cfreq[5];	//����Ƶ��ѡ������,ÿ��Ԫ�ؿ�ѡ��ΧΪ0~3,�Ҵ����Ƶ�ʸ�����ͬ 
					//[0]��ӦƵ��:80,105,135,175
					//[1]��ӦƵ��:230,300,385,500
					//[2]��ӦƵ��:650,850,1100,1400
					//[3]��ӦƵ��:1800,2400,3200,4100
					//[4]��ӦƵ��:5300,6900,9000,11700
	uint8_t freqval[5];	//����Ƶ�������
	uint8_t d3;			//3d����	
	uint8_t speakersw;	//�������ȿ���,0,�ر�;1,�� 
	uint8_t saveflag; 	//�����־,0X0A,�������;����,����δ����	   
}_wm8978_obj;

extern __audiodev audiodev;	//���ֲ��ſ�����
extern uint8_t  *music_name_array[50];		// ����·������Ƶ�ļ���



uint8_t audio_play(void);
void app_wm8978_volset(uint8_t vol);
uint16_t audio_get_tnum(uint8_t *path,uint8_t** name);
void audio_start(void);
void audio_stop(void);
void audio_stop_req(__audiodev *audiodevx);

#endif // !__APP_AUDIO_H__
