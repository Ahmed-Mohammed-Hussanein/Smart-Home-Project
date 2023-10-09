/*
 * atmega32_TIM0_Driver.c
 *
 * Created: 9/27/2023 10:41:46 PM
 *  Author: Ahmed
 */ 

// =============================================
// ================== Includes =================
// =============================================

#include "Utils.h"
#include "Platform_Types.h"

#include "atmega32_BitField.h"
#include "atmega32_device_header.h"
#include "atmega32_peripheral_pins.h"

#include "atmega32_GPIO_Driver.h"
#include "atmega32_TIM0_Driver.h"

#include <avr/interrupt.h>

/*
 * =====================================================================================
 * ================================= Generic Variables =================================
 * =====================================================================================
 */

uint8_t timer_prescaler;
uint8_t PWM_mode;

/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

/**================================================================
* @Fn				- MCAL_TIM0_Init
* @brief			- This is used to configure and initialize Timer0.
* @param [in] 		- config: This is the configuration for Timer0.
* @retval 			- None.
* Note				- None.
*/
void MCAL_TIM0_Init(TIM0_Config_t *config)
{
	
	
	
	/* set prescaler of the Timer.
	
		  CS02 CS01 CS00
			 0	  0    0	--> No clock source (Timer/Counter stopped).
			 0	  0	   1	--> clkI/O/1 (No prescaling)
			 0	  1	   0	--> clkI/O/8 (From prescaler).
			 0    1    1	--> clkI/O/64 (From prescaler).
			 1    0    0	--> clkI/O/256 (From prescaler).
			 1    0    1	--> clkI/O/1024 (From prescaler).
			 1    1    0	-->	External clock source on T0 pin. Clock on falling edge.
			 1    1    1	--> External clock source on T0 pin. Clock on falling edge.
	
	*/
	timer_prescaler = config->TIM0_Prescaler;
	//WRITE_MASK(TIM0->_TCCR0, TIM0_TCCR0_CS0n_Mask, timer_prescaler << TIM0_TCCR0_CS0n_Pos);
	
	/* Wave Generation Mode of the Timer.
	
				 WGM01  WGM00
				 (CTC0) (PWM0)
			 	  0      0		--> Normal 
			 	  0	     1		--> PWM, phase correct
			      1	     0		--> CTC
			      1      1		--> fast PWM
	
	*/
	WRITE_MASK(TIM0->_TCCR0, TIM0_TCCR0_WGM00_Mask | TIM0_TCCR0_WGM01_Mask,
	 ((config->TIM0_Mode & 1) << TIM0_TCCR0_WGM00_Pos) | ((config->TIM0_Mode >> 1) << TIM0_TCCR0_WGM01_Pos));
	 
	
	/* Compare Output Mode of the Timer.
		Non-PWM
				 COM01  COM00
			 	  0      0		--> Normal port operation, OC0 disconnected.
			 	  0	     1		--> Toggle OC0 on Compare Match.
			      1	     0		--> Clear OC0 on Compare Match.
			      1      1		--> Set OC0 on Compare Match.
				  
		Fast PWM
				COM01  COM00
				  0      0		--> Normal port operation, OC0 disconnected.
				  0	     1		--> Reserved.
				  1	     0		--> Clear OC0 on Compare Match, set OC0 at BOTTOM, (non-inverting mode).
				  1      1		--> Set OC0 on Compare Match, clear OC0 at BOTTOM, (inverting mode).
				  
		Phase Correct PWM
				COM01  COM00
				  0      0		--> Normal port operation, OC0 disconnected.
				  0	     1		--> Reserved.
				  1	     0		--> Clear OC0 on Compare Match when up-counting. Set OC0 on Compare Match when down-counting.
				  1      1		--> Set OC0 on Compare Match when up-counting. Clear OC0 on Compare Match when down-counting.
	
	*/
	PWM_mode = config->TIM_OutputCompare;
	WRITE_MASK(TIM0->_TCCR0, TIM0_TCCR0_COM0n_Mask, config->TIM_OutputCompare << TIM0_TCCR0_COM0n_Pos);
	
	/* initialize the interrupts */
	WRITE_MASK(INT->_TIMSK, TIMSK_TOV0_Mask | TIMSK_OCF0_Mask, config->TIM_INT_Enable);
	if (config->TIM_INT_Enable != TIM0_INT_ENABLE_NONE)
	{
		Enable_Global_INT();
	}
}

