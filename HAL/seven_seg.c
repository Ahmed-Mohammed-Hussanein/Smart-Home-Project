/*
 * seven_seg.c
 *
 * Created: 10/6/2023 4:02:03 AM
 *  Author: Ahmed
 */ 

// =============================================
// ================== Includes =================
// =============================================

#include "Utils.h"
#include "Platform_Types.h"

#include "atmega32_GPIO_Driver.h"

#include "seven_seg.h"

/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

void HAL_7seg_Init(void)
{
	GPIO_PinConfig_t _7seg_pins = {_7SEG_PIN_0 | _7SEG_PIN_1 | _7SEG_PIN_2 | _7SEG_PIN_3, GPIO_MODE_OUTPUT};
	MCAL_GPIO_Init(_7SEG_PORT, &_7seg_pins);
}

void HAL_7seg_writeVal(uint8_t val)
{
	MCAL_GPIO_writePin(_7SEG_PORT, _7SEG_PIN_0, READ_BIT(val, 0));
	MCAL_GPIO_writePin(_7SEG_PORT, _7SEG_PIN_1, READ_BIT(val, 1));
	MCAL_GPIO_writePin(_7SEG_PORT, _7SEG_PIN_2, READ_BIT(val, 2));
	MCAL_GPIO_writePin(_7SEG_PORT, _7SEG_PIN_3, READ_BIT(val, 3));
}
