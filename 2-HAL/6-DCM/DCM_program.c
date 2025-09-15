/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	DCM				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "DCM_private.h"
#include "DCM_config.h"
#include "DCM_interface.h"

void DCM_voidBrake(void)
{
	/*Disable CCW pin*/
	DIO_u8SetPinValue(DCM_PORT, DCM_CCW_PIN, DIO_u8PIN_LOW);

	/*Disable CW pin*/
	DIO_u8SetPinValue(DCM_PORT, DCM_CW_PIN, DIO_u8PIN_LOW);
}

void DCM_voidRunCW(void)
{
	/*Disable CCW pin*/
	DIO_u8SetPinValue(DCM_PORT, DCM_CCW_PIN, DIO_u8PIN_LOW);

	/*Enable CW pin*/
	DIO_u8SetPinValue(DCM_PORT, DCM_CW_PIN, DIO_u8PIN_HIGH);
}

void DCM_voidRunCCW(void)
{
	/*Disable CW pin*/
	DIO_u8SetPinValue(DCM_PORT, DCM_CW_PIN, DIO_u8PIN_LOW);

	/*Enable CCW pin*/
	DIO_u8SetPinValue(DCM_PORT, DCM_CCW_PIN, DIO_u8PIN_HIGH);
}
