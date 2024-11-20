/*
 * @Author: your name
 * @Date: 2021-07-08 09:19:09
 * @LastEditTime: 2021-07-12 08:46:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\Fun_FsExFunctions.c
 */
#include "Fun_FsExFunctions.h"
#include "OS_malloc.h"
#include "OS_Debug.h"
#include <string.h>



#define FILE_MAX_TYPE_NUM		7	//���FILE_MAX_TYPE_NUM������
#define FILE_MAX_SUBT_NUM		4	//���FILE_MAX_SUBT_NUM��С��

//�ļ������б�
uint8_t*const FILE_TYPE_TBL[FILE_MAX_TYPE_NUM][FILE_MAX_SUBT_NUM]=
{
  {"BIN"},			//BIN�ļ�
  {"LRC"},			//LRC�ļ�
  {"NES","SMS"},		//NES/SMS�ļ�
  {"TXT","C","H"},	//�ı��ļ�
  {"WAV","MP3","APE","FLAC"},//֧�ֵ������ļ�
  {"BMP","JPG","JPEG","GIF"},//ͼƬ�ļ�
  {"AVI"},			//��Ƶ�ļ�
};
///////////////////////////////�����ļ���,ʹ��malloc��ʱ��////////////////////////////////////////////
FATFS *fs[_VOLUMES];//�߼����̹�����.
FIL *file;	  		//�ļ�1
FIL *ftemp;	  		//�ļ�2.
UINT br,bw;			//��д����
FILINFO fileinfo;	//�ļ���Ϣ
DIR dir;  			//Ŀ¼

uint8_t *fatbuf;			//SD�����ݻ�����
///////////////////////////////////////////////////////////////////////////////////////
//Ϊexfuns�����ڴ�
//����ֵ:0,�ɹ�
//1,ʧ��
uint8_t exfuns_init(void)
{
  uint8_t i;
  for(i=0; i<_VOLUMES; i++)
  {
    fs[i]=(FATFS*)OS_malloc(SRAMIN,sizeof(FATFS));	//Ϊ����i�����������ڴ�
    if(!fs[i])break;
  }
  file=(FIL*)OS_malloc(SRAMIN,sizeof(FIL));		//Ϊfile�����ڴ�
  ftemp=(FIL*)OS_malloc(SRAMIN,sizeof(FIL));		//Ϊftemp�����ڴ�
  fatbuf=(uint8_t*)OS_malloc(SRAMIN,512);				//Ϊfatbuf�����ڴ�
  if(i==_VOLUMES&&file&&ftemp&&fatbuf)return 0;  //������һ��ʧ��,��ʧ��.
  else return 1;
}

//��Сд��ĸתΪ��д��ĸ,���������,�򱣳ֲ���.
uint8_t char_upper(uint8_t c)
{
  if(c<'A')return c;//����,���ֲ���.
  if(c>='a')return c-0x20;//��Ϊ��д.
  else return c;//��д,���ֲ���
}
//�����ļ�������
//fname:�ļ���
//����ֵ:0XFF,��ʾ�޷�ʶ����ļ����ͱ��.
//		 ����,����λ��ʾ��������,����λ��ʾ����С��.
uint8_t exf_FsTypetell(uint8_t *fname)
{
  uint8_t tbuf[5];
  uint8_t *attr='\0';//��׺��
  uint8_t i=0,j;
  while(i<250)
  {
    i++;
    if(*fname=='\0')break;//ƫ�Ƶ��������.
    fname++;
  }
  if(i==250)return 0XFF;//������ַ���.
  for(i=0; i<5; i++) //�õ���׺��
  {
    fname--;
    if(*fname=='.')
    {
      fname++;
      attr=fname;
      break;
    }
  }
  strcpy((char *)tbuf,(const char*)attr);//copy
  for(i=0; i<4; i++)tbuf[i]=char_upper(tbuf[i]); //ȫ����Ϊ��д
  for(i=0; i<FILE_MAX_TYPE_NUM; i++)	//����Ա�
  {
    for(j=0; j<FILE_MAX_SUBT_NUM; j++) //����Ա�
    {
      if(*FILE_TYPE_TBL[i][j]==0)break;//�����Ѿ�û�пɶԱȵĳ�Ա��.
      if(strcmp((const char *)FILE_TYPE_TBL[i][j],(const char *)tbuf)==0)//�ҵ���
      {
        return (i<<4)|j;
      }
    }
  }
  return 0XFF;//û�ҵ�
}

