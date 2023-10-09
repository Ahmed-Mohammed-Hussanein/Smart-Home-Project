/*
 * atmega32_I2C_Driver.h
 *
 * Created: 9/23/2023 6:29:09 PM
 *  Author: Ahmed
 */ 


#ifndef ATMEGA32_I2C_DRIVER_H_
#define ATMEGA32_I2C_DRIVER_H_

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "Utils.h"

#include "atmega32_device_header.h"

// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

/*
	Important Note: the CPU clock frequency in the Slave must be at least 16 times higher than the SCL frequency.
	
	You can Use the following equation to calculate the prescaler and the bit rate.
	I2C_bitRate * I2C_preScaler = (F_CPU / (2 * F_SCL)) - 8
	F_SCL = F_CPU / (16 + 2 * I2C_bitRate * I2C_preScaler)
*/

typedef struct
{
	uint8_t I2C_preScaler;							/* This specifies the prescaler of the clock.
															This parameter must be a value of @ref I2C_PRESCALER_define.
														*/
	
	uint8_t I2C_bitRate;							/* This specifies the bit rate of the clock from 0 to 255.
														*/
	
	uint8_t I2C_slaveAddress;						/* This specifies the address of the module when working as a slave from 0 to 127.
													  */
	
	eFunctional_State_t I2C_generalCall;			/* This Enables or disables the general call recognition.
													  This parameter must be a value of ENABLE or DISABLE.
													  */
	
	eFunctional_State_t I2C_autoAck;				/* This Enables or disables Automatic ACK.
													  This parameter must be a value of ENABLE or DISABLE.
													  */
	
}	I2C_Config_t;

// ===================================================================
// ================== Macros Configuration Reference =================
// ===================================================================

// @ref I2C_PRESCALER_define.
#define I2C_PRESCALER_DIV1				0x0
#define I2C_PRESCALER_DIV4				0x1
#define I2C_PRESCALER_DIV16				0x2
#define I2C_PRESCALER_DIV64				0x3

// @ref I2C_GENERAL_CALL_define.
#define I2C_GENERAL_CALL_DISABLE		0x0
#define I2C_GENERAL_CALL_ENABLE			0x1


typedef enum
{
	START = 0,
	REPEATED_START = !START

}eStartCondition_t;

typedef enum
{
	WITH_STOP = 0,
	WITHOUT_STOP = !WITH_STOP

}eStopCondition_t;

typedef enum
{
	WRITE = 0,
	READ = !WRITE

}eCommDirection_t;

typedef enum
{
	START_Transmitted				= 0x08,
	REPEATED_START_Transmitted		= 0x10,
	MT_SLA_W_ACK					= 0x18,
	MT_SLA_W_NACK					= 0x20,
	MT_DATA_ACK						= 0x28,
	MT_DATA_NACK					= 0x30,
	ARBITARTION_LOST				= 0x38,
	MR_SLA_R_ACK					= 0x40,
	MR_SLA_R_NACK					= 0x48,
	MR_DATA_ACK						= 0x50,
	MR_DATA_NACK					= 0x58,
	SR_SLA_W_ACK					= 0x60,
	SR_DATA_ACK						= 0x80,
	SR_DATA_NACK					= 0x88,
	ST_SLA_R_ACK					= 0xA8,
	ST_SLA_R_NACK					= 0xB0,
	ST_DATA_ACK						= 0xB8,
	ST_DATA_NACK					= 0xC0,
	
}eStatus_t;


// ===================================================
// ================== APIs Functions =================
// ===================================================
void MCAL_I2C_Init(I2C_Config_t *config);
void MCAL_I2C_DeInit(void);


void MCAL_I2C_Start(void);
void MCAL_I2C_Stop(void);


void MCAL_I2C_Master_Tx(uint8_t address, uint8_t data[], uint8_t length, eStartCondition_t start, eStopCondition_t stop);
void MCAL_I2C_Master_Rx(uint8_t address, uint8_t data[], uint8_t length, eStartCondition_t start, eStopCondition_t stop);


/*
 * Generic APIs
 */
void MCAL_I2C_startCondition(void);
void MCAL_I2C_sendAddress(uint8_t address, eCommDirection_t direction);
void MCAL_I2C_sendPayload(uint8_t payload);
void MCAL_I2C_receivePayload(uint8_t *payload);
void MCAL_I2C_stopCondition(void);
void MCAL_I2C_ACKConfig(eFunctional_State_t State);


void MCAL_I2C_waitForEvent(void);
void MCAL_I2C_startOperation(void);
eStatus_t MCAL_I2C_statusFlag(void);


#endif /* ATMEGA32_I2C_DRIVER_H_ */