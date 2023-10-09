/*
 * SS_algorithm.h
 *
 * Created: 10/6/2023 4:36:41 AM
 *  Author: Ahmed
 */ 


#ifndef SS_ALGORITHM_H_
#define SS_ALGORITHM_H_


#include "state.h"

typedef enum
{
	SS_Idle,
	SS_Busy
	
} e_SS_StateId_t;


extern void (*p2SS_state)(void);


void SS_Init(void);
STATE_fn(SS_Idle);
STATE_fn(SS_Busy);


#endif /* SS_ALGORITHM_H_ */