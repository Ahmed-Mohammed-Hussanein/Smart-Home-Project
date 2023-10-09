/*
 * SS_buzzer.h
 *
 * Created: 10/6/2023 1:14:06 PM
 *  Author: Ahmed
 */ 


#ifndef SS_BUZZER_H_
#define SS_BUZZER_H_


#include "state.h"

typedef enum
{
	BUZZER_Idle,
	BUZZER_Busy
	
} e_Buzzer_StateId_t;


extern void (*p2Buzzer_state)(void);


void Buzzer_Init(void);
STATE_fn(BUZZER_Idle);
STATE_fn(BUZZER_Busy);



#endif /* SS_BUZZER_H_ */