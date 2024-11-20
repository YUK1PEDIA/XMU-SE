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
 * WM8978寄存器值缓存区(总共58个寄存器,0~57),占用116字节内存
 * 因为WM8978的IIC操作不支持读操作,所以在本地保存所有寄存器值
 * 写WM8978寄存器时,同步更新到本地寄存器值
 * 读寄存器时,直接返回本地保存的寄存器值.
 * 注意:WM8978的寄存器值是9位的,所以要用uint16_t来存储.
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
 * @description: 写寄存器
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

  WM8978_REGVAL_TBL[reg_addr] = data;	//保存寄存器值到本地

  return 0;
}

/**
 * @description: WM8978读寄存器
 * @param {uint8_t} reg 寄存器地址(读取本地寄存器值缓冲区内的对应值)
 * @return {*} 寄存器值
 */
static uint16_t BSP_WM8978_Register_Read(uint8_t reg)
{
  return WM8978_REGVAL_TBL[reg];
}

/**
 * @description: WM8978初始化
 * @param {*}
 * @return {*}
 */
uint8_t BSP_WM8978_Init(void)
{
  uint8_t res;

  res=BSP_WM8978_Register_Wirter(0,0);	//软复位WM8978
  if(res)return 1;			//发送指令失败,WM8978异常

  //以下为通用设置
  BSP_WM8978_Register_Wirter(1,0X1B);	//R1,MICEN设置为1(MIC使能),BIASEN设置为1(模拟器工作),VMIDSEL[1:0]设置为:11(5K)
  BSP_WM8978_Register_Wirter(2,0X1B0);	//R2,ROUT1,LOUT1输出使能(耳机可以工作),BOOSTENR,BOOSTENL使能
  BSP_WM8978_Register_Wirter(3,0X6C);	//R3,LOUT2,ROUT2输出使能(喇叭工作),RMIX,LMIX使能
  BSP_WM8978_Register_Wirter(6,0);		//R6,MCLK由外部提供
  BSP_WM8978_Register_Wirter(43,1<<4);	//R43,INVROUT2反向,驱动喇叭
  BSP_WM8978_Register_Wirter(47,1<<8);	//R47设置,PGABOOSTL,左通道MIC获得20倍增益
  BSP_WM8978_Register_Wirter(48,1<<8);	//R48设置,PGABOOSTR,右通道MIC获得20倍增益
  BSP_WM8978_Register_Wirter(49,1<<1);	//R49,TSDEN,开启过热保护
  BSP_WM8978_Register_Wirter(49,1<<2);	//R49,SPEAKER BOOST,1.5x
  BSP_WM8978_Register_Wirter(10,1<<3);	//R10,SOFTMUTE关闭,128x采样,最佳SNR
  BSP_WM8978_Register_Wirter(14,1<<3);	//R14,ADC 128x采样率

  return 0;
}

/**
 * @description: WM8978 DAC/ADC配置
 * @param {uint8_t} dacen dac使能(1)/关闭(0)
 * @param {uint8_t} adcen adc使能(1)/关闭(0)
 * @return {*}
 */
void BSP_WM8978_ADDA_Cfg(uint8_t dacen,uint8_t adcen)
{
  uint16_t regval;
  regval=BSP_WM8978_Register_Read(3);	//读取R3
  if(dacen)regval|=3<<0;		//R3最低2个位设置为1,开启DACR&DACL
  else regval&=~(3<<0);		//R3最低2个位清零,关闭DACR&DACL.
  BSP_WM8978_Register_Wirter(3,regval);	//设置R3
  regval=BSP_WM8978_Register_Read(2);	//读取R2
  if(adcen)regval|=3<<0;		//R2最低2个位设置为1,开启ADCR&ADCL
  else regval&=~(3<<0);		//R2最低2个位清零,关闭ADCR&ADCL.
  BSP_WM8978_Register_Wirter(2,regval);	//设置R2
}

/**
 * @description: WM8978 输入通道配置
 * @param {uint8_t} micen     MIC开启(1)/关闭(0)
 * @param {uint8_t} lineinen  Line In开启(1)/关闭(0)
 * @param {uint8_t} auxen     aux开启(1)/关闭(0)
 * @return {*}
 */
