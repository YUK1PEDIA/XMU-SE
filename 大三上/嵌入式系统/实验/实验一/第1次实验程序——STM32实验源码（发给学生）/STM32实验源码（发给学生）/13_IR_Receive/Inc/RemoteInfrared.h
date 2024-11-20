#include "stm32f4xx_hal.h"

#define	Remote_Infrared_DAT_INPUT HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_15)

typedef struct _Remote_Infrared_data_struct //��������߽��յ������ݽṹ������
{
	uint8_t bKeyCodeNot; //�����ĵ�ASIIC��ֵ
	uint8_t bKeyCode; //shift�����±�־
	uint8_t bIDNot; //�����־λ
	uint8_t bID; //�¼���־λ
}Remote_Infrared_data_struct;

typedef union _Remote_Infrared_data_union //��������߽��յ������ݽṹ������
{
	Remote_Infrared_data_struct RemoteInfraredDataStruct; 
	uint32_t uiRemoteInfraredData; 
}Remote_Infrared_data_union;

void Remote_Infrared_KEY_ISR(void);
uint8_t Remote_Infrared_KeyDeCode(void);
