/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	EXTI			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/*Macros for EXTI pins*/
#define EXTI_u8INT0					1
#define EXTI_u8INT1					3
#define EXTI_u8INT2					2

/*Macros for control senses*/
#define FALLING_EDGE				1
#define RISING_EDGE					2
#define ON_CHANGE					3
#define LOW_LEVEL					4

/*
 * NOTE:
 * The EXTI driver supports both prebuild/precompiled and postbuild configurations. To make use of
 * prebuild configuration make sure to set your desired configuration in EXTI_config.h file and call
 * the EXTI_voidInit function at the top of your code. Otherwise you can ignore initialization and
 * use other functions provided for postbuild configuration.
 */

/*
 * Name:		EXTI_voidInit
 * Arguments:	void
 * Return:		void
 * Description:	A function to initialize and set up the EXTIs.
 */
void EXTI_voidInit(void);

/*
 * Name:		EXTI_u8SetSenseControl
 * Arguments:	Copy_u8INTx, Copy_u8SenseControl
 * Return:		Local_u8ErrorState
 * Description:	A function to set control sense (Copy_u8SenseControl) of the EXTI pin (Copy_u8INTx).
 * 				Options for (Copy_u8SenseControl):	FALLING_EDGE
 * 													RISING_EDGE
 * 													ON_CHANGE
 * 													LOW_LEVEL
 * 				Note that only the first two options are valid for EXTI2.
 * 				Options for (Copy_u8INTx):	EXTI_u8INT0
 * 											EXTI_u8INT1
 * 											EXTI_u8INT2
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 EXTI_u8SetSenseControl(u8 Copy_u8INTx, u8 Copy_u8SenseControl);

/*
 * Name:		EXTI_u8EnableINTxPIF
 * Arguments:	Copy_u8INTx
 * Return:		Local_u8ErrorState
 * Description:	A function to enable interrupt flag of the EXTI pin (Copy_u8INTx).
 * 				Options for (Copy_u8INTx):	EXTI_u8INT0
 * 											EXTI_u8INT1
 * 											EXTI_u8INT2
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 EXTI_u8EnableINTxPIF(u8 Copy_u8INTx);

/*
 * Name:		EXTI_u8DisableINTxPIF
 * Arguments:	Copy_u8INTx
 * Return:		Local_u8ErrorState
 * Description:	A function to disable interrupt flag of the EXTI pin (Copy_u8INTx).
 * 				Options for (Copy_u8INTx):	EXTI_u8INT0
 * 											EXTI_u8INT1
 * 											EXTI_u8INT2
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 EXTI_u8DisableINTxPIF(u8 Copy_u8INTx);

/*
 * Name:		EXTI_u8SetINT0Callback
 * Arguments:	Copy_pvoidINT0Func
 * Return:		Local_u8ErrorState
 * Description:	A function to pass the address of the callback function to be called in the ISR of EXTI0.
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 EXTI_u8SetINT0Callback(void (*Copy_pvoidINT0Func)(void));

/*
 * Name:		EXTI_u8SetINT1Callback
 * Arguments:	Copy_pvoidINT1Func
 * Return:		Local_u8ErrorState
 * Description:	A function to pass the address of the callback function to be called in the ISR of EXTI1.
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 EXTI_u8SetINT1Callback(void (*Copy_pvoidINT1Func)(void));

/*
 * Name:		EXTI_u8SetINT2Callback
 * Arguments:	Copy_pvoidINT2Func
 * Return:		Local_u8ErrorState
 * Description:	A function to pass the address of the callback function to be called in the ISR of EXTI2.
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 EXTI_u8SetINT2Callback(void (*Copy_pvoidINT2Func)(void));

#endif
