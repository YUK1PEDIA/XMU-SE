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

#define LED1_ON    _IO('G',1)
#define LED1_OFF   _IO('G',2)
#define LED2_ON    _IO('G',3)
#define LED2_OFF   _IO('G',4)
#define LED3_ON    _IO('G',5)
#define LED3_OFF   _IO('G',6) 

#define IrDevice "/dev/input/event0"
#define LedDevice "/dev/leds_ctl"

static struct input_event inputevent;

int main(int argc,char* argv[])
{
	int fd_ir;
	int fd_led;
	int ret;
	int err=0;
	int led1=0;
	int led2=0;
	int led3=0;

	fd_ir=open(IrDevice,O_RDWR);
	if (fd_ir < 0) 
	{
		perror("Open file error, Check your path ");
		return -1;
	}

	fd_led=open(LedDevice,O_RDWR);
	if (fd_led < 0) 
	{
		perror("Can't open file farsight_buzzer,Check your path");
		return -1;
	} 

	ioctl(fd_led,LED1_OFF);
	ioctl(fd_led,LED2_OFF);
	ioctl(fd_led,LED3_OFF);

                printf("Push 1 than light LED1, Push 1 again than extinguish LED1; Push 2 than light LED2,  Push 2  again than extinguish LED2; Push 3 than light LED3, Push 3 again than extinguish LED3\n");

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
					if(led1 == 0)
					{
						ioctl(fd_led,LED1_ON);
						led1 = 1;
					}
					else
					{
						ioctl(fd_led,LED1_OFF);
						led1 = 0;
					}
					break;
				case 0x03:
					printf("2 is set\n");
					if(led2 == 0)
					{
						ioctl(fd_led,LED2_ON);
						led2 = 1;
					}
					else
					{
						ioctl(fd_led,LED2_OFF);
						led2 = 0;
					}
					break;
				case 0x04:
					printf("3 is set\n");
					if(led3 == 0)
					{
						ioctl(fd_led,LED3_ON);
						led3 = 1;
					}
					else
					{
						ioctl(fd_led,LED3_OFF);
						led3 = 0;
					}
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
	close(fd_led);    
	close(fd_ir);    

	return 0;
}