void BSP_WM8978_Input_Cfg(uint8_t micen,uint8_t lineinen,uint8_t auxen)
{
  uint16_t regval;
  regval=BSP_WM8978_Register_Read(2);	//读取R2
  if(micen)regval|=3<<2;		//开启INPPGAENR,INPPGAENL(MIC的PGA放大)
  else regval&=~(3<<2);		//关闭INPPGAENR,INPPGAENL.
  BSP_WM8978_Register_Wirter(2,regval);	//设置R2

  regval=BSP_WM8978_Register_Read(44);	//读取R44
  if(micen)regval|=3<<4|3<<0;	//开启LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
  else regval&=~(3<<4|3<<0);	//关闭LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
  BSP_WM8978_Register_Wirter(44,regval);//设置R44

  if(lineinen)BSP_WM8978_LINEIN_Gain(5);//LINE IN 0dB增益
  else BSP_WM8978_LINEIN_Gain(0);	//关闭LINE IN
  if(auxen)BSP_WM8978_AUX_Gain(7);//AUX 6dB增益
  else BSP_WM8978_AUX_Gain(0);	//关闭AUX输入
}

/**
 * @description: WM8978 输出配置
 * @param {uint8_t} dacen DAC输出(放音)开启(1)/关闭(0)
 * @param {uint8_t} bpsen Bypass输出(录音,包括MIC,LINE IN,AUX等)开启(1)/关闭(0)
 * @return {*}
 */
void BSP_WM8978_Output_Cfg(uint8_t dacen,uint8_t bpsen)
{
  uint16_t regval=0;
  if(dacen)regval|=1<<0;	//DAC输出使能
  if(bpsen)
  {
    regval|=1<<1;		//BYPASS使能
    regval|=5<<2;		//0dB增益
  }
  BSP_WM8978_Register_Wirter(50,regval);//R50设置
  BSP_WM8978_Register_Wirter(51,regval);//R51设置
}

/**
 * @description: WM8978 MIC增益设置(不包括BOOST的20dB,MIC-->ADC输入部分的增益)
 * @param {uint8_t} gain 0~63,对应-12dB~35.25dB,0.75dB/Step
 * @return {*}
 */
void BSP_WM8978_MIC_Gain(uint8_t gain)
{
  gain&=0X3F;
  BSP_WM8978_Register_Wirter(45,gain);		//R45,左通道PGA设置
  BSP_WM8978_Register_Wirter(46,gain|1<<8);	//R46,右通道PGA设置
}

/**
 * @description: WM8978 L2/R2(也就是Line In)增益设置(L2/R2-->ADC输入部分的增益)
 * @param {uint8_t} gain 0~7,0表示通道禁止,1~7,对应-12dB~6dB,3dB/Step
 * @return {*}
 */
void BSP_WM8978_LINEIN_Gain(uint8_t gain)
{
  uint16_t regval;
  gain&=0X07;
  regval=BSP_WM8978_Register_Read(47);	//读取R47
  regval&=~(7<<4);			//清除原来的设置
  BSP_WM8978_Register_Wirter(47,regval|gain<<4);//设置R47
  regval=BSP_WM8978_Register_Read(48);	//读取R48
  regval&=~(7<<4);			//清除原来的设置
  BSP_WM8978_Register_Wirter(48,regval|gain<<4);//设置R48
}

/**
 * @description: WM8978 AUXR,AUXL(PWM音频部分)增益设置(AUXR/L-->ADC输入部分的增益)
 * @param {uint8_t} gain 0~7,0表示通道禁止,1~7,对应-12dB~6dB,3dB/Step
 * @return {*}
 */
void BSP_WM8978_AUX_Gain(uint8_t gain)
{
  uint16_t regval;
  gain&=0X07;
  regval=BSP_WM8978_Register_Read(47);	//读取R47
  regval&=~(7<<0);			//清除原来的设置
  BSP_WM8978_Register_Wirter(47,regval|gain<<0);//设置R47
  regval=BSP_WM8978_Register_Read(48);	//读取R48
  regval&=~(7<<0);			//清除原来的设置
  BSP_WM8978_Register_Wirter(48,regval|gain<<0);//设置R48
}

/**
 * @description: 设置I2S工作模式
 * @param {uint8_t} fmt 0,LSB(右对齐);1,MSB(左对齐);2,飞利浦标准I2S;3,PCM/DSP;
 * @param {uint8_t} len 0,16位;1,20位;2,24位;3,32位;
 * @return {*}
 */
void BSP_WM8978_I2S_Cfg(uint8_t fmt,uint8_t len)
{
  fmt&=0X03;
  len&=0X03;//限定范围
  BSP_WM8978_Register_Wirter(4,(fmt<<3)|(len<<5));	//R4,WM8978工作模式设置
}

/**
 * @description:  设置耳机左右声道音量
 * @param {uint8_t} voll 左声道音量(0~63)
 * @param {uint8_t} volr 右声道音量(0~63)
 * @return {*}
 */
