#include "RemoteInfrared.h"
#include "stdio.h"

#define REPEAT_KEY  0xEE

extern __IO uint32_t GlobalTimingDelay100us;
extern __IO uint32_t GlobalTimingDelay100usTx;
__IO uint32_t FlagGotKey = 0;
__IO Remote_Infrared_data_union RemoteInfrareddata;
const uint32_t TIME_DELAY_6MS = 60;
const uint32_t TIME_DELAY_10MS = 100;

void Remote_Infrared_KEY_ISR(void)
{
	static __IO uint8_t  bBitCounter = 0; 	//键盘帧位计数
  	static __IO uint32_t bKeyCode = 0;
	bBitCounter++;

	if(bBitCounter == 1)        	// 开始拉低9ms
	{
	        	if(Remote_Infrared_DAT_INPUT) 	// 高电平无效
        		{
            			bBitCounter = 0;
        		}
        		else
        		{
            			GlobalTimingDelay100us = TIME_DELAY_10MS;
        		}
	}
	else if(bBitCounter == 2)   	// 4.5ms的高脉冲
	{
        		if(Remote_Infrared_DAT_INPUT)
        		{
            			if((GlobalTimingDelay100us > 2) && (GlobalTimingDelay100us < 18))
            			{
                			GlobalTimingDelay100us = TIME_DELAY_6MS;
            			}
            			else
            			{ 
                			bBitCounter = 0; 
//                			printf(".");
            			}
        		}
        		else
        		{
            			bBitCounter = 0;            
        		}
	}
	else if(bBitCounter == 3)   	// 4.5ms的高脉冲
	{
        		if(Remote_Infrared_DAT_INPUT)
        		{
            			bBitCounter = 0; 
        		}
        		else
        		{
            			if((GlobalTimingDelay100us > 5) && (GlobalTimingDelay100us < 20))
            			{
                			GlobalTimingDelay100us = TIME_DELAY_6MS;
//                			printf("引导码");
            			}
            			else if((GlobalTimingDelay100us > 32) && (GlobalTimingDelay100us < 46))
            			{
                			bBitCounter = 0;
                			RemoteInfrareddata.uiRemoteInfraredData = bKeyCode;
                			bBitCounter = 0;
                			FlagGotKey = 1;
            			}            
            			else
            			{
                			bBitCounter = 0; 
            			}          
        		}
	}    
	else if(bBitCounter > 3 && bBitCounter < 68)	 //接收8位数据
	{  
        		if(Remote_Infrared_DAT_INPUT)
        		{
            			if((GlobalTimingDelay100us > 50) && (GlobalTimingDelay100us < 58))
            			{
                			GlobalTimingDelay100us = TIME_DELAY_6MS;
            			}
            			else
            			{
                			bBitCounter = 0; 
            			}           
        		}
        		else
        		{
            			if((GlobalTimingDelay100us > 50) && (GlobalTimingDelay100us < 58)) // '0'
            			{
                			GlobalTimingDelay100us = TIME_DELAY_6MS;
		        		bKeyCode <<= 1;  // MSB First 
                			bKeyCode += 0x00;
            			}
            			else if((GlobalTimingDelay100us > 40) && (GlobalTimingDelay100us < 48)) //'1'
            			{
                			GlobalTimingDelay100us = TIME_DELAY_6MS;            
		        		bKeyCode <<= 1;  // MSB First 
                			bKeyCode += 0x01;
            			}              
            			else
            			{
                			bBitCounter = 0; 
            			}  
		}
       		if(bBitCounter == 67)
        		{
            			RemoteInfrareddata.uiRemoteInfraredData = bKeyCode;
            			bBitCounter = 0;
            			FlagGotKey = 1;
        		}
	}
	else
	{
		bBitCounter = 0;
	}
}

uint8_t Remote_Infrared_KeyDeCode(void)
{
	if (FlagGotKey == 1)	//通码
	{
        		FlagGotKey = 0;

        		if((RemoteInfrareddata.RemoteInfraredDataStruct.bID == (uint8_t)~ RemoteInfrareddata.RemoteInfraredDataStruct.bIDNot) && (RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCode == (uint8_t)~ RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCodeNot))
        		{
            			printf("\n\r IR Receive KeyCode = 0x%02X, ", RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCode);

			switch(RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCode)
			{
				case 0:
					printf("ERROR  ");
					break;

				case 0xEA:
					printf("开关    ");
					break;

				case 0xDA:
					printf("静音    ");
					break;

				case 0x68:
					printf("空白    ");
					break;

				case 0x5A:
					printf("i    ");
					break;

				case 0x4A:
					printf("快进    ");
					break;

				case 0x0A:
					printf("鼠标    ");
					break;

				case 0xF0:
					printf("直播    ");
					break;

				case 0x32:
					printf("点播    ");
					break;

				case 0x1A:
					printf("音量-    ");
					break;

				case 0xD8:
					printf("音量+    ");
					break;

				case 0xF2:
					printf("设置    ");
					break;

				case 0x58:
					printf("菜单    ");
					break;

				case 0x60:
					printf("LEFT    ");
					break;

				case 0x70:
					printf("RIGHT    ");
					break;

				case 0xC2:
					printf("UP    ");
					break;

				case 0x50:
					printf("DOWN    ");
					break;

				case 0x40:
					printf("OK    ");
					break;

				case 0x72:
					printf("主页    ");
					break;

				case 0xB2:
					printf("返回    ");
					break;

				case 0x08:
					printf("1      ");
					break;

				case 0x88:
					printf("2      ");
					break;

				case 0x48:
					printf("3      ");
					break;

				case 0xC8:
					printf("4      ");
					break;

				case 0x28:
					printf("5      ");
					break;

				case 0xA8:
					printf("6      ");
					break;

				case 0xE8:
					printf("7      ");
					break;

				case 0x18:
					printf("8      ");
					break;

				case 0x98:
					printf("9      ");
					break;

				case 0x38:
					printf("HTML5/Flash    ");
					break;

				case 0xB8:
					printf("0      ");
					break;

				case 0x78:
					printf("删除   ");
					break;

                			default:
                    				printf("Unknown key!");
			}
        		}
        		else
        		{
          			printf("\n\r ERROR          0x%08X", RemoteInfrareddata.uiRemoteInfraredData);
        		}
    	}
	return RemoteInfrareddata.RemoteInfraredDataStruct.bKeyCode;
}

