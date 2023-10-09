/*
 * seven_seg.h
 *
 * Created: 10/6/2023 4:01:33 AM
 *  Author: Ahmed
 */ 


#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_


// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"


// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

#define _7SEG_PORT		GPIOA
#define _7SEG_PIN_0		GPIO_PIN_0
#define _7SEG_PIN_1		GPIO_PIN_1
#define _7SEG_PIN_2		GPIO_PIN_2
#define _7SEG_PIN_3		GPIO_PIN_3

// ===================================================
// ================== APIs Functions =================
// ===================================================
void HAL_7seg_Init(void);
void HAL_7seg_writeVal(uint8_t val);


#endif /* SEVEN_SEG_H_ */