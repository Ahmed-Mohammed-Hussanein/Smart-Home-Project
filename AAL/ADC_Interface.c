/*
 * ADC_Interface.c
 *
 * Created: 10/7/2023 7:48:15 PM
 *  Author: Ahmed
 */ 

#include "Platform_Types.h"

#include "atmega32_ADC_Driver.h"
#include "LM35.h"

#include "ADC_Interface.h"



static sint8_t adc_temp_value		= 0;
static uint16_t adc_res_value		= 0;
static uint8_t flag					= 0;
void (*p2ADC_state)(void);

e_ADC_StateId_t ADC_state;


void ADC_Init(void)
{
	// state name
	ADC_state = ADC_Idle;

	// state init
	ADC_Config_t adc_init = {ADC_VREF_AREF, ADC_preScaler_div128, ADC_INT_ENABLE};
	MCAL_ADC_Init(&adc_init);
	
	LM35_Config_t lm = {5, LM35_CH_5};
	HAL_LM35_Init(&lm);
	
	MCAL_ADC_start();
	MCAL_ADC_setChannel(ADC_CH5);
	MCAL_ADC_startConversion();
	

	// state transition
	p2ADC_state = STATE(ADC_Idle);
}


STATE_fn(ADC_Idle)
{
	// state name
	ADC_state = ADC_Idle;

	// state action
	

	// state transition
	p2ADC_state = STATE(ADC_Idle);
}

STATE_fn(ADC_calTemp)
{
	// state name
	ADC_state = ADC_calTemp;

	// state action
	FF_setTempValue(adc_temp_value);
	MCAL_ADC_setChannel(ADC_CH7);
	flag = 1;
	MCAL_ADC_startConversion();

	// state transition
	p2ADC_state = STATE(ADC_Idle);
}

STATE_fn(ADC_calResVal)
{
	// state name
	ADC_state = ADC_calResVal;

	// state action
	LS_setResValue(adc_res_value);
	MCAL_ADC_setChannel(ADC_CH5);
	flag = 0;
	MCAL_ADC_startConversion();
	
	// state transition
	p2ADC_state = STATE(ADC_Idle);
}

void MCAL_ADC_IRQHandle(void)
{
	if (flag == 0)
	{
		adc_temp_value = HAL_LM35_tempInCelsius(INTERRUPT);
		STATE(ADC_calTemp)();
	}
	else
	{
		adc_res_value = MCAL_ADC_Read();
		STATE(ADC_calResVal)();
	}
}