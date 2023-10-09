/*
 * FF_algorithm.c
 *
 * Created: 10/7/2023 2:15:11 PM
 *  Author: Ahmed
 */ 


#define F_CPU			1000000UL
#include <util/delay.h>

#include "Platform_Types.h"

#include "atmega32_ADC_Driver.h"
#include "LM35.h"

#include "CS_receiver.h"
#include "FF_alogrithm.h"



static sint8_t temp_value		= 0;
static sint8_t temp_threshold	= 60;
void (*p2FF_state)(void);

e_FF_StateId_t FF_state;

void FF_setTempValue(sint8_t tVal)
{
	temp_value = tVal;
	p2FF_state = STATE(FF_Check);
}


void FF_Init(void)
{
	// state name
	FF_state = FF_Idle;

	// state init
	//ADC_Config_t adc_init = {ADC_VREF_AREF, ADC_preScaler_div128, ADC_INT_ENABLE};
	//MCAL_ADC_Init(&adc_init);
	//
	//LM35_Config_t lm = {5, LM35_CH_5};
	//HAL_LM35_Init(&lm);
	//
	//MCAL_ADC_start();
	//MCAL_ADC_setChannel(ADC_CH5);
	//MCAL_ADC_startConversion();
	

	// state transition
	p2FF_state = STATE(FF_Idle);
}


STATE_fn(FF_Idle)
{
	// state name
	FF_state = FF_Idle;

	// state action
	

	// state transition
	p2FF_state = STATE(FF_Idle);
}

STATE_fn(FF_Check)
{
	// state name
	FF_state = FF_Check;

	// state action
	

	// state transition
	p2FF_state = temp_value < temp_threshold ? STATE(FF_NonBlocking) : STATE(FF_Blocking);
}

STATE_fn(FF_NonBlocking)
{
	// state name
	FF_state = FF_NonBlocking;

	// state action
	turn_led1_off();
	lcd_get_temp(temp_value, 0);

	// state transition
	p2FF_state = STATE(FF_Idle);
}

STATE_fn(FF_Blocking)
{
	// state name
	FF_state = FF_Blocking;

	// state action
	turn_led1_on(1);
	lcd_get_temp(temp_value, 1);
	STATE(CS_Rx_Stopped)();
	
	while (temp_value >= temp_threshold)
	{
		lcd_get_temp(temp_value, 1);
		_delay_ms(50);
	}
	STATE(CS_Rx_Check)();
	

	// state transition
	p2FF_state = STATE(FF_NonBlocking);
}

//void MCAL_ADC_IRQHandle(void)
//{
	//temp_value = HAL_LM35_tempInCelsius(INTERRUPT);
	//p2FF_state = STATE(FF_Check);
	//MCAL_ADC_startConversion();
//}