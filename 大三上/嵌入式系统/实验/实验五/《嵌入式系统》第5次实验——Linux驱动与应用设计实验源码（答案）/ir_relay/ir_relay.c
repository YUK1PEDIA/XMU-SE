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

#define RELAY_ON 	0 
#define RELAY_OFF 	1

#define IrDevice "/dev/input/event0"
#define RelayDevice "/dev/relay"

static struct input_event inputevent;

int main(int argc,char* argv[])
{
	int fd_ir;
	int fd_relay;
	int relay=0;
	int err=0;

	fd_ir=open(IrDevice,O_RDWR);
	if (fd_ir < 0) 
	{
		perror("Open file error, Check your path ");
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
	close(fd_relay);    
	close(fd_ir);    

	return 0;
}

