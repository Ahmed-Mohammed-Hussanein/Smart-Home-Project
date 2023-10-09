/*
 * ADC_Interface.h
 *
 * Created: 10/7/2023 7:48:00 PM
 *  Author: Ahmed
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#include "state.h"

typedef enum
{
	ADC_Idle,
	ADC_calTemp,
	ADC_calResVal
	
} e_ADC_StateId_t;


extern void (*p2ADC_state)(void);


void ADC_Init(void);
STATE_fn(ADC_Idle);
STATE_fn(ADC_calTemp);
STATE_fn(ADC_calResVal);


#endif /* ADC_INTERFACE_H_ */