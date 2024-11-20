/*
 * @Author: your name
 * @Date: 2021-07-07 15:47:23
 * @LastEditTime: 2021-07-21 11:43:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\OS_Malloc.h
 */
#ifndef __OS_MALLOC_H
#define __OS_MALLOC_H

#include "main.h"

#ifndef NULL
#define NULL 0
#endif

//���������ڴ��
#define SRAMIN	 0		//�ڲ��ڴ��
#define SRAMEX   1		//�ⲿ�ڴ��
#define SRAMCCM  2		//CCM�ڴ��(�˲���SRAM����CPU���Է���!!!)
#define SRAMBANK 	3	//����֧�ֵ�SRAM����.	

//mem1�ڴ�����趨.mem1��ȫ�����ڲ�SRAM����.
#define MEM1_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM1_MAX_SIZE			60 *1024  						//�������ڴ� 90K
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//�ڴ���С

//mem2�ڴ�����趨.mem2���ڴ�ش����ⲿSRAM����
#define MEM2_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM2_MAX_SIZE			960 *1024  						//�������ڴ�960K
#define MEM2_ALLOC_TABLE_SIZE	MEM2_MAX_SIZE/MEM2_BLOCK_SIZE 	//�ڴ���С

//mem3�ڴ�����趨.mem3����CCM,���ڹ���CCM(�ر�ע��,�ⲿ��SRAM,��CPU���Է���!!)
#define MEM3_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM3_MAX_SIZE			60 *1024  						//�������ڴ�60K
#define MEM3_ALLOC_TABLE_SIZE	MEM3_MAX_SIZE/MEM3_BLOCK_SIZE 	//�ڴ���С

////////////////////////////////////////////////////////////////////////////////
//�û����ú���
void OS_mem_init(uint8_t memx);				//�ڴ�����ʼ������(��/�ڲ�����)
void OS_free(uint8_t memx,void *ptr);  			//�ڴ��ͷ�(�ⲿ����)
void *OS_malloc(uint8_t memx,uint32_t size);			//�ڴ����(�ⲿ����)
void *OS_realloc(uint8_t memx,void *ptr,uint32_t size);//���·����ڴ�(�ⲿ����)
void OS_memset(void *s,uint8_t c,uint32_t count);	//�����ڴ�
void OS_memcpy(void *des,void *src,uint32_t n);//�����ڴ�
uint8_t OS_mem_perused(uint8_t memx);				//����ڴ�ʹ����(��/�ڲ�����)
#endif // !__OS_MALLOC_H


