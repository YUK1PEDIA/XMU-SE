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

#define IOCTL_MAGIC 	'D'
#define DC_MOTOR_ON 	_IO(IOCTL_MAGIC, 0) 
#define DC_MOTOR_OFF 	_IO(IOCTL_MAGIC, 1) 
#define DC_MOTOR_DIR	_IOW(IOCTL_MAGIC, 2, int)	
#define DC_MOTOR_RATE	_IOW(IOCTL_MAGIC, 3, int)

#define KeyDevice "/dev/farsight_keys"
#define DcmotorDevice "/dev/dc_motor"

static struct input_event inputevent;

int main()
{
	int fd_key;
	int fd_dcmotor;
	int i;
	int err=0;
	int buf[2] = {0};
	int clockwise=0;
	int anticlockwise=0;

	fd_key=open(KeyDevice,O_RDWR);
	if (fd_key < 0) 
	{
		perror("Can't open file farsight_keys,Check your path");
		return -1;
	} 

	fd_dcmotor=open(DcmotorDevice,O_RDWR);
	if (fd_dcmotor < 0) 
	{
		perror("Can't open file farsight_led,Check your path");
		return -1;
	} 

	ioctl(fd_dcmotor, DC_MOTOR_OFF);

	printf("Turn D12 and D13 to the left, others to the right\n\n");

	printf("Push KEY1 than DC motor rotates clockwise, Push KEY1 again than DC motor stop; Push KEY2 than DC motor rotates counterclockwise,  Push KEY2  again than DC motor stop\n");

	while(1)
	{
		err=read(fd_key,buf,sizeof(buf));

		if(err>0)
		{
			if(buf[0] == 1)
			{
				if(buf[1] == 0)
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
			}
			if(buf[0] == 2)
			{
				if(buf[1] == 0)
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
		}
	}
	close(fd_dcmotor);    
	close(fd_key);    
	return 0;
}




