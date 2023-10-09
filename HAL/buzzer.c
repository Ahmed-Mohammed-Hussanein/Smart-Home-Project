/*
 * buzzer.c
 *
 * Created: 10/6/2023 2:48:06 AM
 *  Author: Ahmed
 */ 


// =============================================
// ================== Includes =================
// =============================================

#include <util/delay.h>

#include "Platform_Types.h"

#include "atmega32_GPIO_Driver.h"

/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */
void HAL_buzzer_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig)
{
	MCAL_GPIO_Init(GPIOx, PinConfig);
}

void HAL_buzzer_turnOn(GPIO_TypeDef *GPIOx, uint8_t PinNumber)
{
	MCAL_GPIO_writePin(GPIOx, PinNumber, GPIO_STATE_HIGH);
}

void HAL_buzzer_turnOff(GPIO_TypeDef *GPIOx, uint8_t PinNumber)
{
	MCAL_GPIO_writePin(GPIOx, PinNumber, GPIO_STATE_LOW);
}
