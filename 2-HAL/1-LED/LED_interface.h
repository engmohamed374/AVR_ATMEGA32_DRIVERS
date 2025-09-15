/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL				*********************/
/*******************	SWC:	LED				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef LED_PROGRAM_H_
#define LED_PROGRAM_H_

/*Define struct to hold LED's data*/
typedef struct
{
	u8 u8Port;		/*Define var to hold desired port*/
	u8 u8Pin;		/*Define var to hold desired pin*/
} Led;

u8 LED_u8TurnOn(Led* Copy_pLedPointer);

u8 LED_u8TurnOff(Led* Copy_pLedPointer);

#endif
