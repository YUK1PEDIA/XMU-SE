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

#define IOCTL_MAGIC 	'S'
#define ROTATE_0 		_IO(IOCTL_MAGIC, 0) 
#define ROTATE_30 	_IO(IOCTL_MAGIC, 1) 
#define ROTATE_60 	_IO(IOCTL_MAGIC, 2) 
#define ROTATE_90 	_IO(IOCTL_MAGIC, 3) 
#define ROTATE_120 	_IO(IOCTL_MAGIC, 4) 
#define ROTATE_150 	_IO(IOCTL_MAGIC, 5) 
#define SET_ANGLE	_IO(IOCTL_MAGIC, 6)

#define KeyDevice 		"/dev/farsight_keys"
#define ServoDevice 	"/dev/servo"

#define Number 1000000

static struct input_event inputevent;

unsigned	int fd_key;
unsigned	int fd_servo;
unsigned	int key=0;

void * servo_start(void * data)			//陀机转动线程		
{
	int angle;
	while(1)
	{
	        if(key == 1)
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

int main()
{
	int err=0;
	int buf[2] = {0};

	void * retval;
	pthread_t th_servo_start;

	fd_key=open(KeyDevice,O_RDWR);
	if (fd_key < 0) 
	{
		perror("Can't open file farsight_keys,Check your path");
		return -1;
	} 

	fd_servo = open(ServoDevice, O_RDWR);
	if (fd_servo < 0) {
		perror("Can't open file farsight_servo,Check your path");
		return -1;
	}

	pthread_create(&th_servo_start, NULL, servo_start, 0);

	printf("Turn D6 to the left, others to the right\n\n");

	printf("Push 1 than Steering engine rotates, Push 1 again than Steering engine stop\n");

	while(1)
	{
	        err=read(fd_key,buf,sizeof(buf));

	        if(err>0 && buf[0] == 1 && buf[1] == 0)
	        {
		if(key == 0)
		{
			key = 1;
		}
		else
		{
			key = 0;
		}
	        }
	}

	pthread_join(th_servo_start, &retval);

	close(fd_servo);    
	close(fd_key);    
	return 0;
}




