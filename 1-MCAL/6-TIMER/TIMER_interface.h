/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	TIMER			*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/*
 * Description:
 *
 */

/*==========================================================================================================*/
/*================================================= MACROS =================================================*/
/*==========================================================================================================*/

/*Macros for selection of Timer1 Unit*/
#define UNIT_A											1
#define UNIT_B											2

/*Macros for mode of operation*/
#define TIMER0_NORMAL									0b00000000				/*Timer0 modes*/
#define TIMER0_PWM_PHASE_CORRECT						0b01000000      		/*Timer0 modes*/
#define TIMER0_CTC										0b00001000      		/*Timer0 modes*/
#define TIMER0_FAST_PWM									0b01001000      		/*Timer0 modes*/

#define TIMER2_NORMAL									0b00000000      		/*Timer2 modes*/
#define TIMER2_PWM_PHASE_CORRECT						0b01000000      		/*Timer2 modes*/
#define TIMER2_CTC										0b00001000      		/*Timer2 modes*/
#define TIMER2_FAST_PWM									0b01001000     	 		/*Timer2 modes*/

#define TIMER1_NORMAL									0b0000000000000000      /*Timer1 modes*/
#define TIMER1_PWM_PHASE_CORRECT_8_BIT					0b0000000000000001      /*Timer1 modes*/
#define TIMER1_PWM_PHASE_CORRECT_9_BIT					0b0000000000000010      /*Timer1 modes*/
#define TIMER1_PWM_PHASE_CORRECT_10_BIT					0b0000000000000011      /*Timer1 modes*/
#define TIMER1_CTC_OCR1A								0b0000100000000000      /*Timer1 modes*/
#define TIMER1_FAST_PWM_8_BIT							0b0000100000000001      /*Timer1 modes*/
#define TIMER1_FAST_PWM_9_BIT							0b0000100000000010      /*Timer1 modes*/
#define TIMER1_FAST_PWM_10_BIT							0b0000100000000011      /*Timer1 modes*/
#define TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1				0b0001000000000000      /*Timer1 modes*/
#define TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A				0b0001000000000001      /*Timer1 modes*/
#define TIMER1_PWM_PHASE_CORRECT_ICR1					0b0001000000000010      /*Timer1 modes*/
#define TIMER1_PWM_PHASE_CORRECT_OCR1A					0b0001000000000011      /*Timer1 modes*/
#define TIMER1_CTC_ICR1									0b0001100000000000      /*Timer1 modes*/
#define TIMER1_FAST_PWM_ICR1							0b0001100000000010      /*Timer1 modes*/
#define TIMER1_FAST_PWM_OCR1A							0b0001100000000011      /*Timer1 modes*/

/*Macros for compare output mode*/
#define TIMER0_OC0_NORMAL_PORT_OPERATION				0b00000000				/*Timer0 modes*/
#define TIMER0_OC0_NON_PWM_TOGGLE						0b00010000      		/*Timer0 modes*/
#define TIMER0_OC0_NON_PWM_CLEAR						0b00100000      		/*Timer0 modes*/
#define TIMER0_OC0_NON_PWM_SET							0b00110000      		/*Timer0 modes*/
#define TIMER0_OC0_FAST_PWM_NON_INVRTING				0b00100000      		/*Timer0 modes*/
#define TIMER0_OC0_FAST_PWM_INVRTING					0b00110000      		/*Timer0 modes*/
#define TIMER0_OC0_PHASE_CORRECT_PWM_NON_INVERTING		0b00100000      		/*Timer0 modes*/
#define TIMER0_OC0_PHASE_CORRECT_PWM_INVERTING			0b00110000      		/*Timer0 modes*/

