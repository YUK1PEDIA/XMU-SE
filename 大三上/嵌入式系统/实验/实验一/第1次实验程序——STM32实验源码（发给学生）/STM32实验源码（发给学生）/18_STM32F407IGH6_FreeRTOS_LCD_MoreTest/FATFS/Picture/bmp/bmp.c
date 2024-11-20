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

//不使用内存分配
#if BMP_USE_MALLOC == 0
FIL f_bfile;
uint8_t bmpreadbuf[BMP_DBUF_SIZE];
#endif

//得到path路径下,目标文件的总个数
//path:路径
//返回值:总有效文件数
uint16_t pic_get_tnum(uint8_t *path)
{
	uint8_t res;
	uint16_t rval = 0;
	DIR tdir;												   //临时目录
	FILINFO *tfileinfo;										   //临时文件信息
	tfileinfo = (FILINFO *)OS_malloc(SRAMIN, sizeof(FILINFO)); //申请内存
	res = f_opendir(&tdir, (const TCHAR *)path);			   //打开目录
	if (res == FR_OK && tfileinfo)
	{
		while (1) //查询总的有效文件数
		{
			res = f_readdir(&tdir, tfileinfo); //读取目录下的一个文件
			if (res != FR_OK || tfileinfo->fname[0] == 0)
				break; //错误了/到末尾了,退出
			res = exf_FsTypetell((uint8_t *)tfileinfo->fname);
			if ((res & 0XF0) == 0X50) //取高四位,看看是不是图片文件
			{
				rval++; //有效文件数增加1
			}
		}
		f_closedir(&tdir);
	}
	OS_free(SRAMIN, tfileinfo); //释放内存
	return rval;
}

//标准的bmp解码,解码filename这个BMP文件
//速度比较慢.主要
//filename:包含路径的文件名
//返回值:0,成功;
//		 其他,错误码.
uint8_t stdbmp_decode(const uint8_t *filename)
{
	FIL *f_bmp;
	uint16_t br;

	uint16_t count;
	uint8_t rgb, color_byte;
	uint16_t x, y, color;
	uint16_t countpix = 0; //记录像素

	//x,y的实际坐标
	uint16_t realx = 0;
	uint16_t realy = 0;
	uint8_t yok = 1;
	uint8_t res;

	uint8_t *databuf;				  //数据读取存放地址
	uint16_t readlen = BMP_DBUF_SIZE; //一次从SD卡读取的字节数长度

	uint8_t *bmpbuf;		   //数据解码地址
	uint8_t biCompression = 0; //记录压缩方式

	uint16_t rowlen;  //水平方向字节数
	BITMAPINFO *pbmp; //临时指针

#if BMP_USE_MALLOC == 1							//使用malloc
	databuf = (uint8_t *)pic_memalloc(readlen); //开辟readlen字节的内存区域
	if (databuf == NULL){
		CONSOLE_ERROR("databuf is failed");
		return PIC_MEM_ERR;					  //内存申请失败.
	}
	f_bmp = (FIL *)pic_memalloc(sizeof(FIL)); //开辟FIL字节的内存区域
	if (f_bmp == NULL)						  //内存申请失败.
	{
		CONSOLE_ERROR("f_bmp is failed");
		pic_memfree(databuf);
		return PIC_MEM_ERR;
	}
#else //不使用malloc
	databuf = bmpreadbuf;
	f_bmp = &f_bfile;
#endif
	res = f_open(f_bmp, (const TCHAR *)filename, FA_READ); //打开文件
	if (res == 0)										   //打开成功.
	{
		f_read(f_bmp, databuf, readlen, (UINT *)&br);  //读出readlen个字节
		pbmp = (BITMAPINFO *)databuf;				   //得到BMP的头部信息
		count = pbmp->bmfHeader.bfOffBits;			   //数据偏移,得到数据段的开始地址
		color_byte = pbmp->bmiHeader.biBitCount / 8;   //彩色位 16/24/32
		biCompression = pbmp->bmiHeader.biCompression; //压缩方式
		picinfo.ImgHeight = pbmp->bmiHeader.biHeight;  //得到图片高度
		picinfo.ImgWidth = pbmp->bmiHeader.biWidth;	   //得到图片宽度
		CONSOLE_INFO("PIC_INFO.color_byte = %d\r\n", color_byte);

		ai_draw_init(); //初始化智能画图
		//水平像素必须是4的倍数!!
		if ((picinfo.ImgWidth * color_byte) % 4)
			rowlen = ((picinfo.ImgWidth * color_byte) / 4 + 1) * 4;
		else
			rowlen = picinfo.ImgWidth * color_byte;
		//开始解码BMP
		color = 0; //颜色清空
		x = 0;
		y = picinfo.ImgHeight;
		rgb = 0;
		//对于尺寸小于等于设定尺寸的图片,进行快速解码
		realy = (y * picinfo.Div_Fac) >> 13;
		bmpbuf = databuf;
		while (1)
		{
			while (count < readlen) //读取一簇1024扇区 (SectorsPerClust 每簇扇区数)
			{
				if (color_byte == 3) //24位颜色图
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
				else if (color_byte == 2) //16位颜色图
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
				else if (color_byte == 4) //32位颜色图
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
						//alphabend=bmpbuf[count];//不读取  ALPHA通道
						break;
					}
				}
				else if (color_byte == 1) //8位色,暂时不支持,需要用到颜色表.
				{
				}
				rgb++;
				count++;
				if (rgb == color_byte) //水平方向读取到1像素数数据后显示
				{
					if (x < picinfo.ImgWidth)
					{
						realx = (x * picinfo.Div_Fac) >> 13;	   //x轴实际值
						if (is_element_ok(realx, realy, 1) && yok) //符合条件
						{
							pic_phy.draw_point(realx + picinfo.S_XOFF, realy + picinfo.S_YOFF - 1, color); //显示图片
																										   //POINT_COLOR=color;
																										   //LCD_DrawPoint(realx+picinfo.S_XOFF,realy+picinfo.S_YOFF);
																										   //SRAMLCD.Draw_Point(realx+picinfo.S_XOFF,realy+picinfo.S_YOFF,color);
						}
					}
					x++; //x轴增加一个像素
					color = 0x00;
					rgb = 0;
				}
				countpix++;				//像素累加
				if (countpix >= rowlen) //水平方向像素值到了.换行
				{
					y--;
					if (y == 0)
						break;
					realy = (y * picinfo.Div_Fac) >> 13; //实际y值改变
					if (is_element_ok(realx, realy, 0))
						yok = 1; //此处不改变picinfo.staticx,y的值
					else
						yok = 0;
					x = 0;
					countpix = 0;
					color = 0x00;
					rgb = 0;
				}
			}
			res = f_read(f_bmp, databuf, readlen, (UINT *)&br); //读出readlen个字节
			if (br != readlen)
				readlen = br; //最后一批数据
			if (res || br == 0)
				break; //读取出错
			bmpbuf = databuf;
			count = 0;
		}
		f_close(f_bmp); //关闭文件
	}
