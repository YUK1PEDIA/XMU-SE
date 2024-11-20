/*
 * @Author: your name
 * @Date: 2021-07-12 16:38:25
 * @LastEditTime: 2021-07-21 11:59:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\APP_Operate.c
 */
#include "APP_Operate.h"
#include "APP_StartShow.h"

#include "APP_Audio.h"

#include "BSP_Gt9147.h"
#include "BSP_LcdTouch.h"
#include "BSP_lcd.h"
#include "tim.h"
#include "i2S.h"

#include "BSP_DC_motor.h"
#include "cmsis_os.h"

#include <string.h>

// ��������
extern uint8_t Create_audioPlayTask(void);
extern void Delete_audioPlayTask(void);

extern const uint16_t GT9147_TPX_TBL[5];
ts_globalVariable globalVariable;

void LCD_Touch_AnalysisArea(void);
uint8_t LCD_Touch_Performer(void);

// �������
#define STEERING_GEATR_MOTOR_On __HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 2500)
#define STEERING_GEATR_MOTOR_Off __HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 600)
// �����������
#define STEPPING_MOTOR_On HAL_TIM_Base_Start_IT(&htim5)
#define STEPPING_MOTOR_Off HAL_TIM_Base_Stop_IT(&htim5)
// DCֱ���������   80Ϊת��
#define DC_MOTOR_On Set_DC_Motor_B(80)
#define DC_MOTOR_Off Set_Dc_Motor_Stop()
// �������Ŀ���
#define BUZZER_On HAL_TIM_Base_Start_IT(&htim9)
#define BUZZER_Off HAL_TIM_Base_Stop_IT(&htim9)

static uint8_t STEPPING_MOTOR_Status = 0;
static uint8_t DC_MOTOR_Status = 0;
static uint8_t STEERING_GEATR_Status = 0;
static uint8_t RELAY_Status = 0;
static uint8_t BUZZER_Status = 0;
static uint8_t LED_Status = 0;
/**
 * @description: ɨ�败����(���ò�ѯ��ʽ)
 * @param {uint8_t} mode 0,����ɨ��
 * @return {*} 0,�����޴���;1,�����д���
 */
uint8_t GT9147_Scan(uint8_t mode)
{
    uint8_t buf[4];
    uint8_t i = 0;
    uint8_t res = 0;
    uint8_t temp;
    uint8_t tempsta;
    static uint8_t t = 0; //���Ʋ�ѯ���,�Ӷ�����CPUռ����
    t++;
    if ((t % 10) == 0 || t < 10) //����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
    {
        BSP_GT9147_RD_Reg(GT_GSTID_REG, &mode, 1); //��ȡ�������״̬
        if (mode & 0X80 && ((mode & 0XF) < 6))
        {
            temp = 0;
            BSP_GT9147_WR_Reg(GT_GSTID_REG, &temp, 1); //���־
        }
        if ((mode & 0XF) && ((mode & 0XF) < 6))
        {
            temp = 0XFF << (mode & 0XF); //����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta����
            tempsta = tp_dev.sta;        //���浱ǰ��tp_dev.staֵ
            tp_dev.sta = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;
            tp_dev.x[4] = tp_dev.x[0]; //���津��0������
            tp_dev.y[4] = tp_dev.y[0];
            for (i = 0; i < 5; i++)
            {
                if (tp_dev.sta & (1 << i)) //������Ч?
                {
                    BSP_GT9147_RD_Reg(GT9147_TPX_TBL[i], buf, 4); //��ȡXY����ֵ
                    if (tp_dev.touchtype & 0X01)                  //����
                    {
                        //	tp_dev.y[i]=480-(((uint16_t)buf[1]<<8)+buf[0]);
                        //	tp_dev.x[i]=((uint16_t)buf[3]<<8)+buf[2];
                        tp_dev.y[i] = ((uint16_t)buf[1] << 8) + buf[0];
                        tp_dev.x[i] = 800 - (((uint16_t)buf[3] << 8) + buf[2]);
                    }
                    else
                    {
                        tp_dev.x[i] = ((uint16_t)buf[1] << 8) + buf[0];
                        tp_dev.y[i] = ((uint16_t)buf[3] << 8) + buf[2];
                    }
                    //  printf("x[%d]:%d,y[%d]:%d",i,tp_dev.x[i],i,tp_dev.y[i]);
                }
            }
            res = 1;
            if (tp_dev.x[0] > g_lcddev.width || tp_dev.y[0] > g_lcddev.height) //�Ƿ�����(���곬����)
            {
                if ((mode & 0XF) > 1) //��������������,�򸴵ڶ�����������ݵ���һ������.
                {
                    tp_dev.x[0] = tp_dev.x[1];
                    tp_dev.y[0] = tp_dev.y[1];
                    t = 0; //����һ��,��������������10��,�Ӷ����������
                }
                else //�Ƿ�����,����Դ˴�����(��ԭԭ����)
                {
                    tp_dev.x[0] = tp_dev.x[4];
                    tp_dev.y[0] = tp_dev.y[4];
                    mode = 0X80;
                    tp_dev.sta = tempsta; //�ָ�tp_dev.sta
                }
            }
            else
                t = 0; //����һ��,��������������10��,�Ӷ����������
        }
    }
    if ((mode & 0X8F) == 0X80) //�޴����㰴��
    {
        if (tp_dev.sta & TP_PRES_DOWN) //֮ǰ�Ǳ����µ�
        {
            tp_dev.sta &= ~(1 << 7); //��ǰ����ɿ�
            // printf("x:%d  y:%d",tp_dev.x[0], tp_dev.y[0]);

            globalVariable.CooX = tp_dev.x[0];
            globalVariable.CooY = tp_dev.y[0];

            LCD_Touch_AnalysisArea();
            LCD_Touch_Performer();
        }
        else //֮ǰ��û�б�����
        {
            tp_dev.x[0] = 0xffff;
            tp_dev.y[0] = 0xffff;
            tp_dev.sta &= 0XE0; //�������Ч���
        }
    }
    if (t > 240)
        t = 10; //���´�10��ʼ����
    return res;
}

