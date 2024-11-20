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

__wavctrl wavctrl;		//WAV���ƽṹ��
vu8 wavtransferend = 0; //i2s������ɱ�־
vu8 wavwitchbuf = 0;	//i2sbufxָʾ��־

//WAV������ʼ��
//fname:�ļ�·��+�ļ���
//wavx:wav ��Ϣ��Žṹ��ָ��
//����ֵ:0,�ɹ�;1,���ļ�ʧ��;2,��WAV�ļ�;3,DATA����δ�ҵ�.
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

	if (ftemp && buf) //�ڴ�����ɹ�
	{
		CONSOLE_INFO("�ڴ�����ɹ�");
		res = f_open(ftemp, (TCHAR *)fname, FA_READ); //���ļ�
		if (res == FR_OK)
		{
			f_read(ftemp, buf, 512, &br);	//��ȡ512�ֽ�������
			riff = (ChunkRIFF *)buf;		//��ȡRIFF��
			if (riff->Format == 0X45564157) //��WAV�ļ�
			{
				CONSOLE_INFO("��WAV�ļ�");
				fmt = (ChunkFMT *)(buf + 12);						 //��ȡFMT��
				fact = (ChunkFACT *)(buf + 12 + 8 + fmt->ChunkSize); //��ȡFACT��
				if (fact->ChunkID == 0X74636166 || fact->ChunkID == 0X5453494C)
					wavx->datastart = 12 + 8 + fmt->ChunkSize + 8 + fact->ChunkSize; //����fact/LIST���ʱ��(δ����)
				else
					wavx->datastart = 12 + 8 + fmt->ChunkSize;
				data = (ChunkDATA *)(buf + wavx->datastart); //��ȡDATA��
				if (data->ChunkID == 0X61746164)			 //�����ɹ�!
				{
					wavx->audioformat = fmt->AudioFormat; //��Ƶ��ʽ
					wavx->nchannels = fmt->NumOfChannels; //ͨ����
					wavx->samplerate = fmt->SampleRate;	  //������
					wavx->bitrate = fmt->ByteRate * 8;	  //�õ�λ��
					wavx->blockalign = fmt->BlockAlign;	  //�����
					wavx->bps = fmt->BitsPerSample;		  //λ��,16/24/32λ

					wavx->datasize = data->ChunkSize;	   //���ݿ��С
					wavx->datastart = wavx->datastart + 8; //��������ʼ�ĵط�.
					CONSOLE_INFO("-----�����ɹ�-�ļ�����Ϣ����:-----");
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
					res = 3; //data����δ�ҵ�.
			}
			else
				res = 2; //��wav�ļ�
		}
		else
			res = 1; //���ļ�����
	}
	f_close(ftemp);
	OS_free(SRAMIN, ftemp); //�ͷ��ڴ�
	OS_free(SRAMIN, buf);
	return 0;
}

//���buf
//buf:������
//size:���������
//bits:λ��(16/24)
//����ֵ:���������ݸ���
uint32_t wav_buffill(uint8_t *buf, uint16_t size, uint8_t bits)
{
	uint16_t readlen = 0;
	uint32_t bread;
	uint16_t i;
	uint8_t *p;
	uint8_t res;
	if (bits == 24) //24bit��Ƶ,��Ҫ����һ��
	{
		readlen = (size / 4) * 3; //�˴�Ҫ��ȡ���ֽ���

		res = f_read(audiodev.file, audiodev.tbuf, readlen, (UINT *)&bread); //��ȡ����
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
		bread = (bread * 4) / 3; //����Ĵ�С.
	}
	else
	{
		res = f_read(audiodev.file, buf, size, (UINT *)&bread); //16bit��Ƶ,ֱ�Ӷ�ȡ����
		if(res != FR_OK)
		{
			CONSOLE_ERROR("f_read->FAILE");
			Printf_File_Error_Msg(res);
		}
		if (bread < size)								  //����������,����0
		{
			for (i = bread; i < size - bread; i++)
				buf[i] = 0;
		}
	}
	return bread;
}
//WAV����ʱ,I2S DMA����ص�����
void wav_i2s_dma_tx_callback(void)
{
	uint16_t i;
	if (DMA1_Stream4->CR & (1 << 19))
	{
		wavwitchbuf = 0;
		if ((audiodev.status & 0X01) == 0)
		{
			for (i = 0; i < WAV_I2S_TX_DMA_BUFSIZE; i++) //��ͣ
			{
				audiodev.i2sbuf1[i] = 0; //���0
			}
		}
	}
	else
	{
		wavwitchbuf = 1;
		if ((audiodev.status & 0X01) == 0)
		{
			for (i = 0; i < WAV_I2S_TX_DMA_BUFSIZE; i++) //��ͣ
			{
				audiodev.i2sbuf2[i] = 0; //���0
			}
		}
	}
	wavtransferend = 1;
}
//�õ���ǰ����ʱ��
//fx:�ļ�ָ��
//wavx:wav���ſ�����
void wav_get_curtime(FIL *fx, __wavctrl *wavx)
{
	long long fpos;
	wavx->totsec = wavx->datasize / (wavx->bitrate / 8); //�����ܳ���(��λ:��)
	fpos = fx->fptr - wavx->datastart;					 //�õ���ǰ�ļ����ŵ��ĵط�
	wavx->cursec = fpos * wavx->totsec / wavx->datasize; //��ǰ���ŵ��ڶ�������?
}

