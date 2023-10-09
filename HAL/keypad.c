/*
 * keypad.c
 *
 * Created: 8/31/2023 2:48:17 PM
 *  Author: Ahmed
 */ 


// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "keypad.h"

#include "atmega32_GPIO_Driver.h"

/*
 * ===========================================================================
 * ================================= Generic Macros ==========================
 * ===========================================================================
 */

#define CHECK_STATE			GPIO_STATE_LOW
#define NO_CHECK_STATE		GPIO_STATE_HIGH

/*
 * ==============================================================================
 * ================================= Generic Variables ==========================
 * ==============================================================================
 */



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

void HAL_Keypad_Init()
{
	GPIO_PinConfig_t pin;
	
	pin.GPIO_PinMode		= GPIO_MODE_OUTPUT;
	pin.GPIO_PinNumber		= COL_0 | COL_1 | COL_2 | COL_3;
	MCAL_GPIO_Init(COL_PORT, &pin);
	
	pin.GPIO_PinMode		= GPIO_MODE_INPUT_PUR;
	pin.GPIO_PinNumber		= ROW_0 | ROW_1 | ROW_2 | ROW_3;
	MCAL_GPIO_Init(COL_PORT, &pin);
}

uint8_t HAL_Keypad_getKey(uint8_t (*keys) [])
{
	uint8_t i;
	
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
		MCAL_GPIO_writePin(COL_PORT, COL_0, CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_1, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_2, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_3, NO_CHECK_STATE);
		break;
			
		case 1:
		MCAL_GPIO_writePin(COL_PORT, COL_0, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_1, CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_2, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_3, NO_CHECK_STATE);
		break;
			
		case 2:
		MCAL_GPIO_writePin(COL_PORT, COL_0, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_1, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_2, CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_3, NO_CHECK_STATE);
		break;
		
		case 3:
		MCAL_GPIO_writePin(COL_PORT, COL_0, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_1, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_2, NO_CHECK_STATE);
		MCAL_GPIO_writePin(COL_PORT, COL_3, CHECK_STATE);
		break;
		}
		
		if (MCAL_GPIO_readPin(ROW_PORT, ROW_0) == CHECK_STATE)
		{
			while(MCAL_GPIO_readPin(ROW_PORT, ROW_0) == CHECK_STATE);
			
			return *(*keys + 4 * 0 + i);
		}
		else if (MCAL_GPIO_readPin(ROW_PORT, ROW_1) == CHECK_STATE)
		{
			while(MCAL_GPIO_readPin(ROW_PORT, ROW_1) == CHECK_STATE);
			
			return *(*keys + 4 * 1 + i);
		}
		else if (MCAL_GPIO_readPin(ROW_PORT, ROW_2) == CHECK_STATE)
		{
			while(MCAL_GPIO_readPin(ROW_PORT, ROW_2) == CHECK_STATE);
			
			return *(*keys + 4 * 2 + i);
		}
		else if (MCAL_GPIO_readPin(ROW_PORT, ROW_3) == CHECK_STATE)
		{
			while(MCAL_GPIO_readPin(ROW_PORT, ROW_3) == CHECK_STATE);
			
			return *(*keys + 4 * 3 + i);
		}
	}
	
	return '\0';
}
