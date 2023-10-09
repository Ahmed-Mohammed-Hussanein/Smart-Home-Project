/*
 * atmega32_TIM0_Driver.h
 *
 * Created: 9/27/2023 10:41:26 PM
 *  Author: Ahmed
 */ 


#ifndef ATMEGA32_TIM0_DRIVER_H_
#define ATMEGA32_TIM0_DRIVER_H_

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "Utils.h"

// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

// GPIO pins used for timer0 with 8-bit register.
// output compare match pin OC0  ---> PB3
// external counter input pin T0 ---> PB0

/*

frequency of pin OC in each mode:

Clear Timer on Compare Match (CTC) Mode --> f_OC = f_clk / (2 * prescaler * (1 + OCR))
Fast PWM Mode							--> f_OC = f_clk / (256 * prescaler)
Phase Correct PWM Mode					--> f_OC = f_clk / (510 * prescaler)

*/

typedef struct
{
	uint8_t TIM0_Prescaler;						 /* This specifies the clock of the timer 0.
														This parameter must be a value of @ref TIM0_PRESCALER_define.
														*/
	
	uint8_t TIM0_Mode;								/* This specifies the mode operation of the timer0.
														This parameter must be a value of @ref TIM0_MODE_define.
														*/
	
	uint8_t TIM_OutputCompare;						/* This specifies the output compare mode at the pin of the timer0.
														This parameter must be a value of @ref TIM0_OUT_define.
														*/
	
	uint8_t TIM_INT_Enable;							/* This enables or disables the interrupt of TIM0.
														there is two interrupts: Overflow and Compare match.
														This parameter must be a value of @ref TIM0_INT_ENABLE_define.
														*/
	
}	TIM0_Config_t;

// ===================================================================
// ================== Macros Configuration Reference =================
// ===================================================================

// @ref PRESCALER_define.
#define TIM0_PRESCALER_NOCLOCK							0x0			/*!< No clock source (Timer/Counter stopped) >*/
#define TIM0_PRESCALER_div1								0x1			/*!< clk/1 (No prescaling) >*/
#define TIM0_PRESCALER_div8								0x2			/*!< clk/8 (From prescaler) >*/
#define TIM0_PRESCALER_div64							0x3			/*!< clk/64 (From prescaler) >*/
#define TIM0_PRESCALER_div256							0x4			/*!< clk/256 (From prescaler) >*/
#define TIM0_PRESCALER_div1024							0x5			/*!< clk/1024 (From prescaler) >*/
#define TIM0_PRESCALER_EXTERNAL_CLOCK_FALLING			0x6			/*!< External clock source on T0 pin. Clock on falling edge. >*/
#define TIM0_PRESCALER_EXTERNAL_CLOCK_RISING			0x7			/*!< External clock source on T0 pin. Clock on falling edge. >*/

// @ref TIM0_MODE_define.
#define TIM0_MODE_NORMAL								0x0			/*!< Normal mode >*/
#define TIM0_MODE_PWM_PHASE								0x1			/*!< PWM, Phase Correct >*/
#define TIM0_MODE_CTC									0x2			/*!< Clear Timer on Compare Match >*/
#define TIM0_MODE_PWM_FAST								0x3			/*!< Fast PWM >*/

// @ref TIM0_OUT_define.
// Normal Mode or CTC
#define TIM0_OUT_NORMAL_DISCONNECTED					0x0			/*!< Normal port operation, OC0 disconnected. >*/
#define TIM0_OUT_NORMAL_TOGGLE							0x1			/*!< Toggle OC0 on Compare Match >*/
#define TIM0_OUT_NORMAL_CLEAR							0x2			/*!< Clear OC0 on Compare Match >*/
#define TIM0_OUT_NORMAL_SET								0x3			/*!< Set OC0 on Compare Match >*/

// Fast PWM
#define TIM0_OUT_PWM_FAST_DISCONNECTED					0x0			/*!< Normal port operation, OC0 disconnected. >*/
#define TIM0_OUT_PWM_FAST_NONINV						0x2			/*!< Clear OC0 on Compare Match, set OC0 at BOTTOM, (non-inverting mode) >*/
#define TIM0_OUT_PWM_FAST_INV							0x3			/*!< Set OC0 on Compare Match, clear OC0 at BOTTOM, (inverting mode) >*/

// Phase Correct PWM
#define TIM0_OUT_PWM_PHASE_DISCONNECTED					0x0			/*!< Normal port operation, OC0 disconnected. >*/
#define TIM0_OUT_PWM_PHASE_NONINV						0x2			/*!< Clear OC0 on Compare Match when up-counting. Set OC0 on Compare Match when downcounting. >*/
#define TIM0_OUT_PWM_PHASE_INV							0x3			/*!< Set OC0 on Compare Match when up-counting. Clear OC0 on Compare Match when downcounting. >*/

// @ref TIM0_INT_ENABLE_define.
#define TIM0_INT_ENABLE_NONE							0x0			/*!< Disable all interrupts >*/
#define TIM0_INT_ENABLE_OVERFLOW						0x1			/*!< Enable Overflow interrupt >*/
#define TIM0_INT_ENABLE_COMPARE_MATCH					0x2			/*!< Enable Compare Match interrupt >*/
#define TIM0_INT_ENABLE_ALL								0x3			/*!< Enable ALL interrupts >*/

// ===================================================
// ================== APIs Functions =================
// ===================================================
void MCAL_TIM0_Init(TIM0_Config_t *config);
void MCAL_TIM0_DeInit(void);

void MCAL_TIM0_GPIO_setPins(void);

void MCAL_TIM0_start(void);
void MCAL_TIM0_stop(void);

long long	MCAL_TIM0_getTime_ms(void);
void		MCAL_TIM0_delay_ms(long long ms);
void		MCAL_TIM0_delay_us(uint8_t us);

void	MCAL_TIM0_setCompareValue(uint8_t value);
uint8_t MCAL_TIM0_getCompareValue(void);

void	MCAL_TIM0_setCounterValue(uint8_t value);
uint8_t MCAL_TIM0_getCounterValue(void);

void MCAL_TIM0_PWM(uint8_t dutyCycle);

// Callback functions
void MCAL_TIM0_CompareMatch_IRQHandle(void);
void MCAL_TIM0_OverFlow_IRQHandle(void);

#endif /* ATMEGA32_TIM0_DRIVER_H_ */