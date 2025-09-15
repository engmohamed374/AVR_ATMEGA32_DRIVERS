/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	PORT			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef PORT_REGISTER_H_
#define PORT_REGISTER_H_

#define DDRA		*((volatile u8*)0x3a)		/*Direction Data Register A*/
#define DDRB		*((volatile u8*)0x37)		/*Direction Data Register B*/
#define DDRC		*((volatile u8*)0x34)		/*Direction Data Register C*/
#define DDRD		*((volatile u8*)0x31)		/*Direction Data Register D*/

#define PORTA		*((volatile u8*)0x3b)		/*PORT A Data Register*/
#define PORTB		*((volatile u8*)0x38)		/*PORT A Data Register*/
#define PORTC		*((volatile u8*)0x35)		/*PORT A Data Register*/
#define PORTD		*((volatile u8*)0x32)		/*PORT A Data Register*/

#endif
