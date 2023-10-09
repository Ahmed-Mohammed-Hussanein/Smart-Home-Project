/*
 * SS_7segment.h
 *
 * Created: 10/6/2023 12:59:56 PM
 *  Author: Ahmed
 */ 


#ifndef SS_7SEGMENT_H_
#define SS_7SEGMENT_H_


#include "state.h"

typedef enum
{
	SEG_Idle,
	SEG_Busy
	
} e_SEG_StateId_t;


extern void (*p2SEG_state)(void);


void SEG_Init(void);
STATE_fn(SEG_Idle);
STATE_fn(SEG_Busy);


#endif /* SS_7SEGMENT_H_ */