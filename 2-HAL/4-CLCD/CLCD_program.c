/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	CLCD			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/
#include <stdlib.h>
#include <string.h>
#include "util/delay.h"
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_register.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "DIO_interface.h"

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*Set RS pin for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);

	/*Set RW pin for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN, DIO_u8PIN_LOW);

	/*Put data on data port*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Data);

	/*Provide enable pulse*/
	{
		/*Set E pin high*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);

		/*Wait 1ms*/
		_delay_ms(1);

		/*Set E pin low*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
	}

#if	CLCD_DL_BIT == CLCD_DL_4_BIT

	/*Get lower nibble*/
	Copy_u8Data <<= 4;

	/*Put data on data port*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Data);

	/*Provide enable pulse*/
	{
		/*Set E pin high*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);

		/*Wait 1ms*/
		_delay_ms(1);

		/*Set E pin low*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
	}

#endif
}

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*Set RS pin for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);

	/*Set RW pin for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN, DIO_u8PIN_LOW);

	/*Put command on data port*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);

	/*Provide enable pulse*/
	{
		/*Set E pin high*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);

		/*Wait 1ms*/
		_delay_ms(1);

		/*Set E pin low*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
	}

#if	CLCD_DL_BIT == CLCD_DL_4_BIT

	/*Get lower nibble*/
	Copy_u8Command <<= 4;

	/*Put lower nibble of command on data port*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);

	/*Provide enable pulse*/
	{
		/*Set E pin high*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);

		/*Wait 1ms*/
		_delay_ms(1);

		/*Set E pin low*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
	}

#endif
}

void CLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	/*Define var to hold address of desired position*/
	u8 Local_u8Address;

	/*Case upper line*/
	if (Copy_u8XPos == 0)
	{
		Local_u8Address = Copy_u8YPos;
	}
	/*Case lower line*/
	else if (Copy_u8XPos == 1)
	{
		Local_u8Address = Copy_u8YPos + 0x40;
	}

	/*Force LCD to point to desired location*/
	CLCD_voidSendCommand(SET_BIT(Local_u8Address, 7));
}

void CLCD_voidSendString(char* Copy_pcharString)
{
	/*Define an iterator*/
	u8 Local_u8Iterator;

	for (Local_u8Iterator = 0; Copy_pcharString[Local_u8Iterator] != '\0'; Local_u8Iterator++)
	{
		/*Case string length is bigger than LCD visible window*/
		if(CLCD_WIDTH == Local_u8Iterator)
		{
			/*Complete in next line*/
			CLCD_voidGoToXY(1, 0);
		}

		/*Send string character by character*/
		CLCD_voidSendData(Copy_pcharString[Local_u8Iterator]);
	}
}

void CLCD_voidInit(void)
{
	/*Wait more than 30 ms*/
	_delay_ms(40);

#if CLCD_DL_BIT == CLCD_DL_4_BIT

	/*Set RS pin for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);

	/*Set RW pin for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN, DIO_u8PIN_LOW);

	/*Put command on data port*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, 0b00100000);

	/*Provide enable pulse*/
	{
		/*Set E pin high*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);

		/*Wait 1ms*/
		_delay_ms(1);

		/*Set E pin low*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
	}

#endif

	/*State No. of lines and font size*/
	CLCD_voidSendCommand(CONC(0, 0, 1, CLCD_DL_BIT, CLCD_N_BIT, CLCD_F_BIT, 0, 0));

	/*Enable display and disable cursor*/
	CLCD_voidSendCommand(CONC(0, 0, 0, 0, 1, CLCD_D_BIT, CLCD_C_BIT, CLCD_B_BIT));

	/*Clear display*/
	CLCD_voidSendCommand(0b00000001);
}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8BlockNumber, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	/*Define an iterator*/
	u8 Local_u8Iterator;
	/*Define var to hold pattern address in the CGRAM*/
	u8 Local_u8CGRAMAddress = 8 * Copy_u8BlockNumber;

	/*Send CGRAM address to LCD to make AC points to it*/
	CLCD_voidSendCommand(SET_BIT(Local_u8CGRAMAddress, 6));

	/*Send pattern to be written in CGRAM*/
	for (Local_u8Iterator = 0; Local_u8Iterator < 8; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}

	/*Make AC points to DDRAM*/
	CLCD_voidGoToXY(Copy_u8XPos, Copy_u8YPos);

	/*Make DDRAM reads from CGRAM and display data on LCD*/
	CLCD_voidSendData(Copy_u8BlockNumber);
}

void CLCD_voidWriteNumber(u32 Copy_u32Number)
{
	/*Define an iterator*/
	u8 Local_u8Iterator;
	/*Define pointer to hold digits*/
	u8* Local_pu8Digits = NULL;

	/*Case number = 0*/
	if (0 == Copy_u32Number)
	{
		/*Print digit in ASCII*/
		CLCD_voidSendData('0');
	}
	else
	{
		/*Convert Number to single digits*/
		for (Local_u8Iterator = 0; Copy_u32Number > 0; Local_u8Iterator++)
		{
			/*Add byte to array of digits*/
			Local_pu8Digits = (u8*)realloc(Local_pu8Digits, sizeof(u8) + Local_u8Iterator);

			/*Assign lower digit to the last index of array of digits*/
			Local_pu8Digits[Local_u8Iterator] = Copy_u32Number % 10;

			/*Divide number by ten*/
			Copy_u32Number /= 10;
		}

		/*Display number digit by digit*/
		for (Local_u8Iterator-- ; Local_u8Iterator != 0xff; Local_u8Iterator--)
		{
			/*Print digit in ASCII*/
			CLCD_voidSendData('0' + Local_pu8Digits[Local_u8Iterator]);
		}

		/*Free reserved space*/
		free(Local_pu8Digits);
	}
}

void CLCD_voidSineWave(char* Copy_pcharString)
{
	/*Define an iterator*/
	u8 Local_u8Iterator;
	/*Define var to be toggled*/
	u8 Local_u8Xos = 1;
	/*Define var to hold string length*/
	u8 Local_u8StringLength;

	/*Get length of string*/
	Local_u8StringLength = strlen(Copy_pcharString);

	/*Print string in forward sine wave*/
	for (Local_u8Iterator = 0; Local_u8Iterator < CLCD_WIDTH - Local_u8StringLength + 1; Local_u8Iterator++)
	{
		/*Position string*/
		CLCD_voidGoToXY(TGL_BIT(Local_u8Xos, 0), Local_u8Iterator);

		/*Display name*/
		CLCD_voidSendString(Copy_pcharString);

		/*Wait 1/2 sec*/
		_delay_ms(10);

		/*Clear screen*/
		CLCD_voidSendCommand(0b00000001);
	}

	/*Print string in backward sine wave*/
	for (Local_u8Iterator-- ; Local_u8Iterator < 0xff; Local_u8Iterator--)
	{
		/*Position string*/
		CLCD_voidGoToXY(TGL_BIT(Local_u8Xos, 0), Local_u8Iterator);

		/*Display name*/
		CLCD_voidSendString(Copy_pcharString);

		/*Wait 1/2 sec*/
		_delay_ms(10);

		/*Clear screen*/
		CLCD_voidSendCommand(0b00000001);
	}
}
