/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	TIMER			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_config.h"
#include "TIMER_register.h"
#include "TIMER_private.h"
#include "TIMER_interface.h"

/*==========================================================================================================*/
/*=============================================== GLOBAL VARIABLES =========================================*/
/*==========================================================================================================*/

/*Define pointer to hold address of callback function of Timer 0*/
void (*TIMER_pvoidT0CallbackFunc)(void) = NULL;
/*Define pointer to hold address of callback function of Timer 1*/
void (*TIMER_pvoidT1CallbackFunc)(void) = NULL;
/*Define pointer to hold address of callback function of Timer 2*/
void (*TIMER_pvoidT2CallbackFunc)(void) = NULL;
/*Define flag to hold Timer0 busy state*/
static u8 Global_u8T0BusyState = IDLE;
/*Define flag to hold Timer1 busy state*/
static u8 Global_u8T1BusyState = IDLE;
/*Define flag to hold Timer2 busy state*/
static u8 Global_u8T2BusyState = IDLE;
/*Define flag to hold ICU state*/
static u8 Global_u8ICUFlag = ICU_OFF;
/*Define var to hold Timer0 NO. of counts*/
static u32 Global_u32T0Counter = 0;
/*Define var to hold Timer1 NO. of counts*/
static u32 Global_u32T1Counter = 0;
/*Define var to hold Timer2 NO. of counts*/
static u32 Global_u32T2Counter = 0;

/*==========================================================================================================*/
/*================================================ TIMER0 FUNCTIONS ========================================*/
/*==========================================================================================================*/

