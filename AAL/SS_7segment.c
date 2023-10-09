/*
 * SS_7segment.c
 *
 * Created: 10/6/2023 1:00:11 PM
 *  Author: Ahmed
 */ 

#include "Platform_Types.h"

#include "seven_seg.h"
#include "SS_7segment.h"

static sint8_t SEG_value	= 0;
void (*p2SEG_state)(void);

e_SEG_StateId_t SEG_state;

void SEG_getVal(sint8_t newValue)
{
	SEG_value = newValue;
	p2SEG_state = STATE(SEG_Busy);
}

void SEG_Init(void)
{
	// state name
	SEG_state = SEG_Idle;

	// state init
	HAL_7seg_Init();
	HAL_7seg_writeVal(0);

	// state transition
	p2SEG_state = STATE(SEG_Idle);
}


STATE_fn(SEG_Idle)
{
	// state name
	SEG_state = SEG_Idle;

	// state action
	

	// state transition
	p2SEG_state = STATE(SEG_Idle);
}

STATE_fn(SEG_Busy)
{
	// state name
	SEG_state = SEG_Busy;

	// state action
	HAL_7seg_writeVal(SEG_value);

	// state transition
	p2SEG_state = STATE(SEG_Idle);
}