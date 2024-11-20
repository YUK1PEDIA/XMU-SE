#include "APP_Audio.h"
#include "APP_Operate.h"
#include "APP_StartShow.h"
#include "OS_malloc.h"
#include "BSP_LCD.h"
#include "BSP_wm8978.h"
#include "Fun_FsExFunctions.h"

#include "wav.h"
#include "i2s.h"
#include "piclib.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "cmsis_os.h"
#include "ff.h"

extern osThreadId AudioPlayTaskHandle;
//���ֲ��ſ�����
__audiodev audiodev = {0};
uint8_t *music_name_array[50]; //����·������Ƶ�ļ���

// uint8_t 					current_num=0;//��ǰ���ŵ��ļ�
// uint8_t *pname = 0;     // �����ļ�������

//WM8978Ĭ�ϲ���
_wm8978_obj wm8978set =
    {
        .mvol = 80, //����:50
        0,
        0,
        0,
        0,
        0, //Ƶ�ʱ�־��Ϊ0
        0,
        0,
        0,
        0,
        0,              //����Ƶ�������ȫ0
        .d3 = 0,        //3DЧ��Ϊ0
        .speakersw = 1, //������������
        .saveflag = 0,  // �����־,0X0A,�������;����,����δ����
};
//��ʾ��Ŀ����
//index:��ǰ����
//total:���ļ���
void audio_index_show(uint16_t index, uint16_t total)
{
  //��ʾ��ǰ��Ŀ������,������Ŀ��
  LCD_ShowxNum(60 + 0, 230, index, 3, 16, 0X80); //����
  LCD_ShowChar(60 + 24, 230, '/', 16, 0);
  LCD_ShowxNum(60 + 32, 230, total, 3, 16, 0X80); //����Ŀ
}
//����ĳ����Ƶ�ļ�
uint8_t audio_play_song(uint8_t* fname)
{
	uint8_t res;  
	res=exf_FsTypetell(fname); 
	switch(res)
	{
		case T_WAV:
			res=wav_play_song(fname);
			break;
		default://�����ļ�,�Զ���ת����һ��
			CONSOLE_INFO("can't play:%s",fname);
			break;
	}
	return res;
}
//���ֲ�����
uint8_t audio_play(void)
{  
  uint8_t res = 0;
  DIR wavdir;                  //Ŀ¼
  uint32_t temp;
	FATFS DiskFatFs;

  audiodev.wavfileinfo = (FILINFO *)OS_malloc(SRAMIN, sizeof(FILINFO)); //�����ڴ�
  audiodev.pname = OS_malloc(SRAMIN, _MAX_LFN * 2 + 1);                 //Ϊ��·�����ļ��������ڴ�
  audiodev.mfindextbl = OS_malloc(SRAMIN, 4 * audiodev.mfilenum);     //����4*totwavnum���ֽڵ��ڴ�,���ڴ�������ļ�off block����

  while (!audiodev.wavfileinfo || !audiodev.pname || !audiodev.mfindextbl) //�ڴ�������
  {
    CONSOLE_ERROR("�ڴ����ʧ��!");
    HAL_Delay(1000);
  }
   
  // ��¼����ֵ
  res = f_opendir(&wavdir, (char *)audiodev.path); //��Ŀ¼
  if (res == FR_OK)
  {
    audiodev.curindex = 0; //��ǰ����Ϊ0
   
    while (1)              //ȫ����ѯһ��
    {
      temp = wavdir.dptr;                    //��¼��ǰindex
      res = f_readdir(&wavdir, audiodev.wavfileinfo); //��ȡĿ¼�µ�һ���ļ�
      if (res != FR_OK || audiodev.wavfileinfo->fname[0] == 0)
        break; //������/��ĩβ��,�˳�
         
      res = exf_FsTypetell((uint8_t *)audiodev.wavfileinfo->fname);
         
      if ((res & 0XF0) == 0X40) //ȡ����λ,�����ǲ��������ļ�
      {
        audiodev.mfindextbl[audiodev.curindex] = temp; //��¼����
        audiodev.curindex++;
      }
    }
  }
  f_closedir(&wavdir);
   

  res = f_opendir(&wavdir, (char *)audiodev.path);
  audiodev.curindex = 0; //��ǰ����Ϊ0
	audiodev.status|=1<<4;//������ڲ�������
  while (res == FR_OK) //���ļ��гɹ�
  {
    while(1)
    {
      CONSOLE_INFO("audiodev.curindex = %d",audiodev.curindex);
      dir_sdi(&wavdir, audiodev.mfindextbl[audiodev.curindex]); //�ı䵱ǰĿ¼����
      res = f_readdir(&wavdir, audiodev.wavfileinfo);             //��ȡĿ¼�µ�һ���ļ�
      if (res != FR_OK || audiodev.wavfileinfo->fname[0] == 0)
        break;                                                 //������/��ĩβ��,�˳�
      strcpy((char *)audiodev.pname, "0:/MUSIC/");                      //����·��(Ŀ¼)
      strcat((char *)audiodev.pname, (const char *)audiodev.wavfileinfo->fname); //���ļ������ں���        
      
			CONSOLE_INFO("audiodev.pname = %s", audiodev.pname);
  
      LCD_ShowString(230, 43, strlen((char *)"                             ")*12+24, 24, 24, "                             ");
      LCD_ShowString(230, 43, strlen((char *)audiodev.wavfileinfo->fname)*12+24, 24, 24, audiodev.wavfileinfo->fname);

      audiodev.status|=1<<5;//����и���
      audiodev.status|=1<<4;//������ڲ������� 

      res = audio_play_song(audiodev.pname); //���������Ƶ�ļ�
      if(res == AP_OK) {  // �����������
        if((audiodev.status&(1<<6))==0)//����ֹ����
        {
            //˳�򲥷�
            if(audiodev.curindex<(audiodev.mfilenum-1))
              audiodev.curindex++;
            else 
              audiodev.curindex=0;
        }else 
          break; 
      }else if(res == AP_OVER) {    // ����������ŵ�(��һ������һ��)
        if((audiodev.status >> 6) == 1)// // ���������������ţ�������Ҫɾ�������
				{
          CONSOLE_INFO("�����˳����ֲ���������");
					break;
				}else
          CONSOLE_INFO("���󲥷���һ������һ�� = %d",audiodev.curindex);
      }
    }/* while(1) */
    
    audiodev.status&=~(1<<6);	//����Ѿ��ɹ���ֹ����
	  audiodev.status&=~(1<<4);	//��������ֲ���
		break;
  }/* while (res == FR_OK) */

  CONSOLE_INFO("�ͷ��ڴ� mfindextbl wavfileinfo pname");
  OS_free(SRAMIN, audiodev.mfindextbl);
  OS_free(SRAMIN, audiodev.wavfileinfo);
  OS_free(SRAMIN, audiodev.pname); //�ͷ��ڴ�

  return AP_OVER;
}