u8 TIMER_u8SetTimer0(timer0_t* Copy_ptimer0_tSettings)
{
	//*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Set mode of operation*/
	TCCR0 &= 0b10110111;
	TCCR0 |= Copy_ptimer0_tSettings->u8_OperationMode;

	/*Set compare output mode*/
	TCCR0 &= 0b11001111;
	TCCR0 |= Copy_ptimer0_tSettings->u8_CompareOutputMode;

	/*Load TCNT0 with initial count value*/
	TCNT0 = Copy_ptimer0_tSettings->u8_OverflowPreloadValue;

	/*Load OCR0 with compare match value*/
	OCR0 = Copy_ptimer0_tSettings->u8_CompareMatchValue;

	/*Pass NO. of counts*/
	Global_u32T0Counter = Copy_ptimer0_tSettings->u32_Counter;

	/*Check NULL pointer*/
	if (NULL == Copy_ptimer0_tSettings->pvoid_NotificationFunc)
	{
		/*Error: NULL pointer*/
		Local_u8ErrorState = NULL_PTR;
	}
	else
	{
		/*Pass the notification function to be called in the ISR*/
		TIMER_pvoidT0CallbackFunc = Copy_ptimer0_tSettings->pvoid_NotificationFunc;
	}

	/*Select flags*/
	{
		/*Case OVF*/
		if(TIMER0_NORMAL == Copy_ptimer0_tSettings->u8_OperationMode)
		{
			/*Select TOV0 flag*/
			Copy_ptimer0_tSettings->u8_RollOverFlag = TIFR_TOV0;

			/*Select TOIE0 flag*/
			Copy_ptimer0_tSettings->u8_InterruptFlag = TIMSK_TOIE0;
		}
		/*Case COMP*/
		else if(TIMER0_CTC == Copy_ptimer0_tSettings->u8_OperationMode)
		{
			/*Select OCF0 flag*/
			Copy_ptimer0_tSettings->u8_RollOverFlag = TIFR_OCF0;

			/*Select OCIE0 flag*/
			Copy_ptimer0_tSettings->u8_InterruptFlag = TIMSK_OCIE0;
		}
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8Timer0SchedualeSynch(timer0_t* Copy_ptimer0_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;
	/*Define var to hold number of counts*/
	u32 Local_u32Counter = 0;

	/*Case Timer0 is idle*/
	if (IDLE == Global_u8T0BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T0BusyState = BUSY;

		/*Set clock select to enable Timer0*/
		TCCR0 &= 0b11111000;
		TCCR0 |= Copy_ptimer0_tSettings->u8_ClockSelect;

		/*Start counting*/
		while (Local_u32Counter++ < Global_u32T0Counter)
		{
			/*Wait till flag is set*/
			while(!GET_BIT(TIFR, Copy_ptimer0_tSettings->u8_RollOverFlag));

			/*Clear flag*/
			SET_BIT(TIFR, Copy_ptimer0_tSettings->u8_RollOverFlag);
		}

		/*Disable Timer0*/
		TCCR0 &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T0BusyState = IDLE;
	}
	/*Case Timer0 is busy*/
	else if (BUSY == Global_u8T0BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8Timer0SchedualeASynch(timer0_t* Copy_ptimer0_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Case Timer0 is idle*/
	if (IDLE == Global_u8T0BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T0BusyState = BUSY;

		/*Enable interrupt flag*/
		SET_BIT(TIMSK, Copy_ptimer0_tSettings->u8_InterruptFlag);

		/*Set clock select to enable Timer0*/
		TCCR0 &= 0b11111000;
		TCCR0 |= Copy_ptimer0_tSettings->u8_ClockSelect;
	}
	/*Case Timer0 is busy*/
	else if (BUSY == Global_u8T0BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8StartTimer0PWMAsynch(PWM0_t* Copy_pPWM0_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Case Timer0 is idle*/
	if (IDLE == Global_u8T0BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T0BusyState = BUSY;

		/*Set duty cycle*/
		TIMER_voidSetTimer0DutyCycle(Copy_pPWM0_tSettings);

		/*Set clock select to enable Timer0*/
		TCCR0 &= 0b11111000;
		TCCR0 |= Copy_pPWM0_tSettings->timer0_t_Settings.u8_ClockSelect;
	}
	/*Case Timer0 is busy*/
	else if (BUSY == Global_u8T0BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

void TIMER_voidSetTimer0DutyCycle(PWM0_t* Copy_pPWM0_tSettings)
{
	/*Set converted value from percentage range to register scale to output compare register*/
	OCR0 = Copy_pPWM0_tSettings->u8_DutyCycle > 100 ? 255 : (u8)map(0, 100, 0, 255, Copy_pPWM0_tSettings->u8_DutyCycle);
}

void TIMER_voidStopTimer0(void)
{
	/*Disable Timer0*/
	TCCR0 &= 0b11111000;

	/*Disable TOV interrupt flag*/
	CLR_BIT(TIMSK, TIMSK_TOIE0);
	/*Disable OCF interrupt flag*/
	CLR_BIT(TIMSK, TIMSK_OCIE0);

	/*Set busy state flag to idle*/
	Global_u8T0BusyState = IDLE;
}

/*==========================================================================================================*/
/*================================================ TIMER1 FUNCTIONS ========================================*/
/*==========================================================================================================*/

u8 TIMER_u8SetTimer1(timer1_t* Copy_ptimer1_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Set mode of operation*/
	TCCR1A &= 0b11111100;
	TCCR1A |= LOW(Copy_ptimer1_tSettings->u16_OperationMode);
	TCCR1B &= 0b11100111;
	TCCR1B |= HIGH(Copy_ptimer1_tSettings->u16_OperationMode);

	/*Set compare output mode of Unit A*/
	TCCR1A &= 0b00111111;
	TCCR1A |= Copy_ptimer1_tSettings->u8_CompareOutputModeA;

	/*Set compare output mode of Unit B*/
	TCCR1A &= 0b11001111;
	TCCR1A |= Copy_ptimer1_tSettings->u8_CompareOutputModeB;

	/*Load TCNT1 with initial count value*/
	TCNT1 = Copy_ptimer1_tSettings->u16_OverflowPreloadValue;

	/*Load compare match values*/
	{
		/*Load OCR1A with top value*/
		OCR1A = Copy_ptimer1_tSettings->u16_OCR1ACompareMatchValue;

		/*Load OCR1B with top value*/
		OCR1B = Copy_ptimer1_tSettings->u16_OCR1BCompareMatchValue;

		/*Load ICR1 with top value*/
		ICR1 = Copy_ptimer1_tSettings->u16_ICR1CompareMatchValue;
	}

	/*Pass NO. of counts*/
	Global_u32T1Counter = Copy_ptimer1_tSettings->u32_Counter;

	/*Check NULL pointer*/
	if (NULL == Copy_ptimer1_tSettings->pvoid_NotificationFunc)
	{
		/*Error: NULL pointer*/
		Local_u8ErrorState = NULL_PTR;
	}
	else
	{
		/*Pass the notification function to be called in the ISR*/
		TIMER_pvoidT1CallbackFunc = Copy_ptimer1_tSettings->pvoid_NotificationFunc;
	}

	/*Select flags*/
	{
		/*Case OVF*/
		if (TIMER1_NORMAL == Copy_ptimer1_tSettings->u16_OperationMode)
		{
			/*Select TOV flag*/
			Copy_ptimer1_tSettings->u8_RollOverFlag = TIFR_TOV1;

			/*Select TOIE1 flag*/
			Copy_ptimer1_tSettings->u8_InterruptFlag = TIMSK_TOIE1;
		}
		/*Case COMP & OCR1A is top*/
		else if (TIMER1_CTC_OCR1A == Copy_ptimer1_tSettings->u16_OperationMode)
		{
			/*Select OCF1A flag*/
			Copy_ptimer1_tSettings->u8_RollOverFlag = TIFR_OCF1A;

			/*Select OCIE1A flag*/
			Copy_ptimer1_tSettings->u8_InterruptFlag = TIMSK_OCIE1A;
		}
		/*Case COMP & ICR1 is top*/
		else if (TIMER1_CTC_ICR1 == Copy_ptimer1_tSettings->u16_OperationMode)
		{
			/*Select ICF1 flag*/
			Copy_ptimer1_tSettings->u8_RollOverFlag = TIFR_ICF1;

			/*Select TICIE1 flag*/
			Copy_ptimer1_tSettings->u8_InterruptFlag = TIMSK_TICIE1;
		}
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8Timer1SchedualeSynch(timer1_t* Copy_ptimer1_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;
	/*Define var to hold number of counts*/
	u32 Local_u32Counter = 0;

	/*Case Timer1 is idle*/
	if (IDLE == Global_u8T1BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T1BusyState = BUSY;

		/*Set clock select to enable Timer1*/
		TCCR1B &= 0b11111000;
		TCCR1B |= Copy_ptimer1_tSettings->u8_ClockSelect;

		/*Start counting*/
		while (Local_u32Counter++ < Global_u32T1Counter)
		{
			/*Wait till flag is set*/
			while(!GET_BIT(TIFR, Copy_ptimer1_tSettings->u8_RollOverFlag));

			/*Clear flag*/
			SET_BIT(TIFR, Copy_ptimer1_tSettings->u8_RollOverFlag);
		}

		/*Disable Timer1*/
		TCCR1B &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T1BusyState = IDLE;
	}
	/*Case Timer1 is busy*/
	else if (BUSY == Global_u8T1BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8Timer1SchedualeASynch(timer1_t* Copy_ptimer1_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Case Timer1 is idle*/
	if (IDLE == Global_u8T1BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T1BusyState = BUSY;

		/*Enable interrupt flag*/
		SET_BIT(TIMSK, Copy_ptimer1_tSettings->u8_InterruptFlag);

		/*Set clock select to enable Timer1*/
		TCCR1B &= 0b11111000;
		TCCR1B |= Copy_ptimer1_tSettings->u8_ClockSelect;
	}
	/*Case Timer1 is busy*/
	else if (BUSY == Global_u8T1BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8StartTimer1PWMAsynch(PWM1_t* Copy_pPWM1_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Case Timer1 is idle*/
	if (IDLE == Global_u8T1BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T1BusyState = BUSY;

		/*Set duty cycle for both units A & B*/
		TIMER_voidSetTimer1UnitADutyCycle(Copy_pPWM1_tSettings);
		TIMER_voidSetTimer1UnitBDutyCycle(Copy_pPWM1_tSettings);

		/*Set clock select to enable Timer1*/
		TCCR1B &= 0b11111000;
		TCCR1B |= Copy_pPWM1_tSettings->timer1_t_Settings.u8_ClockSelect;
	}
	/*Case Timer1 is busy*/
	else if (BUSY == Global_u8T1BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

void TIMER_voidSetTimer1UnitADutyCycle(PWM1_t* Copy_pPWM1_tSettings)
{
	/*Define var to hold top value*/
	u16 Local_u16TopValue;

	/*Check and set top value*/
	switch (Copy_pPWM1_tSettings->timer1_t_Settings.u16_OperationMode)
	{
	case TIMER1_FAST_PWM_8_BIT:
	case TIMER1_PWM_PHASE_CORRECT_8_BIT:
		Local_u16TopValue = 255;
		break;
	case TIMER1_FAST_PWM_9_BIT:
	case TIMER1_PWM_PHASE_CORRECT_9_BIT:
		Local_u16TopValue = 511;
		break;
	case TIMER1_FAST_PWM_10_BIT:
	case TIMER1_PWM_PHASE_CORRECT_10_BIT:
		Local_u16TopValue = 1023;
		break;
	case TIMER1_FAST_PWM_ICR1:
	case TIMER1_PWM_PHASE_CORRECT_ICR1:
		Local_u16TopValue = Copy_pPWM1_tSettings->timer1_t_Settings.u16_ICR1CompareMatchValue;
		break;
	}

	/*Case OCR1A doesn't contain top value*/
	if (Copy_pPWM1_tSettings->timer1_t_Settings.u16_OperationMode != TIMER1_FAST_PWM_OCR1A && Copy_pPWM1_tSettings->timer1_t_Settings.u16_OperationMode != TIMER1_PWM_PHASE_CORRECT_OCR1A)
	{
		/*Set converted value from percentage range to register scale to output compare register*/
		OCR1A = Copy_pPWM1_tSettings->u8_UnitADutyCycle > 100 ? Local_u16TopValue : (u16)map(0, 100, 0, Local_u16TopValue, Copy_pPWM1_tSettings->u8_UnitADutyCycle);
	}
}

void TIMER_voidSetTimer1UnitBDutyCycle(PWM1_t* Copy_pPWM1_tSettings)
{
	/*Define var to hold top value*/
	u16 Local_u16TopValue;

	/*Check and set top value*/
	switch (Copy_pPWM1_tSettings->timer1_t_Settings.u16_OperationMode)
	{
	case TIMER1_FAST_PWM_8_BIT:
	case TIMER1_PWM_PHASE_CORRECT_8_BIT:
		Local_u16TopValue = 255;
		break;
	case TIMER1_FAST_PWM_9_BIT:
	case TIMER1_PWM_PHASE_CORRECT_9_BIT:
		Local_u16TopValue = 511;
		break;
	case TIMER1_FAST_PWM_10_BIT:
	case TIMER1_PWM_PHASE_CORRECT_10_BIT:
		Local_u16TopValue = 1023;
		break;
	case TIMER1_FAST_PWM_ICR1:
	case TIMER1_PWM_PHASE_CORRECT_ICR1:
		Local_u16TopValue = Copy_pPWM1_tSettings->timer1_t_Settings.u16_ICR1CompareMatchValue;
		break;
	case TIMER1_FAST_PWM_OCR1A:
	case TIMER1_PWM_PHASE_CORRECT_OCR1A:
		Local_u16TopValue = Copy_pPWM1_tSettings->timer1_t_Settings.u16_OCR1ACompareMatchValue;
		break;
	}

	/*Set converted value from percentage range to register scale to output compare register*/
	OCR1B = Copy_pPWM1_tSettings->u8_UnitBDutyCycle > 100 ? Local_u16TopValue : (u16)map(0, 100, 0, Local_u16TopValue, Copy_pPWM1_tSettings->u8_UnitBDutyCycle);
}

void TIMER_voidDisableTimer1PWMUnitA(void)
{
	/*Set output compare of Unit A to normal port operation*/
	TCCR1A &= TIMER1_OC1A_NORMAL_PORT_OPERATION;
}

void TIMER_voidDisableTimer1PWMUnitB(void)
{
	/*Set output compare of Unit B to normal port operation*/
	TCCR1B &= TIMER1_OC1B_NORMAL_PORT_OPERATION;
}

u8 TIMER_u8StartICUAsynch(ICU_t* Copy_pICU_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Case Timer1 is idle*/
	if (IDLE == Global_u8T1BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T1BusyState = BUSY;

		/*Set mode of operation*/
		TCCR1A &= 0b11111100;
		TCCR1A |= LOW(TIMER1_NORMAL);
		TCCR1B &= 0b11100111;
		TCCR1B |= HIGH(TIMER1_NORMAL);

		/*Set ICU edge select to rising edge*/
		TCCR1B &= 0b10111111;
		TCCR1B |= ICES1_RISING_EDGE;

		/*Enable CAPT interrupt*/
		SET_BIT(TIMSK, TIMSK_TICIE1);

		/*Set clock select to enable Timer1*/
		TCCR1B &= 0b11111000;
		TCCR1B |= Copy_pICU_tSettings->u8_ClockSelect;
	}
	/*Case Timer1 is busy*/
	else if (BUSY == Global_u8T1BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

void TIMER_voidStopTimer1(void)
{
	/*Disable Timer1*/
	TCCR0 &= 0b11111000;

	/*Disable TOV interrupt flag*/
	CLR_BIT(TIMSK, TIMSK_TOIE1);
	/*Disable OCF interrupt flag*/
	CLR_BIT(TIMSK, TIMSK_OCIE1A);
	CLR_BIT(TIMSK, TIMSK_OCIE1B);
	/*Disable ICF interrupt flag*/
	CLR_BIT(TIMSK, TIMSK_TICIE1);

	/*Set busy state flag to idle*/
	Global_u8T1BusyState = IDLE;
}

/*==========================================================================================================*/
/*================================================ TIMER2 FUNCTIONS ========================================*/
/*==========================================================================================================*/

u8 TIMER_u8SetTimer2(timer2_t* Copy_ptimer2_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Set mode of operation*/
	TCCR2 &= 0b10110111;
	TCCR2 |= Copy_ptimer2_tSettings->u8_OperationMode;

	/*Set compare output mode*/
	TCCR2 &= 0b11001111;
	TCCR2 |= Copy_ptimer2_tSettings->u8_CompareOutputMode;

	/*Load TCNT2 with initial count value*/
	TCNT2 = Copy_ptimer2_tSettings->u8_OverflowPreloadValue;

	/*Load OCR2 with compare match value*/
	OCR2 = Copy_ptimer2_tSettings->u8_CompareMatchValue;

	/*Pass NO. of counts*/
	Global_u32T2Counter = Copy_ptimer2_tSettings->u32_Counter;

	/*Check NULL pointer*/
	if (NULL == Copy_ptimer2_tSettings->pvoid_NotificationFunc)
	{
		/*Error: NULL pointer*/
		Local_u8ErrorState = NULL_PTR;
	}
	else
	{
		/*Pass the notification function to be called in the ISR*/
		TIMER_pvoidT2CallbackFunc = Copy_ptimer2_tSettings->pvoid_NotificationFunc;
	}

	/*Select flags*/
	{
		/*Case OVF*/
		if(TIMER0_NORMAL == Copy_ptimer2_tSettings->u8_OperationMode)
		{
			/*Select TOV2 flag*/
			Copy_ptimer2_tSettings->u8_RollOverFlag = TIFR_TOV2;

			/*Select TOIE2 flag*/
			Copy_ptimer2_tSettings->u8_InterruptFlag = TIMSK_TOIE2;
		}
		/*Case COMP*/
		else if(TIMER0_CTC == Copy_ptimer2_tSettings->u8_OperationMode)
		{
			/*Select OCF0 flag*/
			Copy_ptimer2_tSettings->u8_RollOverFlag = TIFR_OCF2;

			/*Select OCIE2 flag*/
			Copy_ptimer2_tSettings->u8_InterruptFlag = TIMSK_OCIE2;
		}
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8Timer2SchedualeSynch(timer2_t* Copy_ptimer2_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;
	/*Define var to hold number of counts*/
	u32 Local_u32Counter = 0;

	/*Case Timer2 is idle*/
	if (IDLE == Global_u8T2BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T2BusyState = BUSY;

		/*Set clock select to enable Timer2*/
		TCCR2 &= 0b11111000;
		TCCR2 |= Copy_ptimer2_tSettings->u8_ClockSelect;

		/*Start counting*/
		while (Local_u32Counter++ < Global_u32T2Counter)
		{
			/*Wait till flag is set*/
			while(!GET_BIT(TIFR, Copy_ptimer2_tSettings->u8_RollOverFlag));

			/*Clear flag*/
			SET_BIT(TIFR, Copy_ptimer2_tSettings->u8_RollOverFlag);
		}

		/*Disable Timer2*/
		TCCR2 &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T2BusyState = IDLE;
	}
	/*Case Timer2 is busy*/
	else if (BUSY == Global_u8T2BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8Timer2SchedualeASynch(timer2_t* Copy_ptimer2_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Case Timer2 is idle*/
	if (IDLE == Global_u8T2BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T2BusyState = BUSY;

		/*Enable interrupt flag*/
		SET_BIT(TIMSK, Copy_ptimer2_tSettings->u8_InterruptFlag);

		/*Set clock select to enable Timer2*/
		TCCR2 &= 0b11111000;
		TCCR2 |= Copy_ptimer2_tSettings->u8_ClockSelect;
	}
	/*Case Timer2 is busy*/
	else if (BUSY == Global_u8T2BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 TIMER_u8StartTimer2PWMAsynch(PWM2_t* Copy_pPWM2_tSettings)
{
	/*Define var to hold error state*/
	u8 Local_u8ErrorState = OK;

	/*Case Timer2 is idle*/
	if (IDLE == Global_u8T2BusyState)
	{
		/*Set busy state flag to busy*/
		Global_u8T2BusyState = BUSY;

		/*Set duty cycle*/
		TIMER_voidSetTimer2DutyCycle(Copy_pPWM2_tSettings);

		/*Set clock select to enable Timer2*/
		TCCR2 &= 0b11111000;
		TCCR2 |= Copy_pPWM2_tSettings->timer2_t_Settings.u8_ClockSelect;
	}
	/*Case Timer2 is busy*/
	else if (BUSY == Global_u8T2BusyState)
	{
		/*Error: function is busy*/
		Local_u8ErrorState = BUSY_FUNC;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

void TIMER_voidSetTimer2DutyCycle(PWM2_t* Copy_pPWM2_tSettings)
{
	/*Set converted value from percentage range to register scale to output compare register*/
	OCR2 = Copy_pPWM2_tSettings->u8_DutyCycle > 100 ? 255 : (u8)map(0, 100, 0, 255, Copy_pPWM2_tSettings->u8_DutyCycle);
}

void TIMER_voidStopTimer2(void)
{
	/*Disable Timer2*/
	TCCR2 &= 0b11111000;

	/*Disable TOV interrupt flag*/
	CLR_BIT(TIMSK, TIMSK_TOIE2);
	/*Disable OCF interrupt flag*/
	CLR_BIT(TIMSK, TIMSK_OCIE2);

	/*Set busy state flag to idle*/
	Global_u8T2BusyState = IDLE;
}

/*==========================================================================================================*/
/*==================================================== LIBRARY =============================================*/
/*==========================================================================================================*/

s32 map(s32 Copy_s32XMin, s32 Copy_s32XMax, s32 Copy_s32YMin, s32 Copy_s32YMax, s32 Copy_s32XValue)
{
	/*Return mapped value*/
	return (Copy_s32XValue - Copy_s32XMin) * (Copy_s32YMax - Copy_s32YMin) / (Copy_s32XMax - Copy_s32XMin) + Copy_s32YMin;
}

/*==========================================================================================================*/
/*============================================== TIMER2 INTERRUPTS =========================================*/
/*==========================================================================================================*/

/*TIMER2 COMP ISR*/
void __vector_4(void)		__attribute__((signal));
void __vector_4(void)
{
	/*Define var to hold number of counts*/
	static u32 Local_u32Counter = 0;

	/*Case counting is not finished yet*/
	if (++Local_u32Counter < Global_u32T2Counter)
	{
		/*Do nothing*/
	}
	/*Case Counting is finished*/
	else
	{
		/*Disable Timer2*/
		TCCR2 &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T2BusyState = IDLE;

		/*Reset counter*/
		Local_u32Counter = 0;

		/*Disable COMP interrupt*/
		SET_BIT(TIMSK, TIMSK_OCIE2);

		/*Call notification function*/
		TIMER_pvoidT2CallbackFunc();
	}
}

/*TIMER2 OVF ISR*/
void __vector_5(void)		__attribute__((signal));
void __vector_5(void)
{
	/*Define var to hold number of counts*/
	static u32 Local_u32Counter = 0;

	/*Case counting is not finished yet*/
	if (++Local_u32Counter < Global_u32T2Counter)
	{
		/*Do nothing*/
	}
	/*Case Counting is finished*/
	else
	{
		/*Disable Timer2*/
		TCCR2 &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T2BusyState = IDLE;

		/*Reset counter*/
		Local_u32Counter = 0;

		/*Disable OVF interrupt*/
		SET_BIT(TIMSK, TIMSK_TOIE2);

		/*Call notification function*/
		TIMER_pvoidT2CallbackFunc();
	}
}

/*==========================================================================================================*/
/*============================================== TIMER1 INTERRUPTS =========================================*/
/*==========================================================================================================*/

/*TIMER1 CAPT*/
void __vector_6(void)		__attribute__((signal));
void __vector_6(void)
{
	/*Define var to hold number of counts*/
	static u32 Local_u32Counter = 0;

	/*Case ICU is functioning*/
	if (ICU_ON == Global_u8ICUFlag)
	{
		/*Case of first rising edge*/
		if (1 == ++Local_u32Counter)
		{
			/*Set TCNT1 to zero*/
			TCNT1 = 0;

			/*Enable OVF interrupt*/
			SET_BIT(TIMSK, TIMSK_TOIE1);

			/*Set ICU edge select to falling edge*/
			TCCR1B &= 0b10111111;
			TCCR1B |= ICES1_FALLING_EDGE;
		}
		/*Case of first falling edge*/
		else if (2 == ++Local_u32Counter)
		{
			/*Set TCNT1 to 0*/
			TCNT1 = 0;

			/*Copy value of ICR1*/

			/*Copy value of OVF counter*/

			/*Set OVF counter to 0*/
			Global_u32T1Counter = 0;

			/*Set ICU edge select to rising edge*/
			TCCR1B &= 0b10111111;
			TCCR1B |= ICES1_RISING_EDGE;
		}
		/*Case of second rising edge*/
		else if (3 == ++Local_u32Counter)
		{
			/*Set TCNT1 to zero*/
			TCNT1 = 0;

			/*Copy value of ICR1*/

			/*Copy value of OVF counter*/

			/*Set OVF counter to 0*/
			Global_u32T1Counter = 0;

			/*Set ICU edge select to falling edge*/
			TCCR1B &= 0b10111111;
			TCCR1B |= ICES1_FALLING_EDGE;

			/*Set counter to 1*/
			Local_u32Counter = 1;
		}
	}
	/*Otherwise*/
	else if (ICU_OFF == Global_u8ICUFlag)
	{
		/*Case counting is not finished yet*/
		if (++Local_u32Counter < Global_u32T1Counter)
		{
			/*Do nothing*/
		}
		/*Case Counting is finished*/
		else
		{
			/*Disable Timer1*/
			TCCR1B &= 0b11111000;

			/*Set busy state flag to idle*/
			Global_u8T1BusyState = IDLE;

			/*Reset counter*/
			Local_u32Counter = 0;

			/*Disable CAPT interrupt*/
			SET_BIT(TIMSK, TIMSK_TICIE1);

			/*Call notification function*/
			TIMER_pvoidT1CallbackFunc();
		}
	}
}

/*TIMER1 COMPA ISR*/
void __vector_7(void)		__attribute__((signal));
void __vector_7(void)
{
	/*Define var to hold number of counts*/
	static u32 Local_u32Counter = 0;

	/*Case counting is not finished yet*/
	if (++Local_u32Counter < Global_u32T1Counter)
	{
		/*Do nothing*/
	}
	/*Case Counting is finished*/
	else
	{
		/*Disable Timer1*/
		TCCR1B &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T1BusyState = IDLE;

		/*Reset counter*/
		Local_u32Counter = 0;

		/*Disable COMP interrupt*/
		SET_BIT(TIMSK, TIMSK_OCIE1A);

		/*Call notification function*/
		TIMER_pvoidT1CallbackFunc();
	}
}

/*TIMER1 COMPB ISR*/
void __vector_8(void)		__attribute__((signal));
void __vector_8(void)
{
	/*Define var to hold number of counts*/
	static u32 Local_u32Counter = 0;

	/*Case counting is not finished yet*/
	if (++Local_u32Counter < Global_u32T1Counter)
	{
		/*Do nothing*/
	}
	/*Case Counting is finished*/
	else
	{
		/*Disable Timer1*/
		TCCR1B &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T1BusyState = IDLE;

		/*Reset counter*/
		Local_u32Counter = 0;

		/*Disable OVF interrupt*/
		SET_BIT(TIMSK, TIMSK_OCIE1B);

		/*Call notification function*/
		TIMER_pvoidT1CallbackFunc();
	}
}

/*TIMER1 OVF ISR*/
void __vector_9(void)		__attribute__((signal));
void __vector_9(void)
{
	/*Define var to hold number of counts*/
	static u32 Local_u32Counter = 0;

	/*Case ICU is functioning*/
	if (ICU_ON == Global_u8ICUFlag)
	{
		/*Increase counter by one*/
		Global_u32T1Counter++;
	}
	/*Otherwise*/
	else if (ICU_OFF == Global_u8ICUFlag)
	{
		/*Case counting is not finished yet*/
		if (++Local_u32Counter < Global_u32T1Counter)
		{
			/*Do nothing*/
		}
		/*Case Counting is finished*/
		else
		{
			/*Disable Timer1*/
			TCCR1B &= 0b11111000;

			/*Set busy state flag to idle*/
			Global_u8T1BusyState = IDLE;

			/*Reset counter*/
			Local_u32Counter = 0;

			/*Disable OVF interrupt*/
			SET_BIT(TIMSK, TIMSK_TOIE1);

			/*Call notification function*/
			TIMER_pvoidT1CallbackFunc();
		}
	}
}

/*==========================================================================================================*/
/*============================================== TIMER0 INTERRUPTS =========================================*/
/*==========================================================================================================*/

/*TIMER0 COMP ISR*/
void __vector_10(void)		__attribute__((signal));
void __vector_10(void)
{
	/*Define var to hold number of counts*/
	static u32 Local_u32Counter = 0;

	/*Case counting is not finished yet*/
	if (++Local_u32Counter < Global_u32T0Counter)
	{
		/*Do nothing*/
	}
	/*Case Counting is finished*/
	else
	{
		/*Disable Timer0*/
		TCCR0 &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T0BusyState = IDLE;

		/*Reset counter*/
		Local_u32Counter = 0;

		/*Disable COMP interrupt*/
		SET_BIT(TIMSK, TIMSK_OCIE0);

		/*Call notification function*/
		TIMER_pvoidT0CallbackFunc();
	}
}

/*TIMER0 OVF ISR*/
void __vector_11(void)		__attribute__((signal));
void __vector_11(void)
{
	/*Define var to hold number of counts*/
	static u32 Local_u32Counter = 0;

	/*Case counting is not finished yet*/
	if (++Local_u32Counter < Global_u32T0Counter)
	{
		/*Do nothing*/
	}
	/*Case Counting is finished*/
	else
	{
		/*Disable Timer0*/
		TCCR0 &= 0b11111000;

		/*Set busy state flag to idle*/
		Global_u8T0BusyState = IDLE;

		/*Reset counter*/
		Local_u32Counter = 0;

		/*Disable OVF interrupt*/
		SET_BIT(TIMSK, TIMSK_TOIE0);

		/*Call notification function*/
		TIMER_pvoidT0CallbackFunc();
	}
}

/*==========================================================================================================*/
/*==========================================================================================================*/
