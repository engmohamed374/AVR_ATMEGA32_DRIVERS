/*Definitions of used types.*/

#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

typedef signed char s8;
typedef unsigned char u8;

typedef signed short int s16;
typedef unsigned short int u16;

typedef signed long int s32;
typedef unsigned long int u32;

typedef float f32;
typedef double f64;

/*Macro  for NULL address*/
#define	NULL	0

/*Macros for error state*/
#define OK							1
#define NOK							2
#define NULL_PTR					3
#define TIMEOUT						4
#define BUSY_FUNC					5

#endif
