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
//音乐播放控制器
__audiodev audiodev = {0};
uint8_t *music_name_array[50]; //保存路径下音频文件名

// uint8_t 					current_num=0;//当前播放的文件
// uint8_t *pname = 0;     // 音乐文件的名字

//WM8978默认参数
_wm8978_obj wm8978set =
    {
        .mvol = 80, //音量:50
        0,
        0,
        0,
        0,
        0, //频率标志设为0
        0,
        0,
        0,
        0,
        0,              //中心频率增益表全0
        .d3 = 0,        //3D效果为0
        .speakersw = 1, //开启板载喇叭
        .saveflag = 0,  // 保存标志,0X0A,保存过了;其他,还从未保存
};
//显示曲目索引
//index:当前索引
//total:总文件数
void audio_index_show(uint16_t index, uint16_t total)
{
  //显示当前曲目的索引,及总曲目数
  LCD_ShowxNum(60 + 0, 230, index, 3, 16, 0X80); //索引
  LCD_ShowChar(60 + 24, 230, '/', 16, 0);
  LCD_ShowxNum(60 + 32, 230, total, 3, 16, 0X80); //总曲目
}
//播放某个音频文件
uint8_t audio_play_song(uint8_t* fname)
{
	uint8_t res;  
	res=exf_FsTypetell(fname); 
	switch(res)
	{
		case T_WAV:
			res=wav_play_song(fname);
			break;
		default://其他文件,自动跳转到下一曲
			CONSOLE_INFO("can't play:%s",fname);
			break;
	}
	return res;
}
//音乐播放器
uint8_t audio_play(void)
{  
  uint8_t res = 0;
  DIR wavdir;                  //目录
  uint32_t temp;
	FATFS DiskFatFs;

  audiodev.wavfileinfo = (FILINFO *)OS_malloc(SRAMIN, sizeof(FILINFO)); //申请内存
  audiodev.pname = OS_malloc(SRAMIN, _MAX_LFN * 2 + 1);                 //为带路径的文件名分配内存
  audiodev.mfindextbl = OS_malloc(SRAMIN, 4 * audiodev.mfilenum);     //申请4*totwavnum个字节的内存,用于存放音乐文件off block索引

  while (!audiodev.wavfileinfo || !audiodev.pname || !audiodev.mfindextbl) //内存分配出错
  {
    CONSOLE_ERROR("内存分配失败!");
    HAL_Delay(1000);
  }
   
  // 记录索引值
  res = f_opendir(&wavdir, (char *)audiodev.path); //打开目录
  if (res == FR_OK)
  {
    audiodev.curindex = 0; //当前索引为0
   
    while (1)              //全部查询一遍
    {
      temp = wavdir.dptr;                    //记录当前index
      res = f_readdir(&wavdir, audiodev.wavfileinfo); //读取目录下的一个文件
      if (res != FR_OK || audiodev.wavfileinfo->fname[0] == 0)
        break; //错误了/到末尾了,退出
         
      res = exf_FsTypetell((uint8_t *)audiodev.wavfileinfo->fname);
         
      if ((res & 0XF0) == 0X40) //取高四位,看看是不是音乐文件
      {
        audiodev.mfindextbl[audiodev.curindex] = temp; //记录索引
        audiodev.curindex++;
      }
    }
  }
  f_closedir(&wavdir);
   

  res = f_opendir(&wavdir, (char *)audiodev.path);
  audiodev.curindex = 0; //当前索引为0
	audiodev.status|=1<<4;//标记正在播放音乐
  while (res == FR_OK) //打开文件夹成功
  {
    while(1)
    {
      CONSOLE_INFO("audiodev.curindex = %d",audiodev.curindex);
      dir_sdi(&wavdir, audiodev.mfindextbl[audiodev.curindex]); //改变当前目录索引
      res = f_readdir(&wavdir, audiodev.wavfileinfo);             //读取目录下的一个文件
      if (res != FR_OK || audiodev.wavfileinfo->fname[0] == 0)
        break;                                                 //错误了/到末尾了,退出
      strcpy((char *)audiodev.pname, "0:/MUSIC/");                      //复制路径(目录)
      strcat((char *)audiodev.pname, (const char *)audiodev.wavfileinfo->fname); //将文件名接在后面        
      
			CONSOLE_INFO("audiodev.pname = %s", audiodev.pname);
  
      LCD_ShowString(230, 43, strlen((char *)"                             ")*12+24, 24, 24, "                             ");
      LCD_ShowString(230, 43, strlen((char *)audiodev.wavfileinfo->fname)*12+24, 24, 24, audiodev.wavfileinfo->fname);

      audiodev.status|=1<<5;//标记切歌了
      audiodev.status|=1<<4;//标记正在播放音乐 

      res = audio_play_song(audiodev.pname); //播放这个音频文件
      if(res == AP_OK) {  // 正常播放完成
        if((audiodev.status&(1<<6))==0)//不终止播放
        {
            //顺序播放
            if(audiodev.curindex<(audiodev.mfilenum-1))
              audiodev.curindex++;
            else 
              audiodev.curindex=0;
        }else 
          break; 
      }else if(res == AP_OVER) {    // 请求结束播放的(上一曲、下一曲)
        if((audiodev.status >> 6) == 1)// // 如果是请求结束播放，并且是要删除任务的
				{
          CONSOLE_INFO("正在退出音乐播放器任务");
					break;
				}else
          CONSOLE_INFO("请求播放上一曲或下一曲 = %d",audiodev.curindex);
      }
    }/* while(1) */
    
    audiodev.status&=~(1<<6);	//标记已经成功终止播放
	  audiodev.status&=~(1<<4);	//标记无音乐播放
		break;
  }/* while (res == FR_OK) */

  CONSOLE_INFO("释放内存 mfindextbl wavfileinfo pname");
  OS_free(SRAMIN, audiodev.mfindextbl);
  OS_free(SRAMIN, audiodev.wavfileinfo);
  OS_free(SRAMIN, audiodev.pname); //释放内存

  return AP_OVER;
}

