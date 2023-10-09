/*
 * SS_pushButtons.h
 *
 * Created: 10/6/2023 4:13:48 AM
 *  Author: Ahmed
 */ 


#ifndef SS_PUSHBUTTONS_H_
#define SS_PUSHBUTTONS_H_


#include "state.h"

typedef enum
{
	SS_PB_Idle,
	SS_PB_Check
	
} e_SS_PB_StateId_t;


extern void (*p2SS_PB_state)(void);


void SS_PB_Init(void);
STATE_fn(SS_PB_Idle);
STATE_fn(SS_PB_Check);


#endif /* SS_PUSHBUTTONS_H_ */