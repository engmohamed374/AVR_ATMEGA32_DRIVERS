/********************************************************************/
/********************************************************************/
/*******************	Author: Mohamed Eid		*********************/
/*******************	Layer:	MCAL		 	*********************/
/*******************	SWC:	GIE				*********************/
/*******************	Version:1.00			*********************/
/********************************************************************/
/********************************************************************/

#include "BIT_MATH.h"
#include "DATA_TYPES.h"
#include "GIE_register.h"
#include "GIE_private.h"
#include "GIE_config.h"
#include "GIE_interface.h"

void GIE_voidEnable(void)
{
	/*Set I bit in SREG register*/
	SET_BIT(SREG, SREG_I);
}

void GIE_voidDisable(void)
{
	/*Clear I bit in SREG register*/
	CLR_BIT(SREG, SREG_I);
}
