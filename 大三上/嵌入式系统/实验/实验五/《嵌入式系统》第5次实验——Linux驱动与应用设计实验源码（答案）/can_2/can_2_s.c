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

#define SLEEPTIME  1500


int getch()						//获取键盘输入
{
     struct termios tm, tm_old;
     int ch;
 
     if (tcgetattr(0, &tm) < 0) 					//保存现在的终端设置
          return -1;     
 
     tm_old = tm;

     cfmakeraw(&tm);					//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理

     if (tcsetattr(0, TCSANOW, &tm) < 0) 			//设置上更改之后的设置
          return -1;     
 
     ch = getchar();

     if (tcsetattr(0, TCSANOW, &tm_old) < 0) 			//更改设置为最初的样子
          return -1;     
    
     return ch;
}


int main(int argc, char *argv[]) 
{ 
	int c,i;
	int readCount;  				// 实际读取的字节数
	int thousand,hundred,ten,one;

	char fileRead[100];  			// 要复制的文件名
	FILE *fpRead;  				// 指向要复制的文件
	int bufferLen = 1024*4; 		 	// 缓冲区长度
	char *buffer = (char*)malloc(bufferLen);  	// 开辟缓存

	int fd_can;
	unsigned char data0[1] = {0};
	unsigned int can_id = 0x1234;
	unsigned int extended = 1;
	struct can_filter filter[] = {
		{0x4321,CAN_EFF_MASK,},
		{0x1234,CAN_EFF_MASK,},
	}; 

	fd_can = can_open("can0", 500000, filter, sizeof(filter)  / sizeof(struct can_filter));
	if (fd_can < 0) 
	{
		perror("can_open");
		can_close("can0", fd_can);
		exit(1);
	}

	printf("\nPlease input copy filename:  ");
	scanf("%s", fileRead);

	if((fpRead=fopen(fileRead, "rb")) == NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		getch();
		exit(1);
	}

	printf("\nCAN-Bus Send  Begin!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);     

	while((readCount = fread(buffer, 1, bufferLen, fpRead)) > 0)          //读文件
	{
		thousand = readCount/1000;
		hundred = (readCount - 1000*thousand)/100;
		ten = (readCount - 1000*thousand - 100*hundred)/10;
		one = readCount - 1000*thousand - 100*hundred - 10*ten;

		write(1,&thousand,1);             				//在终端上显示
		data0[0] = (char)thousand;
		can_write(fd_can, can_id, data0, sizeof(data0), extended);		//发送千位长度
		usleep(SLEEPTIME);

		write(1,&hundred,1);         					//在终端上显示
		data0[0] = (char)hundred;
		can_write(fd_can, can_id, data0, sizeof(data0), extended);		//发送百位长度
		usleep(SLEEPTIME);

		write(1,&ten,1);              					//在终端上显示
		data0[0] = (char)ten;
		can_write(fd_can, can_id, data0, sizeof(data0), extended);		//发送十位长度
		usleep(SLEEPTIME);
	
		write(1,&one,1);            					//在终端上显示
		data0[0] = (char)one;
		can_write(fd_can, can_id, data0, sizeof(data0), extended);		//发送个位长度
		usleep(SLEEPTIME);

		for(i=0; i<readCount; i++)          
		{         
			c = buffer[i];

			write(1,&c,1);						//在终端上显示
			data0[0] = (char)c;
			can_write(fd_can, can_id, data0, sizeof(data0), extended);		//发送数据
			usleep(SLEEPTIME);
 		}
	}

	free(buffer);
	fclose(fpRead);

	can_close("can0", fd_can);

	printf("CAN-Bus  Send  End!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);     

	return 0; 
}



