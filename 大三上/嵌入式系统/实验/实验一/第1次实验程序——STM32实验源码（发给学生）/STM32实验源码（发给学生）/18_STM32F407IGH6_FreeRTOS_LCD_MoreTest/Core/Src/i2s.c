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
 * �����ʼ��㹫ʽ:Fs=I2SxCLK/[256*(2*I2SDIV+ODD)]
 * pllm:��Sys_Clock_Set���õ�ʱ��ȷ����һ����8
 * PLLI2SN:һ����192~432
 * PLLI2SR:2~7
 * I2SDIV:2~255
 * ODD:0/1
 * I2S��Ƶϵ����@pllm=8,HSE=8Mhz,��vco����Ƶ��Ϊ1Mhz
 * ���ʽ:������/10,PLLI2SN,PLLI2SR,I2SDIV,ODD
*/
const uint16_t BSP_I2S_PSC_TBL[][5]=
{
	{800 ,256,5,12,1},		//8Khz������
	{1102,429,4,19,0},		//11.025Khz������ 
	{1600,213,2,13,0},		//16Khz������
	{2205,429,4, 9,1},		//22.05Khz������
	{3200,213,2, 6,1},		//32Khz������
//	{4410,271,2, 6,0},		//44.1Khz������
	{4410,151,7, 2,0},		//44.1Khz������		pllm=8,HSE=16Mhz,��vco����Ƶ��Ϊ2Mhz
	{4800,258,3, 3,1},		//48Khz������
	{8820,316,2, 3,1},		//88.2Khz������
	{9600,344,2, 3,1},  	//96Khz������
	{17640,361,2,2,0},  	//176.4Khz������ 
	{19200,393,2,2,0},  	//192Khz������

};

/**
 * @description: �Զ���I2S2��ʼ��
 * @param {uint32_t} I2S_Standard I2S��׼   I2S_STANDARD_PHILIPS
 *                                          I2S_STANDARD_MSB
 *                                          I2S_STANDARD_LSB
 *                                          I2S_STANDARD_PCM_SHORT
 *                                          I2S_STANDARD_PCM_LONG
 * @param {uint32_t} I2S_Mode I2S����ģʽ    I2S_MODE_SLAVE_TX
 *                                          I2S_MODE_SLAVE_RX
 *                                          I2S_MODE_MASTER_TX
 *                                          I2S_MODE_MASTER_RX
 * @param {uint32_t} I2S_Clock_Polarity ʱ�ӵ�ƽ I2S_CPOL_LOW
 *                                              I2S_CPOL_HIGH
 * @param {uint32_t} I2S_DataFormat ���ݳ���    I2S_DATAFORMAT_16B
 *                                              I2S_DATAFORMAT_16B_EXTENDED
 *                                              I2S_DATAFORMAT_24B
 *                                              I2S_DATAFORMAT_32B
 * @return {*}
 */
void BSP_I2S2_Init(uint32_t I2S_Standard,uint32_t I2S_Mode,uint32_t I2S_Clock_Polarity,uint32_t I2S_DataFormat)
{
	hi2s2.Instance=SPI2;
	hi2s2.Init.Mode=I2S_Mode;					//IISģʽ
	hi2s2.Init.Standard=I2S_Standard;			//IIS��׼
	hi2s2.Init.DataFormat=I2S_DataFormat;		//IIS���ݳ���
	hi2s2.Init.MCLKOutput=I2S_MCLKOUTPUT_ENABLE;	//��ʱ�����ʹ��
	hi2s2.Init.AudioFreq=I2S_AUDIOFREQ_DEFAULT;	//IISƵ������
	hi2s2.Init.CPOL=I2S_Clock_Polarity;			//����״̬ʱ�ӵ�ƽ
	hi2s2.Init.ClockSource=I2S_CLOCK_PLL;		//IISʱ��ԴΪPLL
	HAL_I2S_Init(&hi2s2); 
	HAL_I2S_MspInit(&hi2s2);    // �ر�DMA�����ж�
	SPI2->CR2|=1<<1;									//SPI2 TX DMA����ʹ��.
	__HAL_I2S_ENABLE(&hi2s2);					//ʹ��I2S2	
}

/**
 * @description: ����I2S��DMA����
 * @param {*}
 * @return {*}
 */
void BSP_I2S_DMA_Enable(void)
{
    uint32_t tempreg=0;
    tempreg=SPI2->CR2;    	//�ȶ�����ǰ������			
	tempreg|=1<<1;			//ʹ��DMA
	SPI2->CR2=tempreg;		//д��CR1�Ĵ�����
}

/**
 * @description: ���ò�����
 * @param {uint32_t} samplerate(Hz)
 * @return {*}
 */
