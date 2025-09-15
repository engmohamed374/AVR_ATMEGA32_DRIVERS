/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	KPD				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef	KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_PORT				DIO_u8PORTA

#define KPD_COL0_PIN			DIO_u8PIN0
#define KPD_COL1_PIN			DIO_u8PIN1
#define KPD_COL2_PIN			DIO_u8PIN2
#define KPD_COL3_PIN			DIO_u8PIN3

#define KPD_ROW0_PIN			DIO_u8PIN4
#define KPD_ROW1_PIN			DIO_u8PIN5
#define KPD_ROW2_PIN			DIO_u8PIN6
#define KPD_ROW3_PIN			DIO_u8PIN7

#define KPD_NO_PRESSED_KEY		0x7f

#define KPD_ARR_VAL				{{7, 8, 9, -1}, {4, 5, 6, -6}, {1, 2, 3, -3}, {10, 0, 13, -5}}

#endif
