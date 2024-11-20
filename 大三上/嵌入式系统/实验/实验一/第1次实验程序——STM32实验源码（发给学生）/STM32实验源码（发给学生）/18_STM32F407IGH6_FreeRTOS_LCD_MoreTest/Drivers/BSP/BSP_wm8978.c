/*
 * @Author: your name
 * @Date: 2021-07-01 18:32:46
 * @LastEditTime: 2021-07-12 09:58:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\F407_Multi_core_testing\UserFunctions\BSP\wm8978.c
 */
#include "BSP_wm8978.h"
#include "i2c.h"
#include "i2s.h"

#define I2C_Open_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2C_Open_LONG_TIMEOUT         ((uint32_t)0xffff)
__IO uint32_t  wm8978_I2CTimeout = I2C_Open_FLAG_TIMEOUT;

/**
 * WM8978�Ĵ���ֵ������(�ܹ�58���Ĵ���,0~57),ռ��116�ֽ��ڴ�
 * ��ΪWM8978��IIC������֧�ֶ�����,�����ڱ��ر������мĴ���ֵ
 * дWM8978�Ĵ���ʱ,ͬ�����µ����ؼĴ���ֵ
 * ���Ĵ���ʱ,ֱ�ӷ��ر��ر���ļĴ���ֵ.
 * ע��:WM8978�ļĴ���ֵ��9λ��,����Ҫ��uint16_t���洢.
 **/
static uint16_t WM8978_REGVAL_TBL[58]=
{
  0X0000,0X0000,0X0000,0X0000,0X0050,0X0000,0X0140,0X0000,
  0X0000,0X0000,0X0000,0X00FF,0X00FF,0X0000,0X0100,0X00FF,
  0X00FF,0X0000,0X012C,0X002C,0X002C,0X002C,0X002C,0X0000,
  0X0032,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,
  0X0038,0X000B,0X0032,0X0000,0X0008,0X000C,0X0093,0X00E9,
  0X0000,0X0000,0X0000,0X0000,0X0003,0X0010,0X0010,0X0100,
  0X0100,0X0002,0X0001,0X0001,0X0039,0X0039,0X0039,0X0039,
  0X0001,0X0001
};

/**
 * @description: д�Ĵ���
 * @param {uint8_t} reg_addr
 * @param {uint16_t} data
 * @return {*}
 */
static uint8_t BSP_WM8978_Register_Wirter(uint8_t reg_addr, uint16_t data)
{
  uint8_t pData[10] = {0};

  pData[0] = (reg_addr << 1) | ((data >> 8) & 0x01);
  pData[1] = data & 0xFF;
  if( HAL_I2C_Master_Transmit(&hi2c1, WM8978_WIRTE_ADDRESS, pData, 2, wm8978_I2CTimeout) != HAL_OK) {
    return 1;
  }

  WM8978_REGVAL_TBL[reg_addr] = data;	//����Ĵ���ֵ������

  return 0;
}

/**
 * @description: WM8978���Ĵ���
 * @param {uint8_t} reg �Ĵ�����ַ(��ȡ���ؼĴ���ֵ�������ڵĶ�Ӧֵ)
 * @return {*} �Ĵ���ֵ
 */
static uint16_t BSP_WM8978_Register_Read(uint8_t reg)
{
  return WM8978_REGVAL_TBL[reg];
}

/**
 * @description: WM8978��ʼ��
 * @param {*}
 * @return {*}
 */
