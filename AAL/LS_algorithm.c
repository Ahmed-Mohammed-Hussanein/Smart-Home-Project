/*
 * LS_algorithm.c
 *
 * Created: 10/7/2023 9:32:43 PM
 *  Author: Ahmed
 */ 

#include "Platform_Types.h"

#include "LS_algorithm.h"


static uint16_t LightSystem_res_value			= 0;
static uint8_t LightSystem_led2_timer_value		= 0;
void (*p2LightSystem_state)(void);

e_LightSystem_StateId_t LightSystem_state;


void LS_setResValue(sint8_t rVal)
{
	LightSystem_res_value = rVal;
	p2LightSystem_state = STATE(LightSystem_Busy);
}

void LightSystem_Init(void)
{
	// state name
	LightSystem_state = LightSystem_Idle;

	// state init

	// state transition
	p2LightSystem_state = STATE(LightSystem_Idle);
}


STATE_fn(LightSystem_Idle)
{
	// state name
	LightSystem_state = LightSystem_Idle;

	// state action
	

	// state transition
	p2LightSystem_state = STATE(LightSystem_Idle);
}

STATE_fn(LightSystem_Busy)
{
	// state name
	LightSystem_state = LightSystem_Busy;

	// state action
	// calculate the timer value
	LightSystem_led2_timer_value = LightSystem_res_value * 0.2619 - 1;
	// send it to timer led 2
	LS_LED2_setIntensity(LightSystem_led2_timer_value);
	

	// state transition
	p2LightSystem_state = STATE(LightSystem_Idle);
}