#define TIMER2_OC2_NORMAL_PORT_OPERATION				0b00000000      		/*Timer2 modes*/
#define TIMER2_OC2_NON_PWM_TOGGLE						0b00010000      		/*Timer2 modes*/
#define TIMER2_OC2_NON_PWM_CLEAR						0b00100000      		/*Timer2 modes*/
#define TIMER2_OC2_NON_PWM_SET							0b00110000      		/*Timer2 modes*/
#define TIMER2_OC2_FAST_PWM_NON_INVRTING				0b00100000      		/*Timer2 modes*/
#define TIMER2_OC2_FAST_PWM_INVRTING					0b00110000      		/*Timer2 modes*/
#define TIMER2_OC2_PHASE_CORRECT_PWM_NON_INVERTING		0b00100000      		/*Timer2 modes*/
#define TIMER2_OC2_PHASE_CORRECT_PWM_INVERTING			0b00110000      		/*Timer2 modes*/

#define TIMER1_OC1A_NORMAL_PORT_OPERATION				0b00000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_NON_PWM_TOGGLE						0b01000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_NON_PWM_CLEAR						0b10000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_NON_PWM_SET							0b11000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_FAST_PWM_TOGGLE_MODE_15				0b01000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_FAST_PWM_NON_INVRTING				0b10000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_FAST_PWM_INVRTING					0b11000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_PHASE_CORRECT_PWM_TOGGLE_MODES_9_14	0b01000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_PHASE_CORRECT_PWM_NON_INVERTING		0b10000000      		/*Timer1 unit A modes*/
#define TIMER1_OC1A_PHASE_CORRECT_PWM_INVERTING			0b11000000      		/*Timer1 unit A modes*/

#define TIMER1_OC1B_NORMAL_PORT_OPERATION				0b00000000      		/*Timer0 unit B modes*/
#define TIMER1_OC1B_NON_PWM_TOGGLE						0b00010000      		/*Timer0 unit B modes*/
#define TIMER1_OC1B_NON_PWM_CLEAR						0b00100000      		/*Timer0 unit B modes*/
#define TIMER1_OC1B_NON_PWM_SET							0b00110000      		/*Timer0 unit B modes*/
#define TIMER1_OC1B_FAST_PWM_NON_INVRTING				0b00100000      		/*Timer0 unit B modes*/
#define TIMER1_OC1B_FAST_PWM_INVRTING					0b00110000      		/*Timer0 unit B modes*/
#define TIMER1_OC1B_PHASE_CORRECT_PWM_NON_INVERTING		0b00100000      		/*Timer0 unit B modes*/
#define TIMER1_OC1B_PHASE_CORRECT_PWM_INVERTING			0b00110000      		/*Timer0 unit B modes*/

/*Macros for clock select*/
#define TIMER0_STOPPED									0b00000000      		/*Timer0 selections*/
#define TIMER0_DIVISION_BY_1                            0b00000001      		/*Timer0 selections*/
#define TIMER0_DIVISION_BY_8                            0b00000010      		/*Timer0 selections*/
#define TIMER0_DIVISION_BY_64                           0b00000011      		/*Timer0 selections*/
#define TIMER0_DIVISION_BY_256                          0b00000100      		/*Timer0 selections*/
#define TIMER0_DIVISION_BY_1024                         0b00000101      		/*Timer0 selections*/
#define TIMER0_EXTERNAL_T0_PIN_FALLING_EDGE             0b00000110      		/*Timer0 selections*/
#define TIMER0_EXTERNAL_T0_PIN_RISING_EDGE              0b00000111      		/*Timer0 selections*/

#define TIMER2_STOPPED                                  0b00000000      		/*Timer2 selections*/
#define TIMER2_DIVISION_BY_1                            0b00000001      		/*Timer2 selections*/
#define TIMER2_DIVISION_BY_8                            0b00000010      		/*Timer2 selections*/
#define TIMER2_DIVISION_BY_32                           0b00000011      		/*Timer2 selections*/
#define TIMER2_DIVISION_BY_64                           0b00000100      		/*Timer2 selections*/
#define TIMER2_DIVISION_BY_128                          0b00000101      		/*Timer2 selections*/
#define TIMER2_DIVISION_BY_256                          0b00000110      		/*Timer2 selections*/
#define TIMER2_DIVISION_BY_1024                         0b00000111      		/*Timer2 selections*/

