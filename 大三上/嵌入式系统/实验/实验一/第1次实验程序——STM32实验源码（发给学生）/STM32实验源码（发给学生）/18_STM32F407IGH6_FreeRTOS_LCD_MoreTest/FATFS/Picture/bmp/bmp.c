/*
 * @Author: your name
 * @Date: 2021-07-01 18:31:49
 * @LastEditTime: 2021-07-21 12:01:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\F407_Multi_core_testing\UserFunctions\Picture\bmp.c
 */
#include "bmp.h"
#include "piclib.h"
#include "ff.h"
#include "BSP_lcd.h"
#include "OS_malloc.h"
#include "Fun_FsExFunctions.h"
#include <string.h>

//��ʹ���ڴ����
#if BMP_USE_MALLOC == 0
FIL f_bfile;
uint8_t bmpreadbuf[BMP_DBUF_SIZE];
#endif

//�õ�path·����,Ŀ���ļ����ܸ���
//path:·��
//����ֵ:����Ч�ļ���
uint16_t pic_get_tnum(uint8_t *path)
{
	uint8_t res;
	uint16_t rval = 0;
	DIR tdir;												   //��ʱĿ¼
	FILINFO *tfileinfo;										   //��ʱ�ļ���Ϣ
	tfileinfo = (FILINFO *)OS_malloc(SRAMIN, sizeof(FILINFO)); //�����ڴ�
	res = f_opendir(&tdir, (const TCHAR *)path);			   //��Ŀ¼
	if (res == FR_OK && tfileinfo)
	{
		while (1) //��ѯ�ܵ���Ч�ļ���
		{
			res = f_readdir(&tdir, tfileinfo); //��ȡĿ¼�µ�һ���ļ�
			if (res != FR_OK || tfileinfo->fname[0] == 0)
				break; //������/��ĩβ��,�˳�
			res = exf_FsTypetell((uint8_t *)tfileinfo->fname);
			if ((res & 0XF0) == 0X50) //ȡ����λ,�����ǲ���ͼƬ�ļ�
			{
				rval++; //��Ч�ļ�������1
			}
		}
		f_closedir(&tdir);
	}
	OS_free(SRAMIN, tfileinfo); //�ͷ��ڴ�
	return rval;
}

