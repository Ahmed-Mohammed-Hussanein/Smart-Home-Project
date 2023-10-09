/*
 * atmega32_GPIO_Driver.c
 *
 * Created: 9/18/2022 12:01:32 AM
 *  Author: Ahmed
 */ 

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"

#include "atmega32_GPIO_Driver.h"


/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

/**================================================================
* @Fn				- MCAL_GPIO_Init
* @brief			- This is used to configure and initialize a pin or a port in GPIO.
* @param [in] 		- GPIOx: This specifies which port is used for configuration at @ref GPIOx_define.
* @param [in] 		- PinConfig: This carries the configuration for the pin or port at @ref GPIO_PIN_define. 
* @retval 			- None.
* Note				- None.
*/

void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig)
{
	switch(PinConfig->GPIO_PinMode)
	{
		case GPIO_MODE_INPUT:
		CLEAR_MASK(GPIOx->DDR, PinConfig->GPIO_PinNumber);
		break;
		
		case GPIO_MODE_OUTPUT:
		SET_MASK(GPIOx->DDR, PinConfig->GPIO_PinNumber);
		break;
		
		case GPIO_MODE_INPUT_PUR:
		CLEAR_MASK(GPIOx->DDR, PinConfig->GPIO_PinNumber);
		SET_MASK(GPIOx->PORT, PinConfig->GPIO_PinNumber);
		break;
	}
}


/**================================================================
* @Fn				- MCAL_GPIO_writePins
* @brief			- This is used to write a value to a pin in GPIO if the pin is in OUTPUT mode.
* @param [in] 		- GPIOx: This specifies which port is used for configuration at @ref GPIOx_define.
* @param [in] 		- PinNumber: This is used to determine the pins in the port at @ref GPIO_PIN_define.
* @param [in] 		- value: The value needed to be written on the pins at @ref GPIO_STATE_define.
* @retval 			- None.
* Note				- None.
*/
void MCAL_GPIO_writePins(GPIO_TypeDef *GPIOx, uint8_t PinNumber, uint8_t value)
{
	uint8_t temp = GPIOx->PORT;
	WRITE_MASK(temp, PinNumber, value);
	GPIOx->PORT = temp;
}


/**================================================================
* @Fn				- MCAL_GPIO_writePin
* @brief			- This is used to write a value to a pin in GPIO if the pin is in OUTPUT mode.
* @param [in] 		- GPIOx: This specifies which port is used for configuration at @ref GPIOx_define.
* @param [in] 		- PinNumber: This is used to determine the pin number in the port at @ref GPIO_PIN_define.
* @param [in] 		- value: The value needed to be written on the pin at @ref GPIO_STATE_define.
* @retval 			- None.
* Note				- None.
*/
void MCAL_GPIO_writePin(GPIO_TypeDef *GPIOx, uint8_t PinNumber, uint8_t value)
{
	switch(value)
	{
		case GPIO_STATE_LOW:
		CLEAR_MASK(GPIOx->PORT, PinNumber);
		break;
		
		case GPIO_STATE_HIGH:
		SET_MASK(GPIOx->PORT, PinNumber);
		break;
	}
}



/**================================================================
* @Fn				- MCAL_GPIO_writePort
* @brief			- This is used to write a value to a port GPIO if the port is in OUTPUT mode.
* @param [in] 		- GPIOx: This specifies which port is used for configuration at @ref GPIOx_define.
* @param [in] 		- value: The value needed to be written on the pin at @ref GPIO_STATE_define.
* @retval 			- None.
* Note				- None.
*/
void MCAL_GPIO_writePort(GPIO_TypeDef *GPIOx, uint8_t value)
{
	GPIOx->PORT = value;
}



/**================================================================
* @Fn				- MCAL_GPIO_readPin
* @brief			- This is used to read a value from a pin in GPIO.
* @param [in] 		- GPIOx: This specifies which port is used for configuration at @ref GPIOx_define.
* @param [in] 		- PinNumber: This is used to determine the pin number in the port at @ref GPIO_PIN_define.
* @retval 			- None.
* Note				- None.
*/
uint8_t MCAL_GPIO_readPin(GPIO_TypeDef *GPIOx, uint8_t PinNumber)
{
	switch(READ_MASK(GPIOx->PIN, PinNumber))
	{
		case GPIO_STATE_LOW:
		return GPIO_STATE_LOW;
		
		default:
		return GPIO_STATE_HIGH;
	}
}


/**================================================================
* @Fn				- MCAL_GPIO_readPort
* @brief			- This is used to read a value from a port in GPIO.
* @param [in] 		- GPIOx: This specifies which port is used for configuration at @ref GPIOx_define.
* @retval 			- None.
* Note				- None.
*/
uint8_t MCAL_GPIO_readPort(GPIO_TypeDef *GPIOx)
{
	return (uint8_t)GPIOx->PIN;
}


/**================================================================
* @Fn				- MCAL_GPIO_togglePin
* @brief			- This is used to toggle the state of the pin in GPIO if the pin is in OUTPUT mode.
* @param [in] 		- GPIOx: This specifies which port is used for configuration at @ref GPIOx_define.
* @param [in] 		- PinNumber: This is used to determine the pin number in the port at @ref GPIO_PIN_define.
* @retval 			- None.
* Note				- None.
*/
void MCAL_GPIO_togglePin(GPIO_TypeDef *GPIOx, uint8_t PinNumber)
{
	GPIOx->PORT ^= PinNumber;
}



/**================================================================
* @Fn				- MCAL_GPIO_togglePort
* @brief			- This is used to toggle the state of the port in GPIO if the port is in OUTPUT mode.
* @param [in] 		- GPIOx: This specifies which port is used for configuration at @ref GPIOx_define.
* @retval 			- None.
* Note				- None.
*/
void MCAL_GPIO_togglePort(GPIO_TypeDef *GPIOx)
{
	GPIOx->PORT ^= 0xFF;
}