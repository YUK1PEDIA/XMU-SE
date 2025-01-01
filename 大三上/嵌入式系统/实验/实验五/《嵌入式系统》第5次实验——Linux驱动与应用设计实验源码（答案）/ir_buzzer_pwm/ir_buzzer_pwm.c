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

#define IOCTL_MAGIC 	'B'
#define ROTATE_ON 	_IO(IOCTL_MAGIC, 1) 
#define ROTATE_OFF 	_IO(IOCTL_MAGIC, 0) 

#define IrDevice "/dev/input/event0"
#define BuzzerPwmDevice "/dev/buzzer"

static struct input_event inputevent;

int main(int argc,char* argv[])
{
	int fd_ir;
	int fd_buzzer_pwm;
	int ret;
	int buzzer=0;
	int err=0;

	fd_ir=open(IrDevice,O_RDWR);
	if (fd_ir < 0) 
	{
		perror("Open file error, Check your path ");
		return -1;
	}

	fd_buzzer_pwm=open(BuzzerPwmDevice,O_RDWR);
	if (fd_buzzer_pwm < 0) 
	{
		perror("Can't open file farsight_buzzer,Check your path");
		return -1;
	} 

	ret = ioctl(fd_buzzer_pwm,ROTATE_OFF);
	if(ret < 0)
		perror("ioctl buzzer_ctl driver ");

	printf("Turn D15 to the left, others to the right\n\n");

	printf("Push 1 than sound the buzzer, Push 1 again than mute the buzzer\n");

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
					if(buzzer == 0)
					{
				       		ret = ioctl(fd_buzzer_pwm,ROTATE_ON);
						if(ret < 0)
					           		perror("ioctl buzzer_ctl driver ");
						buzzer = 1;
					}
					else
					{
				       		ret = ioctl(fd_buzzer_pwm,ROTATE_OFF);
						if(ret < 0)
					           		perror("ioctl buzzer_ctl driver ");
						buzzer = 0;
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
	close(fd_buzzer_pwm);    
	close(fd_ir);    

	return 0;
}

