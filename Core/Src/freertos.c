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

uint8_t score = 0;

volatile uint8_t limit_hit = 0;

const uint8_t step_table[4][4] =
{
    {1,0,1,0},   // Step 1
    {0,1,1,0},   // Step 2
    {0,1,0,1},   // Step 3
    {1,0,0,1}    // Step 4
};

int stepIndex = 0;
int stepNumber = 1;          // which step the motor is on
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
/* Definitions for ScoreCounterTas */
osThreadId_t ScoreCounterTasHandle;
const osThreadAttr_t ScoreCounterTas_attributes = {
  .name = "ScoreCounterTas",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void DisplayTouch(void *argument);
void DisplayLCD(void *argument);
void ScoreCount(void *argument);

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

  /* creation of ScoreCounterTas */
  ScoreCounterTasHandle = osThreadNew(ScoreCount, NULL, &ScoreCounterTas_attributes);

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
	void motorOff()
	{
	    HAL_GPIO_WritePin(S_IN_1_GPIO_Port, S_IN_1_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(S_IN_2_GPIO_Port, S_IN_2_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(S_IN_3_GPIO_Port, S_IN_3_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(S_IN_4_GPIO_Port, S_IN_4_Pin, GPIO_PIN_RESET);
	}

	void stepMotor(int direction)
	{
	    stepIndex += direction;

	    if(stepIndex > 3) stepIndex = 0;
	    if(stepIndex < 0) stepIndex = 3;

	    HAL_GPIO_WritePin(S_IN_1_GPIO_Port, S_IN_1_Pin, step_table[stepIndex][0]);
	    HAL_GPIO_WritePin(S_IN_2_GPIO_Port, S_IN_2_Pin, step_table[stepIndex][1]);
	    HAL_GPIO_WritePin(S_IN_3_GPIO_Port, S_IN_3_Pin, step_table[stepIndex][2]);
	    HAL_GPIO_WritePin(S_IN_4_GPIO_Port, S_IN_4_Pin, step_table[stepIndex][3]);
	}

	stepNumber = 1;
  /* Infinite loop */
  for(;;)
  {
	  uint8_t leftBtn  = (HAL_GPIO_ReadPin(C_Left_GPIO_Port, C_Left_Pin) == GPIO_PIN_RESET);
	  uint8_t rightBtn = (HAL_GPIO_ReadPin(C_Right_GPIO_Port, C_Right_Pin) == GPIO_PIN_RESET);
	  uint8_t boost    = (HAL_GPIO_ReadPin(C_Boost_GPIO_Port, C_Boost_Pin) == GPIO_PIN_RESET);

	  uint8_t limitLeft  = (HAL_GPIO_ReadPin(L_Left_GPIO_Port, L_Left_Pin) == GPIO_PIN_SET);
	  uint8_t limitRight = (HAL_GPIO_ReadPin(L_Right_GPIO_Port, L_Right_Pin) == GPIO_PIN_SET);

	  uint8_t delay;

	  if(boost)
		  delay = 1;
	  else
		  delay = 2;

	  if(!limitRight && rightBtn && !leftBtn)
	  {
		  stepMotor(1);
		  osDelay(delay);
	  }
	  else if(!limitLeft && leftBtn && !rightBtn)
	  {
		  stepMotor(-1);
		  osDelay(delay);
	  }
	  else
	  {
		  motorOff();
		  osDelay(10);
	  }
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

  void Draw_Trophy_Custom(uint16_t x, uint16_t y, uint8_t size, uint16_t color) {
      ILI9341_Draw_Rectangle(x + (4 * size), y, 10 * size, 8 * size, color);

      ILI9341_Draw_Rectangle(x, y + (1 * size), 4 * size, 1 * size, color);
      ILI9341_Draw_Rectangle(x, y + (1 * size), 1 * size, 5 * size, color);
      ILI9341_Draw_Rectangle(x, y + (5 * size), 4 * size, 1 * size, color);

      ILI9341_Draw_Rectangle(x + (14 * size), y + (1 * size), 4 * size, 1 * size, color);
      ILI9341_Draw_Rectangle(x + (17 * size), y + (1 * size), 1 * size, 5 * size, color);
      ILI9341_Draw_Rectangle(x + (14 * size), y + (5 * size), 4 * size, 1 * size, color);

      ILI9341_Draw_Rectangle(x + (8 * size), y + (8 * size), 2 * size, 4 * size, color);

      ILI9341_Draw_Rectangle(x + (5 * size), y + (11 * size), 8 * size, 2 * size, color);
  }

  void Draw_Heart_Custom(uint16_t x, uint16_t y, uint8_t size, uint16_t color) {
      ILI9341_Draw_Rectangle(x + (1 * size), y, 2 * size, 1 * size, color);

      ILI9341_Draw_Rectangle(x + (4 * size), y, 2 * size, 1 * size, color);

      ILI9341_Draw_Rectangle(x, y + (1 * size), 7 * size, 2 * size, color);

      ILI9341_Draw_Rectangle(x + (1 * size), y + (3 * size), 5 * size, 1 * size, color);

      ILI9341_Draw_Rectangle(x + (2 * size), y + (4 * size), 3 * size, 1 * size, color);
      ILI9341_Draw_Rectangle(x + (3 * size), y + (5 * size), 1 * size, 1 * size, color);
  }

//  Draw_Trophy_Custom(10, 40, 3, RED);
//  Draw_Trophy_Custom(100, 40, 3, BLUE);
//  Draw_Heart_Custom(120, 100, 5, RED);
  /* Infinite loop */
  for(;;)
  {
	  uint16_t value = timerDefault - timerCounter;
	  uint16_t second = value % 60;
	  uint16_t minute = value / 60;

	  sprintf(buff, "Timer: %02" PRIu16 ":%02" PRIu16, minute, second);
	  ILI9341_Draw_Text(buff, 50, 50, BLACK, 2, WHITE);

	  osDelay(500);
  }
  /* USER CODE END DisplayLCD */
}

/* USER CODE BEGIN Header_ScoreCount */
/**
* @brief Function implementing the ScoreCounterTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ScoreCount */
void ScoreCount(void *argument)
{
  /* USER CODE BEGIN ScoreCount */
  char buff[30];
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13));

	  if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13))
	  {
		  score += 1;

		  sprintf(buff, "Score: %02u", score);
		  ILI9341_Draw_Text(buff, 50, 100, BLACK, 2, WHITE);
		  osDelay(5000);
	  }

	  osDelay(1);
  }
  /* USER CODE END ScoreCount */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

