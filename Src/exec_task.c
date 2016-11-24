#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "exec_task.h"

static char s_sdSwitchState = 0;
static char s_powSwitchState = 0;
static char s_extCtrlState[4] = {0};
static char s_jumpSwitchState[4] = {0};

static int _sd_switch(struct exec_sd_switch_cmd *cmd) {
  switch(cmd->cmd) {
  case CMD_OFF:
    CARD_SWITCH_OFF();
    s_sdSwitchState = 0;
    break;
  case CMD_ON:
    CARD_SWITCH_ON();
    s_sdSwitchState = 1;
    break;
  case CMD_TOGGLE:
    if (s_sdSwitchState) {
      CARD_SWITCH_OFF();
      s_sdSwitchState = 0;
    } else {
      CARD_SWITCH_ON();
      s_sdSwitchState = 1;
    }
    break;
  default:
    return 0;
  }

  CARD_RESET_OFF();
  osDelay(1);
  CARD_RESET_ON();
  return 0;
}

static int _power_switch(struct exec_power_cmd *cmd) {
  switch(cmd->cmd) {
    case CMD_OFF:
    POW_CTRL_OFF();
    s_powSwitchState = 0;
    break;
    case CMD_ON:
    POW_CTRL_ON();
    s_powSwitchState = 1;
    break;
    case CMD_TOGGLE:
    if (s_powSwitchState) {
      POW_CTRL_OFF();
      s_powSwitchState = 0;
    } else {
      POW_CTRL_ON();
      s_powSwitchState = 1;
    }
    break;
    default:
    break;
  }

  return 0;
}

static int _ext_control(struct exec_ext_ctrl_cmd *cmd) {
  switch(cmd->channel) {
    // Channel 1
    case 0:
      switch(cmd->cmd){
        case CMD_OFF:
          EXT_CTRL_1_OFF();
          s_extCtrlState[0] = 0;
          break;
        case CMD_ON:
          EXT_CTRL_1_ON();
          s_extCtrlState[0] = 1;
          break;
        case CMD_TOGGLE:
          if (s_extCtrlState[0]) {
            EXT_CTRL_1_OFF();
            s_extCtrlState[0] = 0;
          } else {
            EXT_CTRL_1_ON();
            s_extCtrlState[0] = 1;
          }
          break;
      }
      break;
    // Channel 2
    case 1:
      switch(cmd->cmd){
        case CMD_OFF:
          EXT_CTRL_2_OFF();
          s_extCtrlState[1] = 0;
          break;
        case CMD_ON:
          EXT_CTRL_2_ON();
          s_extCtrlState[1] = 1;
          break;
        case CMD_TOGGLE:
          if (s_extCtrlState[1]) {
            EXT_CTRL_2_OFF();
            s_extCtrlState[1] = 0;
          } else {
            EXT_CTRL_2_ON();
            s_extCtrlState[1] = 1;
          }
          break;
      }
      break;
    // Channel 3
    case 2:
      switch(cmd->cmd){
        case CMD_OFF:
          EXT_CTRL_3_OFF();
          s_extCtrlState[2] = 0;
          break;
        case CMD_ON:
          EXT_CTRL_3_ON();
          s_extCtrlState[2] = 1;
          break;
        case CMD_TOGGLE:
          if (s_extCtrlState[2]) {
            EXT_CTRL_3_OFF();
            s_extCtrlState[2] = 0;
          } else {
            EXT_CTRL_3_ON();
            s_extCtrlState[2] = 1;
          }
          break;
      }
      break;
    // Channel 4
    case 3:
      switch(cmd->cmd){
        case CMD_OFF:
          EXT_CTRL_4_OFF();
          s_extCtrlState[3] = 0;
          break;
        case CMD_ON:
          EXT_CTRL_4_ON();
          s_extCtrlState[3] = 1;
          break;
        case CMD_TOGGLE:
          if (s_extCtrlState[3]) {
            EXT_CTRL_4_OFF();
            s_extCtrlState[3] = 0;
          } else {
            EXT_CTRL_4_ON();
            s_extCtrlState[3] = 1;
          }
          break;
      }
      break;
      default:
        return -1;
  }
  return 0;
}

