/*
 * atmega32_EXTI_Driver.h
 *
 * Created: 10/6/2023 1:40:49 AM
 *  Author: Ahmed
 */ 


#ifndef ATMEGA32_EXTI_DRIVER_H_
#define ATMEGA32_EXTI_DRIVER_H_

// =============================================
// ================== Includes =================
// =============================================


#include "Platform_Types.h"


// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

// INT0 --> PD2
// INT1 -->	PD3
// INT2 --> PB2

typedef struct
{
	uint8_t EXTI_INTx;			/* This specifies which INT to be configured.
									This parameter must be a value of @ref EXTI_INT_define.
									*/
	
	uint8_t EXTI_Trigger;		/* This specifies the trigger of the interrupt.
									This parameter must be a value of @ref EXTI_TRIGGER_define.
									*/
	
}	EXTI_PinConfig_t;

// ===================================================================
// ================== Macros Configuration Reference =================
// ===================================================================

// @ref EXTI_INT_define.
#define EXTI_INT_0					0
#define EXTI_INT_1					1
#define EXTI_INT_2					2

// @ref EXTI_TRIGGER_define.
// Note only INT2 has Falling or Rising Trigger only.
#define EXTI_TRIGGER_LOWLEVEL		0x0
#define EXTI_TRIGGER_ANY			0x1
#define EXTI_TRIGGER_FALLING		0x2
#define EXTI_TRIGGER_RISING			0x3


// ===================================================
// ================== APIs Functions =================
// ===================================================
void MCAL_EXTI_Init(EXTI_PinConfig_t *EXTI_Config);
void MCAL_EXTI_GPIO_setPins();

void MCAL_EXTI_Update(EXTI_PinConfig_t *EXTI_Config);

void MCAL_EXTI0_CallBack(void);
void MCAL_EXTI1_CallBack(void);
void MCAL_EXTI2_CallBack(void);




#endif /* ATMEGA32_EXTI_DRIVER_H_ */