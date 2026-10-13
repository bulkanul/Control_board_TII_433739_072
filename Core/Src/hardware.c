#include "hardware.h"

void ALARM_on (void)
{
	ALARM_OUT_GPIO_Port->BSRR = ALARM_OUT_Pin;
}
void ALARM_off (void)
{
    ALARM_OUT_GPIO_Port->BSRR = (uint32_t)ALARM_OUT_Pin << 16U;
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

bool is_alarm_pd(int id)
{
	GPIO_TypeDef *port[] = {
			ALARM_PD1_GPIO_Port,
			ALARM_PD2_GPIO_Port,
			ALARM_PD3_GPIO_Port,
			ALARM_PD4_GPIO_Port
	};
	uint16_t pin[] = {
			ALARM_PD1_Pin,
			ALARM_PD2_Pin,
			ALARM_PD3_Pin,
			ALARM_PD4_Pin
	};
	return HAL_GPIO_ReadPin (port[id], pin[id]) == GPIO_PIN_RESET;
}

void set_pd_level_value(int id, float value)
{
	GPIO_TypeDef* cs_port[] = {
			CS1_GPIO_Port,
			CS2_GPIO_Port,
			CS3_GPIO_Port,
			CS4_GPIO_Port
	};
	uint16_t cs_pin[] = {
			CS1_Pin,
			CS2_Pin,
			CS3_Pin,
			CS4_Pin
	};
	HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CS3_GPIO_Port, CS3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CS4_GPIO_Port, CS4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(cs_port[id], cs_pin[id], GPIO_PIN_SET);
	DAC_AD5693(value);
	HAL_GPIO_WritePin(cs_port[id], cs_pin[id], GPIO_PIN_RESET);
}

void set_protection_state(int id, int value)
{
	bool b_val = value;
	b_val = !b_val;
	value = b_val;
	GPIO_TypeDef *gpio[] = {
			PROTECTION_ON_OFF_1_GPIO_Port,
			PROTECTION_ON_OFF_2_GPIO_Port
	};
	uint16_t pin[] = {
			PROTECTION_ON_OFF_1_Pin,
			PROTECTION_ON_OFF_2_Pin
	};
	HAL_GPIO_WritePin(gpio[id], pin[id], value);
}
