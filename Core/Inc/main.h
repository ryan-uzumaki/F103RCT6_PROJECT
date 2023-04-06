/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPIx_SCK_PIN_Pin GPIO_PIN_13
#define SPIx_SCK_PIN_GPIO_Port GPIOC
#define SPIx_MOSI_PIN_Pin GPIO_PIN_14
#define SPIx_MOSI_PIN_GPIO_Port GPIOC
#define MOTOR1_IN1_Pin GPIO_PIN_0
#define MOTOR1_IN1_GPIO_Port GPIOC
#define MOTOR1_IN2_Pin GPIO_PIN_1
#define MOTOR1_IN2_GPIO_Port GPIOC
#define MOTOR2_IN1_Pin GPIO_PIN_2
#define MOTOR2_IN1_GPIO_Port GPIOC
#define MOTOR2_IN2_Pin GPIO_PIN_3
#define MOTOR2_IN2_GPIO_Port GPIOC
#define MOTOR1A_INPUT_Pin GPIO_PIN_0
#define MOTOR1A_INPUT_GPIO_Port GPIOA
#define MOTOR2A_INPUT_Pin GPIO_PIN_1
#define MOTOR2A_INPUT_GPIO_Port GPIOA
#define MOTOR3A_INPUT_Pin GPIO_PIN_2
#define MOTOR3A_INPUT_GPIO_Port GPIOA
#define MOTOR4A_INPUT_Pin GPIO_PIN_3
#define MOTOR4A_INPUT_GPIO_Port GPIOA
#define PWM_SERVO_Pin GPIO_PIN_6
#define PWM_SERVO_GPIO_Port GPIOA
#define SPIx_MISO_PIN_Pin GPIO_PIN_4
#define SPIx_MISO_PIN_GPIO_Port GPIOC
#define SPIx_CS_PIN_Pin GPIO_PIN_5
#define SPIx_CS_PIN_GPIO_Port GPIOC
#define MOTOR1B_INPUT_Pin GPIO_PIN_12
#define MOTOR1B_INPUT_GPIO_Port GPIOB
#define MOTOR2B_INPUT_Pin GPIO_PIN_13
#define MOTOR2B_INPUT_GPIO_Port GPIOB
#define MOTOR3B_INPUT_Pin GPIO_PIN_14
#define MOTOR3B_INPUT_GPIO_Port GPIOB
#define MOTOR4B_INPUT_Pin GPIO_PIN_15
#define MOTOR4B_INPUT_GPIO_Port GPIOB
#define MOTOR3_IN1_Pin GPIO_PIN_6
#define MOTOR3_IN1_GPIO_Port GPIOC
#define MOTOR3_IN2_Pin GPIO_PIN_7
#define MOTOR3_IN2_GPIO_Port GPIOC
#define MOTOR4_IN1_Pin GPIO_PIN_8
#define MOTOR4_IN1_GPIO_Port GPIOC
#define MOTOR4_IN2_Pin GPIO_PIN_9
#define MOTOR4_IN2_GPIO_Port GPIOC
#define LED_PIN_Pin GPIO_PIN_8
#define LED_PIN_GPIO_Port GPIOA
#define PWM_MOTOR1_Pin GPIO_PIN_6
#define PWM_MOTOR1_GPIO_Port GPIOB
#define PWM_MOTOR2_Pin GPIO_PIN_7
#define PWM_MOTOR2_GPIO_Port GPIOB
#define PWM_MOTOR3_Pin GPIO_PIN_8
#define PWM_MOTOR3_GPIO_Port GPIOB
#define PWM_MOTOR4_Pin GPIO_PIN_9
#define PWM_MOTOR4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
