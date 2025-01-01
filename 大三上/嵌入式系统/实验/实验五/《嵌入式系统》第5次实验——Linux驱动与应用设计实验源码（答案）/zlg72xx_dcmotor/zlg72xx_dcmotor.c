#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <fcntl.h>
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

#define IOCTL_MAGIC 	'D'
#define DC_MOTOR_ON 	_IO(IOCTL_MAGIC, 0) 
#define DC_MOTOR_OFF 	_IO(IOCTL_MAGIC, 1) 
#define DC_MOTOR_DIR	_IOW(IOCTL_MAGIC, 2, int)	
#define DC_MOTOR_RATE	_IOW(IOCTL_MAGIC, 3, int)

#define KeyDevice "/dev/zlg72xx"
#define DcmotorDevice "/dev/dc_motor"

int main(int argc, const char *argv[])
{
	int fd_key;
	int fd_dcmotor;
	int key = 0;
	char value ;
	int i = 0;
	char buf[8] = {0};
	int clockwise=0;
	int anticlockwise=0;

	fd_key = open(KeyDevice, O_RDWR);
	if (fd_key < 0) 
	{
		perror("open");
		exit(1);
	}

	fd_dcmotor=open(DcmotorDevice,O_RDWR);
	if (fd_dcmotor < 0) 
	{
		perror("Can't open file farsight_dcmotor,Check your path");
		return -1;
	} 

	ioctl(fd_dcmotor, DC_MOTOR_OFF);

	printf("Turn D12 and D13 to the left, others to the right\n\n");

	printf("Push 1 than DC motor rotates clockwise, Push 1 again than DC motor stop; Push 2 than DC motor rotates counterclockwise,  Push 2  again than DC motor stop\n");

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
			if(clockwise == 0)
			{
				i = 1;
				ioctl(fd_dcmotor, DC_MOTOR_ON);
				ioctl(fd_dcmotor, DC_MOTOR_DIR, &i);
				clockwise = 1;
				anticlockwise = 0;

			}
			else
			{
				ioctl(fd_dcmotor, DC_MOTOR_OFF);
				clockwise = 0;
				anticlockwise = 0;

			}
		}

		if(value == '2')
		{
			if(anticlockwise == 0)
			{
				i = 0;
				ioctl(fd_dcmotor, DC_MOTOR_ON);
				ioctl(fd_dcmotor, DC_MOTOR_DIR, &i);
				clockwise = 0;
				anticlockwise = 1;
			}
			else
			{
				ioctl(fd_dcmotor, DC_MOTOR_OFF);
				clockwise = 0;
				anticlockwise = 0;
			}
		}
	}

	close(fd_dcmotor);    
	close(fd_key);    
	return 0;
}

