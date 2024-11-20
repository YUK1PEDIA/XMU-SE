/*
 * @Author: your name
 * @Date: 2021-07-01 18:32:22
 * @LastEditTime: 2021-07-21 11:50:11
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\F407_Multi_core_testing\UserFunctions\Music\wav.c
 */
#include "APP_Audio.h"
#include "APP_Operate.h"
#include "APP_StartShow.h"

#include "wav.h"
#include "OS_malloc.h"
#include <stdio.h>
#include <string.h>

#include "BSP_lcd.h"
#include "BSP_wm8978.h"
#include "i2s.h"
#include "cmsis_os.h"

__wavctrl wavctrl;		//WAV控制结构体
vu8 wavtransferend = 0; //i2s传输完成标志
vu8 wavwitchbuf = 0;	//i2sbufx指示标志

//WAV解析初始化
//fname:文件路径+文件名
//wavx:wav 信息存放结构体指针
//返回值:0,成功;1,打开文件失败;2,非WAV文件;3,DATA区域未找到.
uint8_t wav_decode_init(uint8_t *fname, __wavctrl *wavx)
{
	FIL *ftemp = NULL;
	uint8_t *buf = NULL;
	uint32_t br = 0;
	uint8_t res = 0;

	ChunkRIFF *riff = NULL;
	ChunkFMT *fmt = NULL;
	ChunkFACT *fact = NULL;
	ChunkDATA *data = NULL;
	ftemp = (FIL *)OS_malloc(SRAMIN, sizeof(FIL));
	buf = OS_malloc(SRAMIN, 512);

	if (ftemp && buf) //内存申请成功
	{
		CONSOLE_INFO("内存申请成功");
		res = f_open(ftemp, (TCHAR *)fname, FA_READ); //打开文件
		if (res == FR_OK)
		{
			f_read(ftemp, buf, 512, &br);	//读取512字节在数据
			riff = (ChunkRIFF *)buf;		//获取RIFF块
			if (riff->Format == 0X45564157) //是WAV文件
			{
				CONSOLE_INFO("是WAV文件");
				fmt = (ChunkFMT *)(buf + 12);						 //获取FMT块
				fact = (ChunkFACT *)(buf + 12 + 8 + fmt->ChunkSize); //读取FACT块
				if (fact->ChunkID == 0X74636166 || fact->ChunkID == 0X5453494C)
					wavx->datastart = 12 + 8 + fmt->ChunkSize + 8 + fact->ChunkSize; //具有fact/LIST块的时候(未测试)
				else
					wavx->datastart = 12 + 8 + fmt->ChunkSize;
				data = (ChunkDATA *)(buf + wavx->datastart); //读取DATA块
				if (data->ChunkID == 0X61746164)			 //解析成功!
				{
					wavx->audioformat = fmt->AudioFormat; //音频格式
					wavx->nchannels = fmt->NumOfChannels; //通道数
					wavx->samplerate = fmt->SampleRate;	  //采样率
					wavx->bitrate = fmt->ByteRate * 8;	  //得到位速
					wavx->blockalign = fmt->BlockAlign;	  //块对齐
					wavx->bps = fmt->BitsPerSample;		  //位数,16/24/32位

					wavx->datasize = data->ChunkSize;	   //数据块大小
					wavx->datastart = wavx->datastart + 8; //数据流开始的地方.
					CONSOLE_INFO("-----解析成功-文件的信息如下:-----");
					CONSOLE_INFO("wavx->audioformat: %d", wavx->audioformat);
					CONSOLE_INFO("wavx->nchannels:   %d", wavx->nchannels);
					CONSOLE_INFO("wavx->samplerate:  %d", wavx->samplerate);
					CONSOLE_INFO("wavx->bitrate:     %d", wavx->bitrate);
					CONSOLE_INFO("wavx->blockalign:  %d", wavx->blockalign);
					CONSOLE_INFO("wavx->bps:         %d", wavx->bps);
					CONSOLE_INFO("wavx->datasize:    %d", wavx->datasize);
					CONSOLE_INFO("wavx->datastart:   %d", wavx->datastart);
				}
				else
					res = 3; //data区域未找到.
			}
			else
				res = 2; //非wav文件
		}
		else
			res = 1; //打开文件错误
	}
	f_close(ftemp);
	OS_free(SRAMIN, ftemp); //释放内存
	OS_free(SRAMIN, buf);
	return 0;
}

