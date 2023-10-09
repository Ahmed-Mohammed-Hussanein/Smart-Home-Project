/*
 * FF_alogrithm.h
 *
 * Created: 10/7/2023 2:14:53 PM
 *  Author: Ahmed
 */ 


#ifndef FF_ALOGRITHM_H_
#define FF_ALOGRITHM_H_

#include "state.h"

typedef enum
{
	FF_Idle,
	FF_Check,
	FF_Blocking,
	FF_NonBlocking
	
} e_FF_StateId_t;


extern void (*p2FF_state)(void);


void FF_Init(void);
STATE_fn(FF_Idle);
STATE_fn(FF_Check);
STATE_fn(FF_Blocking);
STATE_fn(FF_NonBlocking);




#endif /* FF_ALOGRITHM_H_ */