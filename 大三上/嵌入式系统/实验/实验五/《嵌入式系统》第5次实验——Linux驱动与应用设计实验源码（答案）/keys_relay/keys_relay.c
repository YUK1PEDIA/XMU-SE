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

#define RELAY_ON 	0 
#define RELAY_OFF 	1

#define KeyDevice "/dev/farsight_keys"
#define RelayDevice "/dev/relay"

static struct input_event inputevent;

int main()
{
	int fd_key;
	int fd_relay;
    	int ret;
	int err=0;
	int buf[2] = {0};
	int relay=0;

	fd_key=open(KeyDevice,O_RDWR);
	if (fd_key < 0) 
	{
		perror("Can't open file farsight_keys,Check your path");
		return -1;
	} 

	fd_relay=open(RelayDevice,O_RDWR);
	if (fd_relay < 0) 
	{
		perror("Can't open file farsight_relay,Check your path");
		return -1;
	} 

	printf("Turn D16 to the left, others to the right\n\n");

	printf("Push 1 than turn on Relay, Push 1 again than turn off Relay\n");

	while(1)
	{
		err=read(fd_key,buf,sizeof(buf));

		if(err>0)
		{
			if(buf[0] == 1)
			{
				if(buf[1] == 0)
				{
					if(relay == 0)
					{
						ioctl(fd_relay, RELAY_ON);
						relay = 1;
					}
					else
					{
						ioctl(fd_relay, RELAY_OFF);
						relay = 0;
					}
				}
			}
		}
	}

	close(fd_relay);    
	close(fd_key);    
	return 0;
}




