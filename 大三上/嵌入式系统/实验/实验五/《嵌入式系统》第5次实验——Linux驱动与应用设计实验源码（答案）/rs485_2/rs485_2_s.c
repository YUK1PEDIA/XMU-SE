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


int main(int argc, char **argv)
{
	int c,i,nbytes;
	int readCount;  						// 实际读取的字节数
	int thousand,hundred,ten,one;

	int bufferLen = 1024*4; 	
	char fileRead[100];  					// 要复制的文件名
	char *buffer = (char*)malloc(bufferLen);  			// 开辟缓存
	FILE *fpRead;  						// 指向要复制的文件

	fd_485 = open("/dev/ttyS0", O_RDWR);
	if(fd_485 < 0)
	{
		perror("fail to open serial port");
		exit(-1);
	}
	
	serial_init();

	printf("\nPlease input copy filename:  ");
	scanf("%s", fileRead);

	if( (fpRead=fopen(fileRead, "rb")) == NULL )
	{
		printf("Cannot open file, press any key to exit!\n");
		getch();
		exit(1);
	}

	printf("\nRS-485 Send Begin!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);                  

	while((readCount = fread(buffer, 1, bufferLen, fpRead)) > 0)
	{
		thousand = readCount/1000;
		hundred = (readCount - 1000*thousand)/100;
		ten = (readCount - 1000*thousand - 100*hundred)/10;
		one = readCount - 1000*thousand - 100*hundred - 10*ten;

		write(1,&thousand,1);
		nbytes = write(fd_485, &thousand, 1);   					//向RS-485写数据----千位
	
		write(1,&hundred,1);
		nbytes = write(fd_485, &hundred, 1);   						//向RS-485写数据----百位
	
		write(1,&ten,1);
		nbytes = write(fd_485, &ten, 1);   						//向RS-485写数据----十位
	
		write(1,&one,1);
		nbytes = write(fd_485, &one, 1);   						//向RS-485写数据----个位
	
		for(i=0; i<readCount; i++)          
		{         
			c = buffer[i];
			write(1,&c,1);
			nbytes = write(fd_485, &c, 1);   					//向RS-485写数据
 		}
	}

	free(buffer);
	fclose(fpRead);
	close(fd_485);

	printf("RS-485 Send End!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);      

	return 0;
}


