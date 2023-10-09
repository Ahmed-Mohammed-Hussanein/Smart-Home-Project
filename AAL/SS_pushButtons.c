/*
 * SS_pushButtons.c
 *
 * Created: 10/6/2023 4:14:06 AM
 *  Author: Ahmed
 */ 

#include "atmega32_EXTI_Driver.h"
#include "SS_pushButtons.h"

// EXTI0 for decrement
// EXTI1 for increment


static sint8_t PB_state = 0;
void (*p2SS_PB_state)(void);

e_SS_PB_StateId_t SS_PB_state;

void SS_PB_Init(void)
{
	// state name
	SS_PB_state = SS_PB_Idle;
	
	// state init
	EXTI_PinConfig_t PB1_pin = {EXTI_INT_0, EXTI_TRIGGER_RISING};
	MCAL_EXTI_Init(&PB1_pin);
	
	PB1_pin.EXTI_INTx		 = EXTI_INT_1;
	MCAL_EXTI_Init(&PB1_pin);

	// state transition
	p2SS_PB_state = STATE(SS_PB_Idle);
}


STATE_fn(SS_PB_Idle)
{
	// state name
	SS_PB_state = SS_PB_Idle;

	// state action
	

	// state transition
	p2SS_PB_state = STATE(SS_PB_Check);
}

STATE_fn(SS_PB_Check)
{
	// state name
	SS_PB_state = SS_PB_Check;

	// state action
	if (PB_state != 0)
	{
		SS_receive_PB_state(PB_state);
		
	}
	PB_state = 0;

	// state transition
	p2SS_PB_state = STATE(SS_PB_Idle);
}


void MCAL_EXTI0_CallBack(void)
{
	PB_state--;
}

void MCAL_EXTI1_CallBack(void)
{
	PB_state++;
}