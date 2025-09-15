/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	SSD				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include <util/delay.h>
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "SSD_private.h"
#include "SSD_interface.h"
#include "DIO_interface.h"

u8 SSD_u8SetSevenSegment(SevenSegment* Copy_pSevenSegmentPointer)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;

	/*Check for null pointer*/
	if (Copy_pSevenSegmentPointer == NULL)
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Enable connected port for output*/
	Local_u8ErrorState |= DIO_u8SetPortDirection(Copy_pSevenSegmentPointer -> u8Port, DIO_u8PORT_OUTPUT);

	/*Check for multiplexing*/
	if (Copy_pSevenSegmentPointer -> u8MultiplexState)
	{
		Local_u8ErrorState |= DIO_u8SetPinDirection(Copy_pSevenSegmentPointer -> u8EnablePort, Copy_pSevenSegmentPointer -> u8EnablePin, DIO_u8PIN_OUTPUT);
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 SSD_u8SingleDisplay(SevenSegment* Copy_pSevenSegmentPointer)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;

	/*Check for null pointer*/
	if (Copy_pSevenSegmentPointer == NULL)
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Case common anode*/
	if(Copy_pSevenSegmentPointer -> u8CommonType)
	{
		Local_u8ErrorState |= DIO_u8SetPortValue(~(Copy_pSevenSegmentPointer -> u8Port), Copy_pSevenSegmentPointer -> u8Value);
	}
	/*Case common cathode*/
	else
	{
		Local_u8ErrorState |= DIO_u8SetPortValue(Copy_pSevenSegmentPointer -> u8Port, Copy_pSevenSegmentPointer -> u8Value);
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 SSD_u8MultiDisplay(SevenSegment* Copy_pSevenSegmentArray, u8 Copy_u8DisplayNumber)
{
	/*Define var to specify errors*/
	u8 Local_u8ErrorState = 0;
	/*Define var to hold indices*/
	u8 Local_u8Index;
	/*Define 2 iterators*/
	u8 itr;

	/*Check for null pointer*/
	if (Copy_pSevenSegmentArray == NULL)
	{
		/*Set error*/
		Local_u8ErrorState = 1;
	}

	/*Loop on all displays*/
	for (itr = 0; itr < Copy_u8DisplayNumber; itr++)
	{
		/*Clearing all displays*/
		Local_u8ErrorState |= DIO_u8SetPortValue(Copy_pSevenSegmentArray[0].u8Port, DIO_u8PORT_LOW);

		/*Disable last enabled Display*/
		{
			/*Calculate the index of last Display*/
			Local_u8Index = SSD_u8CircleDown(0, Copy_u8DisplayNumber - 1, itr);

			/*Case common anode*/
			if (Copy_pSevenSegmentArray[Local_u8Index].u8CommonType)
			{
				Local_u8ErrorState |= DIO_u8SetPinValue(Copy_pSevenSegmentArray[Local_u8Index].u8EnablePort, Copy_pSevenSegmentArray[Local_u8Index].u8EnablePin, DIO_u8PIN_LOW);
			}
			/*Case common cathode*/
			else
			{
				Local_u8ErrorState |= DIO_u8SetPinValue(Copy_pSevenSegmentArray[Local_u8Index].u8EnablePort, Copy_pSevenSegmentArray[Local_u8Index].u8EnablePin, DIO_u8PIN_HIGH);
			}
		}

		/*Enable recent display*/
		{
			/*Case common anode*/
			if (Copy_pSevenSegmentArray[itr].u8CommonType)
			{
				Local_u8ErrorState |= DIO_u8SetPinValue(Copy_pSevenSegmentArray[itr].u8EnablePort, Copy_pSevenSegmentArray[itr].u8EnablePin, DIO_u8PIN_HIGH);
			}
			/*Case common cathode*/
			else
			{
				Local_u8ErrorState |= DIO_u8SetPinValue(Copy_pSevenSegmentArray[itr].u8EnablePort, Copy_pSevenSegmentArray[itr].u8EnablePin, DIO_u8PIN_LOW);
			}
		}

		/*Put digit on recent display*/
		{
			/*Case common anode*/
			if(Copy_pSevenSegmentArray[itr].u8CommonType)
			{
				Local_u8ErrorState |= DIO_u8SetPortValue(~(Copy_pSevenSegmentArray[itr].u8Port), Copy_pSevenSegmentArray[itr].u8Value);
			}
			/*Case common cathode*/
			else
			{
				Local_u8ErrorState |= DIO_u8SetPortValue(Copy_pSevenSegmentArray[itr].u8Port, Copy_pSevenSegmentArray[itr].u8Value);
			}

		}

		/*Wait a little*/
		_delay_ms(20 / Copy_u8DisplayNumber);
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 SSD_u8CircleUp(u8 Copy_u8LowLim, u8 Copy_u8HighLim, u8 Copy_u8Value)
{
	return  Copy_u8Value == Copy_u8HighLim ? Copy_u8LowLim : Copy_u8Value + 1;
}

u8 SSD_u8CircleDown(u8 Copy_u8LowLim, u8 Copy_u8HighLim, u8 Copy_u8Value)
{
	return  Copy_u8Value == Copy_u8LowLim ? Copy_u8HighLim : Copy_u8Value - 1;
}
