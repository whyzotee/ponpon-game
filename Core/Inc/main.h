/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define T_IRQ_Pin GPIO_PIN_2
#define T_IRQ_GPIO_Port GPIOE
#define T_CLK_Pin GPIO_PIN_3
#define T_CLK_GPIO_Port GPIOE
#define T_MISO_Pin GPIO_PIN_4
#define T_MISO_GPIO_Port GPIOE
#define T_MOSI_Pin GPIO_PIN_5
#define T_MOSI_GPIO_Port GPIOE
#define T_CS_Pin GPIO_PIN_6
#define T_CS_GPIO_Port GPIOE
#define BLUE_BTN_Pin GPIO_PIN_13
#define BLUE_BTN_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define C_Left_Pin GPIO_PIN_10
#define C_Left_GPIO_Port GPIOE
#define C_Right_Pin GPIO_PIN_12
#define C_Right_GPIO_Port GPIOE
#define C_Boost_Pin GPIO_PIN_14
#define C_Boost_GPIO_Port GPIOE
#define C_Shoot_Pin GPIO_PIN_15
#define C_Shoot_GPIO_Port GPIOE
#define L_Left_Pin GPIO_PIN_10
#define L_Left_GPIO_Port GPIOB
#define L_Right_Pin GPIO_PIN_11
#define L_Right_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_8
#define CS_GPIO_Port GPIOC
#define DC_Pin GPIO_PIN_9
#define DC_GPIO_Port GPIOC
#define RST_Pin GPIO_PIN_10
#define RST_GPIO_Port GPIOC
#define S_IN_4_Pin GPIO_PIN_4
#define S_IN_4_GPIO_Port GPIOD
#define S_IN_3_Pin GPIO_PIN_5
#define S_IN_3_GPIO_Port GPIOD
#define S_IN_2_Pin GPIO_PIN_6
#define S_IN_2_GPIO_Port GPIOD
#define S_IN_1_Pin GPIO_PIN_7
#define S_IN_1_GPIO_Port GPIOD
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
