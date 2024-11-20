/*
 * @Author: your name
 * @Date: 2021-07-12 09:15:28
 * @LastEditTime: 2021-07-12 09:24:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_GT9147.c
 */
#include "BSP_GT9147.h"
#include "BSP_MyI2C.h"
#include <string.h>





//GT9147���ò�����
//��һ���ֽ�Ϊ�汾��(0X60),���뱣֤�µİ汾�Ŵ��ڵ���GT9147�ڲ�
//flashԭ�а汾��,�Ż��������.
const uint8_t GT9147_CFG_TBL[]=
{
  0X60,0XE0,0X01,0X20,0X03,0X05,0X35,0X00,0X02,0X08,
  0X1E,0X08,0X50,0X3C,0X0F,0X05,0X00,0X00,0XFF,0X67,
  0X50,0X00,0X00,0X18,0X1A,0X1E,0X14,0X89,0X28,0X0A,
  0X30,0X2E,0XBB,0X0A,0X03,0X00,0X00,0X02,0X33,0X1D,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X32,0X00,0X00,
  0X2A,0X1C,0X5A,0X94,0XC5,0X02,0X07,0X00,0X00,0X00,
  0XB5,0X1F,0X00,0X90,0X28,0X00,0X77,0X32,0X00,0X62,
  0X3F,0X00,0X52,0X50,0X00,0X52,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
  0X0F,0X03,0X06,0X10,0X42,0XF8,0X0F,0X14,0X00,0X00,
  0X00,0X00,0X1A,0X18,0X16,0X14,0X12,0X10,0X0E,0X0C,
  0X0A,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X29,0X28,0X24,0X22,0X20,0X1F,0X1E,0X1D,
  0X0E,0X0C,0X0A,0X08,0X06,0X05,0X04,0X02,0X00,0XFF,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
  0XFF,0XFF,0XFF,0XFF,
};
const uint16_t GT9147_TPX_TBL[5] = {GT_TP1_REG, GT_TP2_REG, GT_TP3_REG, GT_TP4_REG, GT_TP5_REG};
//����GT9147���ò���
//mode:0,���������浽flash
//     1,�������浽flash
uint8_t BSP_GT9147_Send_Cfg(uint8_t mode)
{
    uint8_t buf[2];
    uint8_t i = 0;
    buf[0] = 0;
    buf[1] = mode; //�Ƿ�д�뵽GT9147 FLASH?  ���Ƿ���籣��
    for (i = 0; i < sizeof(GT9147_CFG_TBL); i++)
        buf[0] += GT9147_CFG_TBL[i]; //����У���
    buf[0] = (~buf[0]) + 1;
    BSP_GT9147_WR_Reg(GT_CFGS_REG, (uint8_t *)GT9147_CFG_TBL, sizeof(GT9147_CFG_TBL)); //���ͼĴ�������
    BSP_GT9147_WR_Reg(GT_CHECK_REG, buf, 2);                                           //д��У���,�����ø��±��
    return 0;
}
//��GT9147д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t BSP_GT9147_WR_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    uint8_t ret = 0;
    MY_IIC_Start();
    MY_IIC_Send_Byte(GT_CMD_WR); //����д����
    MY_IIC_Wait_Ack();
    MY_IIC_Send_Byte(reg >> 8); //���͸�8λ��ַ
    MY_IIC_Wait_Ack();
    MY_IIC_Send_Byte(reg & 0XFF); //���͵�8λ��ַ
    MY_IIC_Wait_Ack();
    for (i = 0; i < len; i++)
    {
        MY_IIC_Send_Byte(buf[i]); //������
        ret = MY_IIC_Wait_Ack();
        if (ret)
            break;
    }
    MY_IIC_Stop(); //����һ��ֹͣ����
    return ret;
}
//��GT9147����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���
void BSP_GT9147_RD_Reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    MY_IIC_Start();
    MY_IIC_Send_Byte(GT_CMD_WR); //����д����
    MY_IIC_Wait_Ack();
    MY_IIC_Send_Byte(reg >> 8); //���͸�8λ��ַ
    MY_IIC_Wait_Ack();
    MY_IIC_Send_Byte(reg & 0XFF); //���͵�8λ��ַ
    MY_IIC_Wait_Ack();
    MY_IIC_Start();
    MY_IIC_Send_Byte(GT_CMD_RD); //���Ͷ�����
    MY_IIC_Wait_Ack();
    for (i = 0; i < len; i++)
    {
        buf[i] = MY_IIC_Read_Byte(i == (len - 1) ? 0 : 1); //������
    }
    MY_IIC_Stop(); //����һ��ֹͣ����
}

static void set_TouchINT_OutPutMode(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = TOUCH_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(TOUCH_INT_GPIO_Port, &GPIO_InitStruct);
}
//��ʼ��GT9147������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ��
uint8_t BSP_GT9147_Init(void)
{
    char buf[20] = {0};
    uint8_t temp[5] = {0};

    //GT_RST=0;				//��λ
    HAL_GPIO_WritePin(TOUCH_RST_GPIO_Port, TOUCH_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    //GT_RST=1;				//�ͷŸ�λ
    HAL_GPIO_WritePin(TOUCH_RST_GPIO_Port, TOUCH_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(10);

    set_TouchINT_OutPutMode();
    HAL_Delay(100);

    BSP_GT9147_RD_Reg(GT_PID_REG, temp, 4); //��ȡ��ƷID
    temp[4] = 0;
    sprintf(buf, "TOUCH ID:%s", temp); //��ӡID
    CONSOLE_INFO("TOUCH ID:%s", temp);   //��ӡID
                                       // LCD_ShowString(50, TP_TOUCH_ID_NUM, 360, 24, 24, (uint8_t *)buf);

    if (strcmp((char *)temp, "9147") == 0) //ID==9147
    {
        temp[0] = 0X02;
        BSP_GT9147_WR_Reg(GT_CTRL_REG, temp, 1); //��λGT9147
        BSP_GT9147_RD_Reg(GT_CFGS_REG, temp, 1); //��ȡGT_CFGS_REG�Ĵ���
        if (temp[0] < 0X60)                      //Ĭ�ϰ汾�Ƚϵ�,��Ҫ����flash����
        {
            CONSOLE_INFO("Default Ver:%d", temp[0]);
            BSP_GT9147_Send_Cfg(1); //���²���������
        }
        HAL_Delay(10);
        temp[0] = 0X00;
        BSP_GT9147_WR_Reg(GT_CTRL_REG, temp, 1); //������λ
        return 0;
    }
    return 1;
}
