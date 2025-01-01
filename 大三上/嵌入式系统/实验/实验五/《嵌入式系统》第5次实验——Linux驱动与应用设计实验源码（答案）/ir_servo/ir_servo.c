#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include <poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <pthread.h>

#define IOCTL_MAGIC 	'S'
#define ROTATE_0 		_IO(IOCTL_MAGIC, 0) 
#define ROTATE_30 	_IO(IOCTL_MAGIC, 1) 
#define ROTATE_60 	_IO(IOCTL_MAGIC, 2) 
#define ROTATE_90 	_IO(IOCTL_MAGIC, 3) 
#define ROTATE_120 	_IO(IOCTL_MAGIC, 4) 
#define ROTATE_150 	_IO(IOCTL_MAGIC, 5) 
#define SET_ANGLE	_IO(IOCTL_MAGIC, 6)

#define IrDevice 		"/dev/input/event0"
#define ServoDevice 	"/dev/servo"

#define Number 1000000

static struct input_event inputevent;

unsigned	int fd_ir;
unsigned	int fd_servo;
unsigned	int key1=0;

void * servo_start(void * data)			//陀机转动线程		
{
	int angle;
	while(1)
	{
	        if(key1 == 1)
	        {
		angle = 180;
		ioctl(fd_servo, SET_ANGLE, angle);
		usleep(Number);

		angle = 0;
		ioctl(fd_servo, SET_ANGLE, angle);
		usleep(Number);
	        }
	}
}

int main(int argc,char* argv[])
{
	int err=0;

	void * retval;
	pthread_t th_servo_start;

	fd_ir=open(IrDevice,O_RDWR);
	if (fd_ir < 0) 
	{
		perror("Open file error, Check your path ");
		return -1;
	}

	fd_servo=open(ServoDevice,O_RDWR);
	if (fd_servo < 0) 
	{
		perror("Can't open file farsight_servo,Check your path");
		return -1;
	} 

	pthread_create(&th_servo_start, NULL, servo_start, 0);

	printf("Turn D6 to the left, others to the right\n\n");

	printf("Push 1 than Steering engine rotates, Push 1 again than Steering engine stop\n");

	while(1)
	{
		err=read(fd_ir,&inputevent,sizeof(inputevent));

		if(inputevent.value)
		{
			switch(inputevent.code)
			{
				case 0x74:
					printf("开关 is set\n");
					break;
				case 0x72:
					printf("音量减 is set\n");
					break;
				case 0x73:
					printf("音量加 is set\n");
					break;
				case 0x8d:
					printf("设置 is set\n");
					break;
				case 0x8b:
					printf("菜单 is set\n");
					break;
				case 0x67:
					printf("up is set\n");
					break;
				case 0x6c:
					printf("down is set\n");
					break;
				case 0x69:
					printf("left is set\n");
					break;
				case 0x6a:
					printf("right is set\n");
					break;
				case 0x1c:
					printf("ok is set\n");
					break;
				case 0x66:
					printf("主页 is set\n");
					break;
				case 0x01:
					printf("返回 is set\n");
					break;
				case 0x02:
					printf("1 is set\n");
					if(key1 == 0)
					{
						key1 = 1;
					}
					else
					{
						key1 = 0;
					}					
					break;
				case 0x03:
					printf("2 is set\n");
					break;
				case 0x04:
					printf("3 is set\n");
					break;
				case 0x05:
					printf("4 is set\n");
					break;
				case 0x06:
					printf("5 is set\n");
					break;
				case 0x07:
					printf("6 is set\n");
					break;
				case 0x08:
					printf("7 is set\n");
					break;
				case 0x09:
					printf("8 is set\n");
					break;
				case 0x0a:
					printf("9 is set\n");
					break;
				case 0x0b:
					printf("0 is set\n");
					break;
				default:
					break;		 
			}
		}
	}

	pthread_join(th_servo_start, &retval);

	close(fd_servo);    
	close(fd_ir);    

	return 0;
}

