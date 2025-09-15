/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL				*********************/
/*******************	SWC:	LED				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_register.h"
#include "DIO_interface.h"
#include "LED_interface.h"

u8 LED_u8TurnOn(Led* Copy_pLedPointer)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;

	/*Turn on LED*/
	Local_u8ErrorState = DIO_u8SetPinValue(Copy_pLedPointer -> u8Port, Copy_pLedPointer ->u8Pin, DIO_u8PIN_HIGH);

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 LED_u8TurnOff(Led* Copy_pLedPointer)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;

	/*Turn off LED*/
	Local_u8ErrorState = DIO_u8SetPinValue(Copy_pLedPointer -> u8Port, Copy_pLedPointer ->u8Pin, DIO_u8PIN_LOW);

	/*Return error state*/
	return Local_u8ErrorState;
}
