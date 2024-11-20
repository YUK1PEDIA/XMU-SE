/*
 * @Author: your name
 * @Date: 2021-07-07 15:47:16
 * @LastEditTime: 2021-07-15 10:53:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\OS_Malloc.c
 */
#include "OS_Malloc.h"
#include "cmsis_os.h"

/* �ڴ��(32�ֽڶ���) */
static __align(32) uint8_t mem1base[MEM1_MAX_SIZE];                                 //�ڲ�SRAM�ڴ��
static __align(32) uint8_t mem2base[MEM2_MAX_SIZE] __attribute__((at(0X68000000))); //�ⲿSRAM�ڴ��
static __align(32) uint8_t mem3base[MEM3_MAX_SIZE] __attribute__((at(0X10000000))); //�ڲ�CCM�ڴ��

/* �ڴ����� */
static uint16_t mem1mapbase[MEM1_ALLOC_TABLE_SIZE];                                                 //�ڲ�SRAM�ڴ��MAP
static uint16_t mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000 + MEM2_MAX_SIZE))); //�ⲿSRAM�ڴ��MAP
static uint16_t mem3mapbase[MEM3_ALLOC_TABLE_SIZE] __attribute__((at(0X10000000 + MEM3_MAX_SIZE))); //�ڲ�CCM�ڴ��MAP

/* �ڴ������� */
static const uint32_t memtblsize[SRAMBANK] = {MEM1_ALLOC_TABLE_SIZE, MEM2_ALLOC_TABLE_SIZE, MEM3_ALLOC_TABLE_SIZE}; //�ڴ���С
static const uint32_t memblksize[SRAMBANK] = {MEM1_BLOCK_SIZE, MEM2_BLOCK_SIZE, MEM3_BLOCK_SIZE};                   //�ڴ�ֿ��С
static const uint32_t memsize[SRAMBANK]    = {MEM1_MAX_SIZE, MEM2_MAX_SIZE, MEM3_MAX_SIZE};                            //�ڴ��ܴ�С

/* �ڴ������ */
struct _m_mallco_dev
{
  void (*init)(uint8_t);					//��ʼ��
  uint8_t (*perused)(uint8_t);		  	    	//�ڴ�ʹ����
  uint8_t 	*membase[SRAMBANK];				//�ڴ�� ����SRAMBANK��������ڴ�
  uint16_t *memmap[SRAMBANK]; 				//�ڴ����״̬��
  uint8_t  memrdy[SRAMBANK]; 				//�ڴ�����Ƿ����
};

/* �ڴ��������ʼ�� */
struct _m_mallco_dev mallco_dev =
{
  OS_mem_init,                           //�ڴ��ʼ��
  OS_mem_perused,                        //�ڴ�ʹ����
  mem1base, mem2base, mem3base,          //�ڴ��
  mem1mapbase, mem2mapbase, mem3mapbase, //�ڴ����״̬��
  0, 0, 0,                               //�ڴ����δ����
};

/**
 * @description: �ڴ����(�ڲ�����)
 * @param {uint8_t} memx �����ڴ��
 * @param {uint32_t} size Ҫ������ڴ��С(�ֽ�)
 * @return {uint32_t} 0XFFFFFFFF,�������;����,�ڴ�ƫ�Ƶ�ַ
 */
static uint32_t my_mem_malloc(uint8_t memx, uint32_t size)
{
  signed long offset = 0;
  uint32_t nmemb;     //��Ҫ���ڴ����
  uint32_t cmemb = 0; //�������ڴ����
  uint32_t i;
  if (!mallco_dev.memrdy[memx])
    mallco_dev.init(memx); //δ��ʼ��,��ִ�г�ʼ��
  if (size == 0)
    return 0XFFFFFFFF;             //����Ҫ����
  nmemb = size / memblksize[memx]; //��ȡ��Ҫ����������ڴ����
  if (size % memblksize[memx])
    nmemb++;
  for (offset = memtblsize[memx] - 1; offset >= 0; offset--) //���������ڴ������
  {
    if (!mallco_dev.memmap[memx][offset])
      cmemb++; //�������ڴ��������
    else
      cmemb = 0;        //�����ڴ������
    if (cmemb == nmemb) //�ҵ�������nmemb�����ڴ��
    {
      for (i = 0; i < nmemb; i++) //��ע�ڴ��ǿ�
      {
        mallco_dev.memmap[memx][offset + i] = nmemb;
      }
      return (offset * memblksize[memx]); //����ƫ�Ƶ�ַ
    }
  }
  return 0XFFFFFFFF; //δ�ҵ����Ϸ����������ڴ��
}


/**
 * @description: �ͷ��ڴ�(�ڲ�����)
 * @param {uint8_t} memx �����ڴ��
 * @param {uint32_t} offset �ڴ��ַƫ��
 * @return {uint8_t} 0,�ͷųɹ�;1,�ͷ�ʧ��;
 */
