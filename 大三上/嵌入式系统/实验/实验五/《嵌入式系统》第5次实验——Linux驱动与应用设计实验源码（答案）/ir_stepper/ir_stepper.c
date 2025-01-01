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

#define STEPPER_ON 	0 
#define STEPPER_OFF 	1 

#define IrDevice 		"/dev/input/event0"
#define StepperDevice 	"/dev/stepper"

static struct input_event inputevent;

unsigned	int fd_ir;
unsigned	int fd_stepper;
unsigned	int key1=0;
unsigned	int key2=0;
unsigned	int times = 900;

void * stepper_clockwise(void * data)			//步进电机顺时针转线程		
{
	while(1)
	{
	        if(key1 == 1)
	        {
		ioctl(fd_stepper, STEPPER_ON, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);

		ioctl(fd_stepper, STEPPER_ON, 0);
		ioctl(fd_stepper, STEPPER_ON, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);
		
		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_ON, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);
		
		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_ON, 1);
		ioctl(fd_stepper, STEPPER_ON, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);

		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_ON, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);
	
		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_ON, 2);
		ioctl(fd_stepper, STEPPER_ON, 3);
		usleep(times);
		
		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_ON, 3);
		usleep(times);
		
		ioctl(fd_stepper, STEPPER_ON, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_ON, 3);
		usleep(times);
	        }
	}
}

void * stepper_anticlockwise(void * data)			//步进电机逆时针转线程		
{
	while(1)
	{
	        if(key2 == 1)
	        {
		ioctl(fd_stepper, STEPPER_ON, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_ON, 3);
		usleep(times);

		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_ON, 3);
		usleep(times);
		
		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_ON, 2);
		ioctl(fd_stepper, STEPPER_ON, 3);
		usleep(times);
		
		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_ON, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);

		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_ON, 1);
		ioctl(fd_stepper, STEPPER_ON, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);
	
		ioctl(fd_stepper, STEPPER_OFF, 0);
		ioctl(fd_stepper, STEPPER_ON, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);
		
		ioctl(fd_stepper, STEPPER_ON, 0);
		ioctl(fd_stepper, STEPPER_ON, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);
		
		ioctl(fd_stepper, STEPPER_ON, 0);
		ioctl(fd_stepper, STEPPER_OFF, 1);
		ioctl(fd_stepper, STEPPER_OFF, 2);
		ioctl(fd_stepper, STEPPER_OFF, 3);
		usleep(times);
	        }
	}
}

int main(int argc,char* argv[])
{
	int err=0;

	void * retval;
	pthread_t th_stepper_clockwise, th_stepper_anticlockwise;

	fd_ir=open(IrDevice,O_RDWR);
	if (fd_ir < 0) 
	{
		perror("Open file error, Check your path ");
		return -1;
	}

	fd_stepper=open(StepperDevice,O_RDWR);
	if (fd_stepper < 0) 
	{
		perror("Can't open file farsight_buzzer,Check your path");
		return -1;
	} 

	ioctl(fd_stepper, STEPPER_OFF, 0);
	ioctl(fd_stepper, STEPPER_OFF, 1);
	ioctl(fd_stepper, STEPPER_OFF, 2);
	ioctl(fd_stepper, STEPPER_OFF, 3);

	pthread_create(&th_stepper_clockwise, NULL, stepper_clockwise, 0);
	pthread_create(&th_stepper_anticlockwise, NULL, stepper_anticlockwise, 0);

	printf("Turn D8 and D9 and D10 and D11 to the left, others to the right\n\n");

	printf("Push 1 than Stepper motor rotates clockwise, Push 1 again than Stepper motor stop; Push 2 than Stepper motor rotates counterclockwise,  Push 2  again than Stepper motor stop\n");

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
						key2 = 0;
					}
					else
					{
						key1 = 0;
						key2 = 0;
					}					
					break;
				case 0x03:
					printf("2 is set\n");
					if(key2 == 0)
					{
						key1 = 0;
						key2 = 1;
					}
					else
					{
						key1 = 0;
						key2 = 0;
					}					
					break;
				case 0x04:
					printf("3 is set\n");
					key1 = 0;
					key2 = 0;					
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

	pthread_join(th_stepper_clockwise, &retval);
	pthread_join(th_stepper_anticlockwise, &retval);

	close(fd_stepper);    
	close(fd_ir);    

	return 0;
}

