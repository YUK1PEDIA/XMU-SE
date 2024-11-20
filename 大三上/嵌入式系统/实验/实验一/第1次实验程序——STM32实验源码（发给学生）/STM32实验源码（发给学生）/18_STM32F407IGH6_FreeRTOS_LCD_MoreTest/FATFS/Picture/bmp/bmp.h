/*
 * @Author: your name
 * @Date: 2021-07-01 18:31:49
 * @LastEditTime: 2021-07-21 09:25:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\F407_Multi_core_testing\UserFunctions\Picture\bmp.h
 */
#ifndef __BMP_H__
#define __BMP_H__

#include "main.h"


//////////////////////////////////////////�û�������///////////////////////////////
#define BMP_USE_MALLOC		1 		//�����Ƿ�ʹ��malloc,��������ѡ��ʹ��malloc
#define BMP_DBUF_SIZE		2048	//����bmp��������Ĵ�С(����ӦΪLCD���*3)
//////////////////////////////////////////////END/////////////////////////////////

//BMP��Ϣͷ
typedef __packed struct
{
    uint32_t biSize ;		   	//˵��BITMAPINFOHEADER�ṹ����Ҫ��������
    long  biWidth ;		   	//˵��ͼ��Ŀ�ȣ�������Ϊ��λ 
    long  biHeight ;	   	//˵��ͼ��ĸ߶ȣ�������Ϊ��λ 
    uint16_t  biPlanes ;	   		//ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1 
    uint16_t  biBitCount ;	   	//˵��������/���أ���ֵΪ1��4��8��16��24����32
    uint32_t biCompression ;  	//˵��ͼ������ѹ�������͡���ֵ����������ֵ֮һ��
	//BI_RGB��û��ѹ����
	//BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��  
    //BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
  	//BI_BITFIELDS��ÿ�����صı�����ָ�������������
    uint32_t biSizeImage ;		//˵��ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0  
    long  biXPelsPerMeter ;	//˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ
    long  biYPelsPerMeter ;	//˵����ֱ�ֱ��ʣ�������/�ױ�ʾ
    uint32_t biClrUsed ;	  	 	//˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
    uint32_t biClrImportant ; 	//˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ�� 
}BITMAPINFOHEADER ;
//BMPͷ�ļ�
typedef __packed struct
{
    uint16_t  bfType ;     //�ļ���־.ֻ��'BM',����ʶ��BMPλͼ����
    uint32_t  bfSize ;	  //�ļ���С,ռ�ĸ��ֽ�
    uint16_t  bfReserved1 ;//����
    uint16_t  bfReserved2 ;//����
    uint32_t  bfOffBits ;  //���ļ���ʼ��λͼ����(bitmap data)��ʼ֮��ĵ�ƫ����
}BITMAPFILEHEADER ;
//��ɫ�� 
typedef __packed struct 
{
    uint8_t rgbBlue ;    //ָ����ɫǿ��
    uint8_t rgbGreen ;	//ָ����ɫǿ�� 
    uint8_t rgbRed ;	  	//ָ����ɫǿ�� 
    uint8_t rgbReserved ;//����������Ϊ0 
}RGBQUAD ;
//λͼ��Ϣͷ
typedef __packed struct
{ 
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;  
	uint32_t RGB_MASK[3];			//��ɫ�����ڴ��RGB����.
	//RGBQUAD bmiColors[256];  
}BITMAPINFO; 
typedef RGBQUAD * LPRGBQUAD;//��ɫ��  

//ͼ������ѹ��������
#define BI_RGB	 		0  //û��ѹ��.RGB 5,5,5.
#define BI_RLE8 		1  //ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��
#define BI_RLE4 		2  //ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
#define BI_BITFIELDS 	3  //ÿ�����صı�����ָ�������������  
		       
uint16_t pic_get_tnum(uint8_t *path);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BMP����뺯��
uint8_t stdbmp_decode(const uint8_t *filename);
uint8_t minibmp_decode(uint8_t *filename,uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t acolor,uint8_t mode);//�ߴ�С��240*320��bmpͼƬ����.
uint8_t bmp_encode(uint8_t *filename,uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t mode);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif

