#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <linux/input.h>

#define SET_VAL _IO('Z', 0)
#define GET_KEY _IO('Z', 1)

char int_to_char(int i)
{
	switch(i)
	{
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		default: return '0';
	}
}

int main(int argc, const char *argv[])
{
//	time_t t;
//	struct tm *tm;

	int hour = 23;
	int minute = 59;
	int second = 50;

	int hour_high = 0;
	int hour_low = 0;
	int minute_high = 0;
	int minute_low = 0;
	int second_high = 0;
	int second_low = 0;

	int key = 0;
	char value ;
	int i = 0;
	char buf[8] = {0};

	int fd = open("/dev/zlg72xx", O_RDWR);
	if (fd < 0) 
	{
		perror("open");
		exit(1);
	}

	while(1) 
	{
		second ++;
		if(second == 60)
		{
			second = 0;
			minute ++;
			if(minute == 60)
			{
				minute = 0;
				hour ++;
				if(hour == 24)
					hour = 0;
			}
		}

//		time(&t);
//		tm = localtime(&t);

//		hour = tm->tm_hour;
//		minute = tm->tm_min;
//		second = tm->tm_sec;

		hour_high = hour/10;                   
		hour_low = hour - hour_high*10;                  
		minute_high = minute/10;                   
		minute_low = minute - minute_high*10;                     
		second_high = second/10;                   
		second_low = second - second_high*10;       

		buf[7] = int_to_char(second_low);
		buf[6] = int_to_char(second_high);
		buf[5] = '-';
		buf[4] = int_to_char(minute_low);
		buf[3] = int_to_char(minute_high);
		buf[2] = '-';
		buf[1] = int_to_char(hour_low);
		buf[0] = int_to_char(hour_high);

		ioctl(fd, SET_VAL, buf);
		sleep(1);
	}
	return 0;
}

