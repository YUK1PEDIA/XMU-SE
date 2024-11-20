/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OS_Debug.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DC_MOTOR_Pin GPIO_PIN_2
#define DC_MOTOR_GPIO_Port GPIOE
#define STEP_IN3_Pin GPIO_PIN_4
#define STEP_IN3_GPIO_Port GPIOE
#define STEP_IN4_Pin GPIO_PIN_6
#define STEP_IN4_GPIO_Port GPIOE
#define PHOTO_SWITCH_Pin GPIO_PIN_9
#define PHOTO_SWITCH_GPIO_Port GPIOG
#define TOUCH_SDA_Pin GPIO_PIN_3
#define TOUCH_SDA_GPIO_Port GPIOI
#define TOUCH_INT_Pin GPIO_PIN_2
#define TOUCH_INT_GPIO_Port GPIOI
#define KEY3_Pin GPIO_PIN_9
#define KEY3_GPIO_Port GPIOI
#define SDCARD_INPUT_Pin GPIO_PIN_3
#define SDCARD_INPUT_GPIO_Port GPIOD
#define STEP_IN2_Pin GPIO_PIN_13
#define STEP_IN2_GPIO_Port GPIOH
#define W25x16_CS_Pin GPIO_PIN_2
#define W25x16_CS_GPIO_Port GPIOH
#define TOUCH_RST_Pin GPIO_PIN_7
#define TOUCH_RST_GPIO_Port GPIOC
#define RELAY_Pin GPIO_PIN_8
#define RELAY_GPIO_Port GPIOG
#define TOUCH_SCL_Pin GPIO_PIN_7
#define TOUCH_SCL_GPIO_Port GPIOG
#define BUZZER_Pin GPIO_PIN_6
#define BUZZER_GPIO_Port GPIOG
#define ZLG72128_INT_Pin GPIO_PIN_13
#define ZLG72128_INT_GPIO_Port GPIOD
#define ZLG72128_INT_EXTI_IRQn EXTI15_10_IRQn
#define STEP_IN1_Pin GPIO_PIN_12
#define STEP_IN1_GPIO_Port GPIOD
#define IR_KEY_INT_Pin GPIO_PIN_15
#define IR_KEY_INT_GPIO_Port GPIOF
#define IR_KEY_INT_EXTI_IRQn EXTI15_10_IRQn
#define KEY4_Pin GPIO_PIN_11
#define KEY4_GPIO_Port GPIOF
/* USER CODE BEGIN Private defines */
#define KEY3          HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)
#define KEY4          HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)
#define PHOTO_SWITCH  HAL_GPIO_ReadPin(PHOTO_SWITCH_GPIO_Port,PHOTO_SWITCH_Pin)
#define REMOTE_INFRARED_INPUT HAL_GPIO_ReadPin(IR_KEY_INT_GPIO_Port,IR_KEY_INT_Pin)


#define RELAY_ON			HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET)
#define RELAY_OFF			HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET)


#define DE_A  		    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_B  		    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET)
#define DE_C    	    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_D          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET)

#define DE_AB  		    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_BC  		    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET)
#define DE_CD    	    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET) 
#define DE_DA         HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET)

#define UDP_DATA_LEN 30
#define UDP_PORT 50000
#define UDP_SERVER_IP "192.168.0.222"
#define UDP_CLIENT_IP "192.168.0.111"
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