uint8_t BSP_I2S2_SampleRate_Set(uint32_t samplerate)
{   
  uint8_t i=0; 
	uint32_t tempreg=0;
  RCC_PeriphCLKInitTypeDef RCCI2S2_ClkInitSture;  
	
	for(i=0;i<(sizeof(BSP_I2S_PSC_TBL)/10);i++)//�����Ĳ������Ƿ����֧��
	{
		if((samplerate/10)==BSP_I2S_PSC_TBL[i][0])break;
	}
	if(i==(sizeof(BSP_I2S_PSC_TBL)/10))return 1;//�ѱ���Ҳ�Ҳ���

	RCCI2S2_ClkInitSture.PeriphClockSelection=RCC_PERIPHCLK_I2S;	//����ʱ��Դѡ��
	RCCI2S2_ClkInitSture.PLLI2S.PLLI2SN=(uint32_t)BSP_I2S_PSC_TBL[i][1];    	//����PLLI2SN
	RCCI2S2_ClkInitSture.PLLI2S.PLLI2SR=(uint32_t)BSP_I2S_PSC_TBL[i][2];    	//����PLLI2SR
	HAL_RCCEx_PeriphCLKConfig(&RCCI2S2_ClkInitSture);             	//����ʱ��
	
	RCC->CR|=1<<26;					//����I2Sʱ��
	while((RCC->CR&1<<27)==0);		//�ȴ�I2Sʱ�ӿ����ɹ�. 
	tempreg=BSP_I2S_PSC_TBL[i][3]<<0;	//����I2SDIV
	tempreg|=BSP_I2S_PSC_TBL[i][4]<<8;	//����ODDλ
	tempreg|=1<<9;					//ʹ��MCKOEλ,���MCK
	SPI2->I2SPR=tempreg;			//����I2SPR�Ĵ��� 
	return 0;
} 

/**
 * @description: I2S2 TX DMA���� ����Ϊ˫����ģʽ,������DMA��������ж�
 * @param {uint8_t*} buf0 M0AR��ַ.
 * @param {uint8_t} *buf1 M1AR��ַ.
 * @param {uint16_t} num  ÿ�δ���������
 * @return {*}
 */
void BSP_I2S2_TX_DMA_Init(uint8_t* buf0,uint8_t *buf1,uint16_t num)
{  
    __HAL_RCC_DMA1_CLK_ENABLE();                                    		//ʹ��DMA1ʱ��
    __HAL_LINKDMA(&hi2s2,hdmatx,hdma_spi2_tx);         		//��DMA��I2S��ϵ����
	
    hdma_spi2_tx.Instance=DMA1_Stream4;                       		//DMA1������4                     
    hdma_spi2_tx.Init.Channel=DMA_CHANNEL_0;                  		//ͨ��0
    hdma_spi2_tx.Init.Direction=DMA_MEMORY_TO_PERIPH;         		//�洢��������ģʽ
    hdma_spi2_tx.Init.PeriphInc=DMA_PINC_DISABLE;             		//���������ģʽ
    hdma_spi2_tx.Init.MemInc=DMA_MINC_ENABLE;                 		//�洢������ģʽ
    hdma_spi2_tx.Init.PeriphDataAlignment=DMA_PDATAALIGN_HALFWORD;   	//�������ݳ���:16λ
    hdma_spi2_tx.Init.MemDataAlignment=DMA_MDATAALIGN_HALFWORD;    	//�洢�����ݳ���:16λ
    hdma_spi2_tx.Init.Mode=DMA_CIRCULAR;                      		//ʹ��ѭ��ģʽ 
    hdma_spi2_tx.Init.Priority=DMA_PRIORITY_VERY_HIGH;             		//�����ȼ�
    hdma_spi2_tx.Init.FIFOMode=DMA_FIFOMODE_DISABLE;          		//��ʹ��FIFO
    hdma_spi2_tx.Init.MemBurst=DMA_MBURST_SINGLE;             		//�洢������ͻ������
    hdma_spi2_tx.Init.PeriphBurst=DMA_PBURST_SINGLE;          		//����ͻ�����δ��� 
    HAL_DMA_DeInit(&hdma_spi2_tx);                            		//�������ǰ������
    HAL_DMA_Init(&hdma_spi2_tx);	                            		//��ʼ��DMA

    HAL_DMAEx_MultiBufferStart(&hdma_spi2_tx,(uint32_t)buf0,(uint32_t)&SPI2->DR,(uint32_t)buf1,num);//����˫����
    __HAL_DMA_DISABLE(&hdma_spi2_tx);                         		//�ȹر�DMA 
    HAL_Delay(1);                                                   		//10us��ʱ����ֹ-O2�Ż������� 	
    __HAL_DMA_ENABLE_IT(&hdma_spi2_tx,DMA_IT_TC);             		//������������ж�
    __HAL_DMA_CLEAR_FLAG(&hdma_spi2_tx,DMA_FLAG_TCIF0_4);     		//���DMA��������жϱ�־λ
    HAL_NVIC_SetPriority(DMA1_Stream4_IRQn,0,0);                    		//DMA�ж����ȼ�
    HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
} 

/**
 * @description: I2S��ʼ����
 * @param {*}
 * @return {*}
 */
void BSP_I2S_Play_Start(void)
{   	
	__HAL_DMA_ENABLE(&hdma_spi2_tx);//����DMA TX����  			
}

/**
 * @description: �ر�I2S����
 * @param {*}
 * @return {*}
 */
void BSP_I2S_Play_Stop(void)
{ 
	__HAL_DMA_DISABLE(&hdma_spi2_tx);//��������;		 	 
} 
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
