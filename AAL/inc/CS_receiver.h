/*
 * CS_receiver.h
 *
 * Created: 10/8/2023 12:42:25 AM
 *  Author: Ahmed
 */ 


#ifndef CS_RECEIVER_H_
#define CS_RECEIVER_H_


#include "state.h"

typedef enum
{
	CS_Rx_Idle,
	CS_Rx_Check,
	CS_Rx_Forwarding,
	CS_Rx_Backwarding,
	CS_Rx_Stopped
	
} e_CS_Rx_StateId_t;


extern void (*p2CS_Rx_state)(void);


void CS_Rx_Init(void);
STATE_fn(CS_Rx_Idle);
STATE_fn(CS_Rx_Check);
STATE_fn(CS_Rx_Forwarding);
STATE_fn(CS_Rx_Backwarding);
STATE_fn(CS_Rx_Stopped);



#endif /* CS_RECEIVER_H_ */