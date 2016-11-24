/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
// LEDs definitions
#define BOARD_LED_1_PORT GPIOA
#define BOARD_LED_1_PIN  GPIO_PIN_11

#define BOARD_LED_2_PORT GPIOA
#define BOARD_LED_2_PIN  GPIO_PIN_12

#define LED1_ON()  HAL_GPIO_WritePin(BOARD_LED_1_PORT, BOARD_LED_1_PIN, GPIO_PIN_SET)
#define LED1_OFF() HAL_GPIO_WritePin(BOARD_LED_1_PORT, BOARD_LED_1_PIN, GPIO_PIN_RESET)

#define LED2_ON()  HAL_GPIO_WritePin(BOARD_LED_2_PORT, BOARD_LED_2_PIN, GPIO_PIN_SET)
#define LED2_OFF() HAL_GPIO_WritePin(BOARD_LED_2_PORT, BOARD_LED_2_PIN, GPIO_PIN_RESET)

// EXT interrupt button definitions
typedef enum {
  BTN_INT_JB_1 = GPIO_PIN_0,
  BTN_INT_JB_2 = GPIO_PIN_15,
  BTN_INT_JB_3 = GPIO_PIN_14,
  BTN_INT_JB_4 = GPIO_PIN_13,
  BTN_INT_I2C_INT = GPIO_PIN_6,
  BTN_INT_POW = GPIO_PIN_9,
  BTN_INT_SDCARD = GPIO_PIN_8,
} button_int_number_t;

