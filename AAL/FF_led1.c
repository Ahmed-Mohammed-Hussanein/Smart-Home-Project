/*
 * FF_led1.c
 *
 * Created: 10/7/2023 3:56:58 PM
 *  Author: Ahmed
 */ 

#include "Platform_Types.h"

#include "atmega32_GPIO_Driver.h"

#include "FF_led1.h"


void (*p2LED1_state)(void);

e_LED1_StateId_t LED1_state;


void turn_led1_on(uint8_t led_emergency)
{
	// state transition
	if (led_emergency == 1)
	{
		STATE(LED1_TurnOn)();
	}
	else
	{
		p2LED1_state = STATE(LED1_TurnOn);
	}
}

void turn_led1_off(void)
{
	// state transition
	p2LED1_state = STATE(LED1_TurnOff);
}

void LED1_Init(void)
{
	// state name
	LED1_state = LED1_TurnOff;

	// state init
	GPIO_PinConfig_t led1_pin = {GPIO_PIN_6, GPIO_MODE_OUTPUT};
	MCAL_GPIO_Init(GPIOA, &led1_pin);

	// state transition
	p2LED1_state = STATE(LED1_TurnOff);
}


STATE_fn(LED1_TurnOff)
{
	// state name
	LED1_state = LED1_TurnOff;

	// state action
	MCAL_GPIO_writePin(GPIOA, GPIO_PIN_6, GPIO_STATE_LOW);

	// state transition
	p2LED1_state = STATE(LED1_TurnOff);
}

STATE_fn(LED1_TurnOn)
{
	// state name
	LED1_state = LED1_TurnOn;

	// state action
	MCAL_GPIO_writePin(GPIOA, GPIO_PIN_6, GPIO_STATE_HIGH);

	// state transition
	p2LED1_state = STATE(LED1_TurnOn);
}
