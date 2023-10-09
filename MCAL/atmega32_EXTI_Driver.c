/*
 * atmega32_EXTI_Driver.c
 *
 * Created: 10/6/2023 1:41:08 AM
 *  Author: Ahmed
 */ 

// =============================================
// ================== Includes =================
// =============================================

#include <avr/interrupt.h>

#include "Platform_Types.h"

#include "atmega32_device_header.h"
#include "atmega32_BitField.h"
#include "atmega32_peripheral_pins.h"
#include "atmega32_GPIO_Driver.h"
#include "atmega32_EXTI_Driver.h"


/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

/**================================================================
* @Fn				- MCAL_EXTI_Init
* @brief			- This is used to configure and initialize a pin as EXTI.
* @param [in] 		- EXTI_Config: This is the configuration for EXTI.
* @retval 			- None.
* Note				- None.
*/
void MCAL_EXTI_Init(EXTI_PinConfig_t *EXTI_Config)
{
	switch (EXTI_Config->EXTI_INTx)
	{
		case EXTI_INT_0:
		// Trigger Configuration.
		WRITE_MASK(MCUR->_MCUCR, MCUCR_ISC0n_Mask, EXTI_Config->EXTI_Trigger << MCUCR_ISC0n_Pos);
		
		// Enable Interrupt.
		SET_MASK(INT->_GICR, GICR_INT0);
		break;
		
		case EXTI_INT_1:
		// Trigger Configuration.
		WRITE_MASK(MCUR->_MCUCR, MCUCR_ISC1n_Mask, EXTI_Config->EXTI_Trigger << MCUCR_ISC1n_Pos);
		
		// Enable Interrupt.
		SET_MASK(INT->_GICR, GICR_INT1);
		
		break;
		
		case EXTI_INT_2:
		// Trigger Configuration.
		WRITE_MASK(MCUR->_MCUCSR, MCUCSR_ISC2_Mask, EXTI_Config->EXTI_Trigger << MCUCSR_ISC2_Pos);
		
		// Enable Interrupt.
		SET_MASK(INT->_GICR, GICR_INT2);
		
		break;
	}
	
	// Enable Global INT.
	Enable_Global_INT();
}

void MCAL_EXTI_GPIO_setPins()
{
	GPIO_PinConfig_t EXTI_pin;
	EXTI_pin.GPIO_PinMode = GPIO_MODE_INPUT;
	
	if (READ_MASK(INT->_GICR, GICR_INT0))
	{
		EXTI_pin.GPIO_PinNumber = EXTI0_PIN;
		MCAL_GPIO_Init(EXTI0_PORT, &EXTI_pin);
	}
	if (READ_MASK(INT->_GICR, GICR_INT1))
	{
		EXTI_pin.GPIO_PinNumber = EXTI1_PIN;
		MCAL_GPIO_Init(EXTI1_PORT, &EXTI_pin);
	}
	if (READ_MASK(INT->_GICR, GICR_INT2))
	{
		EXTI_pin.GPIO_PinNumber = EXTI2_PIN;
		MCAL_GPIO_Init(EXTI2_PORT, &EXTI_pin);
	}
}

void MCAL_EXTI_Update(EXTI_PinConfig_t *EXTI_Config);






ISR(INT0_vect)
{
	MCAL_EXTI0_CallBack();
}

ISR(INT1_vect)
{
	MCAL_EXTI1_CallBack();
}

ISR(INT2_vect)
{
	MCAL_EXTI2_CallBack();
}

__attribute__((weak)) void MCAL_EXTI0_CallBack(void)
{
	while(1);
}

__attribute__((weak)) void MCAL_EXTI1_CallBack(void)
{
	while(1);
}

__attribute__((weak)) void MCAL_EXTI2_CallBack(void)
{
	while(1);
}