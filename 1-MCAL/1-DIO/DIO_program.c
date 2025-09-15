/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	DIO				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_interface.h"
#include "DIO_register.h"

u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;

	/*Check for wrong entry*/
	if (Copy_u8Pin > DIO_u8PIN7 || Copy_u8Pin < DIO_u8PIN0)
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Case pin value is high*/
	if (Copy_u8Value == DIO_u8PIN_HIGH)
	{
		/*Check port and set desired pin high*/
		switch (Copy_u8Port)
		{
		case DIO_u8PORTA:	SET_BIT(PORTA, Copy_u8Pin);	break;
		case DIO_u8PORTB:	SET_BIT(PORTB, Copy_u8Pin);	break;
		case DIO_u8PORTC:	SET_BIT(PORTC, Copy_u8Pin);	break;
		case DIO_u8PORTD:	SET_BIT(PORTD, Copy_u8Pin);	break;
		default: Local_u8ErrorState = 1;	/*Case wrong entry: set error*/
		}
	}
	/*Case pin value is low*/
	else if (Copy_u8Value == DIO_u8PIN_LOW)
	{
		/*Check port and set desired pin low*/
		switch (Copy_u8Port)
		{
		case DIO_u8PORTA:	CLR_BIT(PORTA, Copy_u8Pin);	break;
		case DIO_u8PORTB:	CLR_BIT(PORTB, Copy_u8Pin);	break;
		case DIO_u8PORTC:	CLR_BIT(PORTC, Copy_u8Pin);	break;
		case DIO_u8PORTD:	CLR_BIT(PORTD, Copy_u8Pin);	break;
		default: Local_u8ErrorState = 1;	/*Case wrong entry: set error*/
		}
	}
	/*Otherwise*/
	else
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;

	/*Check for wrong entry*/
	if (Copy_u8Value > DIO_u8PORT_HIGH || Copy_u8Value < DIO_u8PORT_LOW)
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Check and enable desired port for output*/
	switch (Copy_u8Port)
	{
	case DIO_u8PORTA:	PORTA = Copy_u8Value;	break;
	case DIO_u8PORTB:	PORTB = Copy_u8Value;	break;
	case DIO_u8PORTC:	PORTC = Copy_u8Value;	break;
	case DIO_u8PORTD:	PORTD = Copy_u8Value;	break;
	default: Local_u8ErrorState = 1;	/*Case wrong entry: set error*/
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_pu8Value)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;

	/*Check for null pointer*/
	if (Copy_pu8Value == NULL)
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Check for wrong entry*/
	if (Copy_u8Pin > DIO_u8PIN7 || Copy_u8Pin < DIO_u8PIN0)
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Check port and get desired pin's value*/
	switch (Copy_u8Port)
	{
	case DIO_u8PORTA:	*Copy_pu8Value = GET_BIT(PINA, Copy_u8Pin);	break;
	case DIO_u8PORTB:	*Copy_pu8Value = GET_BIT(PINB, Copy_u8Pin);	break;
	case DIO_u8PORTC:	*Copy_pu8Value = GET_BIT(PINC, Copy_u8Pin);	break;
	case DIO_u8PORTD:	*Copy_pu8Value = GET_BIT(PIND, Copy_u8Pin);	break;
	default: Local_u8ErrorState = 1;	/*Case wrong entry: set error*/
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 DIO_u8GetPortValue(u8 Copy_u8Port, u8* Copy_pu8Value)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;

	/*Check for null pointer*/
	if (Copy_pu8Value == NULL)
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Check and get desired port's value*/
	switch (Copy_u8Port)
	{
	case DIO_u8PORTA:	*Copy_pu8Value = PINA;	break;
	case DIO_u8PORTB:	*Copy_pu8Value = PINB;	break;
	case DIO_u8PORTC:	*Copy_pu8Value = PINC;	break;
	case DIO_u8PORTD:	*Copy_pu8Value = PIND;	break;
	default: Local_u8ErrorState = 1;	/*Case wrong entry: set error*/
	}

	/*Return error state*/
	return Local_u8ErrorState;
}