/**================================================================
* @Fn				- MCAL_TIM0_DeInit
* @brief			- This is used to reset Timer0.
* @param [in] 		- None.
* @retval 			- None.
* Note				- None.
*/
void MCAL_TIM0_DeInit(void)
{
	TIM0->_TCCR0 = 0x00;
	TIM0->_OCR0  = 0x00;
	TIM0->_TCNT0 = 0x00;
}

/**================================================================
* @Fn				- MCAL_TIM0_GPIO_setPins
* @brief			- This is used to initialize GPIO pins for timer 0 if it is not working in normal mode.
* @param [in] 		- None.
* @retval 			- None.
* Note				- None.
*/
void MCAL_TIM0_GPIO_setPins(void)
{
	GPIO_PinConfig_t tim0_pin;
	
	if (timer_prescaler == TIM0_PRESCALER_EXTERNAL_CLOCK_FALLING || timer_prescaler == TIM0_PRESCALER_EXTERNAL_CLOCK_RISING)
	{
		tim0_pin.GPIO_PinNumber = TIM0_T0_pin;
		tim0_pin.GPIO_PinMode	= GPIO_MODE_INPUT;
		MCAL_GPIO_Init(TIM0_PORT, &tim0_pin);
	}
	else if(READ_MASK(TIM0->_TCCR0, TIM0_TCCR0_WGM00_Mask | TIM0_TCCR0_WGM01_Mask) != TIM0_MODE_NORMAL 
	&& READ_MASK(TIM0->_TCCR0, TIM0_TCCR0_COM0n_Mask) != TIM0_OUT_NORMAL_DISCONNECTED)
	{
		tim0_pin.GPIO_PinNumber = TIM0_OC0_pin;
		tim0_pin.GPIO_PinMode	= GPIO_MODE_OUTPUT;
		MCAL_GPIO_Init(TIM0_PORT, &tim0_pin);
	}
}

/**================================================================
* @Fn				- MCAL_TIM0_start
* @brief			- This is used to start timer 0 to work.
* @param [in] 		- None.
* @retval 			- None.
* Note				- None.
*/
__inline void MCAL_TIM0_start(void)
{
	WRITE_MASK(TIM0->_TCCR0, TIM0_TCCR0_CS0n_Mask, timer_prescaler << TIM0_TCCR0_CS0n_Pos);
}

/**================================================================
* @Fn				- MCAL_TIM0_stop
* @brief			- This is used to stop timer 0 to work.
* @param [in] 		- None.
* @retval 			- None.
* Note				- None.
*/
__inline void MCAL_TIM0_stop(void)
{
	CLEAR_MASK(TIM0->_TCCR0, TIM0_TCCR0_CS0n);
}

long long	MCAL_TIM0_getTime_ms(void);
void		MCAL_TIM0_delay_ms(long long ms);
void		MCAL_TIM0_delay_us(uint8_t us);


void	MCAL_TIM0_setCompareValue(uint8_t value)
{
	TIM0->_OCR0	=	value;
}

uint8_t MCAL_TIM0_getCompareValue(void)
{
	return TIM0->_OCR0;
}

void	MCAL_TIM0_setCounterValue(uint8_t value)
{
	TIM0->_TCNT0	=	value;
}

uint8_t MCAL_TIM0_getCounterValue(void)
{
	return TIM0->_TCNT0;
}

void MCAL_TIM0_PWM(uint8_t dutyCycle)
{
	uint8_t compareValue = (dutyCycle * 255) / 100;
	
	switch (PWM_mode)
	{
		case TIM0_OUT_PWM_FAST_NONINV:
		MCAL_TIM0_setCompareValue(compareValue);
		break;
		
		case TIM0_OUT_PWM_FAST_INV:
		MCAL_TIM0_setCompareValue(256 - compareValue);
		break;
	}
}

/*
 * =====================================================================================
 * ================================= ISR  ==============================================
 * =====================================================================================
 */

ISR(TIMER0_COMP_vect)
{
	MCAL_TIM0_CompareMatch_IRQHandle();
}

ISR(TIMER0_OVF_vect)
{
	MCAL_TIM0_OverFlow_IRQHandle();
}

/*
 * =====================================================================================
 * ================================= CALLBACK Functions ================================
 * =====================================================================================
 */

__attribute__((weak)) void MCAL_TIM0_CompareMatch_IRQHandle(void)
{
	while(1);
}

__attribute__((weak)) void MCAL_TIM0_OverFlow_IRQHandle(void)
{
	while(1);
}