//// Output GPIO control pins definitions
// Power control pin
#define BOARD_POW_CTRL_PORT     GPIOA
#define BOARD_POW_CTRL_PIN      GPIO_PIN_8
#define POW_CTRL_OFF()          HAL_GPIO_WritePin(BOARD_POW_CTRL_PORT, BOARD_POW_CTRL_PIN, GPIO_PIN_SET)
#define POW_CTRL_ON()           HAL_GPIO_WritePin(BOARD_POW_CTRL_PORT, BOARD_POW_CTRL_PIN, GPIO_PIN_RESET)
// SD-Card switch pin
#define BOARD_CARD_SWITCH_PORT  GPIOB
#define BOARD_CARD_SWITCH_PIN   GPIO_PIN_14
#define CARD_SWITCH_ON()        HAL_GPIO_WritePin(BOARD_CARD_SWITCH_PORT, BOARD_CARD_SWITCH_PIN, GPIO_PIN_SET)
#define CARD_SWITCH_OFF()       HAL_GPIO_WritePin(BOARD_CARD_SWITCH_PORT, BOARD_CARD_SWITCH_PIN, GPIO_PIN_RESET)
// SD-Card reset pin
#define BOARD_CARD_RESET_PORT   GPIOB
#define BOARD_CARD_RESET_PIN    GPIO_PIN_15
#define CARD_RESET_ON()         HAL_GPIO_WritePin(BOARD_CARD_RESET_PORT, BOARD_CARD_RESET_PIN, GPIO_PIN_SET)
#define CARD_RESET_OFF()        HAL_GPIO_WritePin(BOARD_CARD_RESET_PORT, BOARD_CARD_RESET_PIN, GPIO_PIN_RESET)
// External control 1 pin
#define BOARD_EXT_CTRL_1_PORT   GPIOB
#define BOARD_EXT_CTRL_1_PIN    GPIO_PIN_5
#define EXT_CTRL_1_ON()         HAL_GPIO_WritePin(BOARD_EXT_CTRL_1_PORT, BOARD_EXT_CTRL_1_PIN, GPIO_PIN_SET)
#define EXT_CTRL_1_OFF()        HAL_GPIO_WritePin(BOARD_EXT_CTRL_1_PORT, BOARD_EXT_CTRL_1_PIN, GPIO_PIN_RESET)
// External control 1 pin
#define BOARD_EXT_CTRL_2_PORT   GPIOB
#define BOARD_EXT_CTRL_2_PIN    GPIO_PIN_4
#define EXT_CTRL_2_ON()         HAL_GPIO_WritePin(BOARD_EXT_CTRL_2_PORT, BOARD_EXT_CTRL_2_PIN, GPIO_PIN_SET)
#define EXT_CTRL_2_OFF()        HAL_GPIO_WritePin(BOARD_EXT_CTRL_2_PORT, BOARD_EXT_CTRL_2_PIN, GPIO_PIN_RESET)
// External control 1 pin
#define BOARD_EXT_CTRL_3_PORT   GPIOB
#define BOARD_EXT_CTRL_3_PIN    GPIO_PIN_3
#define EXT_CTRL_3_ON()         HAL_GPIO_WritePin(BOARD_EXT_CTRL_3_PORT, BOARD_EXT_CTRL_3_PIN, GPIO_PIN_SET)
#define EXT_CTRL_3_OFF()        HAL_GPIO_WritePin(BOARD_EXT_CTRL_3_PORT, BOARD_EXT_CTRL_3_PIN, GPIO_PIN_RESET)
// External control 1 pin
#define BOARD_EXT_CTRL_4_PORT   GPIOA
#define BOARD_EXT_CTRL_4_PIN    GPIO_PIN_15
#define EXT_CTRL_4_ON()         HAL_GPIO_WritePin(BOARD_EXT_CTRL_4_PORT, BOARD_EXT_CTRL_4_PIN, GPIO_PIN_SET)
#define EXT_CTRL_4_OFF()        HAL_GPIO_WritePin(BOARD_EXT_CTRL_4_PORT, BOARD_EXT_CTRL_4_PIN, GPIO_PIN_RESET)
/// Jumper switch
// Jumper 1
#define BOARD_JCTRL_1_1_PORT    GPIOA
#define BOARD_JCTRL_1_1_PIN     GPIO_PIN_7
#define JCTRL_1_1_DIS()         HAL_GPIO_WritePin(BOARD_JCTRL_1_1_PORT, BOARD_JCTRL_1_1_PIN, GPIO_PIN_SET)
#define JCTRL_1_1_CON()         HAL_GPIO_WritePin(BOARD_JCTRL_1_1_PORT, BOARD_JCTRL_1_1_PIN, GPIO_PIN_RESET)
#define BOARD_JCTRL_1_2_PORT    GPIOB
#define BOARD_JCTRL_1_2_PIN     GPIO_PIN_0
#define JCTRL_1_2_DIS()         HAL_GPIO_WritePin(BOARD_JCTRL_1_2_PORT, BOARD_JCTRL_1_2_PIN, GPIO_PIN_SET)
#define JCTRL_1_2_CON()         HAL_GPIO_WritePin(BOARD_JCTRL_1_2_PORT, BOARD_JCTRL_1_2_PIN, GPIO_PIN_RESET)
#define JCTRL_1_TO_1()          JCTRL_1_1_DIS();JCTRL_1_2_CON()
#define JCTRL_1_TO_3()          JCTRL_1_1_CON();JCTRL_1_2_DIS()
#define JCTRL_1_TO_BOTH()       JCTRL_1_1_CON();JCTRL_1_2_CON()
#define JCTRL_1_TO_NONE()       JCTRL_1_1_DIS();JCTRL_1_2_DIS()
// Jumper 2
#define BOARD_JCTRL_2_1_PORT    GPIOA
#define BOARD_JCTRL_2_1_PIN     GPIO_PIN_5
#define JCTRL_2_1_DIS()         HAL_GPIO_WritePin(BOARD_JCTRL_2_1_PORT, BOARD_JCTRL_2_1_PIN, GPIO_PIN_SET)
#define JCTRL_2_1_CON()         HAL_GPIO_WritePin(BOARD_JCTRL_2_1_PORT, BOARD_JCTRL_2_1_PIN, GPIO_PIN_RESET)
#define BOARD_JCTRL_2_2_PORT    GPIOA
#define BOARD_JCTRL_2_2_PIN     GPIO_PIN_6
#define JCTRL_2_2_DIS()         HAL_GPIO_WritePin(BOARD_JCTRL_2_2_PORT, BOARD_JCTRL_2_2_PIN, GPIO_PIN_SET)
#define JCTRL_2_2_CON()         HAL_GPIO_WritePin(BOARD_JCTRL_2_2_PORT, BOARD_JCTRL_2_2_PIN, GPIO_PIN_RESET)
#define JCTRL_2_TO_1()          JCTRL_2_1_DIS();JCTRL_2_2_CON()
#define JCTRL_2_TO_3()          JCTRL_2_1_CON();JCTRL_2_2_DIS()
#define JCTRL_2_TO_BOTH()       JCTRL_2_1_CON();JCTRL_2_2_CON()
#define JCTRL_2_TO_NONE()       JCTRL_2_1_DIS();JCTRL_2_2_DIS()
// Jumper 3
#define BOARD_JCTRL_3_1_PORT    GPIOA
#define BOARD_JCTRL_3_1_PIN     GPIO_PIN_3
#define JCTRL_3_1_DIS()         HAL_GPIO_WritePin(BOARD_JCTRL_3_1_PORT, BOARD_JCTRL_3_1_PIN, GPIO_PIN_SET)
#define JCTRL_3_1_CON()         HAL_GPIO_WritePin(BOARD_JCTRL_3_1_PORT, BOARD_JCTRL_3_1_PIN, GPIO_PIN_RESET)
#define BOARD_JCTRL_3_2_PORT    GPIOA
#define BOARD_JCTRL_3_2_PIN     GPIO_PIN_4
#define JCTRL_3_2_DIS()         HAL_GPIO_WritePin(BOARD_JCTRL_3_2_PORT, BOARD_JCTRL_3_2_PIN, GPIO_PIN_SET)
#define JCTRL_3_2_CON()         HAL_GPIO_WritePin(BOARD_JCTRL_3_2_PORT, BOARD_JCTRL_3_2_PIN, GPIO_PIN_RESET)
#define JCTRL_3_TO_1()          JCTRL_3_1_DIS();JCTRL_3_2_CON()
#define JCTRL_3_TO_3()          JCTRL_3_1_CON();JCTRL_3_2_DIS()
#define JCTRL_3_TO_BOTH()       JCTRL_3_1_CON();JCTRL_3_2_CON()
#define JCTRL_3_TO_NONE()       JCTRL_3_1_DIS();JCTRL_3_2_DIS()
// Jumper 4
#define BOARD_JCTRL_4_1_PORT    GPIOA
#define BOARD_JCTRL_4_1_PIN     GPIO_PIN_1
#define JCTRL_4_1_DIS()         HAL_GPIO_WritePin(BOARD_JCTRL_4_1_PORT, BOARD_JCTRL_4_1_PIN, GPIO_PIN_SET)
#define JCTRL_4_1_CON()         HAL_GPIO_WritePin(BOARD_JCTRL_4_1_PORT, BOARD_JCTRL_4_1_PIN, GPIO_PIN_RESET)
#define BOARD_JCTRL_4_2_PORT    GPIOA
#define BOARD_JCTRL_4_2_PIN     GPIO_PIN_2
#define JCTRL_4_2_DIS()         HAL_GPIO_WritePin(BOARD_JCTRL_4_2_PORT, BOARD_JCTRL_4_2_PIN, GPIO_PIN_SET)
#define JCTRL_4_2_CON()         HAL_GPIO_WritePin(BOARD_JCTRL_4_2_PORT, BOARD_JCTRL_4_2_PIN, GPIO_PIN_RESET)
#define JCTRL_4_TO_1()          JCTRL_4_1_DIS();JCTRL_4_2_CON()
#define JCTRL_4_TO_3()          JCTRL_4_1_CON();JCTRL_4_2_DIS()
#define JCTRL_4_TO_BOTH()       JCTRL_4_1_CON();JCTRL_4_2_CON()
#define JCTRL_4_TO_NONE()       JCTRL_4_1_DIS();JCTRL_4_2_DIS()