#define TIMER1_STOPPED									0b00000000      		/*Timer1 selections*/
#define TIMER1_DIVISION_BY_1                            0b00000001      		/*Timer1 selections*/
#define TIMER1_DIVISION_BY_8                            0b00000010      		/*Timer1 selections*/
#define TIMER1_DIVISION_BY_64                           0b00000011      		/*Timer1 selections*/
#define TIMER1_DIVISION_BY_256                          0b00000100      		/*Timer1 selections*/
#define TIMER1_DIVISION_BY_1024                         0b00000101      		/*Timer1 selections*/
#define TIMER1_EXTERNAL_T0_PIN_FALLING_EDGE             0b00000110      		/*Timer1 selections*/
#define TIMER1_EXTERNAL_T0_PIN_RISING_EDGE              0b00000111      		/*Timer1 selections*/

/*==========================================================================================================*/
/*=================================================== STRUCTS ==============================================*/
/*==========================================================================================================*/

/*Define struct to hold timer0 settings*/
typedef struct
{
	void (*pvoid_NotificationFunc)(void);	/*Define pointer to hold address of callback function*/
	u8 u8_RollOverFlag;						/*Definr var to hold roll over flag*/
	u8 u8_InterruptFlag;					/*Definr var to hold interrupt flag*/
	u8 u8_ClockSelect;						/*Define var to choose prescaler*/
	u8 u8_CompareOutputMode;				/*Define var to choose compare output mode*/
	u8 u8_OperationMode;					/*Define var to choose mode of operation*/
	u8 u8_OverflowPreloadValue;				/*Define var to hold overflow preload value*/
	u8 u8_CompareMatchValue;				/*Define var to hold compare match value*/
	u32 u32_Counter;						/*Define var to hold NO. of overflows or compare matches*/
} timer0_t;

/*Define struct to hold timer2 settings*/
typedef struct
{
	void (*pvoid_NotificationFunc)(void);	/*Define pointer to hold address of callback function*/
	u8 u8_RollOverFlag;						/*Definr var to hold roll over flag*/
	u8 u8_InterruptFlag;					/*Definr var to hold interrupt flag*/
	u8 u8_ClockSelect;						/*Define var to choose prescaler*/
	u8 u8_CompareOutputMode;				/*Define var to choose compare output mode*/
	u8 u8_OperationMode;					/*Define var to choose mode of operation*/
	u8 u8_OverflowPreloadValue;				/*Define var to hold overflow preload value*/
	u8 u8_CompareMatchValue;				/*Define var to hold compare match value*/
	u32 u32_Counter;						/*Define var to hold NO. of overflows or compare matches*/
} timer2_t;

/*Define struct to hold timer1 settings*/
typedef struct
{
	void (*pvoid_NotificationFunc)(void);	/*Define pointer to hold address of callback function*/
	u8 u8_RollOverFlag;						/*Definr var to hold roll over flag*/
	u8 u8_InterruptFlag;					/*Definr var to hold interrupt flag*/
	u8 u8_ClockSelect;						/*Define var to choose prescaler*/
	u8 u8_CompareOutputModeA;				/*Define var to choose compare output mode of Unit A*/
	u8 u8_CompareOutputModeB;				/*Define var to choose compare output mode of Unit B*/
	u16 u16_OperationMode;					/*Define var to choose mode of operation*/
	u16 u16_OverflowPreloadValue;			/*Define var to hold overflow preload value*/
	u16 u16_ICR1CompareMatchValue;			/*Define var to hold compare match value for ICR1*/
	u16 u16_OCR1ACompareMatchValue;			/*Define var to hold compare match value for OCR1A*/
	u16 u16_OCR1BCompareMatchValue;			/*Define var to hold compare match value for OCR1B*/
	u32 u32_Counter;						/*Define var to hold NO. of overflows or compare matches*/
} timer1_t;