//��ʾ����ʱ��,������ ��Ϣ
//totsec;��Ƶ�ļ���ʱ�䳤��
//cursec:��ǰ����ʱ��
//bitrate:������(λ��)
void audio_msg_show(uint32_t totsec, uint32_t cursec, uint32_t bitrate)
{
	//	char Buf[30] = {0};
	static uint16_t playtime = 0XFFFF; //����ʱ����
	static uint32_t Circle_x = 0;	   // ��������Բ����������
	float x = cursec, y = totsec;

	/* ������ */
	if (playtime != cursec) //��Ҫ������ʾʱ��
	{
		playtime = cursec;

		CONSOLE_INFO("%02d:%02d/%02d:%02d", playtime / 60, playtime % 60, totsec / 60, totsec % 60);
		// sprintf(Buf, " %02d:%02d", playtime / 60, playtime % 60);
		// LCD_ShowString(324, 178, strlen(Buf)*12+24, 24, 24, (uint8_t *)Buf); // ��ʾ��ǰ����ʱ��

		Circle_x = (float)(x / y) * 600 + 100;

		// CONSOLE_INFO("totsec = %d, cursec = %d, Circle_x = %d", totsec, cursec, Circle_x);

		// ��������
		LCD_Fill(100, 415, Circle_x, 420, LIGHTGREEN);
	}
}

//����ĳ��WAV�ļ�
//fname:wav�ļ�·��.
//����ֵ:0,�����������
//[b7]:0,����״̬;1,����״̬
//[b6:0]:b7=0ʱ,��ʾ������
//       b7=1ʱ,��ʾ�д���(���ﲻ�ж��������,0X80~0XFF,�����Ǵ���)
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
		res = wav_decode_init(fname, &wavctrl); //�õ��ļ�����Ϣ
		if (res == 0)							//�����ļ��ɹ�
		{
			if (wavctrl.bps == 16)
			{
				BSP_WM8978_I2S_Cfg(2, 0);																			 //�����ֱ�׼,16λ���ݳ���
				BSP_I2S2_Init(I2S_STANDARD_PHILLIPS, I2S_MODE_MASTER_TX, I2S_CPOL_LOW, I2S_DATAFORMAT_16B_EXTENDED); //�����ֱ�׼,��������,ʱ�ӵ͵�ƽ��Ч,16λ��չ֡����
			}
			else if (wavctrl.bps == 24)
			{
				BSP_WM8978_I2S_Cfg(2, 2);																	//�����ֱ�׼,24λ���ݳ���
				BSP_I2S2_Init(I2S_STANDARD_PHILLIPS, I2S_MODE_MASTER_TX, I2S_CPOL_LOW, I2S_DATAFORMAT_24B); //�����ֱ�׼,��������,ʱ�ӵ͵�ƽ��Ч,24λ��չ֡����
			}

			CONSOLE_INFO("���ò����ʣ�%d", wavctrl.samplerate);
			BSP_I2S2_SampleRate_Set(wavctrl.samplerate); //���ò�����

			BSP_I2S2_TX_DMA_Init(audiodev.i2sbuf1, audiodev.i2sbuf2, WAV_I2S_TX_DMA_BUFSIZE / 2); //����TX DMA
																								  //			i2s_tx_callback=wav_i2s_dma_tx_callback;			//�ص�����ָwav_i2s_dma_callback
			audio_stop();
			res = f_open(audiodev.file, (TCHAR *)fname, FA_READ); //���ļ�
			if (res == 0)
			{
				CONSOLE_INFO("����Ƶ�ļ��ɹ�, ��ʼ����");
				f_lseek(audiodev.file, wavctrl.datastart); //�����ļ�ͷ
				fillnum = wav_buffill(audiodev.i2sbuf1, WAV_I2S_TX_DMA_BUFSIZE, wavctrl.bps);
				fillnum = wav_buffill(audiodev.i2sbuf2, WAV_I2S_TX_DMA_BUFSIZE, wavctrl.bps);
				audio_start();
				while (res == 0)
				{
					while (wavtransferend == 0)
					{
						HAL_Delay(5); //�ȴ�wav�������;
					}
					wavtransferend = 0;
					if (wavwitchbuf)
						fillnum = wav_buffill(audiodev.i2sbuf2, WAV_I2S_TX_DMA_BUFSIZE, wavctrl.bps); //���buf2
					else
						fillnum = wav_buffill(audiodev.i2sbuf1, WAV_I2S_TX_DMA_BUFSIZE, wavctrl.bps); //���buf1

					while (audiodev.status & (1 << 1)) //����������
					{
						wav_get_curtime(audiodev.file, &wavctrl); //�õ���ʱ��͵�ǰ���ŵ�ʱ��
						audio_msg_show(wavctrl.totsec, wavctrl.cursec, wavctrl.bitrate);

						if (audiodev.status & 0X01)
							break; //û�а�����ͣ
						else{

							HAL_Delay(1000);
						}
					}
					if (fillnum != WAV_I2S_TX_DMA_BUFSIZE) // �������
					{
						CONSOLE_INFO("���������������");
						// ��ս���������
						LCD_Fill(100, 415, 700, 420, WHITE);
						res = AP_OK;
						break;
					}
					if (!(audiodev.status & (1 << 1)))
					{ // �����������
						CONSOLE_INFO("�����������1");
						// ��ս���������
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
	OS_free(SRAMIN, audiodev.tbuf);	   //�ͷ��ڴ�
	OS_free(SRAMIN, audiodev.i2sbuf1); //�ͷ��ڴ�
	OS_free(SRAMIN, audiodev.i2sbuf2); //�ͷ��ڴ�
	OS_free(SRAMIN, audiodev.file);	   //�ͷ��ڴ�
	CONSOLE_INFO("��ʼ�ͷ��ڴ�, tbuf i2sbuf1 i2sbuf2 file");
	return res;
}
