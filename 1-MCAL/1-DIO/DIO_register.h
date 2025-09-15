/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	DIO				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef DIO_REGISTER_H_
#define DIO_REGISTER_H_

#define PORTA		*((volatile u8*)0x3b)		/*PORT A Data Register*/
#define PINA		*((volatile u8*)0x39)		/*PORT A Input Pins Address*/

#define PORTB		*((volatile u8*)0x38)		/*PORT B Data Register*/
#define PINB		*((volatile u8*)0x36)		/*PORT A Input Pins Address*/

#define PORTC		*((volatile u8*)0x35)		/*PORT C Data Register*/
#define PINC		*((volatile u8*)0x33)		/*PORT A Input Pins Address*/

#define PORTD		*((volatile u8*)0x32)		/*PORT D Data Register*/
#define PIND		*((volatile u8*)0x30)		/*PORT A Input Pins Address*/

#endif
