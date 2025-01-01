#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <linux/input.h>
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#define SET_VAL _IO('Z', 0)
#define GET_KEY _IO('Z', 1)

#define STEPPER_ON 	0 
#define STEPPER_OFF 	1 

#if 0
#define IOCTL_MAGIC 	'S'
#define STEPPER_ON 	_IOW(IOCTL_MAGIC, 0, int) 
#define STEPPER_OFF 	_IOW(IOCTL_MAGIC, 1, int) 
#endif

#define KeyDevice 		"/dev/zlg72xx"
#define StepperDevice 	"/dev/stepper"

unsigned	int fd_key;
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

int main(int argc, const char *argv[])
{
	int key = 0;
	char value ;
	int i = 0;
	char buf[8] = {0};

	void * retval;
	pthread_t th_stepper_clockwise, th_stepper_anticlockwise;

	fd_key = open(KeyDevice, O_RDWR);
	if (fd_key < 0) 
	{
		perror("open");
		exit(1);
	}

	fd_stepper=open(StepperDevice,O_RDWR);
	if (fd_stepper < 0) 
	{
		perror("Can't open file farsight_stepper,Check your path");
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
		ioctl(fd_key, GET_KEY, &key);

		switch(key)
		{
			case 28 : 
				printf("put is '1'\n");
				value = '1'; 
				break;
			case 27 : 
				printf("put is '2'\n"); 
				value = '2'; 
				break;
			case 26 : 
				printf("put is '3'\n"); 
				value = '3'; 
				break;
			case 25 : 
				printf("put is 'A'\n"); 
				value = 'A'; 
				break;
			case 20 : 
				printf("put is '4'\n"); 
				value = '4'; 
				break;
			case 19 : 
				printf("put is '5'\n"); 
				value = '5'; 
				break;
			case 18 : 
				printf("put is '6'\n"); 
				value = '6'; 
				break;
			case 17 : 
				printf("put is 'B'\n"); 
				value = 'B'; 
				break;
			case 12 : 
				printf("put is '7'\n"); 
				value = '7'; 
				break;
			case 11 : 
				printf("put is '8'\n"); 
				value = '8'; 
				break;
			case 10 : 
				printf("put is '9'\n"); 
				value = '9'; 
				break;
			case 9 : 
				printf("put is 'C'\n");  
				value = 'C'; 
				break;
			case 4 : 
				printf("put is '*'\n");  
				value = '*'; 
				break;
			case 3 : 
				printf("put is '0'\n");  
				value = '0'; 
				break;
			case 2 : 
				printf("put is '#'\n"); 
				value = '#'; 
				break;
			case 1 : 
				printf("put is 'D'\n");  
				value = 'D'; 
				break;
			default: 
				value = 0x00; 
				break;
		}

		if(value == '1')
		{
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
		}

		if(value == '2')
		{
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
		}
	}

	pthread_join(th_stepper_clockwise, &retval);
	pthread_join(th_stepper_anticlockwise, &retval);

	close(fd_stepper);    
	close(fd_key);    
	return 0;
}






