/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	EXTI			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*Choose control sense for EXTI pins: 	1)- FALLING_EDGE
 * 										2)- RISING_EDGE
 * 										3)- ON_CHANGE
 * 										4)- LOW_LEVEL
 */
#define EXTI_INT0_CONTROL_SENSE		FALLING_EDGE
#define EXTI_INT1_CONTROL_SENSE		FALLING_EDGE
#define EXTI_INT2_CONTROL_SENSE		FALLING_EDGE

/*Choose initial state for peripheral interrupt:	1)- ENABLED
 * 													2)- DISABLED
 */
#define INT0_INITIAL_STATE			ENABLED
#define INT1_INITIAL_STATE			ENABLED
#define INT2_INITIAL_STATE			ENABLED

#endif