/**
 * @description: ����ֹͣaudio����
 * @param {__audiodev} *audiodevx audio�ṹ��
 * @return {*}
 */
void audio_stop_req(__audiodev *audiodevx)
{
	// while(audiodevx->status&(1<<4))	//�ȴ���ֹ���ųɹ�  
	// {
		audiodevx->status&=~(1<<1);	//�����������,���˳����ڲ��ŵĽ��� 
		audiodevx->status|=1<<6;	//������ֹ����,ֹͣ�Զ�ѭ��/�������
	// 	HAL_Delay(10);
	// };
  CONSOLE_INFO("�ȴ���ֹ���ųɹ�");
}   
/**
 * @description: ��������
 * @param {uint8_t} vol ����ֵ
 * @return {*}
 */
void app_wm8978_volset(uint8_t vol)
{
  if (vol > 63)
    vol = 63;
  if (wm8978set.speakersw)
    BSP_WM8978_SPKvol_Set(vol); //��������
  else
    BSP_WM8978_SPKvol_Set(0); //�ر�����

  BSP_WM8978_HPvol_Set(vol, vol);
}
//�õ�path·����,Ŀ���ļ����ܸ��� ��ȡ�ļ���
//path:·��
//����ֵ:����Ч�ļ���
uint16_t audio_get_tnum(uint8_t *path, uint8_t **name)
{
  uint8_t res;
  uint16_t rval = 0;
  DIR tdir;          //��ʱĿ¼
  FILINFO tfileinfo; //��ʱ�ļ���Ϣ
  uint8_t *fn;

  res = f_opendir(&tdir, (const TCHAR *)path); //��Ŀ¼
  Printf_File_Error_Msg(res);
  if (res == FR_OK)
  {
    while (1) //��ѯ�ܵ���Ч�ļ���
    {
      res = f_readdir(&tdir, &tfileinfo); //��ȡĿ¼�µ�һ���ļ�
      if (res != FR_OK || tfileinfo.fname[0] == 0)
        break; //������/��ĩβ��,�˳�
      CONSOLE_INFO("tfileinfo.fname: %s", tfileinfo.fname);

      fn = (uint8_t *)tfileinfo.fname;

      res = exf_FsTypetell((uint8_t *)tfileinfo.fname);
      CONSOLE_INFO("Music type: 0x%x", res);

      if (res == T_WAV) //ȡ����λ,�����ǲ��������ļ�
      {
        if (name != NULL)
          strcpy((char *)name[rval], (char *)fn); //�����ļ���
        rval++;                                   //��Ч�ļ�������1
      }
      else if (res == 0xFF)
      {
        CONSOLE_ERROR("���������ļ�");
      }
    }
  }
  else{
    Printf_File_Error_Msg(res);
    CONSOLE_ERROR("���ļ���ʧ��");
  }
  return rval;
}

//��ʼ��Ƶ����
void audio_start(void)
{
  audiodev.status|=1<<1;		//��������
	audiodev.status|=1<<0;		//����ͣ״̬
  BSP_I2S_Play_Start();
}
//�ر���Ƶ����
void audio_stop(void)
{
  audiodev.status&=~(1<<0);	//��ͣ����
	audiodev.status&=~(1<<1);	//��������
  BSP_I2S_Play_Stop();
}
