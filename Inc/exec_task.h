#ifndef ___EXEC_TASK_H___
#define ___EXEC_TASK_H___

typedef enum {
  EXEC_ST_OK = 0,
  EXEC_ST_ERROR,
  EXEC_ST_MAX,
} exec_status_t;

typedef enum {
  EXEC_MIN = 0,
  EXEC_SD_SWITCH = EXEC_MIN,
  EXEC_POWER,
  EXEC_EXT_CTRL,
  EXEC_JUMPER_SWITCH,
  EXEC_I2C_CTRL,
  EXEC_MAX
} exec_type_id_t;

typedef enum {
  CMD_CLEAR = 0,
  CMD_OFF = CMD_CLEAR,
  CMD_ON,
  CMD_SET = CMD_ON,
  CMD_SET_BOTH = CMD_SET,
  CMD_SET1,
  CMD_SET2,
  CMD_TOGGLE,
  CMD_MAX
} cmd_id_t;

struct exec_sd_switch_cmd {
  cmd_id_t cmd;
};

struct exec_power_cmd {
  cmd_id_t cmd;
};

struct exec_ext_ctrl_cmd {
  cmd_id_t cmd;
  uint16_t channel;
};

struct exec_jumper_switch_cmd {
  cmd_id_t cmd;
  uint16_t channel;
};

struct exec_i2c_control_cmd {
  exec_type_id_t type;
  cmd_id_t cmd;
  unsigned char addr;
};

struct exec_command {
  exec_type_id_t type;
  osMessageQId resp_queue;
  union {
    struct exec_sd_switch_cmd sd_switch;
    struct exec_power_cmd power;
    struct exec_ext_ctrl_cmd ext_ctrl;
    struct exec_jumper_switch_cmd jump_switch;
    struct exec_i2c_control_cmd i2c_ctrl;
  } u;
};

extern osThreadId execTaskHandle;
extern osMessageQId execQueueHandle;

void execTaskExecution(void);

#endif /* ___EXEC_TASK_H___ */
