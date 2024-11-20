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
 
//音乐播放操作结果定义
typedef enum {
	AP_OK=0X00,				//正常播放完成
	AP_NEXT,				//播放下一曲
	AP_PREV,				//播放上一曲
	AP_OVER,				//播放结束
	AP_ERR=0X80,			//播放有错误(没定义错误代码,仅仅表示出错) 
}APRESULT;

#define MM_BUFF_PATH_SIZE   40
#define MM_BUFF_NAME_SIZE   20

//音乐播放控制器
typedef __packed struct
{  
	//2个I2S解码的BUF
	uint8_t *i2sbuf1;
	uint8_t *i2sbuf2; 
	uint8_t *tbuf;			//零时数组
	FIL *file;			//音频文件指针 	
  	FILINFO *wavfileinfo; //文件信息
	uint32_t(*file_seek)(uint32_t);//文件快进快退函数 

	vu8 status;			//bit0:0,暂停播放;1,继续播放
						//bit1:0,结束播放;1,开启播放  
						//bit2~3:保留
						//bit4:0,无音乐播放;1,音乐播放中 (对外标记)		
						//bit5:0,无动作;1,执行了一次切歌操作(对外标记)
						//bit6:0,无动作;1,请求终止播放(但是不删除音频播放任务),处理完成后,播放任务自动清零该位
 						//bit7:0,音频播放任务已删除/请求删除;1,音频播放任务正在运行(允许继续执行)
	
	uint8_t mode;			//播放模式
								//0,全部循环;1,单曲循环;2,随机播放;
	
	uint8_t *path;			//当前文件夹路径
	uint8_t *name;			//当前播放的MP3歌曲名字
  	uint8_t *pname;
	uint16_t namelen;		//name所占的点数.
	uint16_t curnamepos;		//当前的偏移

	uint32_t totsec ;		//整首歌时长,单位:秒
	uint32_t cursec ;		//当前播放时长 
	uint32_t bitrate;	   	//比特率(位速)
	uint32_t samplerate;		//采样率 
	uint16_t bps;			//位数,比如16bit,24bit,32bit
	
	uint16_t curindex;		//当前播放的音频文件
	uint16_t mfilenum;		//音乐文件数目	    
	uint16_t *mfindextbl;	//音频文件索引表
	
}__audiodev; 
__packed typedef struct 
{							  
	uint8_t mvol;		//音量(耳机和喇叭一起调),范围:0~63
	uint8_t cfreq[5];	//中心频率选择数组,每个元素可选范围为0~3,且代表的频率各不相同 
					//[0]对应频率:80,105,135,175
					//[1]对应频率:230,300,385,500
					//[2]对应频率:650,850,1100,1400
					//[3]对应频率:1800,2400,3200,4100
					//[4]对应频率:5300,6900,9000,11700
	uint8_t freqval[5];	//中心频率增益表
	uint8_t d3;			//3d设置	
	uint8_t speakersw;	//板载喇叭开关,0,关闭;1,打开 
	uint8_t saveflag; 	//保存标志,0X0A,保存过了;其他,还从未保存	   
}_wm8978_obj;

extern __audiodev audiodev;	//音乐播放控制器
extern uint8_t  *music_name_array[50];		// 保存路径下音频文件名



uint8_t audio_play(void);
void app_wm8978_volset(uint8_t vol);
uint16_t audio_get_tnum(uint8_t *path,uint8_t** name);
void audio_start(void);
void audio_stop(void);
void audio_stop_req(__audiodev *audiodevx);

#endif // !__APP_AUDIO_H__