//填充buf
//buf:数据区
//size:填充数据量
//bits:位数(16/24)
//返回值:读到的数据个数
uint32_t wav_buffill(uint8_t *buf, uint16_t size, uint8_t bits)
{
	uint16_t readlen = 0;
	uint32_t bread;
	uint16_t i;
	uint8_t *p;
	uint8_t res;
	if (bits == 24) //24bit音频,需要处理一下
	{
		readlen = (size / 4) * 3; //此次要读取的字节数

		res = f_read(audiodev.file, audiodev.tbuf, readlen, (UINT *)&bread); //读取数据
		if(res != FR_OK)
		{
			CONSOLE_ERROR("f_read->FAILE");
			Printf_File_Error_Msg(res);
		}
		p = audiodev.tbuf;
		for (i = 0; i < size;)
		{
			buf[i++] = p[1];
			buf[i] = p[2];
			i += 2;
			buf[i++] = p[0];
			p += 3;
		}
		bread = (bread * 4) / 3; //填充后的大小.
	}
	else
	{
		res = f_read(audiodev.file, buf, size, (UINT *)&bread); //16bit音频,直接读取数据
		if(res != FR_OK)
		{
			CONSOLE_ERROR("f_read->FAILE");
			Printf_File_Error_Msg(res);
		}
		if (bread < size)								  //不够数据了,补充0
		{
			for (i = bread; i < size - bread; i++)
				buf[i] = 0;
		}
	}
	return bread;
}
//WAV播放时,I2S DMA传输回调函数
void wav_i2s_dma_tx_callback(void)
{
	uint16_t i;
	if (DMA1_Stream4->CR & (1 << 19))
	{
		wavwitchbuf = 0;
		if ((audiodev.status & 0X01) == 0)
		{
			for (i = 0; i < WAV_I2S_TX_DMA_BUFSIZE; i++) //暂停
			{
				audiodev.i2sbuf1[i] = 0; //填充0
			}
		}
	}
	else
	{
		wavwitchbuf = 1;
		if ((audiodev.status & 0X01) == 0)
		{
			for (i = 0; i < WAV_I2S_TX_DMA_BUFSIZE; i++) //暂停
			{
				audiodev.i2sbuf2[i] = 0; //填充0
			}
		}
	}
	wavtransferend = 1;
}
//得到当前播放时间
//fx:文件指针
//wavx:wav播放控制器
void wav_get_curtime(FIL *fx, __wavctrl *wavx)
{
	long long fpos;
	wavx->totsec = wavx->datasize / (wavx->bitrate / 8); //歌曲总长度(单位:秒)
	fpos = fx->fptr - wavx->datastart;					 //得到当前文件播放到的地方
	wavx->cursec = fpos * wavx->totsec / wavx->datasize; //当前播放到第多少秒了?
}

//显示播放时间,比特率 信息
//totsec;音频文件总时间长度
//cursec:当前播放时间
//bitrate:比特率(位速)
void audio_msg_show(uint32_t totsec, uint32_t cursec, uint32_t bitrate)
{
	//	char Buf[30] = {0};
	static uint16_t playtime = 0XFFFF; //播放时间标记
	static uint32_t Circle_x = 0;	   // 进度条中圆的中心坐标
	float x = cursec, y = totsec;

	/* 进度条 */
	if (playtime != cursec) //需要更新显示时间
	{
		playtime = cursec;

		CONSOLE_INFO("%02d:%02d/%02d:%02d", playtime / 60, playtime % 60, totsec / 60, totsec % 60);
		// sprintf(Buf, " %02d:%02d", playtime / 60, playtime % 60);
		// LCD_ShowString(324, 178, strlen(Buf)*12+24, 24, 24, (uint8_t *)Buf); // 显示当前播放时间

		Circle_x = (float)(x / y) * 600 + 100;

		// CONSOLE_INFO("totsec = %d, cursec = %d, Circle_x = %d", totsec, cursec, Circle_x);

		// 填充进度条
		LCD_Fill(100, 415, Circle_x, 420, LIGHTGREEN);
	}
}

