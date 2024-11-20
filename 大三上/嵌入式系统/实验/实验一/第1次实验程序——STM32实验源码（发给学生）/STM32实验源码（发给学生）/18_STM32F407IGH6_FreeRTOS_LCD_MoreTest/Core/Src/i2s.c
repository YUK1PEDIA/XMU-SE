/**
  ******************************************************************************
  * File Name          : I2S.c
  * Description        : This file provides code for the configuration
  *                      of the I2S instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2s.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2S_HandleTypeDef hi2s2;
DMA_HandleTypeDef hdma_spi2_tx;

/* I2S2 init function */
void MX_I2S2_Init(void)
{

  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_8K;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_I2S_MspInit(I2S_HandleTypeDef* i2sHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2sHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
    /* I2S2 clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2S2 GPIO Configuration    
    PC6     ------> I2S2_MCK
    PC2     ------> I2S2_ext_SD
    PC3     ------> I2S2_SD
    PB12     ------> I2S2_WS
    PB13     ------> I2S2_CK 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_I2S2ext;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2S2 DMA Init */
    /* SPI2_TX Init */
    hdma_spi2_tx.Instance = DMA1_Stream4;
    hdma_spi2_tx.Init.Channel = DMA_CHANNEL_0;
    hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.Mode = DMA_CIRCULAR;
    hdma_spi2_tx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(i2sHandle,hdmatx,hdma_spi2_tx);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }
}