uint8_t BSP_WM8978_Init(void)
{
  uint8_t res;

  res=BSP_WM8978_Register_Wirter(0,0);	//��λWM8978
  if(res)return 1;			//����ָ��ʧ��,WM8978�쳣

  //����Ϊͨ������
  BSP_WM8978_Register_Wirter(1,0X1B);	//R1,MICEN����Ϊ1(MICʹ��),BIASEN����Ϊ1(ģ��������),VMIDSEL[1:0]����Ϊ:11(5K)
  BSP_WM8978_Register_Wirter(2,0X1B0);	//R2,ROUT1,LOUT1���ʹ��(�������Թ���),BOOSTENR,BOOSTENLʹ��
  BSP_WM8978_Register_Wirter(3,0X6C);	//R3,LOUT2,ROUT2���ʹ��(���ȹ���),RMIX,LMIXʹ��
  BSP_WM8978_Register_Wirter(6,0);		//R6,MCLK���ⲿ�ṩ
  BSP_WM8978_Register_Wirter(43,1<<4);	//R43,INVROUT2����,��������
  BSP_WM8978_Register_Wirter(47,1<<8);	//R47����,PGABOOSTL,��ͨ��MIC���20������
  BSP_WM8978_Register_Wirter(48,1<<8);	//R48����,PGABOOSTR,��ͨ��MIC���20������
  BSP_WM8978_Register_Wirter(49,1<<1);	//R49,TSDEN,�������ȱ���
  BSP_WM8978_Register_Wirter(49,1<<2);	//R49,SPEAKER BOOST,1.5x
  BSP_WM8978_Register_Wirter(10,1<<3);	//R10,SOFTMUTE�ر�,128x����,���SNR
  BSP_WM8978_Register_Wirter(14,1<<3);	//R14,ADC 128x������

  return 0;
}

/**
 * @description: WM8978 DAC/ADC����
 * @param {uint8_t} dacen dacʹ��(1)/�ر�(0)
 * @param {uint8_t} adcen adcʹ��(1)/�ر�(0)
 * @return {*}
 */
void BSP_WM8978_ADDA_Cfg(uint8_t dacen,uint8_t adcen)
{
  uint16_t regval;
  regval=BSP_WM8978_Register_Read(3);	//��ȡR3
  if(dacen)regval|=3<<0;		//R3���2��λ����Ϊ1,����DACR&DACL
  else regval&=~(3<<0);		//R3���2��λ����,�ر�DACR&DACL.
  BSP_WM8978_Register_Wirter(3,regval);	//����R3
  regval=BSP_WM8978_Register_Read(2);	//��ȡR2
  if(adcen)regval|=3<<0;		//R2���2��λ����Ϊ1,����ADCR&ADCL
  else regval&=~(3<<0);		//R2���2��λ����,�ر�ADCR&ADCL.
  BSP_WM8978_Register_Wirter(2,regval);	//����R2
}

/**
 * @description: WM8978 ����ͨ������
 * @param {uint8_t} micen     MIC����(1)/�ر�(0)
 * @param {uint8_t} lineinen  Line In����(1)/�ر�(0)
 * @param {uint8_t} auxen     aux����(1)/�ر�(0)
 * @return {*}
 */
void BSP_WM8978_Input_Cfg(uint8_t micen,uint8_t lineinen,uint8_t auxen)
{
  uint16_t regval;
  regval=BSP_WM8978_Register_Read(2);	//��ȡR2
  if(micen)regval|=3<<2;		//����INPPGAENR,INPPGAENL(MIC��PGA�Ŵ�)
  else regval&=~(3<<2);		//�ر�INPPGAENR,INPPGAENL.
  BSP_WM8978_Register_Wirter(2,regval);	//����R2

  regval=BSP_WM8978_Register_Read(44);	//��ȡR44
  if(micen)regval|=3<<4|3<<0;	//����LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
  else regval&=~(3<<4|3<<0);	//�ر�LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
  BSP_WM8978_Register_Wirter(44,regval);//����R44

  if(lineinen)BSP_WM8978_LINEIN_Gain(5);//LINE IN 0dB����
  else BSP_WM8978_LINEIN_Gain(0);	//�ر�LINE IN
  if(auxen)BSP_WM8978_AUX_Gain(7);//AUX 6dB����
  else BSP_WM8978_AUX_Gain(0);	//�ر�AUX����
}

/**
 * @description: WM8978 �������
 * @param {uint8_t} dacen DAC���(����)����(1)/�ر�(0)
 * @param {uint8_t} bpsen Bypass���(¼��,����MIC,LINE IN,AUX��)����(1)/�ر�(0)
 * @return {*}
 */
void BSP_WM8978_Output_Cfg(uint8_t dacen,uint8_t bpsen)
{
  uint16_t regval=0;
  if(dacen)regval|=1<<0;	//DAC���ʹ��
  if(bpsen)
  {
    regval|=1<<1;		//BYPASSʹ��
    regval|=5<<2;		//0dB����
  }
  BSP_WM8978_Register_Wirter(50,regval);//R50����
  BSP_WM8978_Register_Wirter(51,regval);//R51����
}