//播放某个WAV文件
//fname:wav文件路径.
//返回值:0,正常播放完成
//[b7]:0,正常状态;1,错误状态
//[b6:0]:b7=0时,表示操作码
//       b7=1时,表示有错误(这里不判定具体错误,0X80~0XFF,都算是错误)
uint8_t wav_play_song(uint8_t *fname)
{
	uint8_t res;
	uint32_t fillnum;
	audiodev.file = (FIL *)OS_malloc(SRAMIN, sizeof(FIL));
	audiodev.i2sbuf1 = OS_malloc(SRAMIN, WAV_I2S_TX_DMA_BUFSIZE);
	audiodev.i2sbuf2 = OS_malloc(SRAMIN, WAV_I2S_TX_DMA_BUFSIZE);
	audiodev.tbuf = OS_malloc(SRAMIN, WAV_I2S_TX_DMA_BUFSIZE);
	// audiodev.file_seek=wav_file_seek;
	if (audiodev.file && audiodev.i2sbuf1 && audiodev.i2sbuf2 && audiodev.tbuf)
	{
		res = wav_decode_init(fname, &wavctrl); //得到文件的信息
		if (res == 0)							//解析文件成功
		{
			if (wavctrl.bps == 16)
			{
				BSP_WM8978_I2S_Cfg(2, 0);																			 //飞利浦标准,16位数据长度
				BSP_I2S2_Init(I2S_STANDARD_PHILLIPS, I2S_MODE_MASTER_TX, I2S_CPOL_LOW, I2S_DATAFORMAT_16B_EXTENDED); //飞利浦标准,主机发送,时钟低电平有效,16位扩展帧长度
			}
			else if (wavctrl.bps == 24)
			{
				BSP_WM8978_I2S_Cfg(2, 2);																	//飞利浦标准,24位数据长度
				BSP_I2S2_Init(I2S_STANDARD_PHILLIPS, I2S_MODE_MASTER_TX, I2S_CPOL_LOW, I2S_DATAFORMAT_24B); //飞利浦标准,主机发送,时钟低电平有效,24位扩展帧长度
			}

			CONSOLE_INFO("设置采样率：%d", wavctrl.samplerate);
			BSP_I2S2_SampleRate_Set(wavctrl.samplerate); //设置采样率

			BSP_I2S2_TX_DMA_Init(audiodev.i2sbuf1, audiodev.i2sbuf2, WAV_I2S_TX_DMA_BUFSIZE / 2); //配置TX DMA
																								  //			i2s_tx_callback=wav_i2s_dma_tx_callback;			//回调函数指wav_i2s_dma_callback
			audio_stop();
			res = f_open(audiodev.file, (TCHAR *)fname, FA_READ); //打开文件
			if (res == 0)
			{
				CONSOLE_INFO("打开音频文件成功, 开始传输");
				f_lseek(audiodev.file, wavctrl.datastart); //跳过文件头
				fillnum = wav_buffill(audiodev.i2sbuf1, WAV_I2S_TX_DMA_BUFSIZE, wavctrl.bps);
				fillnum = wav_buffill(audiodev.i2sbuf2, WAV_I2S_TX_DMA_BUFSIZE, wavctrl.bps);
				audio_start();
				while (res == 0)
				{
					while (wavtransferend == 0)
					{
						HAL_Delay(5); //等待wav传输完成;
					}
					wavtransferend = 0;
					if (wavwitchbuf)
						fillnum = wav_buffill(audiodev.i2sbuf2, WAV_I2S_TX_DMA_BUFSIZE, wavctrl.bps); //填充buf2
					else
						fillnum = wav_buffill(audiodev.i2sbuf1, WAV_I2S_TX_DMA_BUFSIZE, wavctrl.bps); //填充buf1

					while (audiodev.status & (1 << 1)) //正常播放中
					{
						wav_get_curtime(audiodev.file, &wavctrl); //得到总时间和当前播放的时间
						audio_msg_show(wavctrl.totsec, wavctrl.cursec, wavctrl.bitrate);

						if (audiodev.status & 0X01)
							break; //没有按下暂停
						else{

							HAL_Delay(1000);
						}
					}
					if (fillnum != WAV_I2S_TX_DMA_BUFSIZE) // 播放完成
					{
						CONSOLE_INFO("音乐正常播放完成");
						// 清空进度条区域
						LCD_Fill(100, 415, 700, 420, WHITE);
						res = AP_OK;
						break;
					}
					if (!(audiodev.status & (1 << 1)))
					{ // 请求结束播放
						CONSOLE_INFO("请求结束播放1");
						// 清空进度条区域
						LCD_Fill(100, 415, 700, 420, WHITE);
						res = AP_OVER;
						break;
					}
				}
				audio_stop();
			}
			else
				res = 0XFF;
		}
		else
			res = 0XFF;
	}
	else
		res = 0XFF;
	OS_free(SRAMIN, audiodev.tbuf);	   //释放内存
	OS_free(SRAMIN, audiodev.i2sbuf1); //释放内存
	OS_free(SRAMIN, audiodev.i2sbuf2); //释放内存
	OS_free(SRAMIN, audiodev.file);	   //释放内存
	CONSOLE_INFO("开始释放内存, tbuf i2sbuf1 i2sbuf2 file");
	return res;
}
