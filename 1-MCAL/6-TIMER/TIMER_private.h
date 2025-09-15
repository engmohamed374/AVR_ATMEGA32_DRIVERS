/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	TIMER			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/*Macros for busy state*/
#define IDLE					1
#define BUSY					2

/*Macros for ICU state*/
#define ICU_ON					1
#define ICU_OFF					2

/*Macros for ICU edge select*/
#define ICES1_RISING_EDGE		0b01000000
#define ICES1_FALLING_EDGE		0b00000000

#endif
