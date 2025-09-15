/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL				*********************/
/*******************	SWC:	SWITCH			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "SWITCH_private.h"
#include "SWITCH_config.h"
#include "SWITCH_interface.h"

void SWITCH_voidReadPin(Switch* Copy_pSwitchPointer)
{
	/*Define var to hold switch state*/
	u8 Local_u8SwitchState = 0;

	/*Reset Switch state*/
	Copy_pSwitchPointer -> u8Value = 0;

	/*Get value of desired pin*/
	DIO_u8GetPinValue(Copy_pSwitchPointer -> u8Port, Copy_pSwitchPointer -> u8Pin, &(Copy_pSwitchPointer -> u8Value));

	if (Copy_pSwitchPointer -> u8Value)
	{
		/*Loop until user releases switch*/
		do {
			/*Get value of desired pin*/
			DIO_u8GetPinValue(Copy_pSwitchPointer -> u8Port, Copy_pSwitchPointer -> u8Pin, &Local_u8SwitchState);
		} while (Local_u8SwitchState);
	}
}
