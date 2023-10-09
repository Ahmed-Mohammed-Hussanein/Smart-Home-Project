/*
 * SecuritySystem.h
 *
 * Created: 10/8/2023 5:37:37 PM
 *  Author: Ahmed
 */ 


#ifndef SECURITYSYSTEM_H_
#define SECURITYSYSTEM_H_

#include "state.h"

// ===================================================================
// ================== Macros Configuration Reference =================
// ===================================================================

#define PassWord			"1234"
#define KEYPAD_LAYOUT		{'7', '8', '9', '\xFE',\
							 '4', '5', '6', 'x',\
							 '1', '2', '3', '-',\
							 '?', '0', '=', '+'}


// ===================================================
// ================== APIs Functions =================
// ===================================================

void SecuritySystem_Init(void);
void SecuritySystem_checkPassword(void);


#endif /* SECURITYSYSTEM_H_ */