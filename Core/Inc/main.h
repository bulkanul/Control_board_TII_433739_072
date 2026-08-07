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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#ifndef FDCAN
  #include "can.h"
  #define CAN_TYPE CAN_HandleTypeDef
#else
  #include "fdcan.h"
  #define CAN_TYPE FDCAN_HandleTypeDef
#endif

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
#define PHOTO_DIFF_Pin GPIO_PIN_3
#define PHOTO_DIFF_GPIO_Port GPIOF
#define PHOTO3_Pin GPIO_PIN_4
#define PHOTO3_GPIO_Port GPIOF
#define PHOTO4_Pin GPIO_PIN_5
#define PHOTO4_GPIO_Port GPIOF
#define INTERLOCK_1_EXTI_Pin GPIO_PIN_8
#define INTERLOCK_1_EXTI_GPIO_Port GPIOF
#define INTERLOCK_2_EXTI_Pin GPIO_PIN_9
#define INTERLOCK_2_EXTI_GPIO_Port GPIOF
#define ALARM_EXTI_Pin GPIO_PIN_10
#define ALARM_EXTI_GPIO_Port GPIOF
#define TEMPERATURE1_Pin GPIO_PIN_0
#define TEMPERATURE1_GPIO_Port GPIOA
#define TEMPERATURE2_Pin GPIO_PIN_3
#define TEMPERATURE2_GPIO_Port GPIOA
#define PILOT_CURRENT_Pin GPIO_PIN_4
#define PILOT_CURRENT_GPIO_Port GPIOA
#define PHOTO1_Pin GPIO_PIN_0
#define PHOTO1_GPIO_Port GPIOB
#define PHOTO2_Pin GPIO_PIN_1
#define PHOTO2_GPIO_Port GPIOB
#define QBH_EXTI_Pin GPIO_PIN_11
#define QBH_EXTI_GPIO_Port GPIOF
#define KEY_EXTI_Pin GPIO_PIN_12
#define KEY_EXTI_GPIO_Port GPIOF
#define EMERGENCY_EXTI_Pin GPIO_PIN_13
#define EMERGENCY_EXTI_GPIO_Port GPIOF
#define FLASH_ON_IN_Pin GPIO_PIN_14
#define FLASH_ON_IN_GPIO_Port GPIOF
#define CS4_Pin GPIO_PIN_8
#define CS4_GPIO_Port GPIOE
#define CS3_Pin GPIO_PIN_9
#define CS3_GPIO_Port GPIOE
#define CS2_Pin GPIO_PIN_10
#define CS2_GPIO_Port GPIOE
#define CS1_Pin GPIO_PIN_11
#define CS1_GPIO_Port GPIOE
#define LED_POWER2_Pin GPIO_PIN_12
#define LED_POWER2_GPIO_Port GPIOE
#define LED_POWER_Pin GPIO_PIN_13
#define LED_POWER_GPIO_Port GPIOE
#define LED_EMISSION_Pin GPIO_PIN_14
#define LED_EMISSION_GPIO_Port GPIOE
#define LED_ERROR_Pin GPIO_PIN_15
#define LED_ERROR_GPIO_Port GPIOE
#define PROTECTION_ON_OFF_1_Pin GPIO_PIN_8
#define PROTECTION_ON_OFF_1_GPIO_Port GPIOD
#define PROTECTION_ON_OFF_2_Pin GPIO_PIN_9
#define PROTECTION_ON_OFF_2_GPIO_Port GPIOD
#define SHUTDOWN_Pin GPIO_PIN_10
#define SHUTDOWN_GPIO_Port GPIOD
#define LED_RED_Pin GPIO_PIN_13
#define LED_RED_GPIO_Port GPIOD
#define LED_YELLOW_Pin GPIO_PIN_14
#define LED_YELLOW_GPIO_Port GPIOD
#define LED_GREEN_Pin GPIO_PIN_15
#define LED_GREEN_GPIO_Port GPIOD
#define ALARM_PD4_Pin GPIO_PIN_0
#define ALARM_PD4_GPIO_Port GPIOD
#define ALARM_PD3_Pin GPIO_PIN_1
#define ALARM_PD3_GPIO_Port GPIOD
#define ALARM_PD2_Pin GPIO_PIN_2
#define ALARM_PD2_GPIO_Port GPIOD
#define ALARM_PD1_Pin GPIO_PIN_3
#define ALARM_PD1_GPIO_Port GPIOD
#define PILOT_ON_OFF_Pin GPIO_PIN_8
#define PILOT_ON_OFF_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
