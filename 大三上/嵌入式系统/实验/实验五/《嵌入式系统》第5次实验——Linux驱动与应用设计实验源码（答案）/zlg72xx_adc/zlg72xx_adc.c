#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#define SET_VAL 	_IO('Z', 0)
#define GET_KEY 	_IO('Z', 1)

#define MQ3   	_IO('A',0)		//酒精
#define MQ5   	_IO('A',1)		//气体
#define FLAME 	_IO('A',2)		//火焰
#define LDR   	_IO('A',3)		//光敏
#define RP    	_IO('A',4)		//电位器

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
	int fd_adc;
	int fd_zlg;
	int Temp = 0;
	int Temp_integerPart1,Temp_integerPart2,Temp_integerPart3,Temp_integerPart4;
	char buf[8] = {0};

	fd_adc = open ("/dev/adc_ctrl",O_WRONLY);
	if (fd_adc < 0) 
	{
		perror("open");
		exit(0);
	}

	fd_zlg = open("/dev/zlg72xx", O_RDWR);
	if (fd_zlg < 0) 
	{
		perror("open");
		exit(1);
	}

	printf("Please rotate the potentiometer\n");

	while(1) 
	{
		ioctl(fd_adc, RP, &Temp);
		
		Temp_integerPart1 = Temp/1000;									//千位
		Temp_integerPart2 = (Temp - Temp_integerPart1*1000)/100;						//百位
		Temp_integerPart3 = (Temp - Temp_integerPart1*1000 - Temp_integerPart2*100)/10;				//十位
		Temp_integerPart4 = Temp - Temp_integerPart1*1000 - Temp_integerPart2*100 - Temp_integerPart3*10;		//个位

		if(Temp < 10)
		{
			buf[0] = ' ';
			buf[1] = ' ';
			buf[2] = ' ';
			buf[3] = ' ';
			buf[4] = ' ';
			buf[5] = ' ';
			buf[6] = ' ';
			buf[7] = int_to_char(Temp_integerPart4);
		}

		if(Temp >= 10 && Temp < 100)
		{
			buf[0] = ' ';
			buf[1] = ' ';
			buf[2] = ' ';
			buf[3] = ' ';
			buf[4] = ' ';
			buf[5] = ' ';
			buf[6] = int_to_char(Temp_integerPart3);
			buf[7] = int_to_char(Temp_integerPart4);
		}

		if(Temp >= 100 && Temp < 1000)
		{
			buf[0] = ' ';
			buf[1] = ' ';
			buf[2] = ' ';
			buf[3] = ' ';
			buf[4] = ' ';
			buf[5] = int_to_char(Temp_integerPart2);
			buf[6] = int_to_char(Temp_integerPart3);
			buf[7] = int_to_char(Temp_integerPart4);
		}

		if(Temp >= 1000)
		{
			buf[0] = ' ';
			buf[1] = ' ';
			buf[2] = ' ';
			buf[3] = ' ';
			buf[4] = int_to_char(Temp_integerPart1);
			buf[5] = int_to_char(Temp_integerPart2);
			buf[6] = int_to_char(Temp_integerPart3);
			buf[7] = int_to_char(Temp_integerPart4);
		}

		ioctl(fd_zlg, SET_VAL, buf);
		usleep(500000);
	}

	close (fd_adc);
	close (fd_zlg);
	return 0;
}

