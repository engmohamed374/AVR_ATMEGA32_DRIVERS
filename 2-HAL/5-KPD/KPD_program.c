/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	CALC			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "DIO_interface.h"
#include "KPD_config.h"
#include "KPD_private.h"
#include "KPD_interface.h"

s8 KPD_u8GetPressedKey(void)
{
	/*Define var to hold pressed key*/
	u8 Local_u8PressedKey = KPD_NO_PRESSED_KEY;
	/*Define var to hold pin state*/
	u8 Local_u8PinState;
	/*Define iterators*/
	u8 Local_u8ColumnIdx, Local_u8RowIdx;
	/*Define array to hold values of keys*/
	static u8 Local_u8KPDArr[4][4] = KPD_ARR_VAL;
	/*Define array to hold KPD columns*/
	static u8 Local_u8KPDColArr[4] = {KPD_COL0_PIN, KPD_COL1_PIN, KPD_COL2_PIN, KPD_COL3_PIN};
	/*Define array to hold KPD rows*/
	static u8 Local_u8KPDRowArr[4] = {KPD_ROW0_PIN, KPD_ROW1_PIN, KPD_ROW2_PIN, KPD_ROW3_PIN};

	/*Loop on KPD columns*/
	for (Local_u8ColumnIdx = 0; Local_u8ColumnIdx < COL_NUM; Local_u8ColumnIdx++)
	{
		/*Activate current column*/
		DIO_u8SetPinValue(KPD_PORT, Local_u8KPDColArr[Local_u8ColumnIdx], DIO_u8PIN_LOW);

		/*Loop on KPD rows*/
		for (Local_u8RowIdx = 0; Local_u8RowIdx < ROW_NUM; Local_u8RowIdx++)
		{
			/*Read pin state*/
			DIO_u8GetPinValue(KPD_PORT, Local_u8KPDRowArr[Local_u8RowIdx], &Local_u8PinState);

			/*Check if key is pressed*/
			if (DIO_u8PIN_LOW == Local_u8PinState)
			{
				/*Specify pressed key*/
				Local_u8PressedKey = Local_u8KPDArr[Local_u8RowIdx][Local_u8ColumnIdx];

				/*Stay here until key is not pressed*/
				while (DIO_u8PIN_LOW == Local_u8PinState)
				{
					/*Read pin state*/
					DIO_u8GetPinValue(KPD_PORT, Local_u8KPDRowArr[Local_u8RowIdx], &Local_u8PinState);
				}

				/*Return pressed key*/
				return Local_u8PressedKey;
			}
		}

		/*Deactivate current column*/
		DIO_u8SetPinValue(KPD_PORT, Local_u8KPDColArr[Local_u8ColumnIdx], DIO_u8PIN_HIGH);
	}

	/*Return pressed key*/
	return Local_u8PressedKey;
}
