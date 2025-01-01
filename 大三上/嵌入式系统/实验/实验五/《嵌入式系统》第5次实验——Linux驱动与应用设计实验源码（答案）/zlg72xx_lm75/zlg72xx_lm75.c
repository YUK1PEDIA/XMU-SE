#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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

char int_to_char_dot(int i)
{
	switch(i)
	{
		case 0: return 'G';
		case 1: return 'H';
		case 2: return 'I';
		case 3: return 'J';
		case 4: return 'K';
		case 5: return 'L';
		case 6: return 'M';
		case 7: return 'N';
		case 8: return 'O';
		case 9: return 'P';
		default: return '0';
	}
}

int main(int argc, const char *argv[])
{
	int fd_lm75;
	int fd_zlg;
	int data;
	int Temp_integerPart1,Temp_integerPart2;
	int Temp_fractionalPart1,Temp_fractionalPart2,Temp_fractionalPart3,Temp_fractionalPart4,Temp_fractionalPart5,Temp_fractionalPart6;
	float Temp;
	char buf[8] = {0};

	fd_lm75 = open ("/dev/temp",O_RDWR);
	if (fd_lm75 < 0) 
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

	printf("Please press your finger on the temperature sensor chip\n");

	while(1) 
	{
		read (fd_lm75, (char *)&data, sizeof(data));

		Temp = 0.125*(data>>5);

		Temp_integerPart1 = Temp/10;				//温度值整数部分的十位
		Temp_integerPart2 = Temp - Temp_integerPart1*10;		//温度值整数部分的个位

		Temp_fractionalPart1 = (Temp - (Temp_integerPart1*10 + Temp_integerPart2))*10 ;		//温度值小数点后第1位
		Temp_fractionalPart2 = ((Temp - (Temp_integerPart1*10 + Temp_integerPart2))*10)*10-  Temp_fractionalPart1*10;		//温度值小数点后第2位
		Temp_fractionalPart3 = (((Temp - (Temp_integerPart1*10 + Temp_integerPart2))*10)*10-  Temp_fractionalPart1*10)*10 - Temp_fractionalPart2*10;		//温度值小数点后第3位

//		Temp_fractionalPart4 = ((((Temp - (Temp_integerPart1*10 + Temp_integerPart2))*10)*10-  Temp_fractionalPart1*10)*10 - Temp_fractionalPart2*10)*10 - Temp_fractionalPart3*10;		//温度值小数点后第4位
//		Temp_fractionalPart5 = (((((Temp - (Temp_integerPart1*10 + Temp_integerPart2))*10)*10-  Temp_fractionalPart1*10)*10 - Temp_fractionalPart2*10)*10 - Temp_fractionalPart3*10)*10 - Temp_fractionalPart4*10;		//温度值小数点后第5位
//		Temp_fractionalPart6 = ((((((Temp - (Temp_integerPart1*10 + Temp_integerPart2))*10)*10-  Temp_fractionalPart1*10)*10 - Temp_fractionalPart2*10)*10 - Temp_fractionalPart3*10)*10 - Temp_fractionalPart4*10)*10 - Temp_fractionalPart5*10;		//温度值小数点后第6位

//		buf[0] = int_to_char(Temp_integerPart1);
//		buf[1] = int_to_char_dot(Temp_integerPart2);
//		buf[2] = int_to_char(Temp_fractionalPart1);
//		buf[3] = int_to_char(Temp_fractionalPart2);
//		buf[4] = int_to_char(Temp_fractionalPart3);
//		buf[5] = int_to_char(Temp_fractionalPart4);
//		buf[6] = int_to_char(Temp_fractionalPart5);
//		buf[7] = int_to_char(Temp_fractionalPart6);

		buf[0] = ' ';
		buf[1] = ' ';
		buf[2] = ' ';
		buf[3] = int_to_char(Temp_integerPart1);
		buf[4] = int_to_char_dot(Temp_integerPart2);
		buf[5] = int_to_char(Temp_fractionalPart1);
		buf[6] = int_to_char(Temp_fractionalPart2);
		buf[7] = int_to_char(Temp_fractionalPart3);

		Temp_integerPart1 = 1;
		buf[3] = int_to_char(Temp_integerPart1);
		Temp_integerPart2 = 1;
		buf[4] = int_to_char_dot(Temp_integerPart2);
		buf[5] = ' ';
		buf[6] = ' ';
		buf[7] = ' ';

		ioctl(fd_zlg, SET_VAL, buf);
		sleep(5);
	}

	close (fd_lm75);
	close (fd_zlg);
	return 0;
}

