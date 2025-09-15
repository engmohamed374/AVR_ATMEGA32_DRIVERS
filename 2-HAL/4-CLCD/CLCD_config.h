/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	CLCD			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/*Define data length*/
#define CLCD_DL_BIT					CLCD_DL_8_BIT

/*Define No. of lines*/
#define CLCD_N_BIT					CLCD_N_2_LINE

/*Define font size*/
#define CLCD_F_BIT					CLCD_F_2_5x10

/*Define display on or off*/
#define CLCD_D_BIT					CLCD_D_ON

/*Define cursor on or off*/
#define CLCD_C_BIT					CLCD_C_OFF

/*Define cursor blinking*/
#define CLCD_B_BIT					CLCD_B_OFF

/*Port to put data or command on*/
#define CLCD_DATA_PORT				DIO_u8PORTD

/*Port and pins that assists in LCD control*/
#define CLCD_CTRL_PORT				DIO_u8PORTB
#define CLCD_RS_PIN					DIO_u8PIN0
#define CLCD_RW_PIN					DIO_u8PIN1
#define CLCD_E_PIN					DIO_u8PIN2

/*Define command for clearing LCD*/
#define CLCD_u8CLEAR_LCD			0b00000001

/*Width of visible window*/
#define CLCD_WIDTH					16

#endif
