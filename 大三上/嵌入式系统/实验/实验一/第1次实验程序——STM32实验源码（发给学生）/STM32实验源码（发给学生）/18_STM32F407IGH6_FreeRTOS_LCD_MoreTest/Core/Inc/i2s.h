/**
  ******************************************************************************
  * File Name          : I2S.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __i2s_H
#define __i2s_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2S_HandleTypeDef hi2s2;

/* USER CODE BEGIN Private defines */
extern DMA_HandleTypeDef hdma_spi2_tx;   //I2S2����DMA���
/* USER CODE END Private defines */

void MX_I2S2_Init(void);

/* USER CODE BEGIN Prototypes */
void BSP_I2S_Play_Start(void); 
void BSP_I2S_Play_Stop(void);  
uint8_t BSP_I2S2_SampleRate_Set(uint32_t samplerate);
void BSP_I2S2_TX_DMA_Init(uint8_t* buf0,uint8_t *buf1,uint16_t num); 
void BSP_I2S2_Init(uint32_t I2S_Standard,uint32_t I2S_Mode,uint32_t I2S_Clock_Polarity,uint32_t I2S_DataFormat);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ i2s_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
