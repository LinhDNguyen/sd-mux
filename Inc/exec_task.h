#ifndef ___EXEC_TASK_H___
#define ___EXEC_TASK_H___
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

extern QueueHandle_t execQueue;
extern osThreadId execTaskHandle;

void ExecTask(void const * argument);

#endif /* ___EXEC_TASK_H___ */