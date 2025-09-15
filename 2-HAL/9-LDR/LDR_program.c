/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	LDR				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "LDR_private.h"
#include "LDR_config.h"
#include "LDR_interface.h"
#include "ADC_interface.h"

void LDR_voidInit(void)
{
	/*Initialize ADC SWC*/
	ADC_voidInit();
}

u8 LDR_u8GetIntensity(u16* Copy_pu16Intensity)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;
	/*Define var to hold ADC reading*/
	u16 Local_u16DigitalReading;

	/*Read digital value from ADC*/
	Local_u8ErrorState = ADC_u8StartConversionSynch(LDR_ANALOG_CHANNEL, &Local_u16DigitalReading, LDR_INTENSITY_RESOLUTION);

	/*Convert reading from digital reading into intensity*/
	*Copy_pu16Intensity = map(0, 30, 0, 102, Local_u16DigitalReading);

	/*Return error state*/
	return Local_u8ErrorState;
}

s32 map(s32 Copy_s32XMin, s32 Copy_s32XMax, s32 Copy_s32YMin, s32 Copy_s32YMax, s32 Copy_s32XValue)
{
	/*Return mapped value*/
	return (Copy_s32XValue - Copy_s32XMin) * (Copy_s32YMax - Copy_s32YMin) / (Copy_s32XMax - Copy_s32XMin) + Copy_s32YMin;
}