static int _jumper_switch(struct exec_jumper_switch_cmd *cmd) {
  struct jumper_setting jumps[4] = JCTRL_ARRAY;
  struct jumper_setting *jump_ptr;

  if (cmd->channel >= JUMPER_CHANNEL_MAX) {
    return -1;
  }
  if (cmd->cmd >= CMD_MAX) {
    return -1;
  }

  jump_ptr = &jumps[cmd->channel];
  switch (cmd->cmd) {
    case CMD_SET_BOTH:
      HAL_GPIO_WritePin(jump_ptr->port1, jump_ptr->pin1, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(jump_ptr->port2, jump_ptr->pin2, GPIO_PIN_RESET);
      s_jumpSwitchState[cmd->channel] = 3;
      break;
    case CMD_SET1:
      HAL_GPIO_WritePin(jump_ptr->port1, jump_ptr->pin1, GPIO_PIN_SET);
      HAL_GPIO_WritePin(jump_ptr->port2, jump_ptr->pin2, GPIO_PIN_RESET);
      s_jumpSwitchState[cmd->channel] = 1;
      break;
    case CMD_SET2:
      HAL_GPIO_WritePin(jump_ptr->port1, jump_ptr->pin1, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(jump_ptr->port2, jump_ptr->pin2, GPIO_PIN_SET);
      s_jumpSwitchState[cmd->channel] = 2;
      break;
    case CMD_TOGGLE:
      if (++s_jumpSwitchState[cmd->channel] > 3) {
        s_jumpSwitchState[cmd->channel] = 0;
      }
      switch (s_jumpSwitchState[cmd->channel]) {
        case 0:
          // All off
          HAL_GPIO_WritePin(jump_ptr->port1, jump_ptr->pin1, GPIO_PIN_SET);
          HAL_GPIO_WritePin(jump_ptr->port2, jump_ptr->pin2, GPIO_PIN_SET);
          break;
        case 1:
          // SET 1
          HAL_GPIO_WritePin(jump_ptr->port1, jump_ptr->pin1, GPIO_PIN_SET);
          HAL_GPIO_WritePin(jump_ptr->port2, jump_ptr->pin2, GPIO_PIN_RESET);
          break;
        case 2:
          // SET 2
          HAL_GPIO_WritePin(jump_ptr->port1, jump_ptr->pin1, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(jump_ptr->port2, jump_ptr->pin2, GPIO_PIN_SET);
          break;
        case 3:
          // SET BOTH
          HAL_GPIO_WritePin(jump_ptr->port1, jump_ptr->pin1, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(jump_ptr->port2, jump_ptr->pin2, GPIO_PIN_RESET);
          break;
      }
      break;
    default:
      // All off
      HAL_GPIO_WritePin(jump_ptr->port1, jump_ptr->pin1, GPIO_PIN_SET);
      HAL_GPIO_WritePin(jump_ptr->port2, jump_ptr->pin2, GPIO_PIN_SET);
      s_jumpSwitchState[cmd->channel] = 0;
      break;
  }

  return 0;
}

static int _i2c_control(struct exec_i2c_control_cmd *cmd) {

  return 0;
}

void execTaskExecution(void) {
  struct exec_command cmd;
  int res = -1;
  int8_t resp_val = -1;

  // Receive command from queue with timeout is 1ms
  if (xQueueReceive(execQueueHandle, &cmd, 1/portTICK_PERIOD_MS)) {
    switch (cmd.type) {
    case EXEC_SD_SWITCH:
      res = _sd_switch(&cmd.u.sd_switch);
      break;
    case EXEC_POWER:
      res = _power_switch(&cmd.u.power);
      break;
    case EXEC_EXT_CTRL:
      res = _ext_control(&cmd.u.ext_ctrl);
      break;
    case EXEC_JUMPER_SWITCH:
      res = _jumper_switch(&cmd.u.jump_switch);
      break;
    case EXEC_I2C_CTRL:
      res = _i2c_control(&cmd.u.i2c_ctrl);
      break;
    default:
      return;
    }

    if (!res) {
      resp_val = EXEC_ST_OK;
    } else {
      resp_val = EXEC_ST_ERROR;
    }
    if (cmd.resp_queue) {
      // Send reponse if queue handle available
      xQueueSend(cmd.resp_queue, &resp_val, 1/portTICK_PERIOD_MS);
    }
  }
}
