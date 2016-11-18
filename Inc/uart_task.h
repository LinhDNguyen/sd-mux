#ifndef ___UART_TASK_H___
#define ___UART_TASK_H___

#define UART_RX_BUFF_SIZE 128

extern osThreadId uartTaskHandle;
extern osMessageQId uartQueueHandle;

extern uint8_t uartRxBuf[UART_RX_BUFF_SIZE];
extern uint8_t const * uartRxTailPtr;

void uartTaskExecution(void);

#endif /* ___UART_TASK_H___ */
