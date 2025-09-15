/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	ADC				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "DIO_interface.h"

/*Define pointer to hold address of notification function to be passed to ISR*/
static void (*ADC_pvoidNotificationFunc)(void) = NULL;
/*Define pointer to hold address of user variable to be loaded with reading*/
static u16* ADC_pu16Reading = NULL;
/*Define var to hold ADC state*/
static u8 ADC_u8State;

void ADC_voidInit(void)
{
	/*Set ADC state idle*/
	ADC_u8State = IDLE;

	/*Enable ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);

	/*Set conversion speed*/
	ADCSRA &= 0b11111000;
	ADCSRA |= ADC_PRESCALER;

	/*Set Voltage reference*/
	ADMUX &= 0b00111111;
	ADMUX |= ADC_VOLTAGE_REFERNCE;
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_pu16Reading, u8 Copy_u8LeftAdjust)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;
	/*Define var to count time waited for ADC conversion*/
	u8 Local_u8TimeCounter = 0;

	/*Case ADC is busy*/
	if (ADC_u8State == BUSY)
	{
		/*Error: ADC is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}
	/*Case ADC is idle*/
	else if (ADC_u8State == IDLE)
	{
		/*Set ADC state busy*/
		ADC_u8State = BUSY;

		/*Set channel*/
		ADMUX &= 0b11100000;
		ADMUX |= Copy_u8Channel;

		/*Set ADMUX_ADLAR*/
		ADMUX &= 0b11011111;
		ADMUX |= Copy_u8LeftAdjust;

		/*Start conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/*Wait until ADC finish conversion or timeout*/
		while (0 == GET_BIT(ADCSRA, ADCSRA_ADIF) && ADC_u16ALLOWED_CONVERSION_TIME > Local_u8TimeCounter)
		{
			/*Increase counter*/
			Local_u8TimeCounter++;
		}

		/*Case complete conversion*/
		if (ADC_u16ALLOWED_CONVERSION_TIME != Local_u8TimeCounter)
		{
			/*Clear ADC flag*/
			SET_BIT(ADCSRA, ADCSRA_ADIF);

			/*Case NULL pointer*/
			if (!Copy_pu16Reading)
			{
				/*Error: NULL pointer*/
				Local_u8ErrorState = NULL_PTR;
			}
			/*Case LEFT_ADJUST*/
			else if (Copy_u8LeftAdjust == ADC_u8LEFT_ADJUST)
			{
				/*Read the high byte*/
				*Copy_pu16Reading = ADCH;
			}
			/*Case RIGHT_ADJUST*/
			else if (Copy_u8LeftAdjust == ADC_u8RIGHT_ADJUST)
			{
				/*Read the whole two bytes*/
				*Copy_pu16Reading = ADCS;
			}

			/*Set ADC state idle*/
			ADC_u8State = IDLE;
		}
		/*Case timeout*/
		else
		{
			/*Error: timeout*/
			Local_u8ErrorState = TIMEOUT;
		}
	}

	/*Return digital value*/
	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u16* Copy_pu16Reading, void (*Copy_pvoidNotificationFunc)(void) ,u8 Copy_u8LeftAdjust)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Case ADC is busy*/
	if (ADC_u8State == BUSY)
	{
		/*Error: ADC is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}
	/*Case ADC is idle*/
	else if (ADC_u8State == IDLE)
	{
		/*Check NULL pointer*/
		if (NULL == Copy_pvoidNotificationFunc || NULL == Copy_pu16Reading)
		{
			/*Error: NULL pointer*/
			Local_u8ErrorState = NULL_PTR;
		}
		else
		{
			/*Set ADC state to busy*/
			ADC_u8State = BUSY;

			/*Assign address of notification function*/
			ADC_pvoidNotificationFunc = Copy_pvoidNotificationFunc;

			/*Assign address of user variable to be loaded with reading*/
			ADC_pu16Reading = Copy_pu16Reading;

			/*Set channel*/
			ADMUX &= 0b11100000;
			ADMUX |= Copy_u8Channel;

			/*Set ADMUX_ADLAR*/
			ADMUX &= 0b11011111;
			ADMUX |= Copy_u8LeftAdjust;

			/*Enable ADC interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);
		}
	}

	/*Return digital value*/
	return Local_u8ErrorState;
}

void __vector_16(void)		__attribute__((signal));
void __vector_16(void)
{
	/*Case LEFT_ADJUST*/
	if (GET_BIT(ADMUX, ADMUX_ADLAR))
	{
		/*Read the high byte*/
		*ADC_pu16Reading = ADCH;
	}
	/*Case RIGHT_ADJUST*/
	else if (!GET_BIT(ADMUX, ADMUX_ADLAR))
	{
		/*Read the whole two bytes*/
		*ADC_pu16Reading = ADCS;
	}

	/*Set ADC state to idle*/
	ADC_u8State = IDLE;

	/*Call user notification function*/
	ADC_pvoidNotificationFunc();

	/*Disable ADC interrupt*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);
}
