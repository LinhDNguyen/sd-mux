#ifndef ___UART_TASK_H___
#define ___UART_TASK_H___
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"


extern osThreadId uartTaskHandle;
extern QueueHandle_t uartQueue;

void UartTask(void const * argument);

#endif /* ___UART_TASK_H___ */