/*
 * SS_buzzer.c
 *
 * Created: 10/6/2023 1:14:18 PM
 *  Author: Ahmed
 */ 

#define F_CPU		1000000UL

#include <util/delay.h>

#include "Platform_Types.h"

#include "atmega32_GPIO_Driver.h"
#include "buzzer.h"
#include "SS_buzzer.h"

void (*p2Buzzer_state)(void);

e_Buzzer_StateId_t Buzzer_state;

void buzzer_turnOn(void)
{
	p2Buzzer_state = STATE(BUZZER_Busy);
}


void Buzzer_Init(void)
{
	// state name
	Buzzer_state = BUZZER_Idle;

	// state init
	// turn off buzzer
	GPIO_PinConfig_t buzzer_pin = {GPIO_PIN_4, GPIO_MODE_OUTPUT};
	HAL_buzzer_Init(GPIOA, &buzzer_pin);
	HAL_buzzer_turnOff(GPIOA, GPIO_PIN_4);

	// state transition
	p2Buzzer_state = STATE(BUZZER_Idle);
}


STATE_fn(BUZZER_Idle)
{
	// state name
	Buzzer_state = BUZZER_Idle;

	// state action
	

	// state transition
	p2Buzzer_state = STATE(BUZZER_Idle);
}

STATE_fn(BUZZER_Busy)
{
	// state name
	Buzzer_state = BUZZER_Busy;

	// state action
	HAL_buzzer_turnOn(GPIOA, GPIO_PIN_4);
	_delay_ms(50);
	HAL_buzzer_turnOff(GPIOA, GPIO_PIN_4);

	// state transition
	p2Buzzer_state = STATE(BUZZER_Idle);
}