/*
	File for bitwise operations.
*/

#include "DATA_TYPES.h"

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/*Setting a bit*/
#define SET_BIT(Var, BitNo) (Var |= (1 << BitNo))

/*Clearing a bit*/
#define CLR_BIT(Var, BitNo) (Var &= ~(1 << BitNo))

/*Toggling a bit*/
#define TGL_BIT(Var, BitNo) (Var ^= (1 << BitNo))

/*Getting a bit*/
#define GET_BIT(Var, BitNo) (1 & (Var >> BitNo))

/*Getting lower byte of 16-bit variable*/
#define LOW(Var)			u8(Var)

/*Getting higher byte of 16-bit variable*/
#define HIGH(Var)			u8(Var >> 8)

#endif
