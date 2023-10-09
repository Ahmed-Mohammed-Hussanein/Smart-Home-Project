/*
 * LM35.c
 *
 * Created: 10/31/2022 2:16:35 PM
 *  Author: Ahmed
 */ 

// =============================================
// ================== Includes =================
// =============================================

#include "Utils.h"
#include "Platform_Types.h"
#include "LM35.h"

/*
 * ===========================================================================
 * ================================= Generic Macros ==========================
 * ===========================================================================
 */

/*
 * ==============================================================================
 * ================================= Generic Variables ==========================
 * ==============================================================================
 */

uint8_t gLM35_Vref;
uint8_t gLM35_CH;

/*
 * ========================================================================================
 * ================================= Generic Function Definition ==========================
 * ========================================================================================
 */


/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

/**================================================================
* @Fn				- HAL_LM35_Init
* @brief			- This is used to initialize LM35 Temperature Sensor.
* @param [in] 		- LM35_Config: This is used to configure the LM35 Temperature Sensor.
* @retval 			- None.
* Note				- None.
*/
void HAL_LM35_Init(LM35_Config_t *config)
{
	gLM35_Vref = config->LM35_Vref;
	
	gLM35_CH   = config->LM35_CH;
}

/**================================================================
* @Fn				- HAL_LM35_tempInCelsius
* @brief			- This is used to get the temperature in celsius.
* @retval 			- None.
* Note				- None.
*/

uint8_t HAL_LM35_tempInCelsius(eLM35_readMechanism_t pollEnable)
{
	uint16_t ADC_out;
	
	if (pollEnable == INTERRUPT)
	{
		ADC_out = MCAL_ADC_Read();
	}
	else
	{
		ADC_out = MCAL_ADC_convert((eADC_channelSelection_t)gLM35_CH);
	}
	
	uint32_t temp = ((uint32_t)ADC_out * ((uint32_t)gLM35_Vref * 1000)) / 1024;
	
	return (uint8_t)(temp / 10);
}