struct jumper_setting {
  GPIO_TypeDef* port1;
  uint16_t pin1;
  GPIO_TypeDef* port2;
  uint16_t pin2;
};

typedef enum {
  JUMPER_CHANNEL_1 = 0,
  JUMPER_CHANNEL_2,
  JUMPER_CHANNEL_3,
  JUMPER_CHANNEL_4,
  JUMPER_CHANNEL_MAX,
} jumper_channel_t;

#define JCTRL_ARRAY {                                                                             \
  {BOARD_JCTRL_1_1_PORT, BOARD_JCTRL_1_1_PIN, BOARD_JCTRL_1_2_PORT, BOARD_JCTRL_1_2_PIN},         \
  {BOARD_JCTRL_2_1_PORT, BOARD_JCTRL_2_1_PIN, BOARD_JCTRL_2_2_PORT, BOARD_JCTRL_2_2_PIN},         \
  {BOARD_JCTRL_3_1_PORT, BOARD_JCTRL_3_1_PIN, BOARD_JCTRL_3_2_PORT, BOARD_JCTRL_3_2_PIN},         \
  {BOARD_JCTRL_4_1_PORT, BOARD_JCTRL_4_1_PIN, BOARD_JCTRL_4_2_PORT, BOARD_JCTRL_4_2_PIN},         \
}

// Input jumper definitions
#define BOARD_I2C_CONF_PORT GPIOB
#define BOARD_I2C_CONF_PIN  GPIO_PIN_7
#define GET_I2C_CONF() HAL_GPIO_ReadPin(BOARD_I2C_CONF_PORT,BOARD_I2C_CONF_PIN)
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
