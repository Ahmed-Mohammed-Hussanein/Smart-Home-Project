/*
 * buzzer.h
 *
 * Created: 10/6/2023 2:47:55 AM
 *  Author: Ahmed
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_


// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"

// ==========================================================
// ================== User Type Definitions =================
// ==========================================================


// ===================================================
// ================== APIs Functions =================
// ===================================================

void HAL_buzzer_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig);
void HAL_buzzer_turnOn(GPIO_TypeDef *GPIOx, uint8_t PinNumber);
void HAL_buzzer_turnOff(GPIO_TypeDef *GPIOx, uint8_t PinNumber);

#endif /* BUZZER_H_ */