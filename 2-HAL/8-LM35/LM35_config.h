/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	LM35			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef LM35_CONFIG_H
#define LM35_CONFIG_H

/*
 * Options:	EIGHT_BIT
 * 			TEN_BIT
 */
#define LM35_TEMPERATURE_RESOLUTION		EIGHT_BIT

/*
 * Options: ADC_u8SINGLE_ENDED_ADC0
 * 			ADC_u8SINGLE_ENDED_ADC1
 * 			ADC_u8SINGLE_ENDED_ADC2
 * 			ADC_u8SINGLE_ENDED_ADC3
 * 			ADC_u8SINGLE_ENDED_ADC4
 * 			ADC_u8SINGLE_ENDED_ADC5
 * 			ADC_u8SINGLE_ENDED_ADC6
 * 			ADC_u8SINGLE_ENDED_ADC7
 * 			ADC_u8DEFRENTIAL_P0_N0_G10
 * 			ADC_u8DEFRENTIAL_P1_N0_G10
 * 			ADC_u8DEFRENTIAL_P0_N0_G200
 * 			ADC_u8DEFRENTIAL_P1_N0_G200
 * 			ADC_u8DEFRENTIAL_P2_N2_G10
 * 			ADC_u8DEFRENTIAL_P3_N2_G10
 * 			ADC_u8DEFRENTIAL_P2_N2_G200
 * 			ADC_u8DEFRENTIAL_P3_N2_G200
 * 			ADC_u8DEFRENTIAL_P0_N1_G1
 * 			ADC_u8DEFRENTIAL_P1_N1_G1
 * 			ADC_u8DEFRENTIAL_P2_N1_G1
 * 			ADC_u8DEFRENTIAL_P3_N1_G1
 * 			ADC_u8DEFRENTIAL_P4_N1_G1
 * 			ADC_u8DEFRENTIAL_P5_N1_G1
 * 			ADC_u8DEFRENTIAL_P6_N1_G1
 * 			ADC_u8DEFRENTIAL_P7_N1_G1
 * 			ADC_u8DEFRENTIAL_P0_N2_G1
 * 			ADC_u8DEFRENTIAL_P1_N2_G1
 * 			ADC_u8DEFRENTIAL_P2_N2_G1
 * 			ADC_u8DEFRENTIAL_P3_N2_G1
 * 			ADC_u8DEFRENTIAL_P4_N2_G1
 * 			ADC_u8DEFRENTIAL_P5_N2_G1
 * 			ADC_u8SINGLE_ENDED_122V
 * 			ADC_u8SINGLE_ENDED_GND
 */
#define LM35_ANALOG_CHANNEL				ADC_u8SINGLE_ENDED_ADC0

#endif
