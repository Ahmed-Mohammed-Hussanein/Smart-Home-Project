/*
 * LS_algorithm.h
 *
 * Created: 10/7/2023 9:33:10 PM
 *  Author: Ahmed
 */ 


#ifndef LS_ALGORITHM_H_
#define LS_ALGORITHM_H_


#include "state.h"

typedef enum
{
	LightSystem_Idle,
	LightSystem_Busy,
	
} e_LightSystem_StateId_t;


extern void (*p2LightSystem_state)(void);


void LightSystem_Init(void);
STATE_fn(LightSystem_Idle);
STATE_fn(LightSystem_Busy);




#endif /* LS_ALGORITHM_H_ */