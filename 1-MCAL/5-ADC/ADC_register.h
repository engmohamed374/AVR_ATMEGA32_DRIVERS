/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	ADC				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX			*((volatile u8*)0X27)	/*ADC Multiplexer Selection Register*/
#define ADMUX_MUX0		0						/*Analog Channel & Reference selection Bits*/
#define ADMUX_MUX1		1						/*Analog Channel & Reference selection Bits*/
#define ADMUX_MUX2		2						/*Analog Channel & Reference selection Bits*/
#define ADMUX_MUX3		3						/*Analog Channel & Reference selection Bits*/
#define ADMUX_MUX4		4						/*Analog Channel & Reference selection Bits*/
#define ADMUX_ADLAR		5						/*ADC Left Adjust Result*/
#define ADMUX_REFS0		6						/*Reference Selection Bits*/
#define ADMUX_REFS1		7						/*Reference Selection Bits*/

#define ADCSRA			*((volatile u8*)0X26)	/*ADC Control and Status Register A*/
#define ADCSRA_ADPS0	0						/*ADC Prescaler Select Bits*/
#define ADCSRA_ADPS1	1						/*ADC Prescaler Select Bits*/
#define ADCSRA_ADPS2	2						/*ADC Prescaler Select Bits*/
#define ADCSRA_ADIE		3						/*ADC Interrupt Enable*/
#define ADCSRA_ADIF		4						/*ADC Interrupt Flag*/
#define ADCSRA_ADATE	5						/*ADC Auto Trigger Enable*/
#define ADCSRA_ADSC		6						/*ADC Start Conversion*/
#define ADCSRA_ADEN		7						/*ADC Enable*/

#define SFIOR			*((volatile u8*)0X50)	/*Special FunctionIO Register*/
#define SFIOR_ADTS0		5						/*ADC Auto Trigger Source*/
#define SFIOR_ADTS1		6						/*ADC Auto Trigger Source*/
#define SFIOR_ADTS2		7						/*ADC Auto Trigger Source*/

#define ADCH			*((volatile u8*)0X25)	/*The ADC Data Register Low*/
#define ADCL			*((volatile u8*)0X24)	/*The ADC Data Register High*/
#define ADCS			*((volatile u16*)0X24)	/*The 16-bit ADC Data Register*/

#endif