/**
 * func: ������������
 * para: void
 * ret : void
 */
void LCD_Touch_AnalysisArea(void)
{
    CONSOLE_INFO("Coox: %d     CooY: %d", globalVariable.CooX, globalVariable.CooY);
    /* ��ʼ�������ذ�ť */
    if (((55 <= globalVariable.CooX) && (globalVariable.CooX <= 142)) && ((102 < globalVariable.CooY) && (globalVariable.CooY < 214)))
        globalVariable.TouchFlag = STEPPING_MOTOR_FLAG;

    else if (((156 <= globalVariable.CooX) && (globalVariable.CooX <= 242)) && ((102 < globalVariable.CooY) && (globalVariable.CooY < 214)))
        globalVariable.TouchFlag = DC_MOTOR_FLAG;

    else if (((257 <= globalVariable.CooX) && (globalVariable.CooX <= 344)) && ((102 < globalVariable.CooY) && (globalVariable.CooY < 214)))
        globalVariable.TouchFlag = STEERING_GEATR_FLAG;

    else if (((359 <= globalVariable.CooX) && (globalVariable.CooX <= 447)) && ((102 < globalVariable.CooY) && (globalVariable.CooY < 214)))
        globalVariable.TouchFlag = RELAY_FLAG;

    else if (((456 <= globalVariable.CooX) && (globalVariable.CooX <= 547)) && ((102 < globalVariable.CooY) && (globalVariable.CooY < 214)))
        globalVariable.TouchFlag = BUZZER_FLAG;

    /* ���ֲ���������ذ�ť */
    else if (((663 <= globalVariable.CooX) && (globalVariable.CooX <= 747)) && ((300 < globalVariable.CooY) && (globalVariable.CooY < 410)))
        globalVariable.TouchFlag = LED_FLAG; // ���벥����
    else if (((656 <= globalVariable.CooX) && (globalVariable.CooX <= 800)) && ((0 < globalVariable.CooY) && (globalVariable.CooY < 100)))
        globalVariable.TouchFlag = EXIT_MUSIC_FLAG; // �˳�������
    else if (((315 <= globalVariable.CooX) && (globalVariable.CooX <= 456)) && ((170 < globalVariable.CooY) && (globalVariable.CooY < 330)))
        globalVariable.TouchFlag = START_STOP_MUSIC_FLAG; // ���ź���ͣ
    else if (((70 <= globalVariable.CooX) && (globalVariable.CooX <= 190)) && ((170 < globalVariable.CooY) && (globalVariable.CooY < 330)))
        globalVariable.TouchFlag = ON_SONG_MUSIC_FLAG; // ��һ��
    else if (((520 <= globalVariable.CooX) && (globalVariable.CooX <= 640)) && ((170 < globalVariable.CooY) && (globalVariable.CooY < 330)))
        globalVariable.TouchFlag = NEXT_SONG_MUSIC_FLAG; // ��һ��
    else
        globalVariable.TouchFlag = ERROR_FLAG;
}
/**
 * func: �ж������ְ�ť����ִ����Ӧ�Ķ���
 * para: void
 * ret : void
 */
