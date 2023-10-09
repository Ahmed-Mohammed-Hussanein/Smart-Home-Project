/*
 * atmega32_ADC_Driver.h
 *
 * Created: 9/28/2023 1:35:30 AM
 *  Author: Ahmed
 */ 


#ifndef ATMEGA32_ADC_DRIVER_H_
#define ATMEGA32_ADC_DRIVER_H_

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "atmega32_BitField.h"

// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

typedef struct
{
	uint8_t ADC_VREF;							/* This specifies voltage reference for ADC.
												This parameter must be a value of @ref ADC_VREF_define.
												*/
	
	uint8_t ADC_preScaler;						 /* This specifies the clock input to ADC.
													This parameter must be a value of @ref ADC_preScaler_define.
													*/
	
	uint8_t ADC_INT;							/* This enables or disables the interrupt of ADC.
													there is one interrupt: ADC end of conversion.
													This parameter must be a value of @ref ADC_INT_define.
													*/
	
} ADC_Config_t;

// This Selects which channel is connected to ADC.
typedef enum
{
	ADC_CH0 = 0,	// PA0
	ADC_CH1,		// PA1
	ADC_CH2,		// PA2
	ADC_CH3,		// PA3
	ADC_CH4,		// PA4
	ADC_CH5,		// PA5
	ADC_CH6,		// PA6
	ADC_CH7			// PA7
	
} eADC_channelSelection_t;

// ===================================================================
// ================== Macros Configuration Reference =================
// ===================================================================

// @ref ADC_VREF_define.
#define ADC_VREF_AREF						0x0					/*	AREF, Internal Vref turned off. */
#define ADC_VREF_AVCC						0x1					/*	AVCC with external capacitor at AREF pin. */
#define ADC_VREF_internal					0x3					/*	Internal 2.56V Voltage Reference with external capacitor at AREF pin. */

// @ref ADC_preScaler_define.						
// XTAL clock / ADC_preScaler
#define ADC_preScaler_div2					0x1
#define ADC_preScaler_div4					0x2
#define ADC_preScaler_div8					0x3
#define ADC_preScaler_div16					0x4
#define ADC_preScaler_div32					0x5
#define ADC_preScaler_div64					0x6
#define ADC_preScaler_div128				0x7

// @ref ADC_INT_define.
#define ADC_INT_DISABLE						0x0
#define ADC_INT_ENABLE						0x1

// ===================================================
// ================== APIs Functions =================
// ===================================================
void MCAL_ADC_Init(ADC_Config_t *config);
void MCAL_ADC_DeInit(void);

void MCAL_ADC_start(void);
void MCAL_ADC_stop(void);

uint16_t MCAL_ADC_convert(eADC_channelSelection_t ADC_CH);

void MCAL_ADC_setChannel(eADC_channelSelection_t ADC_CH);
void MCAL_ADC_startConversion(void);
void MCAL_ADC_waitForEndOfConversion(void);
uint16_t MCAL_ADC_Read(void);

// Callback functions
void MCAL_ADC_IRQHandle(void);

#endif /* ATMEGA32_ADC_DRIVER_H_ */