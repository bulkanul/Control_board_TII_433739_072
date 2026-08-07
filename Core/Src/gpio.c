/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS4_Pin|CS3_Pin|CS2_Pin|CS1_Pin
                          |LED_POWER2_Pin|LED_POWER_Pin|LED_EMISSION_Pin|LED_ERROR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, PROTECTION_ON_OFF_1_Pin|PROTECTION_ON_OFF_2_Pin|SHUTDOWN_Pin|LED_RED_Pin
                          |LED_YELLOW_Pin|LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PILOT_ON_OFF_GPIO_Port, PILOT_ON_OFF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : INTERLOCK_1_EXTI_Pin INTERLOCK_2_EXTI_Pin ALARM_EXTI_Pin QBH_EXTI_Pin
                           KEY_EXTI_Pin EMERGENCY_EXTI_Pin */
  GPIO_InitStruct.Pin = INTERLOCK_1_EXTI_Pin|INTERLOCK_2_EXTI_Pin|ALARM_EXTI_Pin|QBH_EXTI_Pin
                          |KEY_EXTI_Pin|EMERGENCY_EXTI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : FLASH_ON_IN_Pin */
  GPIO_InitStruct.Pin = FLASH_ON_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(FLASH_ON_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CS4_Pin CS3_Pin CS2_Pin CS1_Pin
                           LED_POWER2_Pin LED_POWER_Pin LED_EMISSION_Pin LED_ERROR_Pin */
  GPIO_InitStruct.Pin = CS4_Pin|CS3_Pin|CS2_Pin|CS1_Pin
                          |LED_POWER2_Pin|LED_POWER_Pin|LED_EMISSION_Pin|LED_ERROR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PROTECTION_ON_OFF_1_Pin PROTECTION_ON_OFF_2_Pin SHUTDOWN_Pin LED_RED_Pin
                           LED_YELLOW_Pin LED_GREEN_Pin */
  GPIO_InitStruct.Pin = PROTECTION_ON_OFF_1_Pin|PROTECTION_ON_OFF_2_Pin|SHUTDOWN_Pin|LED_RED_Pin
                          |LED_YELLOW_Pin|LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : ALARM_PD4_Pin ALARM_PD3_Pin ALARM_PD2_Pin ALARM_PD1_Pin */
  GPIO_InitStruct.Pin = ALARM_PD4_Pin|ALARM_PD3_Pin|ALARM_PD2_Pin|ALARM_PD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PILOT_ON_OFF_Pin */
  GPIO_InitStruct.Pin = PILOT_ON_OFF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PILOT_ON_OFF_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
