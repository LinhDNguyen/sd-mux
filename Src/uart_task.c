#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <string.h>
#include "uart_task.h"
#include "exec_task.h"
#include "usart.h"
#include "stm32f1xx_hal.h"

typedef int (* uartCommandFPtr)(int argc, char **argv);

struct uartCommand {
  char *name;
  uartCommandFPtr func;
};

#define UART_CMD(_x,_y) {_x,_y}

uint8_t uartRxBuf[UART_RX_BUFF_SIZE];
uint8_t const * uartRxTailPtr;

static char s_uartDataBuf[UART_RX_BUFF_SIZE];
static uint32_t s_uartCurIdx = 0;

static int do_help(int argc, char **argv);
static int uart_reponse(uint8_t *resp);

static struct uartCommand s_supportedCommands[] = {
  UART_CMD("help", do_help),
};

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
  struct exec_command cmd;
  char isCmd = 0;

  // Error if the command is too short
  if (len < 3) goto lb_error;
  // Error if the command does not start with `AT`
  if (strncmp(s_uartDataBuf, "AT", 2) != 0) goto lb_error;

  // TODO: Parsing and process UART command here.
  // If command is valid, build command structure `struct exec_command` with resp_queue = uartRespQueueHandle,
  // then send into queue `execQueueHandle`

  //// Some HARDCODE COMMAND. TODO: update later
  if (strncmp(s_uartDataBuf, "AT help", 7) == 0) {
    do_help(0, NULL);
  } else if (strncmp(s_uartDataBuf, "AT sd dut", 9) == 0) {
    // Swith to DUT
    cmd.type = EXEC_SD_SWITCH;
    cmd.resp_queue = uartRespQueueHandle;
    cmd.u.sd_switch.cmd = CMD_OFF;
    isCmd = 1;
  }
  else if (strncmp(s_uartDataBuf, "AT sd reader", 12) == 0) {
    // Swith to reaDER
    cmd.type = EXEC_SD_SWITCH;
    cmd.resp_queue = uartRespQueueHandle;
    cmd.u.sd_switch.cmd = CMD_ON;
    isCmd = 1;
  }
  else if (strncmp(s_uartDataBuf, "AT pow on", 9) == 0) {
    // Swith to READER
    cmd.type = EXEC_POWER;
    cmd.resp_queue = uartRespQueueHandle;
    cmd.u.power.cmd = CMD_ON;
    isCmd = 1;
  }
  else if (strncmp(s_uartDataBuf, "AT pow off", 10) == 0) {
    // Swith to READER
    cmd.type = EXEC_POWER;
    cmd.resp_queue = uartRespQueueHandle;
    cmd.u.power.cmd = CMD_OFF;
    isCmd = 1;
  }
  else if (strncmp(s_uartDataBuf, "AT jump 1 1", 10) == 0) {
    cmd.type = EXEC_JUMPER_SWITCH;
    cmd.resp_queue = uartRespQueueHandle;
    cmd.u.jump_switch.cmd = CMD_SET1;
    cmd.u.jump_switch.channel = 0;
    isCmd = 1;
  }
  else if (strncmp(s_uartDataBuf, "AT jump 1 3", 10) == 0) {
    cmd.type = EXEC_JUMPER_SWITCH;
    cmd.resp_queue = uartRespQueueHandle;
    cmd.u.jump_switch.cmd = CMD_SET2;
    cmd.u.jump_switch.channel = 0;
    isCmd = 1;
  }
  else if (strncmp(s_uartDataBuf, "AT ext 1 on", 11) == 0) {
    cmd.type = EXEC_EXT_CTRL;
    cmd.resp_queue = uartRespQueueHandle;
    cmd.u.ext_ctrl.cmd = CMD_ON;
    cmd.u.ext_ctrl.channel = 0;
    isCmd = 1;
  }
  else if (strncmp(s_uartDataBuf, "AT ext 1 off", 12) == 0) {
    cmd.type = EXEC_EXT_CTRL;
    cmd.resp_queue = uartRespQueueHandle;
    cmd.u.ext_ctrl.cmd = CMD_OFF;
    cmd.u.ext_ctrl.channel = 0;
    isCmd = 1;
  }
  // INVALID COMMAND
  else goto lb_error;

  if(isCmd) {
    xQueueSend(execQueueHandle, &cmd, 0);
  }

  return 0;
lb_error:
  uart_reponse("\r\nERR\r\n\r\n");
  return -1;
}

static int uart_reponse(uint8_t *resp) {
  HAL_UART_Transmit(&huart1, resp, strlen(resp), 1000);

  return 0;
}

void uartTaskExecution(void) {
  int avail = 0;
  char ch = 0;

  if ((avail = _getAvailSize()) <= 0) {
    // No data, wait 5ms
    if (xQueueReceive(uartRespQueueHandle, &ch, 5/portTICK_PERIOD_MS)) {
      if (ch == EXEC_ST_OK) {
        uart_reponse("\r\nOK\r\n\r\n");
      } else {
        uart_reponse("\r\nERR\r\n\r\n");
      }
      osDelay(5);
    }
    return;
  }

  // Has data, get until new line
  while (avail > 0) {
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

static int do_help(int argc, char **argv) {
  HAL_UART_Transmit(&huart1, "\r\nSD MUX DEVICE COMMANDS:\r\n", 27, 1000);
  HAL_UART_Transmit(&huart1, "AT help\r\n", 9, 1000);
  HAL_UART_Transmit(&huart1, "AT sd dut\r\n", 11, 1000);
  HAL_UART_Transmit(&huart1, "AT sd reader\r\n", 14, 1000);
  HAL_UART_Transmit(&huart1, "AT pow on\r\n", 11, 1000);
  HAL_UART_Transmit(&huart1, "AT pow off\r\n", 12, 1000);
  HAL_UART_Transmit(&huart1, "AT jump 1 1\r\n", 13, 1000);
  HAL_UART_Transmit(&huart1, "AT jump 1 3\r\n", 13, 1000);
  HAL_UART_Transmit(&huart1, "AT ext 1 on\r\n", 13, 1000);
  HAL_UART_Transmit(&huart1, "AT ext 1 off\r\n", 14, 1000);
  HAL_UART_Transmit(&huart1, "\r\n\r\n", 4, 1000);
  return 0;
}