uint8_t LCD_Touch_Performer(void)
{
//    uint8_t res;

    switch (globalVariable.TouchFlag)
    {
    case STEPPING_MOTOR_FLAG:
//        // ������ֲ�������״̬����ֹ�����ֲ��������棬��
//        if (audiodev.status == 0)
//        {
            CONSOLE_INFO("�������");
            STEPPING_MOTOR_Status ^= 0x01;
            if (STEPPING_MOTOR_Status == 1)
            {
                STEPPING_MOTOR_On;
                LCD_ShowString(53, 225, 90, 30, 24, (uint8_t *)"  ON ");
            }
            else
            {
                STEPPING_MOTOR_Off;
                LCD_ShowString(53, 225, 90, 30, 24, (uint8_t *)"  OFF ");
            }
//        }
        break;

    case DC_MOTOR_FLAG:
//        if (audiodev.status == 0)
//        {
            CONSOLE_INFO("ֱ�����");
            DC_MOTOR_Status ^= 0x01;
            if (DC_MOTOR_Status == 1)
            {
                DC_MOTOR_On;
                LCD_ShowString(155, 225, 90, 30, 24, (uint8_t *)"  ON ");
            }
            else
            {
                DC_MOTOR_Off;
                LCD_ShowString(155, 225, 90, 30, 24, (uint8_t *)"  OFF ");
            }
//        }
        break;

    case STEERING_GEATR_FLAG:
//        if (audiodev.status == 0)
//        {
            CONSOLE_INFO("���");
            STEERING_GEATR_Status ^= 0x01;
            if (STEERING_GEATR_Status == 1)
            {
                STEERING_GEATR_MOTOR_On;
                LCD_ShowString(255, 225, 90, 30, 24, (uint8_t *)"  ON ");
            }
            else
            {
                STEERING_GEATR_MOTOR_Off;
                LCD_ShowString(255, 225, 90, 30, 24, (uint8_t *)"  OFF ");
            }
//        }
        break;

    case RELAY_FLAG:
//        if (audiodev.status == 0)
//        {
            CONSOLE_INFO("�̵���");
            RELAY_Status ^= 0x01;
            if (RELAY_Status == 1)
            {
                RELAY_ON;
                LCD_ShowString(357, 225, 90, 30, 24, (uint8_t *)"  ON  ");
            }
            else
            {
                RELAY_OFF;
                LCD_ShowString(357, 225, 90, 30, 24, (uint8_t *)"  OFF ");
            }
//        }
        break;

    case BUZZER_FLAG:
//        if (audiodev.status == 0)
//        {
            CONSOLE_INFO("������");
            BUZZER_Status ^= 0x01;
            if (BUZZER_Status == 1)
            {
                BUZZER_On;
                LCD_ShowString(462, 225, 90, 30, 24, (uint8_t *)"  ON  ");
            }
            else
            {
                BUZZER_Off;
                LCD_ShowString(462, 225, 90, 30, 24, (uint8_t *)"  OFF ");
            }
//        }
        break;
		
						case LED_FLAG:
							CONSOLE_INFO("LED��");
            LED_Status ^= 0x01;
            if (LED_Status == 1)
            {
								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
								HAL_GPIO_WritePin(GPIOH, GPIO_PIN_15, GPIO_PIN_RESET);
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
								HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
                LCD_ShowString(664, 419, 90, 30, 24, (uint8_t *)"  ON  ");
            }
            else
            {
								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
								HAL_GPIO_WritePin(GPIOH, GPIO_PIN_15, GPIO_PIN_SET);
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
								HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
                LCD_ShowString(664, 419, 90, 30, 24, (uint8_t *)"  OFF ");
            }
						break;
    default:
        // globalVariable.TouchFlag = ERROR_FLAG;
        break;
    }
    return 0;
}
