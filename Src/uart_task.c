#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <string.h>
#include "uart_task.h"
#include "exec_task.h"
#include "usart.h"

uint8_t uartRxBuf[UART_RX_BUFF_SIZE];
uint8_t const * uartRxTailPtr;

static char s_uartDataBuf[UART_RX_BUFF_SIZE];
static uint32_t s_uartCurIdx = 0;

static int _getAvailSize() {
  uint8_t const * head = uartRxBuf + UART_RX_BUFF_SIZE - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
  uint8_t const * tail = uartRxTailPtr;
    if( head>=tail )
      return head-tail;
    else
      return head-tail+UART_RX_BUFF_SIZE;
}

static char _getByte() {
  char c =  *uartRxTailPtr++;
  if(uartRxTailPtr>=uartRxBuf + UART_RX_BUFF_SIZE)
    uartRxTailPtr-=UART_RX_BUFF_SIZE;
  return c;
}

static int _processCommand(int len) {
  // Error if the command is too short
  if (len < 3) return -1;
  // Error if the command does not start with `AT`
  if (strncmp(s_uartDataBuf, "AT", 2) != 0) return -2;

  // TODO: Parsing and process UART command here.
  // If command is valid, build command structure `struct exec_command`,
  // then send into queue `execQueueHandle`
  return -1;
}

void uartTaskExecution(void) {
  int avail = 0;
  char ch = 0;

  if ((avail = _getAvailSize()) <= 0) {
    // No data, wait 5ms
    osDelay(5);
    return;
  }

  // Has data, get until new line
  while (avail >= 0) {
    ch = _getByte();
    s_uartDataBuf[s_uartCurIdx++] = ch;
    if (ch == '\r') {
      // New line. Process command
      s_uartDataBuf[s_uartCurIdx] = 0;
      _processCommand(s_uartCurIdx);
      // Reset commadn buf
      s_uartCurIdx = 0;
      return;
    }
    avail --;
  }

  // Incomplete command, wait for 1ms
  osDelay(1);
}
