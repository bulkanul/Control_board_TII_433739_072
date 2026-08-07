#include "hardware.h"

bool is_alarm_ALARM (void)
{
	return HAL_GPIO_ReadPin (ALARM_EXTI_GPIO_Port, ALARM_EXTI_Pin) == GPIO_PIN_RESET;
}

bool is_alarm_emergency (void)
{
	return HAL_GPIO_ReadPin (EMERGENCY_EXTI_GPIO_Port, EMERGENCY_EXTI_Pin) == GPIO_PIN_RESET;
}

bool is_alarm_keylock (void)
{
	return HAL_GPIO_ReadPin (KEY_EXTI_GPIO_Port, KEY_EXTI_Pin) == GPIO_PIN_RESET;
}

bool is_alarm_interlock1 (void)
{
	return HAL_GPIO_ReadPin (INTERLOCK_1_EXTI_GPIO_Port, INTERLOCK_1_EXTI_Pin) == GPIO_PIN_RESET;
}

bool is_alarm_interlock2 (void)
{
	return HAL_GPIO_ReadPin (INTERLOCK_2_EXTI_GPIO_Port, INTERLOCK_2_EXTI_Pin) == GPIO_PIN_RESET;
}

bool is_alarm_QBH(void)
{
	return HAL_GPIO_ReadPin (QBH_EXTI_GPIO_Port, QBH_EXTI_Pin) == GPIO_PIN_RESET;
}