//�õ�����ʣ������
//drv:���̱��("0:"/"1:")
//total:������	 ����λKB��
//free:ʣ������	 ����λKB��
//����ֵ:0,����.����,�������
uint8_t exf_getfree(uint8_t *drv,uint32_t *total,uint32_t *free)
{
  FATFS *fs1;
  uint8_t res;
  uint32_t fre_clust=0, fre_sect=0, tot_sect=0;
  //�õ�������Ϣ�����д�����
  res =(uint32_t)f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
  if(res==0)
  {
    tot_sect=(fs1->n_fatent-2)*fs1->csize;	//�õ���������
    fre_sect=fre_clust*fs1->csize;			//�õ�����������
#if _MAX_SS!=512				  				//������С����512�ֽ�,��ת��Ϊ512�ֽ�
    tot_sect*=fs1->ssize/512;
    fre_sect*=fs1->ssize/512;
#endif
    *total=tot_sect>>1;	//��λΪKB
    *free=fre_sect>>1;	//��λΪKB
  }
  return res;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����
//ע���ļ���С��Ҫ����4GB.
//��psrc�ļ�,copy��pdst.
//fcpymsg,����ָ��,����ʵ�ֿ���ʱ����Ϣ��ʾ
//        pname:�ļ�/�ļ�����
//        pct:�ٷֱ�
//        mode:
//			[0]:�����ļ���
//			[1]:���°ٷֱ�pct
//			[2]:�����ļ���
//			[3~7]:����
//psrc,pdst:Դ�ļ���Ŀ���ļ�
//totsize:�ܴ�С(��totsizeΪ0��ʱ��,��ʾ����Ϊ�����ļ�����)
//cpdsize:�Ѹ����˵Ĵ�С.
//fwmode:�ļ�д��ģʽ
//0:������ԭ�е��ļ�
//1:����ԭ�е��ļ�
//����ֵ:0,����
//    ����,����,0XFF,ǿ���˳�
uint8_t exf_copy(uint8_t(*fcpymsg)(uint8_t*pname,uint8_t pct,uint8_t mode),uint8_t *psrc,uint8_t *pdst,uint32_t totsize,uint32_t cpdsize,uint8_t fwmode)
{
  uint8_t res;
  uint16_t br=0;
  uint16_t bw=0;
  FIL *fsrc=0;
  FIL *fdst=0;
  uint8_t *fbuf=0;
  uint8_t curpct=0;
  unsigned long long lcpdsize=cpdsize;
  fsrc=(FIL*)OS_malloc(SRAMIN,sizeof(FIL));//�����ڴ�
  fdst=(FIL*)OS_malloc(SRAMIN,sizeof(FIL));
  fbuf=(uint8_t*)OS_malloc(SRAMIN,8192);
  if(fsrc==NULL||fdst==NULL||fbuf==NULL)res=100;//ǰ���ֵ����fatfs
  else
  {
    if(fwmode==0)fwmode=FA_CREATE_NEW;//������
    else fwmode=FA_CREATE_ALWAYS;	  //���Ǵ��ڵ��ļ�

    res=f_open(fsrc,(const TCHAR*)psrc,FA_READ|FA_OPEN_EXISTING);	//��ֻ���ļ�
    if(res==0)res=f_open(fdst,(const TCHAR*)pdst,FA_WRITE|fwmode); 	//��һ���򿪳ɹ�,�ſ�ʼ�򿪵ڶ���
    if(res==0)//�������򿪳ɹ���
    {
      if(totsize==0)//�����ǵ����ļ�����
      {
        totsize=fsrc->obj.objsize;
        lcpdsize=0;
        curpct=0;
      } else curpct=(lcpdsize*100)/totsize;	//�õ��°ٷֱ�
      fcpymsg(psrc,curpct,0X02);			//���°ٷֱ�
      while(res==0)//��ʼ����
      {
        res=f_read(fsrc,fbuf,8192,(UINT*)&br);	//Դͷ����512�ֽ�
        if(res||br==0)break;
        res=f_write(fdst,fbuf,(UINT)br,(UINT*)&bw);	//д��Ŀ���ļ�
        lcpdsize+=bw;
        if(curpct!=(lcpdsize*100)/totsize)//�Ƿ���Ҫ���°ٷֱ�
        {
          curpct=(lcpdsize*100)/totsize;
          if(fcpymsg(psrc,curpct,0X02))//���°ٷֱ�
          {
            res=0XFF;//ǿ���˳�
            break;
          }
        }
        if(res||bw<br)break;
      }
      f_close(fsrc);
      f_close(fdst);
    }
  }
  OS_free(SRAMIN,fsrc);//�ͷ��ڴ�
  OS_free(SRAMIN,fdst);
  OS_free(SRAMIN,fbuf);
  return res;
}

//�õ�·���µ��ļ���
//����ֵ:0,·�����Ǹ�����.
//    ����,�ļ��������׵�ַ
uint8_t* exf_get_src_dname(uint8_t* dpfn)
{
  uint16_t temp=0;
  while(*dpfn!=0)
  {
    dpfn++;
    temp++;
  }
  if(temp<4)return 0;
  while((*dpfn!=0x5c)&&(*dpfn!=0x2f))dpfn--;	//׷����������һ��"\"����"/"��
  return ++dpfn;
}
//�õ��ļ��д�С
//ע���ļ��д�С��Ҫ����4GB.
//����ֵ:0,�ļ��д�СΪ0,���߶�ȡ�����з����˴���.
//    ����,�ļ��д�С.
uint32_t exf_fdsize(uint8_t *fdname)
{
#define MAX_PATHNAME_DEPTH	512+1	//���Ŀ���ļ�·��+�ļ������
  uint8_t res=0;
  DIR *fddir=0;		//Ŀ¼
  FILINFO *finfo=0;	//�ļ���Ϣ
  uint8_t * pathname=0;	//Ŀ���ļ���·��+�ļ���
  uint16_t pathlen=0;		//Ŀ��·������
  uint32_t fdsize=0;

  fddir=(DIR*)OS_malloc(SRAMIN,sizeof(DIR));//�����ڴ�
  finfo=(FILINFO*)OS_malloc(SRAMIN,sizeof(FILINFO));
  if(fddir==NULL||finfo==NULL)res=100;
  if(res==0)
  {
    pathname=OS_malloc(SRAMIN,MAX_PATHNAME_DEPTH);
    if(pathname==NULL)res=101;
    if(res==0)
    {
      pathname[0]=0;
      strcat((char*)pathname,(const char*)fdname); //����·��
      res=f_opendir(fddir,(const TCHAR*)fdname); 		//��ԴĿ¼
      if(res==0)//��Ŀ¼�ɹ�
      {
        while(res==0)//��ʼ�����ļ�������Ķ���
        {
          res=f_readdir(fddir,finfo);						//��ȡĿ¼�µ�һ���ļ�
          if(res!=FR_OK||finfo->fname[0]==0)break;		//������/��ĩβ��,�˳�
          if(finfo->fname[0]=='.')continue;     			//�����ϼ�Ŀ¼
          if(finfo->fattrib&0X10)//����Ŀ¼(�ļ�����,0X20,�鵵�ļ�;0X10,��Ŀ¼;)
          {
            pathlen=strlen((const char*)pathname);		//�õ���ǰ·���ĳ���
            strcat((char*)pathname,(const char*)"/");	//��б��
            strcat((char*)pathname,(const char*)finfo->fname);	//Դ·��������Ŀ¼����
            //printf("\r\nsub folder:%s\r\n",pathname);	//��ӡ��Ŀ¼��
            fdsize+=exf_fdsize(pathname);				//�õ���Ŀ¼��С,�ݹ����
            pathname[pathlen]=0;						//���������
          } else fdsize+=finfo->fsize;						//��Ŀ¼,ֱ�Ӽ����ļ��Ĵ�С

        }
      }
      OS_free(SRAMIN,pathname);
    }
  }
  OS_free(SRAMIN,fddir);
  OS_free(SRAMIN,finfo);
  if(res)return 0;
  else return fdsize;
}
//�ļ��и���
//ע���ļ��д�С��Ҫ����4GB.
//��psrc�ļ���,copy��pdst�ļ���.
//pdst:��������"X:"/"X:XX"/"X:XX/XX"֮���.����Ҫʵ��ȷ����һ���ļ��д���
//fcpymsg,����ָ��,����ʵ�ֿ���ʱ����Ϣ��ʾ
//        pname:�ļ�/�ļ�����
//        pct:�ٷֱ�
//        mode:
//			[0]:�����ļ���
//			[1]:���°ٷֱ�pct
//			[2]:�����ļ���
//			[3~7]:����
//psrc,pdst:Դ�ļ��к�Ŀ���ļ���
//totsize:�ܴ�С(��totsizeΪ0��ʱ��,��ʾ����Ϊ�����ļ�����)
//cpdsize:�Ѹ����˵Ĵ�С.
//fwmode:�ļ�д��ģʽ
//0:������ԭ�е��ļ�
//1:����ԭ�е��ļ�
//����ֵ:0,�ɹ�
//    ����,�������;0XFF,ǿ���˳�
uint8_t exf_fdcopy(uint8_t(*fcpymsg)(uint8_t*pname,uint8_t pct,uint8_t mode),uint8_t *psrc,uint8_t *pdst,uint32_t *totsize,uint32_t *cpdsize,uint8_t fwmode)
{
#define MAX_PATHNAME_DEPTH	512+1	//���Ŀ���ļ�·��+�ļ������
  uint8_t res=0;
  DIR *srcdir=0;		//ԴĿ¼
  DIR *dstdir=0;		//ԴĿ¼
  FILINFO *finfo=0;	//�ļ���Ϣ
  uint8_t *fn=0;   		//���ļ���

  uint8_t * dstpathname=0;	//Ŀ���ļ���·��+�ļ���
  uint8_t * srcpathname=0;	//Դ�ļ���·��+�ļ���

  uint16_t dstpathlen=0;	//Ŀ��·������
  uint16_t srcpathlen=0;	//Դ·������


  srcdir=(DIR*)OS_malloc(SRAMIN,sizeof(DIR));//�����ڴ�
  dstdir=(DIR*)OS_malloc(SRAMIN,sizeof(DIR));
  finfo=(FILINFO*)OS_malloc(SRAMIN,sizeof(FILINFO));

  if(srcdir==NULL||dstdir==NULL||finfo==NULL)res=100;
  if(res==0)
  {
    dstpathname=OS_malloc(SRAMIN,MAX_PATHNAME_DEPTH);
    srcpathname=OS_malloc(SRAMIN,MAX_PATHNAME_DEPTH);
    if(dstpathname==NULL||srcpathname==NULL)res=101;
    if(res==0)
    {
      dstpathname[0]=0;
      srcpathname[0]=0;
      strcat((char*)srcpathname,(const char*)psrc); 	//����ԭʼԴ�ļ�·��
      strcat((char*)dstpathname,(const char*)pdst); 	//����ԭʼĿ���ļ�·��
      res=f_opendir(srcdir,(const TCHAR*)psrc); 		//��ԴĿ¼
      if(res==0)//��Ŀ¼�ɹ�
      {
        strcat((char*)dstpathname,(const char*)"/");//����б��
        fn=exf_get_src_dname(psrc);
        if(fn==0)//��꿽��
        {
          dstpathlen=strlen((const char*)dstpathname);
          dstpathname[dstpathlen]=psrc[0];	//��¼���
          dstpathname[dstpathlen+1]=0;		//������
        } else strcat((char*)dstpathname,(const char*)fn);//���ļ���
        fcpymsg(fn,0,0X04);//�����ļ�����
        res=f_mkdir((const TCHAR*)dstpathname);//����ļ����Ѿ�����,�Ͳ�����.��������ھʹ����µ��ļ���.
        if(res==FR_EXIST)res=0;
        while(res==0)//��ʼ�����ļ�������Ķ���
        {
          res=f_readdir(srcdir,finfo);					//��ȡĿ¼�µ�һ���ļ�
          if(res!=FR_OK||finfo->fname[0]==0)break;		//������/��ĩβ��,�˳�
          if(finfo->fname[0]=='.')continue;     			//�����ϼ�Ŀ¼
          fn=(uint8_t*)finfo->fname; 							//�õ��ļ���
          dstpathlen=strlen((const char*)dstpathname);	//�õ���ǰĿ��·���ĳ���
          srcpathlen=strlen((const char*)srcpathname);	//�õ�Դ·������

          strcat((char*)srcpathname,(const char*)"/");//Դ·����б��
          if(finfo->fattrib&0X10)//����Ŀ¼(�ļ�����,0X20,�鵵�ļ�;0X10,��Ŀ¼;)
          {
            strcat((char*)srcpathname,(const char*)fn);		//Դ·��������Ŀ¼����
            res=exf_fdcopy(fcpymsg,srcpathname,dstpathname,totsize,cpdsize,fwmode);	//�����ļ���
          } else //��Ŀ¼
          {
            strcat((char*)dstpathname,(const char*)"/");//Ŀ��·����б��
            strcat((char*)dstpathname,(const char*)fn);	//Ŀ��·�����ļ���
            strcat((char*)srcpathname,(const char*)fn);	//Դ·�����ļ���
            fcpymsg(fn,0,0X01);//�����ļ���
            res=exf_copy(fcpymsg,srcpathname,dstpathname,*totsize,*cpdsize,fwmode);//�����ļ�
            *cpdsize+=finfo->fsize;//����һ���ļ���С
          }
          srcpathname[srcpathlen]=0;//���������
          dstpathname[dstpathlen]=0;//���������
        }
      }
      OS_free(SRAMIN,dstpathname);
      OS_free(SRAMIN,srcpathname);
    }
  }
  OS_free(SRAMIN,srcdir);
  OS_free(SRAMIN,dstdir);
  OS_free(SRAMIN,finfo);
  return res;
}