#if BMP_USE_MALLOC == 1 //使用malloc
	pic_memfree(databuf);
	pic_memfree(f_bmp);
#endif
	return res; //BMP显示结束.
}
//小尺寸的bmp解码,解码filename这个BMP文件
//filename:包含路径的文件名
//x,y,width,height:开窗大小
//acolor:附加的alphablend的颜色(这个仅对32位色bmp有效!!!)
//mode:模式(除了bit5,其他的均只对32位色bmp有效!!!)
//     bit[7:6]:0,仅使用图片本身和底色alphablend;
//              1,仅图片和acolor进行alphablend,并且不适用附加的透明度;
//              2,底色,acolor,图片,一起进行alphablend;
//	   bit5:保留
//     bit4~0:0~31,使用附加alphablend的透明程度
//返回值:0,成功;
//    其他,错误码.
uint8_t minibmp_decode(uint8_t *filename, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t acolor, uint8_t mode) //尺寸小于240*320的bmp图片解码.
{
	FIL *f_bmp;
	uint16_t br;
	uint8_t color_byte;
	uint16_t tx, ty, color;
	//tx,ty的实际坐标
	uint8_t res;
	uint16_t i, j;
	uint8_t *databuf;				  //数据读取存                                                                       放地址
	uint16_t readlen = BMP_DBUF_SIZE; //一次从SD卡读取的字节数长度,不能小于LCD宽度*3!!!

	uint8_t *bmpbuf;		   //数据解码地址
	uint8_t biCompression = 0; //记录压缩方式

	uint16_t rowcnt;	 //一次读取的行数
	uint16_t rowlen;	 //水平方向字节数
	uint16_t rowpix = 0; //水平方向像素数
	uint8_t rowadd;		 //每行填充字节数

	uint16_t tmp_color;

	uint8_t alphabend = 0xff;	   //代表透明色为0，完全不透明
	uint8_t alphamode = mode >> 6; //得到模式值,0/1/2
	BITMAPINFO *pbmp;			   //临时指针
	//得到窗体尺寸
	picinfo.S_Height = height;
	picinfo.S_Width = width;

#if BMP_USE_MALLOC == 1							//使用malloc
	databuf = (uint8_t *)pic_memalloc(readlen); //开辟readlen字节的内存区域
	if (databuf == NULL){//内存申请失败.
		CONSOLE_ERROR("databuf memalloc");
		return PIC_MEM_ERR;	
	}
						  
	CONSOLE_INFO("sizeof(FIL): %d", sizeof(FIL));
	
	f_bmp = (FIL *)pic_memalloc(sizeof(FIL)); //开辟FIL字节的内存区域
	if (f_bmp == NULL)						  //内存申请失败.
	{
		pic_memfree(databuf);
		CONSOLE_ERROR("f_bmp memalloc");
		return PIC_MEM_ERR;
	}
#else
	databuf = bmpreadbuf;
	f_bmp = &f_bfile;
#endif
	res = f_open(f_bmp, (const TCHAR *)filename, FA_READ); //打开文件
	if (res == 0)										   //打开成功.
	{
		f_read(f_bmp, databuf, sizeof(BITMAPINFO), (UINT *)&br); //读出BITMAPINFO信息
		pbmp = (BITMAPINFO *)databuf;							 //得到BMP的头部信息
		color_byte = pbmp->bmiHeader.biBitCount / 8;			 //彩色位 16/24/32
		biCompression = pbmp->bmiHeader.biCompression;			 //压缩方式
		picinfo.ImgHeight = pbmp->bmiHeader.biHeight;			 //得到图片高度
		picinfo.ImgWidth = pbmp->bmiHeader.biWidth;				 //得到图片宽度

		CONSOLE_INFO("color_byte is %d", color_byte);

		//水平像素必须是4的倍数!!
		if ((picinfo.ImgWidth * color_byte) % 4)
			rowlen = ((picinfo.ImgWidth * color_byte) / 4 + 1) * 4;
		else
			rowlen = picinfo.ImgWidth * color_byte;
		rowadd = rowlen - picinfo.ImgWidth * color_byte; //每行填充字节数
														 //开始解码BMP
		color = 0;										 //颜色清空
		tx = 0;
		ty = picinfo.ImgHeight - 1;
		if (picinfo.ImgWidth <= picinfo.S_Width && picinfo.ImgHeight <= picinfo.S_Height)
		{
			rowcnt = readlen / rowlen;				   //一次读取的行数
			readlen = rowcnt * rowlen;				   //一次读取的字节数
			rowpix = picinfo.ImgWidth;				   //水平像素数就是宽度
			f_lseek(f_bmp, pbmp->bmfHeader.bfOffBits); //偏移到数据起始位置
			while (1)
			{
				res = f_read(f_bmp, databuf, readlen, (UINT *)&br); //读出readlen个字节
				bmpbuf = databuf;									//数据首地址
				if (br != readlen)
					rowcnt = br / rowlen; //最后剩下的行数
				if (color_byte == 3)	  //24位BMP图片
				{
					for (j = 0; j < rowcnt; j++) //每次读到的行数
					{
						for (i = 0; i < rowpix; i++) //写一行像素
						{
							color = (*bmpbuf++) >> 3;						//B
							color += ((uint16_t)(*bmpbuf++) << 3) & 0X07E0; //G
							color += (((uint16_t)*bmpbuf++) << 8) & 0XF800; //R
							pic_phy.draw_point(x + tx, y + ty, color);		//显示图片
							tx++;
						}
						bmpbuf += rowadd; //跳过填充区
						tx = 0;
						ty--;
					}
				}
				else if (color_byte == 2) //16位BMP图片
				{
					for (j = 0; j < rowcnt; j++) //每次读到的行数
					{
						if (biCompression == BI_RGB) //RGB:5,5,5
						{
							for (i = 0; i < rowpix; i++)
							{
								color = ((uint16_t)*bmpbuf & 0X1F);			  //R
								color += (((uint16_t)*bmpbuf++) & 0XE0) << 1; //G
								color += ((uint16_t)*bmpbuf++) << 9;		  //R,G
								pic_phy.draw_point(x + tx, y + ty, color);	  //显示图片
								tx++;
							}
						}
						else //RGB 565
						{
							for (i = 0; i < rowpix; i++)
							{
								color = *bmpbuf++;						   //G,B
								color += ((uint16_t)*bmpbuf++) << 8;	   //R,G
								pic_phy.draw_point(x + tx, y + ty, color); //显示图片
								tx++;
							}
						}
						bmpbuf += rowadd; //跳过填充区
						tx = 0;
						ty--;
					}
				}
				else if (color_byte == 4) //32位BMP图片
				{
					for (j = 0; j < rowcnt; j++) //每次读到的行数
					{
						for (i = 0; i < rowpix; i++)
						{
							color = (*bmpbuf++) >> 3;						//B
							color += ((uint16_t)(*bmpbuf++) << 3) & 0X07E0; //G
							color += (((uint16_t)*bmpbuf++) << 8) & 0XF800; //R
							alphabend = *bmpbuf++;							//ALPHA通道
							if (alphamode != 1)								//需要读取底色
							{
								tmp_color = pic_phy.read_point(x + tx, y + ty); //读取颜色
								if (alphamode == 2)								//需要附加的alphablend
								{
									tmp_color = piclib_alpha_blend(tmp_color, acolor, mode & 0X1F); //与指定颜色进行blend
								}
								color = piclib_alpha_blend(tmp_color, color, alphabend / 8); //和底色进行alphablend
							}
							else
								tmp_color = piclib_alpha_blend(acolor, color, alphabend / 8); //与指定颜色进行blend
							pic_phy.draw_point(x + tx, y + ty, color);						  //显示图片
							tx++;															  //x轴增加一个像素
						}
						bmpbuf += rowadd; //跳过填充区
						tx = 0;
						ty--;
					}
				}
				if (br != readlen || res)
					break;
			}
		}
		f_close(f_bmp); //关闭文件
	}
	else
		res = PIC_SIZE_ERR; //图片尺寸错误
#if BMP_USE_MALLOC == 1		//使用malloc
	pic_memfree(databuf);
	pic_memfree(f_bmp);
#endif
	return res;
}
