#ifndef ___EXEC_TASK_H___
#define ___EXEC_TASK_H___

typedef enum {
  EXEC_MIN = 0,
  EXEC_SD_SWITCH = EXEC_MIN,
  EXEC_POWER,
  EXEC_EXT_CTRL,
  EXEC_JUMPER_SWITCH,
  EXEC_I2C_CTRL,
  EXEC_MAX
} exec_type_id_t;

struct exec_sd_switch_cmd {
  unsigned int cmd;
};

struct exec_power_cmd {
  unsigned int cmd;
};

struct exec_ext_ctrl_cmd {
  unsigned int channel:16;
  unsigned int cmd:16;
};

struct exec_jumper_switch_cmd {
  unsigned int channel:16;
  unsigned int cmd:16;
};

struct exec_i2c_control_cmd {
  exec_type_id_t type;
  unsigned char addr;
  unsigned char cmd;
};

struct exec_command {
  exec_type_id_t type;

  union {
    struct exec_sd_switch_cmd sd_switch;
    struct exec_power_cmd power;
    struct exec_ext_ctrl_cmd ext_ctl;
    struct exec_jumper_switch_cmd jump_switch;
    struct exec_i2c_control_cmd i2c_ctrl;
  } u;
};

extern osThreadId execTaskHandle;
extern osMessageQId execQueueHandle;

void execTaskExecution(void);

#endif /* ___EXEC_TASK_H___ */