/**
 * @description: WM8978 MIC��������(������BOOST��20dB,MIC-->ADC���벿�ֵ�����)
 * @param {uint8_t} gain 0~63,��Ӧ-12dB~35.25dB,0.75dB/Step
 * @return {*}
 */
void BSP_WM8978_MIC_Gain(uint8_t gain)
{
  gain&=0X3F;
  BSP_WM8978_Register_Wirter(45,gain);		//R45,��ͨ��PGA����
  BSP_WM8978_Register_Wirter(46,gain|1<<8);	//R46,��ͨ��PGA����
}

/**
 * @description: WM8978 L2/R2(Ҳ����Line In)��������(L2/R2-->ADC���벿�ֵ�����)
 * @param {uint8_t} gain 0~7,0��ʾͨ����ֹ,1~7,��Ӧ-12dB~6dB,3dB/Step
 * @return {*}
 */
void BSP_WM8978_LINEIN_Gain(uint8_t gain)
{
  uint16_t regval;
  gain&=0X07;
  regval=BSP_WM8978_Register_Read(47);	//��ȡR47
  regval&=~(7<<4);			//���ԭ��������
  BSP_WM8978_Register_Wirter(47,regval|gain<<4);//����R47
  regval=BSP_WM8978_Register_Read(48);	//��ȡR48
  regval&=~(7<<4);			//���ԭ��������
  BSP_WM8978_Register_Wirter(48,regval|gain<<4);//����R48
}

/**
 * @description: WM8978 AUXR,AUXL(PWM��Ƶ����)��������(AUXR/L-->ADC���벿�ֵ�����)
 * @param {uint8_t} gain 0~7,0��ʾͨ����ֹ,1~7,��Ӧ-12dB~6dB,3dB/Step
 * @return {*}
 */
void BSP_WM8978_AUX_Gain(uint8_t gain)
{
  uint16_t regval;
  gain&=0X07;
  regval=BSP_WM8978_Register_Read(47);	//��ȡR47
  regval&=~(7<<0);			//���ԭ��������
  BSP_WM8978_Register_Wirter(47,regval|gain<<0);//����R47
  regval=BSP_WM8978_Register_Read(48);	//��ȡR48
  regval&=~(7<<0);			//���ԭ��������
  BSP_WM8978_Register_Wirter(48,regval|gain<<0);//����R48
}

/**
 * @description: ����I2S����ģʽ
 * @param {uint8_t} fmt 0,LSB(�Ҷ���);1,MSB(�����);2,�����ֱ�׼I2S;3,PCM/DSP;
 * @param {uint8_t} len 0,16λ;1,20λ;2,24λ;3,32λ;
 * @return {*}
 */
void BSP_WM8978_I2S_Cfg(uint8_t fmt,uint8_t len)
{
  fmt&=0X03;
  len&=0X03;//�޶���Χ
  BSP_WM8978_Register_Wirter(4,(fmt<<3)|(len<<5));	//R4,WM8978����ģʽ����
}

/**
 * @description:  ���ö���������������
 * @param {uint8_t} voll ����������(0~63)
 * @param {uint8_t} volr ����������(0~63)
 * @return {*}
 */
void BSP_WM8978_HPvol_Set(uint8_t voll,uint8_t volr)
{
  voll&=0X3F;
  volr&=0X3F;//�޶���Χ
  if(voll==0)voll|=1<<6;//����Ϊ0ʱ,ֱ��mute
  if(volr==0)volr|=1<<6;//����Ϊ0ʱ,ֱ��mute
  BSP_WM8978_Register_Wirter(52,voll);			//R52,������������������
  BSP_WM8978_Register_Wirter(53,volr|(1<<8));	//R53,������������������,ͬ������(HPVU=1)
}

/**
 * @description: ������������
 * @param {uint8_t} volx ����������(0~63)
 * @return {*}
 */
