/*
 * FF_led1.h
 *
 * Created: 10/7/2023 3:56:47 PM
 *  Author: Ahmed
 */ 


#ifndef FF_LED1_H_
#define FF_LED1_H_

#include "state.h"

typedef enum
{
	LED1_TurnOff,
	LED1_TurnOn,
	
} e_LED1_StateId_t;


extern void (*p2LED1_state)(void);


void LED1_Init(void);
STATE_fn(LED1_TurnOff);
STATE_fn(LED1_TurnOn);



#endif /* FF_LED1_H_ */