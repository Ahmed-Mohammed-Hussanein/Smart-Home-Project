/*
 * LM35.h
 *
 * Created: 10/31/2022 2:16:22 PM
 *  Author: Ahmed
 */ 


#ifndef LM35_H_
#define LM35_H_

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "atmega32_ADC_Driver.h"

// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

typedef struct
{	
	uint8_t LM35_Vref;				/* This specifies the reference voltage to ADC.
									*/
	
	uint8_t LM35_CH;				/* This specifies the channel of ADC connected to LM35.
										This parameter must be a value of @ref LM35_CH_define.
										*/

} LM35_Config_t;


// ===================================================================
// ================== Macros Configuration Reference =================
// ===================================================================

// @ref LM35_CH_define
#define LM35_CH_0					ADC_CH0
#define LM35_CH_1					ADC_CH1
#define LM35_CH_2					ADC_CH2
#define LM35_CH_3					ADC_CH3
#define LM35_CH_4					ADC_CH4
#define LM35_CH_5					ADC_CH5
#define LM35_CH_6					ADC_CH6
#define LM35_CH_7					ADC_CH7


typedef enum
{
	POLLING = 0,
	INTERRUPT = !POLLING
	
} eLM35_readMechanism_t;

// ===================================================
// ================== APIs Functions =================
// ===================================================

void HAL_LM35_Init(LM35_Config_t *config);

uint8_t HAL_LM35_tempInCelsius(eLM35_readMechanism_t pollEnable);
uint8_t HAL_LM35_tempInFahrenheit(void);

#endif /* LM35_H_ */