/**
 * @description: 请求停止audio播放
 * @param {__audiodev} *audiodevx audio结构体
 * @return {*}
 */
void audio_stop_req(__audiodev *audiodevx)
{
	// while(audiodevx->status&(1<<4))	//等待终止播放成功  
	// {
		audiodevx->status&=~(1<<1);	//请求结束播放,以退出正在播放的进程 
		audiodevx->status|=1<<6;	//请求终止播放,停止自动循环/随机播放
	// 	HAL_Delay(10);
	// };
  CONSOLE_INFO("等待终止播放成功");
}   
/**
 * @description: 音量设置
 * @param {uint8_t} vol 音量值
 * @return {*}
 */
void app_wm8978_volset(uint8_t vol)
{
  if (vol > 63)
    vol = 63;
  if (wm8978set.speakersw)
    BSP_WM8978_SPKvol_Set(vol); //开启喇叭
  else
    BSP_WM8978_SPKvol_Set(0); //关闭喇叭

  BSP_WM8978_HPvol_Set(vol, vol);
}
//得到path路径下,目标文件的总个数 获取文件名
//path:路径
//返回值:总有效文件数
uint16_t audio_get_tnum(uint8_t *path, uint8_t **name)
{
  uint8_t res;
  uint16_t rval = 0;
  DIR tdir;          //临时目录
  FILINFO tfileinfo; //临时文件信息
  uint8_t *fn;

  res = f_opendir(&tdir, (const TCHAR *)path); //打开目录
  Printf_File_Error_Msg(res);
  if (res == FR_OK)
  {
    while (1) //查询总的有效文件数
    {
      res = f_readdir(&tdir, &tfileinfo); //读取目录下的一个文件
      if (res != FR_OK || tfileinfo.fname[0] == 0)
        break; //错误了/到末尾了,退出
      CONSOLE_INFO("tfileinfo.fname: %s", tfileinfo.fname);

      fn = (uint8_t *)tfileinfo.fname;

      res = exf_FsTypetell((uint8_t *)tfileinfo.fname);
      CONSOLE_INFO("Music type: 0x%x", res);

      if (res == T_WAV) //取高四位,看看是不是音乐文件
      {
        if (name != NULL)
          strcpy((char *)name[rval], (char *)fn); //保存文件名
        rval++;                                   //有效文件数增加1
      }
      else if (res == 0xFF)
      {
        CONSOLE_ERROR("不是音乐文件");
      }
    }
  }
  else{
    Printf_File_Error_Msg(res);
    CONSOLE_ERROR("打开文件夹失败");
  }
  return rval;
}

//开始音频播放
void audio_start(void)
{
  audiodev.status|=1<<1;		//开启播放
	audiodev.status|=1<<0;		//非暂停状态
  BSP_I2S_Play_Start();
}
//关闭音频播放
void audio_stop(void)
{
  audiodev.status&=~(1<<0);	//暂停播放
	audiodev.status&=~(1<<1);	//结束播放
  BSP_I2S_Play_Stop();
}
