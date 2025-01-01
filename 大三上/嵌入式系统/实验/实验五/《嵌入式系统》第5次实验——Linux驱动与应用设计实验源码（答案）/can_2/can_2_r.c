#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <iconv.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sockcan.h"

unsigned	int fd_can;


int getch()							//��ȡ��������
{
     	struct termios tm, tm_old;
     	int ch;
 
     	if (tcgetattr(0, &tm) < 0) 					//�������ڵ��ն�����
        	  return -1;     
 
     	tm_old = tm;

     	cfmakeraw(&tm);						//�����ն�����Ϊԭʼģʽ����ģʽ�����е������������ֽ�Ϊ��λ������

     	if (tcsetattr(0, TCSANOW, &tm) < 0) 				//�����ϸ���֮�������
        	  return -1;     
 
     	ch = getchar();

     	if (tcsetattr(0, TCSANOW, &tm_old) < 0) 			//��������Ϊ���������
        	  return -1;     
    
     	return ch;
}


static void* canRev(void* t)					//���������߳�
{
	int c,i,nbyte;
	int readCount;
	int thousand,hundred,ten,one;

	unsigned char data0[1] = {0};
	unsigned int can_id = 0x1234;
	unsigned int extended = 1;

 	char fileWrite[100];  				// ���ƺ���ļ���
	FILE *fpWrite;  					// ָ���ƺ���ļ�
	int bufferLen = 1024*4;  				// ����������
	char *buffer = (char*)malloc(bufferLen);  		// ���ٻ���

	printf("\nPlease input copy filename:  ");
	scanf("%s", fileWrite);

	if((fpWrite=fopen(fileWrite, "wb")) == NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		getch();
		exit(1);
	}

	printf("\nCAN-Bus Receive Begin!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);          

	do
	{
		nbyte = can_read(fd_can, &can_id, data0, &extended);		//����ǧλ����
		thousand = (int)data0[0];
		write(1,&thousand,1);   
		fflush(stdout);	

		nbyte = can_read(fd_can, &can_id, data0, &extended);		//���հ�λ����
		hundred = (int)data0[0];
		write(1,&hundred,1);   
		fflush(stdout);	

		nbyte = can_read(fd_can, &can_id, data0, &extended);		//����ʮλ����
		ten = (int)data0[0];
		write(1,&ten,1);   
		fflush(stdout);	

		nbyte = can_read(fd_can, &can_id, data0, &extended);		//���ո�λ����
		one = (int)data0[0];
		write(1,&one,1);   
		fflush(stdout);	

		readCount = 1000*thousand + 100*hundred + 10*ten + one;

		for(i=0; i<readCount; i++)          
		{         
			nbyte = can_read(fd_can, &can_id, data0, &extended);		//��������
			c = (int)data0[0];
			write(1,&c,1);   
			fflush(stdout);	

			buffer[i] = c;
 		}

		fwrite(buffer, readCount, 1, fpWrite);                              			//д���ļ���

	}while(readCount == bufferLen);

	free(buffer);
	fclose(fpWrite);

	printf("CAN-Bus Receive End!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);        

	return NULL;
}


int main(int argc, char *argv[]) 
{ 
	struct can_filter filter[] = {
		{0x4321,CAN_EFF_MASK,},
		{0x1234,CAN_EFF_MASK,},
	}; 

	pthread_t th_can;
	void * retval;
     
	fd_can = can_open("can0", 500000, filter, sizeof(filter)  / sizeof(struct can_filter));
	if (fd_can < 0) 
	{
		perror("can_open");
		can_close("can0", fd_can);
		exit(1);
	}

	pthread_create(&th_can, NULL, canRev, 0);
	pthread_join(th_can, &retval);

	can_close("can0", fd_can);

	return 0; 
}



