/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	ADC				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*Macros for ADC_VOLTAGE_REFERNCE*/
#define AREF							0b00000000
#define AVCC							0b01000000
#define INNTERNAL_256V					0b11000000

/*Macros for ADC_PRESCALER*/
#define DIVISION_FACTOR_2				0b00000001
#define DIVISION_FACTOR_4				0b00000010
#define DIVISION_FACTOR_8				0b00000011
#define DIVISION_FACTOR_16				0b00000100
#define DIVISION_FACTOR_32				0b00000101
#define DIVISION_FACTOR_64				0b00000110
#define DIVISION_FACTOR_128				0b00000111

/*Macros for ADC state*/
#define IDLE							0
#define BUSY							1

#endif
