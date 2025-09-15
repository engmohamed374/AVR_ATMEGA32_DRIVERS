/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	ADC				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/* Options:	AREF
 *         	AVCC
 *         	INNTERNAL_256V
 */
#define ADC_VOLTAGE_REFERNCE					AVCC

/* Options:	DIVISION_FACTOR_2
 *          DIVISION_FACTOR_2
 *          DIVISION_FACTOR_4
 *          DIVISION_FACTOR_8
 *          DIVISION_FACTOR_16
 *          DIVISION_FACTOR_32
 *          DIVISION_FACTOR_64
 *          DIVISION_FACTOR_128
 */
#define ADC_PRESCALER							DIVISION_FACTOR_4

/*
 * Macro to specify allowed time for the ADC to finish conversion before setting an error.
 * Note that selected number refers to No. of while loops which checks counter and conversion
 * completion as well as incrementing the counter in case of false conditions above.
 */
#define ADC_u16ALLOWED_CONVERSION_TIME			10000

#endif
