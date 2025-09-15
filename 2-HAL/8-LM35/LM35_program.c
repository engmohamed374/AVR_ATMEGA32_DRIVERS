/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	LM35			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "LM35_private.h"
#include "LM35_config.h"
#include "LM35_interface.h"
#include "ADC_interface.h"

/*Macro for digital reference*/
#if	LM35_TEMPERATURE_RESOLUTION == TEN_BIT
#define REFERENCE			1023
#elif LM35_TEMPERATURE_RESOLUTION == EIGHT_BIT
#define REFERENCE			255
#endif

void LM35_voidInit(void)
{
	/*Initialize ADC SWC*/
	ADC_voidInit();
}

u8 LM35_u8GetTemperature(s16* Copy_ps16Temperature)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;
	/*Define var to hold ADC reading*/
	u16 Local_u16DigitalReading;

	/*Read digital value from ADC*/
	Local_u8ErrorState = ADC_u8StartConversionSynch(LM35_ANALOG_CHANNEL, &Local_u16DigitalReading, LM35_TEMPERATURE_RESOLUTION);

	/*Convert reading from digital reading into temperature*/
	*Copy_ps16Temperature = map(0, REFERENCE, 0, 500, Local_u16DigitalReading);

	/*Return error state*/
	return Local_u8ErrorState;
}

s32 map(s32 Copy_s32XMin, s32 Copy_s32XMax, s32 Copy_s32YMin, s32 Copy_s32YMax, s32 Copy_s32XValue)
{
	/*Return mapped value*/
	return (Copy_s32XValue - Copy_s32XMin) * (Copy_s32YMax - Copy_s32YMin) / (Copy_s32XMax - Copy_s32XMin) + Copy_s32YMin;
}

