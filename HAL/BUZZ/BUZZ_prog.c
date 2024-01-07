#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/ErrType.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_interface.h"
#include "BUZZ_cfg.h"
#include "BUZZ_interface.h"
#include "BUZZ_prv.h"


uint8 BUZZ_u8SetOn(const BUZZ_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;

	if(Copy_pstConfig != NULL)
	{
		if(Copy_pstConfig->u8ACT_type == BUZZ_ACT_HIGH)
		{
			DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_HIGH);
		}
		else if(Copy_pstConfig->u8ACT_type == BUZZ_ACT_LOW)
		{
			DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_LOW);
		}
		else
		{
			Local_ErrorState = NOK;
		}
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}
uint8 BUZZ_u8SetOff(const BUZZ_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;

	if(Copy_pstConfig != NULL)
	{
		if(Copy_pstConfig->u8ACT_type == BUZZ_ACT_HIGH)
		{
			DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_LOW);
		}
		else if(Copy_pstConfig->u8ACT_type == BUZZ_ACT_LOW)
		{
			DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_LOW);
		}
		else
		{
			Local_ErrorState = NOK;
		}
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}
uint8 BUZZ_u8Toggle(const BUZZ_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;
	if(Copy_pstConfig != NULL)
	{
		DIO_u8TogglePinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin);
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}
	return Local_ErrorState;
}
