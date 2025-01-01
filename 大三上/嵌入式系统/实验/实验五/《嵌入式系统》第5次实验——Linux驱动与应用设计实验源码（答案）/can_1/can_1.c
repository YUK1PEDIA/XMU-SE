#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <iconv.h>
#include <string.h>
#include <pthread.h>
#include "sockcan.h"

#define ENDMINITERM 	27 
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

void* receive(void * data)							//接收数据线程
{
	int c;
	int nbyte;
	unsigned char data0[1] = {0};
	unsigned int can_id = 0x1234;
	unsigned int extended = 1;

  	printf("CAN Receive Begin!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);          

	while (1)
	{
		nbyte = can_read(fd_can, &can_id, data0, &extended);		//接收数据
		c = (int)data0[0];
		write(1,&c,1);                                        				//显示读出的数据

		if(c == 0x0d)
		            	printf("\n");	
	
		if(c == ENDMINITERM)
            			break;
	}

	printf("CAN Receive End!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);          

	return NULL;
}

int main(int argc, const char *argv[])
{
	int c;
	pthread_t th_rece;
	void * retval;
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

	pthread_create(&th_rece, NULL, receive, 0);

	printf("Please press the keys on the computer keyboard, then watch the monitor of another computer\n\n");

	printf("Press the Esc key to exit the program\n\n");

	printf("CAN Send Begin!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);          

	while(1)
	{
		c = getch();
		write(1,&c,1);
		data0[0] = (char)c;
		can_write(fd_can, can_id, data0, sizeof(data0), extended);		//发送数据

		if(c == 0x0d)
		            	printf("\n");	

		if(c == ENDMINITERM)
	            		break;

		usleep(50);
	}

	pthread_join(th_rece, &retval);

	can_close("can0", fd_can);

	printf("CAN Send End!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);          

	return 0;
}