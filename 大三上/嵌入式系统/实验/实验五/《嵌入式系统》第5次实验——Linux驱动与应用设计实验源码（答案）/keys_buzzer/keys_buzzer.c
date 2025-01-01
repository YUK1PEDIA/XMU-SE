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

#define Buzzer_on   1
#define Buzzer_off  0

#define KeyDevice "/dev/farsight_keys"
#define BuzzerDevice "/dev/buzzer_ctl"

static struct input_event inputevent;

int main()
{
	int fd_key;
	int fd_buzzer;
    	int ret;
	int err=0;
	int buf[2] = {0};
	int buzzer=0;

	fd_key=open(KeyDevice,O_RDWR);
	if (fd_key < 0) 
	{
		perror("Can't open file farsight_keys,Check your path");
		return -1;
	} 

	fd_buzzer=open(BuzzerDevice,O_RDWR);
	if (fd_buzzer < 0) 
	{
		perror("Can't open file farsight_buzzer,Check your path");
		return -1;
	} 

	ret = ioctl(fd_buzzer,Buzzer_off);
	if(ret < 0)
	           	perror("ioctl buzzer_ctl driver ");

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
						ret = ioctl(fd_buzzer,Buzzer_on);
						if(ret < 0)
	           						perror("ioctl buzzer_ctl driver ");
						buzzer = 1;
					}
					else
					{
						ret = ioctl(fd_buzzer,Buzzer_off);
						if(ret < 0)
	           						perror("ioctl buzzer_ctl driver ");
						buzzer = 0;
					}
				}
			}
		}
	}

	close(fd_buzzer);    
	close(fd_key);    
	return 0;
}