void BSP_WM8978_SPKvol_Set(uint8_t volx)
{
  volx&=0X3F;//�޶���Χ
  if(volx==0)volx|=1<<6;//����Ϊ0ʱ,ֱ��mute
  BSP_WM8978_Register_Wirter(54,volx);			//R54,������������������
  BSP_WM8978_Register_Wirter(55,volx|(1<<8));	//R55,������������������,ͬ������(SPKVU=1)
}

/**
 * @description: ����3D������
 * @param {uint8_t} depth 0~15(3Dǿ��,0����,15��ǿ)
 * @return {*} 
 */
void BSP_WM8978_3D_Set(uint8_t depth)
{
  depth&=0XF;//�޶���Χ
  BSP_WM8978_Register_Wirter(41,depth);	//R41,3D��������
}

/**
 * @description: ����EQ/3D���÷���
 * @param {uint8_t} dir 0,��ADC������ 1,��DAC������(Ĭ��)
 * @return {*}
 */
void BSP_WM8978_EQ_3D_Dir(uint8_t dir)
{
  uint16_t regval;
  regval=BSP_WM8978_Register_Read(0X12);
  if(dir)regval|=1<<8;
  else regval&=~(1<<8);
  BSP_WM8978_Register_Wirter(18,regval);//R18,EQ1�ĵ�9λ����EQ/3D����
}

/**
 * @description: ����EQ1
 * @param {uint8_t} cfreq ��ֹƵ��,0~3,�ֱ��Ӧ:80/105/135/175Hz
 * @param {uint8_t} gain  ����,0~24,��Ӧ-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ1_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval;
  cfreq&=0X3;//�޶���Χ
  if(gain>24)gain=24;
  gain=24-gain;
  regval=BSP_WM8978_Register_Read(18);
  regval&=0X100;
  regval|=cfreq<<5;	//���ý�ֹƵ��
  regval|=gain;		//��������
  BSP_WM8978_Register_Wirter(18,regval);//R18,EQ1����
}

/**
 * @description: ����EQ2
 * @param {uint8_t} cfreq ����Ƶ��,0~3,�ֱ��Ӧ:230/300/385/500Hz
 * @param {uint8_t} gain  ����,0~24,��Ӧ-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ2_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval=0;
  cfreq&=0X3;//�޶���Χ
  if(gain>24)gain=24;
  gain=24-gain;
  regval|=cfreq<<5;	//���ý�ֹƵ��
  regval|=gain;		//��������
  BSP_WM8978_Register_Wirter(19,regval);//R19,EQ2����
}

/**
 * @description: ����EQ3
 * @param {uint8_t} cfreq ����Ƶ��,0~3,�ֱ��Ӧ:650/850/1100/1400Hz
 * @param {uint8_t} gain  ����,0~24,��Ӧ-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ3_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval=0;
  cfreq&=0X3;//�޶���Χ
  if(gain>24)gain=24;
  gain=24-gain;
  regval|=cfreq<<5;	//���ý�ֹƵ��
  regval|=gain;		//��������
  BSP_WM8978_Register_Wirter(20,regval);//R20,EQ3����
}

/**
 * @description: ����EQ4
 * @param {uint8_t} cfreq ����Ƶ��,0~3,�ֱ��Ӧ:1800/2400/3200/4100Hz
 * @param {uint8_t} gain  ����,0~24,��Ӧ-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ4_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval=0;
  cfreq&=0X3;//�޶���Χ
  if(gain>24)gain=24;
  gain=24-gain;
  regval|=cfreq<<5;	//���ý�ֹƵ��
  regval|=gain;		//��������
  BSP_WM8978_Register_Wirter(21,regval);//R21,EQ4����
}

/**
 * @description:  ����EQ5
 * @param {uint8_t} cfreq ����Ƶ��,0~3,�ֱ��Ӧ:5300/6900/9000/11700Hz
 * @param {uint8_t} gain  ����,0~24,��Ӧ-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ5_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval=0;
  cfreq&=0X3;//�޶���Χ
  if(gain>24)gain=24;
  gain=24-gain;
  regval|=cfreq<<5;	//���ý�ֹƵ��
  regval|=gain;		//��������
  BSP_WM8978_Register_Wirter(22,regval);//R22,EQ5����
}






