/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	HAL			 	*********************/
/*******************	SWC:	SSD				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

/*Define a struct to hold component's data*/
typedef struct
{
	u8 u8Port;				/*Define var to hold connected port*/
	u8 u8CommonType;		/*Define var to specify common type*/
	u8 u8MultiplexState;	/*Define var to specify if display is in multiplexing mode*/
	u8 u8EnablePort;		/*Define var to hold connected port for common*/
	u8 u8EnablePin;			/*Define var to hold connected pin for common*/
	u8 u8Value;				/*Define var to hold displayed value*/
} SevenSegment;

u8 SSD_u8SetSevenSegment(SevenSegment* Copy_pSevenSegmentPointer);

u8 SSD_u8SingleDisplay(SevenSegment* Copy_pSevenSegmentPointer);

u8 SSD_u8MultiDisplay(SevenSegment* Copy_pSevenSegmentArray, u8 Copy_u8DisplayNumber);

u8 SSD_u8CircleUp(u8 Copy_u8LowLim, u8 Copy_u8HighLim, u8 Copy_u8Value);

u8 SSD_u8CircleDown(u8 Copy_u8LowLim, u8 Copy_u8HighLim, u8 Copy_u8Value);

#endif
