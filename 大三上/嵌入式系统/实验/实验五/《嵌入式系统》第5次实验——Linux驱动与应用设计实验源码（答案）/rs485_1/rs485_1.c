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

#define ENDMINITERM 	27 

unsigned	int fd_485;

void serial_init()		//串口初始化
{
	struct termios options;

	tcgetattr(fd_485,&options);

	options.c_cflag |=(CLOCAL | CREAD);
	options.c_cflag &= ~CSIZE;
	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CSTOPB;
	options.c_iflag |= IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	
	if((cfsetispeed(&options,B115200)) == -1)
	{
		printf("cfsetospeed is erro\n");
		exit(-1);
	}

	tcsetattr(fd_485,TCSANOW,&options);
}


unsigned short int getch()					//获取键盘输入
{
     	struct termios tm, tm_old;
     	unsigned short int ch;
 
     	if (tcgetattr(0, &tm) < 0) 				//保存现在的终端设置
        		return -1;     
 
     	tm_old = tm;

     	cfmakeraw(&tm);					//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理

     	if (tcsetattr(0, TCSANOW, &tm) < 0) 			//设置上更改之后的设置
        		return -1;     
 
     	ch = getchar();

     	if (tcsetattr(0, TCSANOW, &tm_old) < 0) 		//更改设置为最初的样子
        		return -1;     
    
     	return ch;
}


void* receive(void * data)					//接收数据线程
{
	unsigned short int c;
	unsigned short int ccc;
	int nbytes;
	char cc;

  	printf("RS-485 Receive Begin!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);                                        

	while (1)
	{
		nbytes = read(fd_485, &c, 1);		
		cc = (char)c;
		ccc = (int)cc;

		if(c == 10)
		{
			c = 0x0d;
			write(1,&c,1);                                        
			c = 0x0a;
			write(1,&c,1);                                        
		}
		else
			write(1,&c,1);                                        
	
		if(c == ENDMINITERM)
            			break;
	}

	printf("RS-485 Receive End!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);             

	return NULL;
}


int main(int argc, char **argv)
{
	unsigned short int c;
	int nbytes;
	pthread_t th_rece;
	void * retval;

	fd_485 = open("/dev/ttyS0", O_RDWR);
	if(fd_485 < 0)
	{
		perror("fail to open serial port");
		exit(-1);
	}
	
	serial_init();

	pthread_create(&th_rece, NULL, receive, 0);

	printf("Please press the keys on the computer keyboard, then watch the monitor of another computer\n\n");

	printf("Press the Esc key to exit the program\n\n");

	printf("RS-485 Send Begin!\n");

	c = 0x0d;
	write(1,&c,1);                                        
	c = 0x0a;
	write(1,&c,1);                                        

	while (1)
	{
		c = getch();

		if(c == 13)
		{
			c = 10;
			write(1,&c,1);
			nbytes = write(fd_485, &c, 1);	
		}
		else
		{
			write(1,&c,1);
			nbytes = write(fd_485, &c, 1);	
		}

		if(c == ENDMINITERM)
            			break;

		usleep(50);
	}

	pthread_join(th_rece, &retval);

	close(fd_485);

	printf("RS-485 Send End!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);             

	return 0;
}