/*Define struct to hold timer0 PWM settings*/
typedef struct
{
	u8 u8_DutyCycle;						/*Define var to hold desired duty cycle*/
	timer0_t timer0_t_Settings;				/*Define struct of type timer0_t to hold settings*/
} PWM0_t;

/*Define struct to hold timer2 PWM settings*/
typedef struct
{
	u8 u8_DutyCycle;						/*Define var to hold desired duty cycle*/
	timer2_t timer2_t_Settings;				/*Define struct of type timer0_t to hold settings*/
} PWM2_t;

/*Define struct to hold timer1 PWM settings*/
typedef struct
{
	u8 u8_UnitADutyCycle;						/*Define var to hold desired duty cycle of Unit A*/
	u8 u8_UnitBDutyCycle;						/*Define var to hold desired duty cycle of Unit B*/
	timer1_t timer1_t_Settings;					/*Define struct of type timer0_t to hold settings*/
} PWM1_t;

/*Define struct to hold timer1 ICU settings*/
typedef struct
{
	u16 u16_TonValue;							/*Define var to hold time of high signal*/
	u16 u16_ToffValue;							/*Define var to hold time of low signal*/
	u8 u8_ClockSelect;							/*Define var to choose prescaler*/
} ICU_t;

/*==========================================================================================================*/
/*================================================ FUNCTIONS ===============================================*/
/*==========================================================================================================*/

u8 TIMER_u8SetTimer0(timer0_t* Copy_ptimer0_tSettings);

u8 TIMER_u8SetTimer2(timer2_t* Copy_ptimer2tSettings);

u8 TIMER_u8SetTimer1(timer1_t* Copy_ptimer1_tSettings);

u8 TIMER_u8Timer0SchedualeSynch(timer0_t* Copy_ptimer0_tSettings);

u8 TIMER_u8Timer2SchedualeSynch(timer2_t* Copy_ptimer2_tSettings);

u8 TIMER_u8Timer1SchedualeSynch(timer1_t* Copy_ptimer1_tSettings);

u8 TIMER_u8Timer0SchedualeASynch(timer0_t* Copy_ptimer0_tSettings);

u8 TIMER_u8Timer2SchedualeASynch(timer2_t* Copy_ptimer2_tSettings);

u8 TIMER_u8Timer1SchedualeASynch(timer1_t* Copy_ptimer1_tSettings);

u8 TIMER_u8StartTimer0PWMAsynch(PWM0_t* Copy_pPWM0_tSettings);

u8 TIMER_u8StartTimer2PWMAsynch(PWM2_t* Copy_pPWM2_tSettings);

u8 TIMER_u8StartTimer1PWMAsynch(PWM1_t* Copy_pPWM1_tSettings);

void TIMER_voidSetTimer0DutyCycle(PWM0_t* Copy_pPWM0_tSettings);

void TIMER_voidSetTimer2DutyCycle(PWM2_t* Copy_pPWM2_tSettings);

void TIMER_voidSetTimer1UnitADutyCycle(PWM1_t* Copy_pPWM1_tSettings);

void TIMER_voidSetTimer1UnitBDutyCycle(PWM1_t* Copy_pPWM1_tSettings);

void TIMER_voidDisableTimer1PWMUnitA(void);

void TIMER_voidDisableTimer1PWMUnitB(void);

u8 TIMER_u8StartICUAsynch(ICU_t* Copy_pICU_tSettings);

void TIMER_voidStopTimer0(void);

void TIMER_voidStopTimer2(void);

void TIMER_voidStopTimer1(void);

s32 map(s32 Copy_s32XMin, s32 Copy_s32XMax, s32 Copy_s32YMin, s32 Copy_s32YMax, s32 Copy_s32XValue);

/*==========================================================================================================*/
/*==========================================================================================================*/
#endif