void HAL_I2S_MspDeInit(I2S_HandleTypeDef* i2sHandle)
{

  if(i2sHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();
  
    /**I2S2 GPIO Configuration    
    PC6     ------> I2S2_MCK
    PC2     ------> I2S2_ext_SD
    PC3     ------> I2S2_SD
    PB12     ------> I2S2_WS
    PB13     ------> I2S2_CK 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_2|GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* I2S2 DMA DeInit */
    HAL_DMA_DeInit(i2sHandle->hdmatx);
  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/**
 * 采样率计算公式:Fs=I2SxCLK/[256*(2*I2SDIV+ODD)]
 * pllm:在Sys_Clock_Set设置的时候确定，一般是8
 * PLLI2SN:一般是192~432
 * PLLI2SR:2~7
 * I2SDIV:2~255
 * ODD:0/1
 * I2S分频系数表@pllm=8,HSE=8Mhz,即vco输入频率为1Mhz
 * 表格式:采样率/10,PLLI2SN,PLLI2SR,I2SDIV,ODD
*/
const uint16_t BSP_I2S_PSC_TBL[][5]=
{
	{800 ,256,5,12,1},		//8Khz采样率
	{1102,429,4,19,0},		//11.025Khz采样率 
	{1600,213,2,13,0},		//16Khz采样率
	{2205,429,4, 9,1},		//22.05Khz采样率
	{3200,213,2, 6,1},		//32Khz采样率
//	{4410,271,2, 6,0},		//44.1Khz采样率
	{4410,151,7, 2,0},		//44.1Khz采样率		pllm=8,HSE=16Mhz,即vco输入频率为2Mhz
	{4800,258,3, 3,1},		//48Khz采样率
	{8820,316,2, 3,1},		//88.2Khz采样率
	{9600,344,2, 3,1},  	//96Khz采样率
	{17640,361,2,2,0},  	//176.4Khz采样率 
	{19200,393,2,2,0},  	//192Khz采样率

};

/**
 * @description: 自定义I2S2初始化
 * @param {uint32_t} I2S_Standard I2S标准   I2S_STANDARD_PHILIPS
 *                                          I2S_STANDARD_MSB
 *                                          I2S_STANDARD_LSB
 *                                          I2S_STANDARD_PCM_SHORT
 *                                          I2S_STANDARD_PCM_LONG
 * @param {uint32_t} I2S_Mode I2S工作模式    I2S_MODE_SLAVE_TX
 *                                          I2S_MODE_SLAVE_RX
 *                                          I2S_MODE_MASTER_TX
 *                                          I2S_MODE_MASTER_RX
 * @param {uint32_t} I2S_Clock_Polarity 时钟电平 I2S_CPOL_LOW
 *                                              I2S_CPOL_HIGH
 * @param {uint32_t} I2S_DataFormat 数据长度    I2S_DATAFORMAT_16B
 *                                              I2S_DATAFORMAT_16B_EXTENDED
 *                                              I2S_DATAFORMAT_24B
 *                                              I2S_DATAFORMAT_32B
 * @return {*}
 */
void BSP_I2S2_Init(uint32_t I2S_Standard,uint32_t I2S_Mode,uint32_t I2S_Clock_Polarity,uint32_t I2S_DataFormat)
{
	hi2s2.Instance=SPI2;
	hi2s2.Init.Mode=I2S_Mode;					//IIS模式
	hi2s2.Init.Standard=I2S_Standard;			//IIS标准
	hi2s2.Init.DataFormat=I2S_DataFormat;		//IIS数据长度
	hi2s2.Init.MCLKOutput=I2S_MCLKOUTPUT_ENABLE;	//主时钟输出使能
	hi2s2.Init.AudioFreq=I2S_AUDIOFREQ_DEFAULT;	//IIS频率设置
	hi2s2.Init.CPOL=I2S_Clock_Polarity;			//空闲状态时钟电平
	hi2s2.Init.ClockSource=I2S_CLOCK_PLL;		//IIS时钟源为PLL
	HAL_I2S_Init(&hi2s2); 
	HAL_I2S_MspInit(&hi2s2);    // 关闭DMA传输中断
	SPI2->CR2|=1<<1;									//SPI2 TX DMA请求使能.
	__HAL_I2S_ENABLE(&hi2s2);					//使能I2S2	
}

/**
 * @description: 开启I2S的DMA功能
 * @param {*}
 * @return {*}
 */
void BSP_I2S_DMA_Enable(void)
{
    uint32_t tempreg=0;
    tempreg=SPI2->CR2;    	//先读出以前的设置			
	tempreg|=1<<1;			//使能DMA
	SPI2->CR2=tempreg;		//写入CR1寄存器中
}

/**
 * @description: 设置采样率
 * @param {uint32_t} samplerate(Hz)
 * @return {*}
 */
uint8_t BSP_I2S2_SampleRate_Set(uint32_t samplerate)
{   
  uint8_t i=0; 
	uint32_t tempreg=0;
  RCC_PeriphCLKInitTypeDef RCCI2S2_ClkInitSture;  
	
	for(i=0;i<(sizeof(BSP_I2S_PSC_TBL)/10);i++)//看看改采样率是否可以支持
	{
		if((samplerate/10)==BSP_I2S_PSC_TBL[i][0])break;
	}
	if(i==(sizeof(BSP_I2S_PSC_TBL)/10))return 1;//搜遍了也找不到

	RCCI2S2_ClkInitSture.PeriphClockSelection=RCC_PERIPHCLK_I2S;	//外设时钟源选择
	RCCI2S2_ClkInitSture.PLLI2S.PLLI2SN=(uint32_t)BSP_I2S_PSC_TBL[i][1];    	//设置PLLI2SN
	RCCI2S2_ClkInitSture.PLLI2S.PLLI2SR=(uint32_t)BSP_I2S_PSC_TBL[i][2];    	//设置PLLI2SR
	HAL_RCCEx_PeriphCLKConfig(&RCCI2S2_ClkInitSture);             	//设置时钟
	
	RCC->CR|=1<<26;					//开启I2S时钟
	while((RCC->CR&1<<27)==0);		//等待I2S时钟开启成功. 
	tempreg=BSP_I2S_PSC_TBL[i][3]<<0;	//设置I2SDIV
	tempreg|=BSP_I2S_PSC_TBL[i][4]<<8;	//设置ODD位
	tempreg|=1<<9;					//使能MCKOE位,输出MCK
	SPI2->I2SPR=tempreg;			//设置I2SPR寄存器 
	return 0;
} 

/**
 * @description: I2S2 TX DMA配置 设置为双缓冲模式,并开启DMA传输完成中断
 * @param {uint8_t*} buf0 M0AR地址.
 * @param {uint8_t} *buf1 M1AR地址.
 * @param {uint16_t} num  每次传输数据量
 * @return {*}
 */
void BSP_I2S2_TX_DMA_Init(uint8_t* buf0,uint8_t *buf1,uint16_t num)
{  
    __HAL_RCC_DMA1_CLK_ENABLE();                                    		//使能DMA1时钟
    __HAL_LINKDMA(&hi2s2,hdmatx,hdma_spi2_tx);         		//将DMA与I2S联系起来
	
    hdma_spi2_tx.Instance=DMA1_Stream4;                       		//DMA1数据流4                     
    hdma_spi2_tx.Init.Channel=DMA_CHANNEL_0;                  		//通道0
    hdma_spi2_tx.Init.Direction=DMA_MEMORY_TO_PERIPH;         		//存储器到外设模式
    hdma_spi2_tx.Init.PeriphInc=DMA_PINC_DISABLE;             		//外设非增量模式
    hdma_spi2_tx.Init.MemInc=DMA_MINC_ENABLE;                 		//存储器增量模式
    hdma_spi2_tx.Init.PeriphDataAlignment=DMA_PDATAALIGN_HALFWORD;   	//外设数据长度:16位
    hdma_spi2_tx.Init.MemDataAlignment=DMA_MDATAALIGN_HALFWORD;    	//存储器数据长度:16位
    hdma_spi2_tx.Init.Mode=DMA_CIRCULAR;                      		//使用循环模式 
    hdma_spi2_tx.Init.Priority=DMA_PRIORITY_VERY_HIGH;             		//高优先级
    hdma_spi2_tx.Init.FIFOMode=DMA_FIFOMODE_DISABLE;          		//不使用FIFO
    hdma_spi2_tx.Init.MemBurst=DMA_MBURST_SINGLE;             		//存储器单次突发传输
    hdma_spi2_tx.Init.PeriphBurst=DMA_PBURST_SINGLE;          		//外设突发单次传输 
    HAL_DMA_DeInit(&hdma_spi2_tx);                            		//先清除以前的设置
    HAL_DMA_Init(&hdma_spi2_tx);	                            		//初始化DMA

    HAL_DMAEx_MultiBufferStart(&hdma_spi2_tx,(uint32_t)buf0,(uint32_t)&SPI2->DR,(uint32_t)buf1,num);//开启双缓冲
    __HAL_DMA_DISABLE(&hdma_spi2_tx);                         		//先关闭DMA 
    HAL_Delay(1);                                                   		//10us延时，防止-O2优化出问题 	
    __HAL_DMA_ENABLE_IT(&hdma_spi2_tx,DMA_IT_TC);             		//开启传输完成中断
    __HAL_DMA_CLEAR_FLAG(&hdma_spi2_tx,DMA_FLAG_TCIF0_4);     		//清除DMA传输完成中断标志位
    HAL_NVIC_SetPriority(DMA1_Stream4_IRQn,0,0);                    		//DMA中断优先级
    HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
} 

/**
 * @description: I2S开始播放
 * @param {*}
 * @return {*}
 */
void BSP_I2S_Play_Start(void)
{   	
	__HAL_DMA_ENABLE(&hdma_spi2_tx);//开启DMA TX传输  			
}

/**
 * @description: 关闭I2S播放
 * @param {*}
 * @return {*}
 */
void BSP_I2S_Play_Stop(void)
{ 
	__HAL_DMA_DISABLE(&hdma_spi2_tx);//结束播放;		 	 
} 
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
