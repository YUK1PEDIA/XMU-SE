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

#define KeyDevice "/dev/farsight_keys"
#define BuzzerPwmDevice "/dev/buzzer"

static struct input_event inputevent;

int main(int argc,char* argv[])
{
	int fd_key;
	int fd_buzzer_pwm;
	int ret;
	int err=0;
	int buf[2] = {0};
	int buzzer = 0;

	fd_key = open(KeyDevice,O_RDWR);
	if (fd_key < 0) {
		perror("Can't open file farsight_keys,Check your path");
		return -1;
	} 

	fd_buzzer_pwm = open(BuzzerPwmDevice, O_WRONLY);
    	if(fd_buzzer_pwm < 0)
    	{
        		perror("open buzzer driver");
        		return -1;      
    	}

	ret = ioctl(fd_buzzer_pwm,ROTATE_OFF);
	if(ret < 0)
		perror("ioctl buzzer_ctl driver ");

	printf("Turn D15 to the left, others to the right\n\n");

	printf("Push KEY1 than sound the buzzer, Push KEY1 again than mute the buzzer\n");

	while(1)
	{
		err=read(fd_key,buf,sizeof(buf));

		if(err>0)
		{
			if(buf[0] == 1)
			{
				if(buf[1] == 0)
				{
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
				}
			}
		}
	}

	close(fd_buzzer_pwm);    
	close(fd_key);    
	return 0;
}