void BSP_WM8978_HPvol_Set(uint8_t voll,uint8_t volr)
{
  voll&=0X3F;
  volr&=0X3F;//限定范围
  if(voll==0)voll|=1<<6;//音量为0时,直接mute
  if(volr==0)volr|=1<<6;//音量为0时,直接mute
  BSP_WM8978_Register_Wirter(52,voll);			//R52,耳机左声道音量设置
  BSP_WM8978_Register_Wirter(53,volr|(1<<8));	//R53,耳机右声道音量设置,同步更新(HPVU=1)
}

/**
 * @description: 设置喇叭音量
 * @param {uint8_t} volx 左声道音量(0~63)
 * @return {*}
 */
void BSP_WM8978_SPKvol_Set(uint8_t volx)
{
  volx&=0X3F;//限定范围
  if(volx==0)volx|=1<<6;//音量为0时,直接mute
  BSP_WM8978_Register_Wirter(54,volx);			//R54,喇叭左声道音量设置
  BSP_WM8978_Register_Wirter(55,volx|(1<<8));	//R55,喇叭右声道音量设置,同步更新(SPKVU=1)
}

/**
 * @description: 设置3D环绕声
 * @param {uint8_t} depth 0~15(3D强度,0最弱,15最强)
 * @return {*} 
 */
void BSP_WM8978_3D_Set(uint8_t depth)
{
  depth&=0XF;//限定范围
  BSP_WM8978_Register_Wirter(41,depth);	//R41,3D环绕设置
}

/**
 * @description: 设置EQ/3D作用方向
 * @param {uint8_t} dir 0,在ADC起作用 1,在DAC起作用(默认)
 * @return {*}
 */
void BSP_WM8978_EQ_3D_Dir(uint8_t dir)
{
  uint16_t regval;
  regval=BSP_WM8978_Register_Read(0X12);
  if(dir)regval|=1<<8;
  else regval&=~(1<<8);
  BSP_WM8978_Register_Wirter(18,regval);//R18,EQ1的第9位控制EQ/3D方向
}

/**
 * @description: 设置EQ1
 * @param {uint8_t} cfreq 截止频率,0~3,分别对应:80/105/135/175Hz
 * @param {uint8_t} gain  增益,0~24,对应-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ1_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval;
  cfreq&=0X3;//限定范围
  if(gain>24)gain=24;
  gain=24-gain;
  regval=BSP_WM8978_Register_Read(18);
  regval&=0X100;
  regval|=cfreq<<5;	//设置截止频率
  regval|=gain;		//设置增益
  BSP_WM8978_Register_Wirter(18,regval);//R18,EQ1设置
}

/**
 * @description: 设置EQ2
 * @param {uint8_t} cfreq 中心频率,0~3,分别对应:230/300/385/500Hz
 * @param {uint8_t} gain  增益,0~24,对应-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ2_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval=0;
  cfreq&=0X3;//限定范围
  if(gain>24)gain=24;
  gain=24-gain;
  regval|=cfreq<<5;	//设置截止频率
  regval|=gain;		//设置增益
  BSP_WM8978_Register_Wirter(19,regval);//R19,EQ2设置
}

/**
 * @description: 设置EQ3
 * @param {uint8_t} cfreq 中心频率,0~3,分别对应:650/850/1100/1400Hz
 * @param {uint8_t} gain  增益,0~24,对应-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ3_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval=0;
  cfreq&=0X3;//限定范围
  if(gain>24)gain=24;
  gain=24-gain;
  regval|=cfreq<<5;	//设置截止频率
  regval|=gain;		//设置增益
  BSP_WM8978_Register_Wirter(20,regval);//R20,EQ3设置
}

/**
 * @description: 设置EQ4
 * @param {uint8_t} cfreq 中心频率,0~3,分别对应:1800/2400/3200/4100Hz
 * @param {uint8_t} gain  增益,0~24,对应-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ4_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval=0;
  cfreq&=0X3;//限定范围
  if(gain>24)gain=24;
  gain=24-gain;
  regval|=cfreq<<5;	//设置截止频率
  regval|=gain;		//设置增益
  BSP_WM8978_Register_Wirter(21,regval);//R21,EQ4设置
}

/**
 * @description:  设置EQ5
 * @param {uint8_t} cfreq 中心频率,0~3,分别对应:5300/6900/9000/11700Hz
 * @param {uint8_t} gain  增益,0~24,对应-12~+12dB
 * @return {*}
 */
void BSP_WM8978_EQ5_Set(uint8_t cfreq,uint8_t gain)
{
  uint16_t regval=0;
  cfreq&=0X3;//限定范围
  if(gain>24)gain=24;
  gain=24-gain;
  regval|=cfreq<<5;	//设置截止频率
  regval|=gain;		//设置增益
  BSP_WM8978_Register_Wirter(22,regval);//R22,EQ5设置
}






