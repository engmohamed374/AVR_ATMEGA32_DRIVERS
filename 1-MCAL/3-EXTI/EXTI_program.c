/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	EXTI			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "EXTI_register.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"

/*Define global pointers*/
void (*EXTI_pvoidINT0Fun)(void) = NULL;
void (*EXTI_pvoidINT1Fun)(void) = NULL;
void (*EXTI_pvoidINT2Fun)(void) = NULL;

void EXTI_voidInit(void)
{
	/*Set control sense for INT0*/
	{
#if	EXTI_INT0_CONTROL_SENSE == FALLING_EDGE

		/*Set ISC00 bit*/
		SET_BIT(MCUCR, MCUCR_ISC01);
		/*Clear ISC01 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC00);

#elif EXTI_INT0_CONTROL_SENSE == RISING_EDGE

		/*Set ISC00 bit*/
		SET_BIT(MCUCR, MCUCR_ISC01);
		/*Set ISC01 bit*/
		SET_BIT(MCUCR, MCUCR_ISC00);

#elif EXTI_INT0_CONTROL_SENSE == ON_CHANGE

		/*Clear ISC00 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC01);
		/*Set ISC01 bit*/
		SET_BIT(MCUCR, MCUCR_ISC00);

#elif EXTI_INT0_CONTROL_SENSE == LOW_LEVEL

		/*Clear ISC00 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC01);
		/*Clear ISC01 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC00);

#else

		/*Set ISC00 bit*/
		SET_BIT(MCUCR, MCUCR_ISC01);
		/*Clear ISC01 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC00);

#warning "No such control sense! FALLING_EDGE control sense is set."

#endif
	}

	/*Set control sense for INT1*/
	{
#if	EXTI_INT1_CONTROL_SENSE == FALLING_EDGE

		/*Set ISC00 bit*/
		SET_BIT(MCUCR, MCUCR_ISC11);
		/*Clear ISC01 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC10);

#elif EXTI_INT1_CONTROL_SENSE == RISING_EDGE

		/*Set ISC00 bit*/
		SET_BIT(MCUCR, MCUCR_ISC11);
		/*Set ISC01 bit*/
		SET_BIT(MCUCR, MCUCR_ISC10);

#elif EXTI_INT1_CONTROL_SENSE == ON_CHANGE

		/*Clear ISC00 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC11);
		/*Set ISC01 bit*/
		SET_BIT(MCUCR, MCUCR_ISC10);

#elif EXTI_INT1_CONTROL_SENSE == LOW_LEVEL

		/*Clear ISC00 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC11);
		/*Clear ISC01 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC10);

#else

		/*Set ISC00 bit*/
		SET_BIT(MCUCR, MCUCR_ISC11);
		/*Clear ISC01 bit*/
		CLR_BIT(MCUCR, MCUCR_ISC10);

#warning "No such control sense! FALLING_EDGE control sense is set."

#endif
	}

	/*Set control sense for INT2*/
	{
#if	EXTI_INT2_CONTROL_SENSE == FALLING_EDGE

		/*Clear ISC2*/
		CLR_BIT(MCUCSR, MCUCSR_ISC2);

#elif EXTI_INT2_CONTROL_SENSE == RISING_EDGE

		/*Set ISC2*/
		SET_BIT(MCUCSR, MCUCSR_ISC2);

#else

		/*Clear ISC2*/
		CLR_BIT(MCUCSR, MCUCSR_ISC2);

#warning "This type of control sense is not valid for INT2 pin, alternatively FALLING_EDGE control sense is set."

#endif
	}

	/*Set peripheral interrupt flag for INT0*/
	{
#if INT0_INITIAL_STATE == ENABLED

		/*Enable peripheral interrupt flag for INT0*/
		SET_BIT(GICR, GICR_INT0);

#elif INT0_INITIAL_STATE == DISABLED

		/*Disable peripheral interrupt flag for INT0*/
		CLR_BIT(GICR, GICR_INT0);

#else

		/*Enable peripheral interrupt flag for INT0*/
		SET_BIT(GICR, GICR_INT0);

#warning "Wrong initial state for INT0! Peripheral interrupt flag is ENABLED"

#endif
	}

	/*Set peripheral interrupt flag for INT1*/
	{
#if INT1_INITIAL_STATE == ENABLED

		/*Enable peripheral interrupt for INT1*/
		SET_BIT(GICR, GICR_INT1);

#elif INT1_INITIAL_STATE == DISABLED

		/*Disable peripheral interrupt for INT1*/
		CLR_BIT(GICR, GICR_INT1);

#else

		/*Enable peripheral interrupt for INT1*/
		SET_BIT(GICR, GICR_INT1);

#warning "Wrong initial state for INT1! Peripheral interrupt flag is ENABLED"

#endif
	}

	/*Set peripheral interrupt flag for INT2*/
	{
#if INT2_INITIAL_STATE == ENABLED

		/*Enable peripheral interrupt for INT2*/
		SET_BIT(GICR, GICR_INT2);

#elif INT2_INITIAL_STATE == DISABLED

		/*Disable peripheral interrupt for INT2*/
		CLR_BIT(GICR, GICR_INT2);

#else

		/*Enable peripheral interrupt for INT2*/
		SET_BIT(GICR, GICR_INT2);

#warning "Wrong initial state for INT2! Peripheral interrupt flag is ENABLED"

#endif
	}
}

u8 EXTI_u8SetSenseControl(u8 Copy_u8INTx, u8 Copy_u8SenseControl)
{
	/*Define var to hold errors*/
	u8 Local_u8ErrorState = OK;

	/*Select pin*/
	switch (Copy_u8INTx)
	{
	case EXTI_u8INT0:
		/*Select control sense*/
		switch (Copy_u8SenseControl)
		{
		case FALLING_EDGE:	SET_BIT(MCUCR, MCUCR_ISC01);	CLR_BIT(MCUCR, MCUCR_ISC00);	break;
		case RISING_EDGE:	SET_BIT(MCUCR, MCUCR_ISC01);	SET_BIT(MCUCR, MCUCR_ISC00);	break;
		case ON_CHANGE:		CLR_BIT(MCUCR, MCUCR_ISC01);	SET_BIT(MCUCR, MCUCR_ISC00);	break;
		case LOW_LEVEL:		CLR_BIT(MCUCR, MCUCR_ISC01);	CLR_BIT(MCUCR, MCUCR_ISC00);	break;
		default:	Local_u8ErrorState = NOK;
		}
		break;
		case EXTI_u8INT1:
			/*Select control sense*/
			switch (Copy_u8SenseControl)
			{
			case FALLING_EDGE:	SET_BIT(MCUCR, MCUCR_ISC11);	CLR_BIT(MCUCR, MCUCR_ISC10);	break;
			case RISING_EDGE:	SET_BIT(MCUCR, MCUCR_ISC11);	SET_BIT(MCUCR, MCUCR_ISC10);	break;
			case ON_CHANGE:		CLR_BIT(MCUCR, MCUCR_ISC11);	SET_BIT(MCUCR, MCUCR_ISC10);	break;
			case LOW_LEVEL:		CLR_BIT(MCUCR, MCUCR_ISC11);	CLR_BIT(MCUCR, MCUCR_ISC10);	break;
			default:	Local_u8ErrorState = NOK;
			}
			break;
			case EXTI_u8INT2:
				/*Select control sense*/
				switch (Copy_u8SenseControl)
				{
				case FALLING_EDGE:	CLR_BIT(MCUCSR, MCUCSR_ISC2);	break;
				case RISING_EDGE:	SET_BIT(MCUCSR, MCUCSR_ISC2);	break;
				default:	Local_u8ErrorState = NOK;
				}
				break;
				default:	Local_u8ErrorState = NOK;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 EXTI_u8EnableINTxPIF(u8 Copy_u8INTx)
{
	/*Define var to hold errors*/
	u8 Local_u8ErrorState = OK;

	/*Select pin*/
	switch (Copy_u8INTx)
	{
	case EXTI_u8INT0:	SET_BIT(GICR, GICR_INT0);	break;
	case EXTI_u8INT1:	SET_BIT(GICR, GICR_INT1);	break;
	case EXTI_u8INT2:	SET_BIT(GICR, GICR_INT2);	break;
	default:	Local_u8ErrorState = NOK;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 EXTI_u8DisableINTxPIF(u8 Copy_u8INTx)
{
	/*Define var to hold errors*/
	u8 Local_u8ErrorState = OK;

	/*Select pin*/
	switch (Copy_u8INTx)
	{
	case EXTI_u8INT0:	CLR_BIT(GICR, GICR_INT0);	break;
	case EXTI_u8INT1:	CLR_BIT(GICR, GICR_INT1);	break;
	case EXTI_u8INT2:	CLR_BIT(GICR, GICR_INT2);	break;
	default:	Local_u8ErrorState = NOK;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 EXTI_u8SetINT0Callback(void (*Copy_pvoidINT0Func)(void))
{
	/*Define var to hold errors*/
	u8 Local_u8ErrorState = OK;

	/*Check if pointer is not NULL*/
	if (NULL != Copy_pvoidINT0Func)
	{
		/*Assign address of ISR function made by user to global pointer*/
		EXTI_pvoidINT0Fun = Copy_pvoidINT0Func;
	}
	else
	{
		/*Error*/
		Local_u8ErrorState = NULL_PTR;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 EXTI_u8SetINT1Callback(void (*Copy_pvoidINT1Func)(void))
{
	/*Define var to hold errors*/
	u8 Local_u8ErrorState = OK;

	/*Check if pointer is not NULL*/
	if (NULL != Copy_pvoidINT1Func)
	{
		/*Assign address of ISR function made by user to global pointer*/
		EXTI_pvoidINT1Fun = Copy_pvoidINT1Func;
	}
	else
	{
		/*Error*/
		Local_u8ErrorState = NULL_PTR;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

u8 EXTI_u8SetINT2Callback(void (*Copy_pvoidINT2Func)(void))
{
	/*Define var to hold errors*/
	u8 Local_u8ErrorState = OK;

	/*Check if pointer is not NULL*/
	if (NULL != Copy_pvoidINT2Func)
	{
		/*Assign address of ISR function made by user to global pointer*/
		EXTI_pvoidINT2Fun = Copy_pvoidINT2Func;
	}
	else
	{
		/*Error*/
		Local_u8ErrorState = NULL_PTR;
	}

	/*Return error state*/
	return Local_u8ErrorState;
}

void __vector_1 (void)		__attribute__((signal));
void __vector_1 (void)
{
	/*Check if pointer is not NULL*/
	if (NULL != EXTI_pvoidINT0Fun)
	{
		/*Call user INT0 ISR*/
		EXTI_pvoidINT0Fun();
	}
}

void __vector_2 (void)		__attribute__((signal));
void __vector_2 (void)
{
	/*Check if pointer is not NULL*/
	if (NULL != EXTI_pvoidINT1Fun)
	{
		/*Call user INT1 ISR*/
		EXTI_pvoidINT1Fun();
	}
}
void __vector_3 (void)		__attribute__((signal));
void __vector_3 (void)
{
	/*Check if pointer is not NULL*/
	if (NULL != EXTI_pvoidINT2Fun)
	{
		/*Call user INT2 ISR*/
		EXTI_pvoidINT2Fun();
	}
}
