#include "stm32f4xx_hal.h"

#define	Remote_Infrared_DAT_INPUT HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_15)

typedef struct _Remote_Infrared_data_struct //定义红外线接收到的数据结构体类型
{
	uint8_t bKeyCodeNot; //按键的的ASIIC码值
	uint8_t bKeyCode; //shift键按下标志
	uint8_t bIDNot; //断码标志位
	uint8_t bID; //新键标志位
}Remote_Infrared_data_struct;

typedef union _Remote_Infrared_data_union //定义红外线接收到的数据结构体类型
{
	Remote_Infrared_data_struct RemoteInfraredDataStruct; 
	uint32_t uiRemoteInfraredData; 
}Remote_Infrared_data_union;

void Remote_Infrared_KEY_ISR(void);
uint8_t Remote_Infrared_KeyDeCode(void);