//��׼��bmp����,����filename���BMP�ļ�
//�ٶȱȽ���.��Ҫ
//filename:����·�����ļ���
//����ֵ:0,�ɹ�;
//		 ����,������.
uint8_t stdbmp_decode(const uint8_t *filename)
{
	FIL *f_bmp;
	uint16_t br;

	uint16_t count;
	uint8_t rgb, color_byte;
	uint16_t x, y, color;
	uint16_t countpix = 0; //��¼����

	//x,y��ʵ������
	uint16_t realx = 0;
	uint16_t realy = 0;
	uint8_t yok = 1;
	uint8_t res;

	uint8_t *databuf;				  //���ݶ�ȡ��ŵ�ַ
	uint16_t readlen = BMP_DBUF_SIZE; //һ�δ�SD����ȡ���ֽ�������

	uint8_t *bmpbuf;		   //���ݽ����ַ
	uint8_t biCompression = 0; //��¼ѹ����ʽ

	uint16_t rowlen;  //ˮƽ�����ֽ���
	BITMAPINFO *pbmp; //��ʱָ��

#if BMP_USE_MALLOC == 1							//ʹ��malloc
	databuf = (uint8_t *)pic_memalloc(readlen); //����readlen�ֽڵ��ڴ�����
	if (databuf == NULL){
		CONSOLE_ERROR("databuf is failed");
		return PIC_MEM_ERR;					  //�ڴ�����ʧ��.
	}
	f_bmp = (FIL *)pic_memalloc(sizeof(FIL)); //����FIL�ֽڵ��ڴ�����
	if (f_bmp == NULL)						  //�ڴ�����ʧ��.
	{
		CONSOLE_ERROR("f_bmp is failed");
		pic_memfree(databuf);
		return PIC_MEM_ERR;
	}
#else //��ʹ��malloc
	databuf = bmpreadbuf;
	f_bmp = &f_bfile;
#endif
	res = f_open(f_bmp, (const TCHAR *)filename, FA_READ); //���ļ�
	if (res == 0)										   //�򿪳ɹ�.
	{
		f_read(f_bmp, databuf, readlen, (UINT *)&br);  //����readlen���ֽ�
		pbmp = (BITMAPINFO *)databuf;				   //�õ�BMP��ͷ����Ϣ
		count = pbmp->bmfHeader.bfOffBits;			   //����ƫ��,�õ����ݶεĿ�ʼ��ַ
		color_byte = pbmp->bmiHeader.biBitCount / 8;   //��ɫλ 16/24/32
		biCompression = pbmp->bmiHeader.biCompression; //ѹ����ʽ
		picinfo.ImgHeight = pbmp->bmiHeader.biHeight;  //�õ�ͼƬ�߶�
		picinfo.ImgWidth = pbmp->bmiHeader.biWidth;	   //�õ�ͼƬ���
		CONSOLE_INFO("PIC_INFO.color_byte = %d\r\n", color_byte);

		ai_draw_init(); //��ʼ�����ܻ�ͼ
		//ˮƽ���ر�����4�ı���!!
		if ((picinfo.ImgWidth * color_byte) % 4)
			rowlen = ((picinfo.ImgWidth * color_byte) / 4 + 1) * 4;
		else
			rowlen = picinfo.ImgWidth * color_byte;
		//��ʼ����BMP
		color = 0; //��ɫ���
		x = 0;
		y = picinfo.ImgHeight;
		rgb = 0;
		//���ڳߴ�С�ڵ����趨�ߴ��ͼƬ,���п��ٽ���
		realy = (y * picinfo.Div_Fac) >> 13;
		bmpbuf = databuf;
		while (1)
		{
			while (count < readlen) //��ȡһ��1024���� (SectorsPerClust ÿ��������)
			{
				if (color_byte == 3) //24λ��ɫͼ
				{
					switch (rgb)
					{
					case 0:
						color = bmpbuf[count] >> 3; //B
						break;
					case 1:
						color += ((uint16_t)bmpbuf[count] << 3) & 0X07E0; //G
						break;
					case 2:
						color += ((uint16_t)bmpbuf[count] << 8) & 0XF800; //R
						break;
					}
				}
				else if (color_byte == 2) //16λ��ɫͼ
				{
					switch (rgb)
					{
					case 0:
						if (biCompression == BI_RGB) //RGB:5,5,5
						{
							color = ((uint16_t)bmpbuf[count] & 0X1F);		  //R
							color += (((uint16_t)bmpbuf[count]) & 0XE0) << 1; //G
						}
						else //RGB:5,6,5
						{
							color = bmpbuf[count]; //G,B
						}
						break;
					case 1:
						if (biCompression == BI_RGB) //RGB:5,5,5
						{
							color += (uint16_t)bmpbuf[count] << 9; //R,G
						}
						else //RGB:5,6,5
						{
							color += (uint16_t)bmpbuf[count] << 8; //R,G
						}
						break;
					}
				}
				else if (color_byte == 4) //32λ��ɫͼ
				{
					switch (rgb)
					{
					case 0:
						color = bmpbuf[count] >> 3; //B
						break;
					case 1:
						color += ((uint16_t)bmpbuf[count] << 3) & 0X07E0; //G
						break;
					case 2:
						color += ((uint16_t)bmpbuf[count] << 8) & 0XF800; //R
						break;
					case 3:
						//alphabend=bmpbuf[count];//����ȡ  ALPHAͨ��
						break;
					}
				}
				else if (color_byte == 1) //8λɫ,��ʱ��֧��,��Ҫ�õ���ɫ��.
				{
				}
				rgb++;
				count++;
				if (rgb == color_byte) //ˮƽ�����ȡ��1���������ݺ���ʾ
				{
					if (x < picinfo.ImgWidth)
					{
						realx = (x * picinfo.Div_Fac) >> 13;	   //x��ʵ��ֵ
						if (is_element_ok(realx, realy, 1) && yok) //��������
						{
							pic_phy.draw_point(realx + picinfo.S_XOFF, realy + picinfo.S_YOFF - 1, color); //��ʾͼƬ
																										   //POINT_COLOR=color;
																										   //LCD_DrawPoint(realx+picinfo.S_XOFF,realy+picinfo.S_YOFF);
																										   //SRAMLCD.Draw_Point(realx+picinfo.S_XOFF,realy+picinfo.S_YOFF,color);
						}
					}
					x++; //x������һ������
					color = 0x00;
					rgb = 0;
				}
				countpix++;				//�����ۼ�
				if (countpix >= rowlen) //ˮƽ��������ֵ����.����
				{
					y--;
					if (y == 0)
						break;
					realy = (y * picinfo.Div_Fac) >> 13; //ʵ��yֵ�ı�
					if (is_element_ok(realx, realy, 0))
						yok = 1; //�˴����ı�picinfo.staticx,y��ֵ
					else
						yok = 0;
					x = 0;
					countpix = 0;
					color = 0x00;
					rgb = 0;
				}
			}
			res = f_read(f_bmp, databuf, readlen, (UINT *)&br); //����readlen���ֽ�
			if (br != readlen)
				readlen = br; //���һ������
			if (res || br == 0)
				break; //��ȡ����
			bmpbuf = databuf;
			count = 0;
		}
		f_close(f_bmp); //�ر��ļ�
	}
#if BMP_USE_MALLOC == 1 //ʹ��malloc
	pic_memfree(databuf);
	pic_memfree(f_bmp);
#endif
	return res; //BMP��ʾ����.
}
//С�ߴ��bmp����,����filename���BMP�ļ�
//filename:����·�����ļ���
//x,y,width,height:������С
//acolor:���ӵ�alphablend����ɫ(�������32λɫbmp��Ч!!!)
//mode:ģʽ(����bit5,�����ľ�ֻ��32λɫbmp��Ч!!!)
//     bit[7:6]:0,��ʹ��ͼƬ����͵�ɫalphablend;
//              1,��ͼƬ��acolor����alphablend,���Ҳ����ø��ӵ�͸����;
//              2,��ɫ,acolor,ͼƬ,һ�����alphablend;
//	   bit5:����
//     bit4~0:0~31,ʹ�ø���alphablend��͸���̶�
//����ֵ:0,�ɹ�;
//    ����,������.
uint8_t minibmp_decode(uint8_t *filename, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t acolor, uint8_t mode) //�ߴ�С��240*320��bmpͼƬ����.
{
	FIL *f_bmp;
	uint16_t br;
	uint8_t color_byte;
	uint16_t tx, ty, color;
	//tx,ty��ʵ������
	uint8_t res;
	uint16_t i, j;
	uint8_t *databuf;				  //���ݶ�ȡ��                                                                       �ŵ�ַ
	uint16_t readlen = BMP_DBUF_SIZE; //һ�δ�SD����ȡ���ֽ�������,����С��LCD���*3!!!

	uint8_t *bmpbuf;		   //���ݽ����ַ
	uint8_t biCompression = 0; //��¼ѹ����ʽ

	uint16_t rowcnt;	 //һ�ζ�ȡ������
	uint16_t rowlen;	 //ˮƽ�����ֽ���
	uint16_t rowpix = 0; //ˮƽ����������
	uint8_t rowadd;		 //ÿ������ֽ���

	uint16_t tmp_color;

	uint8_t alphabend = 0xff;	   //����͸��ɫΪ0����ȫ��͸��
	uint8_t alphamode = mode >> 6; //�õ�ģʽֵ,0/1/2
	BITMAPINFO *pbmp;			   //��ʱָ��
	//�õ�����ߴ�
	picinfo.S_Height = height;
	picinfo.S_Width = width;

#if BMP_USE_MALLOC == 1							//ʹ��malloc
	databuf = (uint8_t *)pic_memalloc(readlen); //����readlen�ֽڵ��ڴ�����
	if (databuf == NULL){//�ڴ�����ʧ��.
		CONSOLE_ERROR("databuf memalloc");
		return PIC_MEM_ERR;	
	}
						  
	CONSOLE_INFO("sizeof(FIL): %d", sizeof(FIL));
	
	f_bmp = (FIL *)pic_memalloc(sizeof(FIL)); //����FIL�ֽڵ��ڴ�����
	if (f_bmp == NULL)						  //�ڴ�����ʧ��.
	{
		pic_memfree(databuf);
		CONSOLE_ERROR("f_bmp memalloc");
		return PIC_MEM_ERR;
	}
#else
	databuf = bmpreadbuf;
	f_bmp = &f_bfile;
#endif
	res = f_open(f_bmp, (const TCHAR *)filename, FA_READ); //���ļ�
	if (res == 0)										   //�򿪳ɹ�.
	{
		f_read(f_bmp, databuf, sizeof(BITMAPINFO), (UINT *)&br); //����BITMAPINFO��Ϣ
		pbmp = (BITMAPINFO *)databuf;							 //�õ�BMP��ͷ����Ϣ
		color_byte = pbmp->bmiHeader.biBitCount / 8;			 //��ɫλ 16/24/32
		biCompression = pbmp->bmiHeader.biCompression;			 //ѹ����ʽ
		picinfo.ImgHeight = pbmp->bmiHeader.biHeight;			 //�õ�ͼƬ�߶�
		picinfo.ImgWidth = pbmp->bmiHeader.biWidth;				 //�õ�ͼƬ���

		CONSOLE_INFO("color_byte is %d", color_byte);

		//ˮƽ���ر�����4�ı���!!
		if ((picinfo.ImgWidth * color_byte) % 4)
			rowlen = ((picinfo.ImgWidth * color_byte) / 4 + 1) * 4;
		else
			rowlen = picinfo.ImgWidth * color_byte;
		rowadd = rowlen - picinfo.ImgWidth * color_byte; //ÿ������ֽ���
														 //��ʼ����BMP
		color = 0;										 //��ɫ���
		tx = 0;
		ty = picinfo.ImgHeight - 1;
		if (picinfo.ImgWidth <= picinfo.S_Width && picinfo.ImgHeight <= picinfo.S_Height)
		{
			rowcnt = readlen / rowlen;				   //һ�ζ�ȡ������
			readlen = rowcnt * rowlen;				   //һ�ζ�ȡ���ֽ���
			rowpix = picinfo.ImgWidth;				   //ˮƽ���������ǿ��
			f_lseek(f_bmp, pbmp->bmfHeader.bfOffBits); //ƫ�Ƶ�������ʼλ��
			while (1)
			{
				res = f_read(f_bmp, databuf, readlen, (UINT *)&br); //����readlen���ֽ�
				bmpbuf = databuf;									//�����׵�ַ
				if (br != readlen)
					rowcnt = br / rowlen; //���ʣ�µ�����
				if (color_byte == 3)	  //24λBMPͼƬ
				{
					for (j = 0; j < rowcnt; j++) //ÿ�ζ���������
					{
						for (i = 0; i < rowpix; i++) //дһ������
						{
							color = (*bmpbuf++) >> 3;						//B
							color += ((uint16_t)(*bmpbuf++) << 3) & 0X07E0; //G
							color += (((uint16_t)*bmpbuf++) << 8) & 0XF800; //R
							pic_phy.draw_point(x + tx, y + ty, color);		//��ʾͼƬ
							tx++;
						}
						bmpbuf += rowadd; //���������
						tx = 0;
						ty--;
					}
				}
				else if (color_byte == 2) //16λBMPͼƬ
				{
					for (j = 0; j < rowcnt; j++) //ÿ�ζ���������
					{
						if (biCompression == BI_RGB) //RGB:5,5,5
						{
							for (i = 0; i < rowpix; i++)
							{
								color = ((uint16_t)*bmpbuf & 0X1F);			  //R
								color += (((uint16_t)*bmpbuf++) & 0XE0) << 1; //G
								color += ((uint16_t)*bmpbuf++) << 9;		  //R,G
								pic_phy.draw_point(x + tx, y + ty, color);	  //��ʾͼƬ
								tx++;
							}
						}
						else //RGB 565
						{
							for (i = 0; i < rowpix; i++)
							{
								color = *bmpbuf++;						   //G,B
								color += ((uint16_t)*bmpbuf++) << 8;	   //R,G
								pic_phy.draw_point(x + tx, y + ty, color); //��ʾͼƬ
								tx++;
							}
						}
						bmpbuf += rowadd; //���������
						tx = 0;
						ty--;
					}
				}
				else if (color_byte == 4) //32λBMPͼƬ
				{
					for (j = 0; j < rowcnt; j++) //ÿ�ζ���������
					{
						for (i = 0; i < rowpix; i++)
						{
							color = (*bmpbuf++) >> 3;						//B
							color += ((uint16_t)(*bmpbuf++) << 3) & 0X07E0; //G
							color += (((uint16_t)*bmpbuf++) << 8) & 0XF800; //R
							alphabend = *bmpbuf++;							//ALPHAͨ��
							if (alphamode != 1)								//��Ҫ��ȡ��ɫ
							{
								tmp_color = pic_phy.read_point(x + tx, y + ty); //��ȡ��ɫ
								if (alphamode == 2)								//��Ҫ���ӵ�alphablend
								{
									tmp_color = piclib_alpha_blend(tmp_color, acolor, mode & 0X1F); //��ָ����ɫ����blend
								}
								color = piclib_alpha_blend(tmp_color, color, alphabend / 8); //�͵�ɫ����alphablend
							}
							else
								tmp_color = piclib_alpha_blend(acolor, color, alphabend / 8); //��ָ����ɫ����blend
							pic_phy.draw_point(x + tx, y + ty, color);						  //��ʾͼƬ
							tx++;															  //x������һ������
						}
						bmpbuf += rowadd; //���������
						tx = 0;
						ty--;
					}
				}
				if (br != readlen || res)
					break;
			}
		}
		f_close(f_bmp); //�ر��ļ�
	}
	else
		res = PIC_SIZE_ERR; //ͼƬ�ߴ����
#if BMP_USE_MALLOC == 1		//ʹ��malloc
	pic_memfree(databuf);
	pic_memfree(f_bmp);
#endif
	return res;
}
