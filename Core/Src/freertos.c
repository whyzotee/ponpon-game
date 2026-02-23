/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "semphr.h"
#include "string.h"
#include "inttypes.h"
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_Touchscreen.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern uint16_t timerCounter;
uint16_t timerDefault = 120;

char *one = "1";
char *two = "2";

SemaphoreHandle_t xSemaphorel = NULL;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TouchDisplayTas */
osThreadId_t TouchDisplayTasHandle;
const osThreadAttr_t TouchDisplayTas_attributes = {
  .name = "TouchDisplayTas",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DisplayMenuTask */
osThreadId_t DisplayMenuTaskHandle;
const osThreadAttr_t DisplayMenuTask_attributes = {
  .name = "DisplayMenuTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void DisplayTouch(void *argument);
void DisplayLCD(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TouchDisplayTas */
  TouchDisplayTasHandle = osThreadNew(DisplayTouch, NULL, &TouchDisplayTas_attributes);

  /* creation of DisplayMenuTask */
  DisplayMenuTaskHandle = osThreadNew(DisplayLCD, NULL, &DisplayMenuTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_DisplayTouch */
/**
* @brief Function implementing the TouchDisplayTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DisplayTouch */
void DisplayTouch(void *argument)
{
  /* USER CODE BEGIN DisplayTouch */
  /* Infinite loop */
  for(;;)
  {
	  if(TP_Touchpad_Pressed())
	  {
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	  }
	  else
	  {
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
	  }
  }
  /* USER CODE END DisplayTouch */
}

/* USER CODE BEGIN Header_DisplayLCD */
/**
* @brief Function implementing the DisplayMenuTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DisplayLCD */
void DisplayLCD(void *argument)
{
  /* USER CODE BEGIN DisplayLCD */
  char buff[30];
  /* Infinite loop */
  for(;;)
  {
	  uint16_t value = timerDefault - timerCounter;
	  uint16_t second = value % 60;
	  uint16_t minute = value / 60;

	  sprintf(buff, "Timer: %02" PRIu16 ":%02" PRIu16 "\r", minute, second);
	  ILI9341_Draw_Text(buff, 50, 50, BLACK, 2, WHITE);
	  osDelay(500);
  }
  /* USER CODE END DisplayLCD */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

