/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * Copyright (c) 2016 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "exec_task.h"
#include "uart_task.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId idleTaskHandle;
osThreadId execTaskHandle;
osThreadId uartTaskHandle;
osThreadId i2cTaskHandle;
osMessageQId uartQueueHandle;
osMessageQId i2cQueueHandle;
osMessageQId execQueueHandle;
osMessageQId uartRespQueueHandle;
osMessageQId i2cRespQueueHandle;
osMutexId cmdMutexHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void IdleTask(void const * argument);
void StartExecTask(void const * argument);
void StartUartTask(void const * argument);
void StartI2cTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Create the mutex(es) */
  /* definition and creation of cmdMutex */
  osMutexDef(cmdMutex);
  cmdMutexHandle = osMutexCreate(osMutex(cmdMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of idleTask */
  osThreadDef(idleTask, IdleTask, osPriorityIdle, 0, 128);
  idleTaskHandle = osThreadCreate(osThread(idleTask), NULL);

  /* definition and creation of execTask */
  osThreadDef(execTask, StartExecTask, osPriorityAboveNormal, 0, 128);
  execTaskHandle = osThreadCreate(osThread(execTask), NULL);

  /* definition and creation of uartTask */
  osThreadDef(uartTask, StartUartTask, osPriorityNormal, 0, 128);
  uartTaskHandle = osThreadCreate(osThread(uartTask), NULL);

  /* definition and creation of i2cTask */
  osThreadDef(i2cTask, StartI2cTask, osPriorityNormal, 0, 128);
  i2cTaskHandle = osThreadCreate(osThread(i2cTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of uartQueue */
  osMessageQDef(uartQueue, 8, 32);
  uartQueueHandle = osMessageCreate(osMessageQ(uartQueue), NULL);

  /* definition and creation of i2cQueue */
  osMessageQDef(i2cQueue, 8, 4);
  i2cQueueHandle = osMessageCreate(osMessageQ(i2cQueue), NULL);

  /* definition and creation of execQueue */
  osMessageQDef(execQueue, 16, 8);
  execQueueHandle = osMessageCreate(osMessageQ(execQueue), NULL);

  /* definition and creation of uartRespQueue */
  osMessageQDef(uartRespQueue, 5, 1);
  uartRespQueueHandle = osMessageCreate(osMessageQ(uartRespQueue), NULL);

  /* definition and creation of i2cRespQueue */
  osMessageQDef(i2cRespQueue, 5, 1);
  i2cRespQueueHandle = osMessageCreate(osMessageQ(i2cRespQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* IdleTask function */
void IdleTask(void const * argument)
{

  /* USER CODE BEGIN IdleTask */
  char flag = 0;
  /* Infinite loop */
  for(;;)
  {
    // Delay 1s
    osDelay(1000);
    if (flag) {
      LED1_ON();
      LED2_OFF();
    } else {
      LED1_OFF();
      LED2_ON();
    }
    flag = !flag;
  }
  /* USER CODE END IdleTask */
}

/* StartExecTask function */
void StartExecTask(void const * argument)
{
  /* USER CODE BEGIN StartExecTask */
  /* Infinite loop */
  for(;;)
  {
    execTaskExecution();
  }
  /* USER CODE END StartExecTask */
}

/* StartUartTask function */
void StartUartTask(void const * argument)
{
  /* USER CODE BEGIN StartUartTask */
  /* Infinite loop */
  for(;;)
  {
    uartTaskExecution();
  }
  /* USER CODE END StartUartTask */
}

/* StartI2cTask function */
void StartI2cTask(void const * argument)
{
  /* USER CODE BEGIN StartI2cTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END StartI2cTask */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
