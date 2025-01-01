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


int getch()							//获取键盘输入
{
     	struct termios tm, tm_old;
     	int ch;
 
     	if (tcgetattr(0, &tm) < 0) 					//保存现在的终端设置
        	  return -1;     
 
     	tm_old = tm;

     	cfmakeraw(&tm);						//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理

     	if (tcsetattr(0, TCSANOW, &tm) < 0) 				//设置上更改之后的设置
        	  return -1;     
 
     	ch = getchar();

     	if (tcsetattr(0, TCSANOW, &tm_old) < 0) 			//更改设置为最初的样子
        	  return -1;     
    
     	return ch;
}


static void* canRev(void* t)					//接收数据线程
{
	int c,i,nbyte;
	int readCount;
	int thousand,hundred,ten,one;

	unsigned char data0[1] = {0};
	unsigned int can_id = 0x1234;
	unsigned int extended = 1;

 	char fileWrite[100];  				// 复制后的文件名
	FILE *fpWrite;  					// 指向复制后的文件
	int bufferLen = 1024*4;  				// 缓冲区长度
	char *buffer = (char*)malloc(bufferLen);  		// 开辟缓存

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
		nbyte = can_read(fd_can, &can_id, data0, &extended);		//接收千位长度
		thousand = (int)data0[0];
		write(1,&thousand,1);   
		fflush(stdout);	

		nbyte = can_read(fd_can, &can_id, data0, &extended);		//接收百位长度
		hundred = (int)data0[0];
		write(1,&hundred,1);   
		fflush(stdout);	

		nbyte = can_read(fd_can, &can_id, data0, &extended);		//接收十位长度
		ten = (int)data0[0];
		write(1,&ten,1);   
		fflush(stdout);	

		nbyte = can_read(fd_can, &can_id, data0, &extended);		//接收个位长度
		one = (int)data0[0];
		write(1,&one,1);   
		fflush(stdout);	

		readCount = 1000*thousand + 100*hundred + 10*ten + one;

		for(i=0; i<readCount; i++)          
		{         
			nbyte = can_read(fd_can, &can_id, data0, &extended);		//接收数据
			c = (int)data0[0];
			write(1,&c,1);   
			fflush(stdout);	

			buffer[i] = c;
 		}

		fwrite(buffer, readCount, 1, fpWrite);                              			//写到文件中

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



