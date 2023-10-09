/*
 * atmega32_ADC_Driver.c
 *
 * Created: 9/28/2023 1:35:46 AM
 *  Author: Ahmed
 */ 

// =============================================
// ================== Includes =================
// =============================================

#include "Utils.h"
#include "Platform_Types.h"

#include "atmega32_device_header.h"
#include "atmega32_BitField.h"
#include "atmega32_ADC_Driver.h"

#include <avr/interrupt.h>

/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

/**================================================================
* @Fn				- MCAL_ADC_Init
* @brief			- This is used to configure and initialize ADC.
* @param [in] 		- config: This is the configuration for ADC.
* @retval 			- None.
* Note				- None.
*/

void MCAL_ADC_Init(ADC_Config_t *config)
{
	/*  Reference Selection
	
		REFSn
		00		-->	AREF, Internal Vref turned off.
		01		-->	AVCC with external capacitor at AREF pin.
		10		-->	Reserved.
		11		-->	Internal 2.56V Voltage Reference with external capacitor at AREF pin.
	*/
	WRITE_MASK(_ADC->_ADMUX, ADC_ADMUX_REFSn_Mask, config->ADC_VREF << ADC_ADMUX_REFSn_Pos);
	
	/*  Prescaler
	
		ADPSn
		000			-->	division by 2.
		001			-->	division by 2.
		010			-->	division by 4.
		011			-->	division by 8.
		100			-->	division by 16.
		101			-->	division by 32.
		110			-->	division by 64.
		111			-->	division by 128.
	*/
	WRITE_MASK(_ADC->_ADCSRA, ADC_ADCSRA_ADPSn_Mask, config->ADC_preScaler);
	
	/* Initialize the interrupt */
	WRITE_MASK(_ADC->_ADCSRA, ADC_ADCSRA_ADIE_Mask, config->ADC_INT << ADC_ADCSRA_ADIE_Pos);
	if (config->ADC_INT == ADC_INT_ENABLE)
	{
		Enable_Global_INT();
	}
}

/**================================================================
* @Fn				- MCAL_ADC_DeInit
* @brief			- This is used to reset ADC.
* @param [in] 		- None.
* @retval 			- None.
* Note				- None.
*/
void MCAL_ADC_DeInit(void)
{
	_ADC->_ADMUX = 0x00;
	_ADC->_ADCSRA  = 0x00;
}

/**================================================================
* @Fn				- MCAL_ADC_start
* @brief			- This is used to start ADC to work.
* @param [in] 		- None.
* @retval 			- None.
* Note				- None.
*/
void MCAL_ADC_start(void)
{
	SET_MASK(_ADC->_ADCSRA, ADC_ADCSRA_ADEN);
}

/**================================================================
* @Fn				- MCAL_ADC_stop
* @brief			- This is used to stop ADC to work.
* @param [in] 		- None.
* @retval 			- None.
* Note				- None.
*/
void MCAL_ADC_stop(void)
{
	CLEAR_MASK(_ADC->_ADCSRA, ADC_ADCSRA_ADEN);
}


uint16_t MCAL_ADC_convert(eADC_channelSelection_t ADC_CH)
{
	// set channel
	MCAL_ADC_setChannel(ADC_CH);
	
	// start conversion
	MCAL_ADC_startConversion();
	
	// wait for end of conversion
	MCAL_ADC_waitForEndOfConversion();
	
	// return the result
	return MCAL_ADC_Read();
}

void MCAL_ADC_setChannel(eADC_channelSelection_t ADC_CH)
{
	/*  Channel Selection --> Port A
	
		MUXn
						Single Ended
		00000			-->	ADC0.
		00001			-->	ADC1.
		00010			-->	ADC2.
		00011			-->	ADC3.
		00100			-->	ADC4.
		00101			-->	ADC5.
		00110			-->	ADC6.
		00111			-->	ADC7.
	*/
	WRITE_MASK(_ADC->_ADMUX, ADC_ADMUX_MUXn_Mask, ADC_CH);
}

void MCAL_ADC_startConversion(void)
{
	// Start of Conversion by writing 1 to ADSC.
	SET_MASK(_ADC->_ADCSRA, ADC_ADCSRA_ADSC);
}

void MCAL_ADC_waitForEndOfConversion(void)
{
	// wait for the end of conversion.
	while(!READ_MASK(_ADC->_ADCSRA, ADC_ADCSRA_ADIF));
	SET_MASK(_ADC->_ADCSRA, ADC_ADCSRA_ADIF);
}

uint16_t MCAL_ADC_Read(void)
{
	return (_ADC->_ADCL | (_ADC->_ADCH << 8));
}


/*
 * =====================================================================================
 * ================================= ISR  ==============================================
 * =====================================================================================
 */

ISR(ADC_vect)
{
	MCAL_ADC_IRQHandle();
}

/*
 * =====================================================================================
 * ================================= CALLBACK Functions ================================
 * =====================================================================================
 */

__attribute__((weak)) void MCAL_ADC_IRQHandle(void)
{
	while(1);
}