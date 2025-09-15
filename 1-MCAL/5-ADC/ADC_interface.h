/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	ADC				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*Macros for Copy_u8LeftAdjust*/
#define ADC_u8RIGHT_ADJUST				0b00000000
#define ADC_u8LEFT_ADJUST				0b00100000

/*Macros for Copy_u8Channel*/
#define ADC_u8SINGLE_ENDED_ADC0			0b00000000
#define ADC_u8SINGLE_ENDED_ADC1			0b00000001
#define ADC_u8SINGLE_ENDED_ADC2			0b00000010
#define ADC_u8SINGLE_ENDED_ADC3			0b00000011
#define ADC_u8SINGLE_ENDED_ADC4			0b00000100
#define ADC_u8SINGLE_ENDED_ADC5			0b00000101
#define ADC_u8SINGLE_ENDED_ADC6			0b00000110
#define ADC_u8SINGLE_ENDED_ADC7			0b00000111
#define ADC_u8DEFRENTIAL_P0_N0_G10		0b00001000
#define ADC_u8DEFRENTIAL_P1_N0_G10		0b00001001
#define ADC_u8DEFRENTIAL_P0_N0_G200		0b00001010
#define ADC_u8DEFRENTIAL_P1_N0_G200		0b00001011
#define ADC_u8DEFRENTIAL_P2_N2_G10		0b00001100
#define ADC_u8DEFRENTIAL_P3_N2_G10		0b00001101
#define ADC_u8DEFRENTIAL_P2_N2_G200		0b00001110
#define ADC_u8DEFRENTIAL_P3_N2_G200		0b00001111
#define ADC_u8DEFRENTIAL_P0_N1_G1		0b00010000
#define ADC_u8DEFRENTIAL_P1_N1_G1		0b00010001
#define ADC_u8DEFRENTIAL_P2_N1_G1		0b00010010
#define ADC_u8DEFRENTIAL_P3_N1_G1		0b00010011
#define ADC_u8DEFRENTIAL_P4_N1_G1		0b00010100
#define ADC_u8DEFRENTIAL_P5_N1_G1		0b00010101
#define ADC_u8DEFRENTIAL_P6_N1_G1		0b00010110
#define ADC_u8DEFRENTIAL_P7_N1_G1		0b00010111
#define ADC_u8DEFRENTIAL_P0_N2_G1		0b00011000
#define ADC_u8DEFRENTIAL_P1_N2_G1		0b00011001
#define ADC_u8DEFRENTIAL_P2_N2_G1		0b00011010
#define ADC_u8DEFRENTIAL_P3_N2_G1		0b00011011
#define ADC_u8DEFRENTIAL_P4_N2_G1		0b00011100
#define ADC_u8DEFRENTIAL_P5_N2_G1		0b00011101
#define ADC_u8SINGLE_ENDED_122V			0b00011110
#define ADC_u8SINGLE_ENDED_GND			0b00011111

/*
 * Name:		ADC_voidInit
 * Arguments:	void
 * Return:		void
 * Description:	A function to initialize and set up the ADC peripheral.
 */
void ADC_voidInit(void);

/*
 * Name:		ADC_u8StartConversionSynch
 * Arguments:	Copy_u8Channel, Copy_pu16Reading, Copy_u8LeftAdjust
 * Return:		Local_u8ErrorState
 * Description:	A function to convert the analog value read from an ADC's channel (Copy_u8Channel)
 * 				into digital and store the result into the address pointed to by (Copy_pu16Reading).
 * 				The digital reading can be either left or right adjusted based on your value for
 * 				(Copy_u8LeftAdjust) whose options are: ADC_u8RIGHT_ADJUST
 * 				                                       ADC_u8LEFT_ADJUST
 * 				The ADC's channel can be one of the options: ADC_u8SINGLE_ENDED_ADC0
 *                                                           ADC_u8SINGLE_ENDED_ADC1
 * 				                                             ADC_u8SINGLE_ENDED_ADC2
 * 				                                             ADC_u8SINGLE_ENDED_ADC3
 * 				                                             ADC_u8SINGLE_ENDED_ADC4
 * 				                                             ADC_u8SINGLE_ENDED_ADC5
 * 				                                             ADC_u8SINGLE_ENDED_ADC6
 * 				                                             ADC_u8SINGLE_ENDED_ADC7
 * 				                                             ADC_u8DEFRENTIAL_P0_N0_G10
 * 				                                             ADC_u8DEFRENTIAL_P1_N0_G10
 * 				                                             ADC_u8DEFRENTIAL_P0_N0_G200
 * 				                                             ADC_u8DEFRENTIAL_P1_N0_G200
 * 				                                             ADC_u8DEFRENTIAL_P2_N2_G10
 * 				                                             ADC_u8DEFRENTIAL_P3_N2_G10
 * 				                                             ADC_u8DEFRENTIAL_P2_N2_G200
 * 				                                             ADC_u8DEFRENTIAL_P3_N2_G200
 * 				                                             ADC_u8DEFRENTIAL_P0_N1_G1
 * 				                                             ADC_u8DEFRENTIAL_P1_N1_G1
 * 				                                             ADC_u8DEFRENTIAL_P2_N1_G1
 * 				                                             ADC_u8DEFRENTIAL_P3_N1_G1
 * 				                                             ADC_u8DEFRENTIAL_P4_N1_G1
 * 				                                             ADC_u8DEFRENTIAL_P5_N1_G1
 * 				                                             ADC_u8DEFRENTIAL_P6_N1_G1
 * 				                                             ADC_u8DEFRENTIAL_P7_N1_G1
 * 				                                             ADC_u8DEFRENTIAL_P0_N2_G1
 * 				                                             ADC_u8DEFRENTIAL_P1_N2_G1
 * 				                                             ADC_u8DEFRENTIAL_P2_N2_G1
 * 				                                             ADC_u8DEFRENTIAL_P3_N2_G1
 * 				                                             ADC_u8DEFRENTIAL_P4_N2_G1
 * 				                                             ADC_u8DEFRENTIAL_P5_N2_G1
 * 				                                             ADC_u8SINGLE_ENDED_122V
 * 				                                             ADC_u8SINGLE_ENDED_GND
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 */
u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_pu16Reading, u8 Copy_u8LeftAdjust);

/*
 * Name:		ADC_u8StartConversionAsynch
 * Arguments:	Copy_u8Channel, Copy_pu16Reading, (*Copy_pvoidNotificationFunc)(void),
 * 				Copy_u8LeftAdjust
 * Return:		Local_u8ErrorState
 * Description:	A function to start ADC conversion process. This function takes 4 arguments. The
 * 				first argument (Copy_u8Channel) specifies the analog channel to be read, the second
 * 				argument (Copy_pu16Reading) contains the address of user variable to be loaded with
 * 				converted reading, the third argument ((*Copy_pvoidNotificationFunc)(void))
 * 				contains the notification function made by user to be called after ADC conversion
 * 				is finished, while the last argument specifies left adjust configuration whose
 * 				options: ADC_u8RIGHT_ADJUST
 * 				         ADC_u8LEFT_ADJUST
 * 				The returned value (Local_u8ErrorState) specifies if an error occurred during
 * 				the process and its type as well. There are different types of errors, codes of
 * 				errors and types can be found in the file error_code.h.
 * 				Note that it is the user responsibility to enable global interrupt GIE since
 * 				it is not enabled inside this SW component.
 */
u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u16* Copy_pu16Reading, void (*Copy_pvoidNotificationFunc)(void) ,u8 Copy_u8LeftAdjust);

#endif
