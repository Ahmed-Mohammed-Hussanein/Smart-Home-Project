/*
 * SS_algorithm.c
 *
 * Created: 10/6/2023 4:37:16 AM
 *  Author: Ahmed
 */ 

#include "Platform_Types.h"

#include "SS_algorithm.h"


static sint8_t SS_PB_state		= 0;
static sint8_t SS_7seg_max		= 9;
static sint8_t SS_7seg_min		= 0;
static sint8_t SS_7seg_value	= 0;
void (*p2SS_state)(void);

e_SS_StateId_t SS_state;

void SS_receive_PB_state(sint8_t state)
{
	SS_PB_state = state;
}

void SS_Init(void)
{
	// state name
	SS_state = SS_Idle;

	// state init
	SEG_getVal(0);
	

	// state transition
	p2SS_state = STATE(SS_Idle);
}


STATE_fn(SS_Idle)
{
	// state name
	SS_state = SS_Idle;

	// state action
	

	// state transition
	p2SS_state = (SS_PB_state == 0) ? STATE(SS_Idle) : STATE(SS_Busy);
}

STATE_fn(SS_Busy)
{
	// state name
	SS_state = SS_Busy;

	// state action
	SS_7seg_value += SS_PB_state;
	if (SS_7seg_value > SS_7seg_max)
	{
		SS_7seg_value = SS_7seg_max;
		
		// turn on the buzzer
		buzzer_turnOn();
	}
	else if (SS_7seg_value < SS_7seg_min)
	{
		SS_7seg_value = SS_7seg_min;
		
		// turn on the buzzer
		buzzer_turnOn();
	}
	
	// write this value to seven segment
	SEG_getVal(SS_7seg_value);
	SS_PB_state = 0;

	// state transition
	p2SS_state = STATE(SS_Idle);
}