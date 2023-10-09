/*
 * LS_led2.h
 *
 * Created: 10/7/2023 9:43:26 PM
 *  Author: Ahmed
 */ 


#ifndef LS_LED2_H_
#define LS_LED2_H_


#include "state.h"

typedef enum
{
	LS_LED2_Idle,
	LS_LED2_Busy,
	
} e_LS_LED2_StateId_t;


extern void (*p2LS_LED2_state)(void);


void LS_LED2_Init(void);
STATE_fn(LS_LED2_Idle);
STATE_fn(LS_LED2_Busy);



#endif /* LS_LED2_H_ */