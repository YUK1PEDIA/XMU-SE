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

void* receive(void * data)						//接收数据线程
{
	int c,i,nbytes;
	int thousand,hundred,ten,one;
	int readCount;  

	unsigned short int ccc;
	char cc;						// 实际读取的字节数

	int bufferLen = 1024*4;  					// 缓冲区长度
	FILE *fpWrite;  						// 指向复制后的文件
 	char fileWrite[100];  					// 复制后的文件名
	char *buffer = (char*)malloc(bufferLen);  			// 开辟缓存

	printf("\nPlease input copy filename:  ");
	scanf("%s", fileWrite);

	if( (fpWrite=fopen(fileWrite, "wb")) == NULL )
	{
		printf("Cannot open file, press any key to exit!\n");
		getch();
		exit(1);
	}

  	printf("\nRS-485 Receive Begin!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);                  

	do
	{
    		nbytes = read(fd_485, &thousand, 1); 			              	//读RS-485的数据----千位
		cc = (char)c;
		ccc = (int)cc;
		write(1,&thousand,1);                                       			//显示读出的数据

    		nbytes = read(fd_485, &hundred, 1); 			              	//读RS-485的数据----百位
		cc = (char)c;
		ccc = (int)cc;
		write(1,&hundred,1);                                        			//显示读出的数据

    		nbytes = read(fd_485, &ten, 1); 			              	//读RS-485的数据----十位
		cc = (char)c;
		ccc = (int)cc;
		write(1,&ten,1);                                        			//显示读出的数据

    		nbytes = read(fd_485, &one, 1); 			              	//读RS-485的数据----个位
		cc = (char)c;
		ccc = (int)cc;
		write(1,&one,1);                                        			//显示读出的数据

		readCount = 1000*thousand + 100*hundred + 10*ten + one;	//计算文件的长度

		for(i=0; i<readCount; i++)          
		{         
    			nbytes = read(fd_485, &c, 1); 			//读RS-485的数据
			cc = (char)c;
			ccc = (int)cc;
			write(1,&c,1);                                        			//显示读出的数据
			buffer[i] = c;
 		}

		fwrite(buffer, readCount, 1, fpWrite);				//将接收到的数据写到文件中

	}while(readCount == bufferLen);

	free(buffer);
	fclose(fpWrite);

  	printf("RS-485 Receive  End!\n");

	c = 0x0d;
	write(1,&c,1);                                     
	c = 0x0a;
	write(1,&c,1);      

  	return NULL; 
}


int main(int argc, char **argv)
{
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
	pthread_join(th_rece, &retval);

	close(fd_485);

	return 0;
}