static uint8_t my_mem_free(uint8_t memx, uint32_t offset)
{
  int i;
  if (!mallco_dev.memrdy[memx]) //δ��ʼ��,��ִ�г�ʼ��
  {
    mallco_dev.init(memx);
    return 1; //δ��ʼ��
  }
  if (offset < memsize[memx]) //ƫ�����ڴ����.
  {
    int index = offset / memblksize[memx];      //ƫ�������ڴ�����
    int nmemb = mallco_dev.memmap[memx][index]; //�ڴ������
    for (i = 0; i < nmemb; i++)                 //�ڴ������
    {
      mallco_dev.memmap[memx][index + i] = 0;
    }
    return 0;
  }
  else
    return 2; //ƫ�Ƴ�����.
}
//�����ڴ�
//*des:Ŀ�ĵ�ַ
//*src:Դ��ַ
//n:��Ҫ���Ƶ��ڴ泤��(�ֽ�Ϊ��λ)
void OS_memcpy(void *des, void *src, uint32_t n)
{
  uint8_t *xdes = des;
  uint8_t *xsrc = src;
  while (n--)
    *xdes++ = *xsrc++;
}
//�����ڴ�
//*s:�ڴ��׵�ַ
//c :Ҫ���õ�ֵ
//count:��Ҫ���õ��ڴ��С(�ֽ�Ϊ��λ)
void OS_memset(void *s, uint8_t c, uint32_t count)
{
  uint8_t *xs = s;
  while (count--)
    *xs++ = c;
}
//�ڴ�����ʼ��
//memx:�����ڴ��
void OS_mem_init(uint8_t memx)
{
  OS_memset(mallco_dev.memmap[memx], 0, memtblsize[memx] * 2); //�ڴ�״̬����������
  OS_memset(mallco_dev.membase[memx], 0, memsize[memx]);       //�ڴ��������������
  mallco_dev.memrdy[memx] = 1;                                //�ڴ�����ʼ��OK
}
//��ȡ�ڴ�ʹ����
//memx:�����ڴ��
//����ֵ:ʹ����(0~100)
uint8_t OS_mem_perused(uint8_t memx)
{
  uint32_t used = 0;
  uint32_t i;
  for (i = 0; i < memtblsize[memx]; i++)
  {
    if (mallco_dev.memmap[memx][i])
      used++;
  }
  return (used * 100) / (memtblsize[memx]);
}

//�ͷ��ڴ�(�ⲿ����)
//memx:�����ڴ��
//ptr:�ڴ��׵�ַ
void OS_free(uint8_t memx, void *ptr)
{
  uint32_t offset;
  if (ptr == NULL)
    return;            //��ַΪ0.
  //printf("free:%d,%x\r\n",memx,ptr);
//  taskENTER_CRITICAL(); //�����ٽ���(�޷����жϴ��)  // �����ٽ���ʱ�䲻�˹���
  offset = (uint32_t)ptr - (uint32_t)mallco_dev.membase[memx];
  my_mem_free(memx, offset); //�ͷ��ڴ�
//  taskEXIT_CRITICAL();        //�˳��ٽ���(���Ա��жϴ��)
}
//�����ڴ�(�ⲿ����)
//memx:�����ڴ��
//size:�ڴ��С(�ֽ�)
//����ֵ:���䵽���ڴ��׵�ַ.
void *OS_malloc(uint8_t memx, uint32_t size)
{

  uint32_t offset;
  //printf("m:%d,%d\r\n",memx,size);
//  taskENTER_CRITICAL(); //�����ٽ���(�޷����жϴ��)  // �����ٽ���ʱ�䲻�˹���
  offset = my_mem_malloc(memx, size);
//  taskEXIT_CRITICAL(); //�˳��ٽ���(���Ա��жϴ��)
  if (offset == 0XFFFFFFFF)
    return NULL;
  else
    return (void *)((uint32_t)mallco_dev.membase[memx] + offset);
}
//���·����ڴ�(�ⲿ����)
//memx:�����ڴ��
//*ptr:���ڴ��׵�ַ
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:�·��䵽���ڴ��׵�ַ.
void *OS_realloc(uint8_t memx, void *ptr, uint32_t size)
{
  uint32_t offset;

//  taskENTER_CRITICAL(); //�����ٽ���(�޷����жϴ��)  // �����ٽ���ʱ�䲻�˹���
  offset = my_mem_malloc(memx, size);
//  taskEXIT_CRITICAL(); //�˳��ٽ���(���Ա��жϴ��)
  if (offset == 0XFFFFFFFF)
    return NULL;
  else
  {
    OS_memcpy((void *)((uint32_t)mallco_dev.membase[memx] + offset), ptr, size); //�������ڴ����ݵ����ڴ�
    OS_free(memx, ptr);                                                          //�ͷž��ڴ�
    return (void *)((uint32_t)mallco_dev.membase[memx] + offset);               //�������ڴ��׵�ַ
  }
}


