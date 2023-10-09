/*
 * atmega32_I2C_Driver.c
 *
 * Created: 9/23/2023 6:29:29 PM
 *  Author: Ahmed
 */ 

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"

#include "atmega32_device_header.h"
#include "atmega32_BitField.h"
#include "atmega32_GPIO_Driver.h"
#include "atmega32_I2C_Driver.h"


/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

/**================================================================
* @Fn				- MCAL_I2C_Init
* @brief			- This is used to configure and initialize I2C Module.
* @param [in] 		- config: configuration for I2C.
* @retval 			- None.
* Note				- None.
*/
void MCAL_I2C_Init(I2C_Config_t *config)
{
	// set the bit rate
	I2C->_TWBR = config->I2C_bitRate;
	
	// set the pre scaler
	WRITE_MASK(I2C->_TWSR, I2C_TWSR_TWPSn_Mask, config->I2C_preScaler << I2C_TWSR_TWPSn_Pos);
	
	// general call
	WRITE_MASK(I2C->_TWAR, I2C_TWAR_TWGCE_Mask, config->I2C_generalCall << I2C_TWAR_TWGCE_Pos);
	
	// slave address
	WRITE_MASK(I2C->_TWAR, I2C_TWAR_TWAn_Mask, config->I2C_slaveAddress << I2C_TWAR_TWAn_Pos);
	
	// auto Ack
	WRITE_MASK(I2C->_TWCR, I2C_TWCR_TWEA_Mask, config->I2C_autoAck << I2C_TWCR_TWEA_Pos);
}

/**================================================================
* @Fn				- MCAL_I2C_DeInit
* @brief			- This is used to DeInitialize I2C Module.
* @param [in] 		- None.
* @retval 			- None.
* Note				- None.
*/
void MCAL_I2C_DeInit(void);


void MCAL_I2C_Start(void)
{
	// enable I2C
	SET_MASK(I2C->_TWCR, I2C_TWCR_TWEN);	
}

void MCAL_I2C_Stop(void)
{
	// disable I2C
	CLEAR_MASK(I2C->_TWCR, I2C_TWCR_TWEN);
}


void MCAL_I2C_Master_Tx(uint8_t address, uint8_t data[], uint8_t length, eStartCondition_t start, eStopCondition_t stop);
void MCAL_I2C_Master_Rx(uint8_t address, uint8_t data[], uint8_t length, eStartCondition_t start, eStopCondition_t stop);



void MCAL_I2C_startCondition(void)
{
	CLEAR_MASK(I2C->_TWCR, I2C_TWCR_TWSTA);
	SET_MASK(I2C->_TWCR, I2C_TWCR_TWSTA | I2C_TWCR_TWINT);
}

void MCAL_I2C_sendAddress(uint8_t address, eCommDirection_t direction)
{
	I2C->_TWDR = (address << 1) | (direction&1);
	SET_MASK(I2C->_TWCR, I2C_TWCR_TWINT);
}

void MCAL_I2C_sendPayload(uint8_t payload)
{
	I2C->_TWDR = payload;
	MCAL_I2C_startOperation();
}

void MCAL_I2C_receivePayload(uint8_t *payload)
{
	*payload = I2C->_TWDR;
}

void MCAL_I2C_stopCondition(void)
{
	SET_MASK(I2C->_TWCR, I2C_TWCR_TWSTO | I2C_TWCR_TWINT);
}

void MCAL_I2C_ACKConfig(eFunctional_State_t State)
{
	if(State == ENABLE)
	{
		SET_MASK(I2C->_TWCR, I2C_TWCR_TWEA);
	}
	else
	{
		CLEAR_MASK(I2C->_TWCR, I2C_TWCR_TWEA);
	}
}

__inline void MCAL_I2C_startOperation(void)
{
	SET_MASK(I2C->_TWCR, I2C_TWCR_TWINT);
}

void MCAL_I2C_waitForEvent(void)
{
	while(!READ_MASK(I2C->_TWCR, I2C_TWCR_TWINT));
}

eStatus_t MCAL_I2C_statusFlag(void)
{
	return READ_MASK(I2C->_TWSR, I2C_TWSR_TWSn);
}