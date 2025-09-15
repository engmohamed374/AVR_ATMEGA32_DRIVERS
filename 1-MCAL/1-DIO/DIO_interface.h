/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	DIO				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*Port Output Macros*/
#define DIO_u8PORT_LOW			0x00
#define DIO_u8PORT_HIGH			0xff

/*Port Macros*/
#define DIO_u8PORTA				0
#define DIO_u8PORTB				1
#define DIO_u8PORTC				2
#define DIO_u8PORTD				3

/*Pin Output Macros*/
#define DIO_u8PIN_LOW			0
#define DIO_u8PIN_HIGH			1

/*Pin Macros*/
#define DIO_u8PIN0				0
#define DIO_u8PIN1				1
#define DIO_u8PIN2				2
#define DIO_u8PIN3				3
#define DIO_u8PIN4				4
#define DIO_u8PIN5				5
#define DIO_u8PIN6				6
#define DIO_u8PIN7				7

/*
 * Name:		DIO_u8SetPinValue
 * Arguments:	Copy_u8Port, Copy_u8Pin, Copy_u8Value
 * Return:		Local_u8ErrorState
 * Description:	A function to set the pin number (Copy_u8Pin) of port (Copy_u8Port) to the value
 * 				(Copy_u8Value). The returned value (Local_u8ErrorState) specifies if an error occurred
 * 				during the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

/*
 * Name:		DIO_u8SetPortValue
 * Arguments:	Copy_u8Port, Copy_u8Value
 * Return:		Local_u8ErrorState
 * Description:	A function to set the port (Copy_u8Port) to the value (Copy_u8Value).
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);

/*
 * Name:		DIO_u8GetPinValue
 * Arguments:	Copy_u8Port, Copy_u8Pin, Copy_pu8Value
 * Return:		Local_u8ErrorState
 * Description:	A function to get the value of pin number (Copy_u8Pin) of port (Copy_u8Port) and save it
 * 				into the address (Copy_u8Value).
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_pu8Value);

/*
 * Name:		DIO_u8GetPortValue
 * Arguments:	Copy_u8Port, Copy_pu8Value
 * Return:		Local_u8ErrorState
 * Description:	A function to get the value of of port (Copy_u8Port) and save it into the address (Copy_u8Value).
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 DIO_u8GetPortValue(u8 Copy_u8Port, u8* Copy_pu8Value);

#endif
