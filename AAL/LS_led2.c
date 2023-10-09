/*
 * LS_led2.c
 *
 * Created: 10/7/2023 9:43:40 PM
 *  Author: Ahmed
 */ 

#include "Platform_Types.h"

#include "atmega32_GPIO_Driver.h"
#include "atmega32_TIM0_Driver.h"
#include "LS_led2.h"


static uint8_t LS_LED2_oldIntensity				= 0;
static uint8_t LS_LED2_newIntensity				= 0;
void (*p2LS_LED2_state)(void);

e_LS_LED2_StateId_t LS_LED2_state;

void LS_LED2_setIntensity(uint8_t led_intensity)
{
	if (led_intensity != LS_LED2_oldIntensity)
	{
		LS_LED2_newIntensity = led_intensity;
		p2LS_LED2_state = STATE(LS_LED2_Busy);
	}
}


void LS_LED2_Init(void)
{
	// state name
	LS_LED2_state = LS_LED2_Idle;

	// state init
	GPIO_PinConfig_t led2_pin =  {GPIO_PIN_6, GPIO_MODE_OUTPUT};
	MCAL_GPIO_Init(GPIOD, &led2_pin);
	
	TIM0_Config_t led2_timer = {TIM0_PRESCALER_div1024, TIM0_MODE_NORMAL, TIM0_OUT_NORMAL_DISCONNECTED, TIM0_INT_ENABLE_ALL};
	MCAL_TIM0_Init(&led2_timer);
	MCAL_TIM0_start();

	// state transition
	p2LS_LED2_state = STATE(LS_LED2_Idle);
}


STATE_fn(LS_LED2_Idle)
{
	// state name
	LS_LED2_state = LS_LED2_Idle;

	// state action
	

	// state transition
	p2LS_LED2_state = STATE(LS_LED2_Idle);
}

STATE_fn(LS_LED2_Busy)
{
	// state name
	LS_LED2_state = LS_LED2_Busy;

	// state action
	// set pwm value
	MCAL_TIM0_setCompareValue(LS_LED2_newIntensity);
	LS_LED2_oldIntensity = LS_LED2_newIntensity;

	// state transition
	p2LS_LED2_state = STATE(LS_LED2_Idle);
}

void MCAL_TIM0_CompareMatch_IRQHandle(void)
{
	MCAL_GPIO_writePin(GPIOD, GPIO_PIN_6, GPIO_STATE_HIGH);
}

void MCAL_TIM0_OverFlow_IRQHandle(void)
{
	MCAL_GPIO_writePin(GPIOD, GPIO_PIN_6, GPIO_STATE_LOW);
}