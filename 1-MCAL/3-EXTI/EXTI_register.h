/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	EXTI			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

#define GICR			*((volatile u8*)0x5b)		/*General Interrupt Control Register*/
#define GICR_INT1		7							/*EXTI1 Request Enable*/
#define GICR_INT0		6							/*EXTI0 Request Enable*/
#define GICR_INT2		5							/*EXTI2 Request Enable*/

#define GIFR			*((volatile u8*)0x5a)		/*General Interrupt Flag Register*/
#define GIFR_INTF1		7							/*EXTI1 Flag*/
#define GIFR_INTF0		6							/*EXTI0 Flag*/
#define GIFR_INTF2		5							/*EXTI2 Flag*/

#define MCUCR			*((volatile u8*)0x55)		/*MCU Control Register*/
#define MCUCR_ISC11		3							/*EXTI1 Sense Control Bits*/
#define MCUCR_ISC10		2							/*EXTI1 Sense Control Bits*/
#define MCUCR_ISC01		1							/*EXTI0 Sense Control Bits*/
#define MCUCR_ISC00		0							/*EXTI0 Sense Control Bits*/

#define MCUCSR			*((volatile u8*)0x54)		/*MCU Control & Status Register*/
#define MCUCSR_ISC2		6							/*EXTI2 Sense Control*/

#endif
