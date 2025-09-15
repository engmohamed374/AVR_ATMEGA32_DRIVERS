/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL				*********************/
/*******************	SWC:	SWITCH			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef SWITCH_PRIVATE_H_
#define SWITCH_PRIVATE_H_

/*Define struct to hold switch's data*/
typedef struct
{
	u8 u8Port;		/*Define var to hold desired port*/
	u8 u8Pin;		/*Define var to hold desired pin*/
	u8 u8Value;		/*Define var to hold pin value*/
} Switch;

#endif
