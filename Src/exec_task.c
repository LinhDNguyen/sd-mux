#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "exec_task.h"

void execTaskExecution(void) {
  struct exec_command cmd;

  // Receive command from queue with timeout is 1ms
  if (xQueueReceive(execQueueHandle, &cmd, 1/portTICK_PERIOD_MS)) {
    // TODO: Command received, process it
  }
}
