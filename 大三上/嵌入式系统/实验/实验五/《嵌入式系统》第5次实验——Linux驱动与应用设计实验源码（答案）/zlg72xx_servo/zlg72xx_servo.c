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

#define IOCTL_MAGIC 	'S'
#define ROTATE_0 		_IO(IOCTL_MAGIC, 0) 
#define ROTATE_30 	_IO(IOCTL_MAGIC, 1) 
#define ROTATE_60 	_IO(IOCTL_MAGIC, 2) 
#define ROTATE_90 	_IO(IOCTL_MAGIC, 3) 
#define ROTATE_120 	_IO(IOCTL_MAGIC, 4) 
#define ROTATE_150 	_IO(IOCTL_MAGIC, 5) 
#define SET_ANGLE	_IO(IOCTL_MAGIC, 6)

#define KeyDevice 		"/dev/zlg72xx"
#define ServoDevice 	"/dev/servo"

#define Number 1000000

unsigned	int fd_key;
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

int main(int argc, const char *argv[])
{
	int key = 0;
	char value ;
	int i = 0;
	char buf[8] = {0};

	void * retval;
	pthread_t th_servo_start;

	fd_key = open(KeyDevice, O_RDWR);
	if (fd_key < 0) 
	{
		perror("open");
		exit(1);
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
			}
			else
			{
				key1 = 0;
			}
		}
	}

	pthread_join(th_servo_start, &retval);

	close(fd_servo);    
	close(fd_key);    
	return 0;
}






